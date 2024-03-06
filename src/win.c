/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:42:43 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/03/04 18:19:17 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	change_high_score(t_game *game, char **line, char *old_score)
{
	char	*new_score;
	char	*line_s1;
	char	*temp;
	char	*line_s2;

	new_score = ft_itoa(game->moves);
	if (!new_score)
		clean_close(ERROR_ITOA, game, 1);
	line_s1 = ft_substr(*line, 0, ft_strlen(*line) - ft_strlen(old_score));
	line_s2 = ft_strdup(old_score + ft_strlen(game->map_name) \
	+ ft_nlen_base(game->high_score, 10) + 1);
	temp = *line;
	*line = ft_free_strjoin(line_s1, game->map_name);
	free(temp);
	*line = ft_free_strjoin(*line, " ");
	*line = ft_free_strjoin(*line, new_score);
	free(new_score);
	*line = ft_free_strjoin(*line, line_s2);
	free(line_s2);
}

static void	write_first_high_score(t_game *game, char **line)
{
	char	*first_score;

	*line = ft_free_strjoin(*line, game->map_name);
	*line = ft_free_strjoin(*line, " ");
	first_score = ft_itoa(game->moves);
	if (!first_score)
	{
		free(*line);
		clean_close(ERROR_ITOA, game, 1);
	}
	*line = ft_free_strjoin(*line, first_score);
	free(first_score);
	*line = ft_free_strjoin(*line, " | ");
}

static int	update_score(t_game *game)
{
	char	*line;
	char	*score;

	game->fd = open("./maps/high_score.txt", O_RDWR);
	if (game->fd < 0)
		return (1);
	line = get_next_line(game->fd, 0);
	if (!line)
		return (free(line), clean_close(ERROR_GNL, game, 1));
	score = ft_strnstr(line, game->map_name, ft_strlen(line));
	if (!score)
		write_first_high_score(game, &line);
	else
		change_high_score(game, &line, score);
	close(game->fd);
	game->fd = open("./maps/high_score.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (write(game->fd, line, ft_strlen(line)) < 0)
		return (free(line), clean_close(ERROR_WRITE, game, 1));
	free(line);
	close(game->fd);
	return (0);
}

void	ft_win(t_game *game)
{
	int	diff;

	diff = game->moves - game->high_score;
	if (game->high_score != -1 && game->moves > game->high_score)
		ft_printf("\r    🥈 SUCCESS ! but you can do better...\
		\n       you collected cherry blossoms in %d moves\
		\n       it's %d moves from highest score. \
		\n       Try again and good Luck ! 🐼\n\
		\n     ♡ Thank you for playing\n\n", game->moves, diff);
	if ((game->high_score == -1 || game->moves < game->high_score) && \
	!game->ignore_high_score)
		update_score(game);
	if (game->high_score == -1 || game->moves <= game->high_score)
		ft_printf("\
		\r⬛🟩🟩🟩⬛⬜⬜⬜⬜⬜⬜⬜⬛🟩🟩🟩⬛  🎉 HIGH SCORE ! \
		\n🟩🟩🟩🟩⬜⬜⬜⬜⬜⬜⬜⬜⬜🟩🟩🟩🟩 \
		\n🟩🟩🟨⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜🟨🟩🟩   you collected \
		\n🟩🟨⬜⬜⬛⬛⬜⬜⬜⬜⬜⬛⬛⬜⬜🟨🟩  cherry blossoms \
		\n🟩⬜⬜⬛⬛⬛⬜⬜⬜⬜⬜⬛⬛⬛⬜⬜🟩   in %d moves ! \
		\n⬛⬜⬜⬛⬜⬛⬜⬜⬛⬜⬜⬛⬜⬛⬜⬜⬛ \
		\n⬛⬜⬜⬛⬛⬜⬜⬛⬜⬛⬜⬜⬛⬛⬜⬜⬛    Thank you ♡ \
		\n⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛   for playing \
		\n\n", game->moves);
	clean_close(NULL, game, 0);
}
