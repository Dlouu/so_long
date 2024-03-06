/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 16:14:29 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/03/04 18:19:11 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_images(t_game *game)
{
	int				category;
	int				img_number;

	category = 0;
	while (category < CAT_COUNT)
	{
		img_number = 0;
		while (game->tile[category][img_number].end != 1)
		{
			mlx_delete_image(game->mlx, game->tile[category][img_number].img);
			mlx_delete_xpm42(game->tile[category][img_number].xpm);
			img_number++;
		}
		category++;
	}
}

int	clean_close(char *error, t_game *game, int code)
{
	int	i;

	i = 0;
	if (game->map)
	{
		while (*(game->map + i))
		{
			free(*(game->map + i));
			i++;
		}
		free(game->map);
	}
	if (game->map_name)
		free(game->map_name);
	close(game->fd);
	if (game->mlx)
	{
		free_images(game);
		mlx_close_window(game->mlx);
		mlx_terminate(game->mlx);
	}
	if (code == 0)
		exit(EXIT_SUCCESS);
	ft_printf("Error\n🔺 %s\n", error);
	exit(EXIT_FAILURE);
}

void	ft_error(char *error, t_game *game)
{
	int	i;

	i = 0;
	if (error != NULL)
		ft_printf("Error\n🔺 %s\n", error);
	if (game)
	{
		if (game->map_name)
			free(game->map_name);
		if (game->map_lst)
			ft_lstclear(&game->map_lst, free);
		if (game->map)
		{
			while (*(game->map + i))
			{
				free(*(game->map + i));
				i++;
			}
			free(game->map);
		}
	}
	if (game != NULL && game->fd >= 0 && game->gnl_free)
		get_next_line(game->fd, 1);
	exit(EXIT_FAILURE);
}

void	put_clean_image(t_game *game, t_tile tile, int x, int y)
{
	if ((mlx_image_to_window(game->mlx, tile.img, x * TILE, y * TILE) < 0))
		clean_close(ERROR_MLX, game, 1);
}
