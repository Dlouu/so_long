/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:13:28 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/03/04 18:20:54 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	load_img(t_game *game, t_tile *tile)
{
	tile->img = mlx_texture_to_image(game->mlx, &tile->xpm->texture);
	if (!tile->img)
		clean_close(ERROR_MLX, game, 1);
}

void	xpm_to_image(t_game *game, t_tile **tile)
{
	int	category;
	int	img_number;

	category = 0;
	while (category < CAT_COUNT)
	{
		img_number = 0;
		while (tile[category][img_number].end != 1)
		{
			load_img(game, &tile[category][img_number]);
			img_number++;
		}
		category++;
	}
}

static void	xpm_init(t_game *game, t_tile *tile, const char *path)
{
	tile->xpm = mlx_load_xpm42(path);
	if (!tile->xpm)
		clean_close(ERROR_MLX, game, 1);
	tile->end = 0;
}

static void	load_sprites(t_game *game)
{
	xpm_init(game, &game->tile[PLAYER][0], "./assets/player0.xpm42");
	xpm_init(game, &game->tile[PLAYER][1], "./assets/player1.xpm42");
	xpm_init(game, &game->tile[PLAYER][2], "./assets/player2.xpm42");
	xpm_init(game, &game->tile[PLAYER][3], "./assets/player3.xpm42");
	xpm_init(game, &game->tile[COLL][0], "./assets/coll0.xpm42");
	xpm_init(game, &game->tile[EXIT][0], "./assets/exit0.xpm42");
	xpm_init(game, &game->tile[BORDER][0], "./assets/border0.xpm42");
	xpm_init(game, &game->tile[BORDER][1], "./assets/border1.xpm42");
	xpm_init(game, &game->tile[BORDER][2], "./assets/border2.xpm42");
	xpm_init(game, &game->tile[BORDER][3], "./assets/border3.xpm42");
	xpm_init(game, &game->tile[BORDER][4], "./assets/border4.xpm42");
	xpm_init(game, &game->tile[BORDER][5], "./assets/border5.xpm42");
	xpm_init(game, &game->tile[BORDER][6], "./assets/border6.xpm42");
	xpm_init(game, &game->tile[BORDER][7], "./assets/border7.xpm42");
	xpm_init(game, &game->tile[BORDER][8], "./assets/border8.xpm42");
	xpm_init(game, &game->tile[WALL][0], "./assets/wall0.xpm42");
	xpm_init(game, &game->tile[WALL][1], "./assets/wall1.xpm42");
	xpm_init(game, &game->tile[WALL][2], "./assets/wall2.xpm42");
	xpm_init(game, &game->tile[WALL][3], "./assets/wall3.xpm42");
	xpm_init(game, &game->tile[FLOOR][0], "./assets/floor0.xpm42");
	xpm_init(game, &game->tile[FLOOR][1], "./assets/floor1.xpm42");
	xpm_init(game, &game->tile[FLOOR][2], "./assets/floor2.xpm42");
	xpm_init(game, &game->tile[FLOOR][3], "./assets/floor3.xpm42");
	xpm_init(game, &game->tile[FLOOR][4], "./assets/floor4.xpm42");
	xpm_init(game, &game->tile[FLOOR][5], "./assets/floor4.xpm42");
}

void	load_xpm(t_game *game)
{
	game->tile = (t_tile **)malloc(sizeof(t_tile *) * (CAT_COUNT + 1));
	if (!game->tile)
		clean_close(ERROR_MALLOC, game, 1);
	game->tile[PLAYER] = (t_tile *)malloc(sizeof(t_tile) * (CAT_P + 1));
	game->tile[BORDER] = (t_tile *)malloc(sizeof(t_tile) * (CAT_B + 1));
	game->tile[FLOOR] = (t_tile *)malloc(sizeof(t_tile) * (CAT_F + 1));
	game->tile[WALL] = (t_tile *)malloc(sizeof(t_tile) * (CAT_W + 1));
	game->tile[COLL] = (t_tile *)malloc(sizeof(t_tile) * (CAT_C + 1));
	game->tile[EXIT] = (t_tile *)malloc(sizeof(t_tile) * (CAT_E + 1));
	if (!game->tile[PLAYER] || !game->tile[BORDER] || !game->tile[FLOOR] \
		|| !game->tile[WALL] || !game->tile[COLL] || !game->tile[EXIT])
		clean_close(ERROR_MALLOC, game, 1);
	game->tile[EXIT][CAT_E].end = 1;
	game->tile[COLL][CAT_C].end = 1;
	game->tile[WALL][CAT_W].end = 1;
	game->tile[FLOOR][CAT_F].end = 1;
	game->tile[PLAYER][CAT_P].end = 1;
	game->tile[BORDER][CAT_B].end = 1;
	load_sprites(game);
}
