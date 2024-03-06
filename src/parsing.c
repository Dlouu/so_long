/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:06:06 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/03/04 11:16:11 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

/* This function checks in file "/maps/high_score.txt" if there is already a 
high score based on map name (.ber).
'start' is a pointer to the end of the file name in the entire file.
'high_score' is a conversion from a string of the file to an integer.
(the position is the len of map_name + the diff between the len of the entire
file and the start)

- If there is no high score recorded, it returns -1 and it will be reported in
  game->high_score, later it will trigger the function called 
  "write_first_high_score" if the player win the game.

- If there is already a high score, it will be shown on the console and will be
  compared with the game->moves when the player win the game to update high 
  score if needed.*/
static int	get_high_score(t_game *game, char *file_name)
{
	int		fd;
	char	*line;
	int		high_score;
	char	*start;

	high_score = 0;
	fd = open("./maps/high_score.txt", O_RDWR);
	if (fd < 0)
		return (game->ignore_high_score = 1, -1);
	line = get_next_line(fd, 0);
	if (!line)
	{
		game->gnl_free = 1;
		return (ft_error(ERROR_GNL, game), -1);
	}
	start = ft_strnstr(line, file_name, ft_strlen(line));
	if (!start)
		return (free(line), close(fd), -1);
	else
	{
		high_score = ft_atoi(line + ft_strlen(file_name) + \
		(ft_strlen(line) - ft_strlen(start)));
		return (free(line), close(fd), high_score);
	}
}

static void	delete_newline(char **node, t_game *game)
{
	char	*node_no_nl;

	node_no_nl = ft_substr(*node, 0, ft_strlen(*node) - 1);
	if (!node_no_nl)
	{
		game->gnl_free = 1;
		free(*node);
		ft_error(ERROR_MALLOC, game);
	}
	free(*node);
	*node = node_no_nl;
}

void	get_map(t_game *game)
{
	t_list	*node;
	char	*map_node;
	int		first_read;

	first_read = 1;
	while (1)
	{
		map_node = get_next_line(game->fd, 0);
		if (!map_node && first_read == 1)
			ft_error(ERROR_EMPTY, game);
		first_read = 0;
		if (map_node && map_node[ft_strlen(map_node) - 1] == '\n')
			delete_newline(&map_node, game);
		if (map_node == NULL)
			break ;
		node = ft_lstnew(map_node);
		if (!node)
		{
			game->gnl_free = 1;
			free(map_node);
			ft_error(ERROR_MALLOC, game);
		}
		game->height += 1;
		ft_lstadd_back(&game->map_lst, node);
	}
}

void	init_struct(t_game *game)
{
	game->map_lst = NULL;
	game->map = NULL;
	game->width = 0;
	game->height = 0;
	game->collect = 0;
	game->player_count = 0;
	game->exit_count = 0;
	game->gnl_free = 0;
	game->touch_exit = 0;
	game->current_pos = 3;
	game->next_pos = 3;
	game->moves = 0;
	game->ignore_high_score = 0;
}

void	parsing(int argc, char *file, t_game *game)
{
	if (argc < 2)
		ft_error(ERROR_ARG, NULL);
	game->fd = -1;
	if (!ft_strnstr(file, ".ber", ft_strlen(file)))
		ft_error(ERROR_EXT, NULL);
	game->fd = open(file, O_RDONLY);
	if (game->fd < 0)
		ft_error(ERROR_OPEN, NULL);
	init_struct(game);
	game->map_name = ft_strdup(file);
	if (!game->map_name)
		ft_error(ERROR_MALLOC, game);
	game->high_score = get_high_score(game, file);
	get_map(game);
	check_map(game);
}
