/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:08:01 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/03/04 17:54:09 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	main(int argc, char **argv)
{
	t_game	game;

	parsing(argc, argv[1], &game);
	if (game.width > 110 || game.height > 55)
		ft_error(ERROR_SIZE, &game);
	game.mlx = mlx_init(game.width * TILE, game.height * TILE, \
	"Pandakiwi", true);
	if (!(game.mlx))
		clean_close(ERROR_MLX, &game, 1);
	load_xpm(&game);
	xpm_to_image(&game, game.tile);
	render_background(&game);
	render_player(&game, -1, 1);
	mlx_key_hook(game.mlx, &keyhook, &game);
	mlx_loop(game.mlx);
	ft_printf(CROSS_EXIT);
	return (clean_close(NULL, &game, 0));
}
