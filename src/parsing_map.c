/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:06:03 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/03/04 18:08:05 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	check_charset(t_game *game, char *charset)
{
	int		i;
	t_list	*map_lst;
	char	*line;

	map_lst = game->map_lst;
	while (map_lst != NULL)
	{
		line = map_lst->content;
		i = 0;
		while (line[i])
		{
			if (!ft_strchr(charset, line[i]))
				return (0);
			i++;
		}
		map_lst = map_lst->next;
	}
	return (1);
}

static void	check_walls(t_game *game)
{
	t_list	*map_lst;
	char	*line;
	int		i;

	i = -1;
	map_lst = game->map_lst;
	while (map_lst != NULL)
	{
		line = map_lst->content;
		if (i == -1 || map_lst == ft_lstlast(game->map_lst))
		{
			i = 0;
			while (line[i])
			{
				if (line[i] != '1')
					ft_error(ERROR_WALL, game);
				i++;
			}
		}
		if (line[0] != '1' || line[game->width - 1] != '1')
			ft_error(ERROR_WALL, game);
		map_lst = map_lst->next;
	}
}

static void	check_things(t_game *game)
{
	check_walls(game);
	if (game->collect < 1)
		ft_error(ERROR_COINS, game);
	if (game->player_count != 1)
		ft_error(ERROR_START, game);
	if (game->exit_count != 1)
		ft_error(ERROR_EXIT, game);
	if (!check_charset(game, "01CEP"))
		ft_error(ERROR_CHAR, game);
	if (!check_path(game))
		ft_error(ERROR_PATH, game);
	ft_printf("\
	\n       s o _ l o n g  .-.       .-.    4           2 \
	\n.---.  .--.  ,-.,-. .-' : .--.  : `.-..-..-..-..-..-.\
	\n: .; `' .; ; : ,. :' .; :' .; ; : . `.: :: `; `; :: :\
	\n: ._.'`.__,_;:_;:_;`.__.'`.__,_;:_;:_;:_;`.__.__.':_;\
	\n:_;                       & thanks for all the fish !\
	\n    r u l e s :\
	\n    🌸 Collect all cherry blossoms \
	\n    ⛩️  and go to the torii to win !\n");
	if (game->high_score != -1)
		ft_printf("    🏆 Fewer moves for this map : %d\n\n", game->high_score);
	else
		ft_printf("    🏆 No high score yet, give your best !\n\n");
}

static void	count_things(char *line, int *set_pos_y, t_game *game)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'C')
			game->collect += 1;
		else if (line[i] == 'P')
		{
			game->player_count += 1;
			game->p_x = i;
			game->p_y = *set_pos_y;
		}
		else if (line[i] == 'E')
			game->exit_count += 1;
		i++;
	}
}

void	check_map(t_game *game)
{
	int		set_pos_y;
	char	*map_node;
	t_list	*map_lst;

	set_pos_y = 0;
	map_lst = game->map_lst;
	game->width = ft_strlen(map_lst->content);
	while (map_lst != NULL)
	{
		if (ft_strlen(map_lst->content) != (size_t)game->width)
			ft_error(ERROR_SHAPE, game);
		map_node = map_lst->content;
		count_things(map_node, &set_pos_y, game);
		map_lst = map_lst->next;
		set_pos_y++;
	}
	check_things(game);
}
