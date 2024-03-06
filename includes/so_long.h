/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 18:03:54 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/03/05 15:19:03 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <unistd.h>
# include <fcntl.h>

//parsing_utils
# define FILLED '2'
# define TILE 32

//images category count
# define CAT_COUNT 6

//arg_numb of each image category
# define PLAYER 0
# define BORDER 1
# define FLOOR 2
# define WALL 3
# define COLL 4
# define EXIT 5

//image count in each category
# define CAT_P 4
# define CAT_B 9
# define CAT_F 6
# define CAT_W 4
# define CAT_C 1
# define CAT_E 1

//keys
# define KEY_ESC 256
# define KEY_UP 265
# define KEY_DOWN 264
# define KEY_LEFT 263
# define KEY_RIGHT 262
# define KEY_W 87
# define KEY_S 83
# define KEY_A 65
# define KEY_D 68

//move utils
# define UP -1
# define DOWN 1
# define RIGHT 1
# define LEFT -1

//errors
# define CROSS_EXIT "\rExit button clicked - Game aborted - Good bye !\n\n"
# define ESCAPE_EXIT "\rYou pressed escape - Game aborted - Good bye !\n\n"
# define ERROR_SIZE "Window is too big, unplayable. (max : 55 row / 110 col)"
# define ERROR_ARG "Please, select a map.\n   example : ./so_long maps/map.ber"
# define ERROR_EXT "File extension must be .ber !"
# define ERROR_OPEN "Open failed."
# define ERROR_MALLOC "Maloc failed."
# define ERROR_EMPTY "Map is empty."
# define ERROR_GNL "get_next_line failed."
# define ERROR_ITOA "ft_itoa failed."
# define ERROR_WRITE "High score write failed."
# define ERROR_WALL "Map not surrounded by walls."
# define ERROR_COINS "You need at least one collectible."
# define ERROR_START "You need to set one player start position."
# define ERROR_EXIT "Map should have one exit."
# define ERROR_CHAR "There is an invalid character in the map."
# define ERROR_PATH "Impossible map !\nNo valid path found."
# define ERROR_SHAPE "Map must be in a rectangle shape."
# define ERROR_SPLIT "ft_lstsplit failed."
# define ERROR_COPY "Map copy failed."
# define ERROR_MLX "problem with MLX."

typedef struct s_tile
{
	xpm_t			*xpm;
	mlx_image_t		*img;
	int				end;
}	t_tile;

typedef struct s_game
{
	int				fd;
	char			*map_name;
	t_list			*map_lst;
	char			**map;
	char			**temp_map;
	int				width;
	int				height;
	int				collect;
	int				player_count;
	int				exit_count;
	int				touch_exit;
	int				high_score;
	int				ignore_high_score;
	int				p_x;
	int				p_y;
	int				current_pos;
	int				next_pos;
	int				moves;
	int				gnl_free;
	mlx_t			*mlx;
	t_tile			**tile;
}	t_game;

//parsing
void	parsing(int argc, char *file, t_game *game);
void	init_struct(t_game *game);
void	get_map(t_game *game);
void	check_map(t_game *game);
int		check_path(t_game *game);
//load images
void	load_xpm(t_game *game);
void	xpm_to_image(t_game *game, t_tile **tile);
void	load_img(t_game *game, t_tile *tile);
//render
void	put_clean_image(t_game *game, t_tile tile, int x, int y);
void	render_background(t_game *game);
void	render_player(t_game *game, int current, int next);
//game controls
void	move_player(t_game *game, int y, int x);
void	keyhook(mlx_key_data_t k, void *tgame);
//end program
void	ft_win(t_game *game);
void	ft_error(char *error, t_game *game);
int		clean_close(char *error, t_game *game, int code);

#endif
