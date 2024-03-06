/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:06:00 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/02/29 16:07:03 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	flood_fill(t_game *game, int x, int y, int *collect)
{
	if (x < 0 || y < 0 || x > game->width - 1 || y > game->height - 1)
		return (0);
	if (game->temp_map[y][x] == '1' || game->temp_map[y][x] == FILLED)
		return (0);
	if (game->temp_map[y][x] == 'C')
		(*collect)--;
	if (game->temp_map[y][x] == 'E')
		game->touch_exit = 1;
	if (game->touch_exit == 1 && *collect == 0)
		return (1);
	game->temp_map[y][x] = FILLED;
	if (flood_fill(game, x + 1, y, collect) || \
		flood_fill(game, x - 1, y, collect) || \
		flood_fill(game, x, y + 1, collect) || \
		flood_fill(game, x, y - 1, collect))
		return (1);
	return (0);
}

int	check_path(t_game *game)
{
	int	temp_collect;
	int	temp_x;
	int	temp_y;

	temp_collect = game->collect;
	temp_x = game->p_x;
	temp_y = game->p_y;
	game->map = ft_lstsplit(game->map_lst);
	if (!game->map)
		return (game->gnl_free = 1, ft_error(ERROR_SPLIT, game), 0);
	game->temp_map = ft_strdup_array(game->map, game->height);
	if (!game->temp_map)
		return (game->map_lst = NULL, ft_error(ERROR_COPY, game), 0);
	if (!(flood_fill(game, temp_x, temp_y, &temp_collect)))
	{
		game->map_lst = NULL;
		ft_free_tab(game->temp_map, game->height);
		ft_error(ERROR_PATH, game);
		return (0);
	}
	game->map_lst = NULL;
	ft_free_tab(game->temp_map, game->height);
	return (1);
}
