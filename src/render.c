/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:18:33 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/02/29 15:03:41 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	random_in_range(int range)
{
	int					random_number;
	unsigned long long	current_time;

	current_time = mlx_get_time() * 1000000000;
	random_number = (int)(current_time % (unsigned long long)(range));
	return (random_number);
}

static void	put_floor(t_game *game, t_tile **tile, int y, int x)
{
	int	floor;

	floor = random_in_range(CAT_F);
	put_clean_image(game, tile[FLOOR][floor], x, y);
}

static void	put_inner_wall(t_game *game, t_tile **tile, int y, int x)
{
	int	wall;

	wall = random_in_range(CAT_W);
	put_clean_image(game, tile[WALL][wall], x, y);
}

static void	put_border(t_game *game, t_tile *tile, int y, int x)
{
	int	border;

	if (y == 0 && x == 0)
		border = 0;
	else if (y == 0 && x == game->width - 1)
		border = 2;
	else if (y == 0)
		border = 1;
	else if (y == game->height - 1 && x == 0)
		border = 5;
	else if (y == game->height - 1 && x == game->width - 1)
		border = 7;
	else if (y == game->height - 1 && x == 1)
		border = 8;
	else if (y == game->height - 1)
		border = 6;
	else if (x == 0)
		border = 3;
	else if (x == game->width - 1)
		border = 4;
	else
		return (put_inner_wall(game, game->tile, y, x));
	put_clean_image(game, tile[border], x, y);
}

void	render_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == 'C')
				put_clean_image(game, game->tile[COLL][0], x, y);
			else if (game->map[y][x] == '1')
				put_border(game, game->tile[BORDER], y, x);
			else if (game->map[y][x] == 'E')
				put_clean_image(game, game->tile[EXIT][0], x, y);
			else
				put_floor(game, game->tile, y, x);
			x++;
		}
		y++;
	}
}
