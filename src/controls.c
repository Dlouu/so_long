/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 17:29:36 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/03/04 18:20:31 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	render_player(t_game *game, int current, int next)
{
	if (current != -1)
	{
		mlx_delete_image(game->mlx, game->tile[PLAYER][current].img);
		load_img(game, &game->tile[PLAYER][next]);
	}
	put_clean_image(game, game->tile[PLAYER][next], game->p_x, game->p_y);
	game->current_pos = next;
}

static void	nomnom_collectible(t_game *game)
{
	game->map[game->p_y][game->p_x] = 0;
	if (game->collect == 0)
		mlx_delete_image(game->mlx, game->tile[COLL][0].img);
	load_img(game, &game->tile[FLOOR][0]);
	put_clean_image(game, game->tile[FLOOR][0], game->p_x, game->p_y);
	game->collect -= 1;
}

void	move_player(t_game *game, int y, int x)
{
	game->p_y += y;
	game->p_x += x;
	if (y == UP)
		game->next_pos = 0;
	if (y == DOWN)
		game->next_pos = 1;
	if (x == LEFT)
		game->next_pos = 2;
	if (x == RIGHT)
		game->next_pos = 3;
	if (game->map[game->p_y][game->p_x] == 'C')
		nomnom_collectible(game);
	game->moves += 1;
	render_player(game, game->current_pos, game->next_pos);
	if (game->map[game->p_y][game->p_x] == 'E' && game->collect == 0)
		ft_win(game);
	ft_printf("\rmoves: %d | collectibles left : %d   ", \
	game->moves, game->collect);
}

void	keyhook(mlx_key_data_t k, void *tgame)
{
	t_game	*game;

	game = (t_game *)tgame;
	if ((k.key == KEY_UP || k.key == KEY_W) && (k.action == MLX_PRESS || \
	k.action == MLX_REPEAT) && game->map[game->p_y - 1][game->p_x] != '1')
		move_player(game, UP, 0);
	if ((k.key == KEY_DOWN || k.key == KEY_S) && (k.action == MLX_PRESS || \
	k.action == MLX_REPEAT) && game->map[game->p_y + 1][game->p_x] != '1')
		move_player(game, DOWN, 0);
	if ((k.key == KEY_LEFT || k.key == KEY_A) && (k.action == MLX_PRESS || \
	k.action == MLX_REPEAT) && game->map[game->p_y][game->p_x - 1] != '1')
		move_player(game, 0, LEFT);
	if ((k.key == KEY_RIGHT || k.key == KEY_D) && (k.action == MLX_PRESS || \
	k.action == MLX_REPEAT) && game->map[game->p_y][game->p_x + 1] != '1')
		move_player(game, 0, RIGHT);
	if (k.key == KEY_ESC && k.action == MLX_RELEASE)
	{
		ft_printf(ESCAPE_EXIT);
		clean_close(NULL, game, 0);
	}
}
