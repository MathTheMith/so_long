#include "so_long.h"

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_ESC 65307
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

void display_victory_message(int player_step)
{
    ft_printf(GREEN"\n\
██████████████████████████████████████████████████████████████████\n\
██                                                              ██\n\
██  ███  ███  ██████  ██    ██     ██      ██ ██ ██    ██   ██  ██\n\
██   ██  ██  ██    ██ ██    ██     ██      ██ ██ ███   ██   ██  ██\n\
██    ████   █      █ ██    ██     ██  ██  ██ ██ ██ ██ ██   ██  ██\n\
██     ██    ██    ██ ██    ██     ██ ████ ██ ██ ██  ████       ██\n\
██     ██     ██████    ████        ███  ███  ██ ██   ███   ██  ██\n\
██                                                              ██\n\
██████████████████████████████████████████████████████████████████\n\n\
"RESET, player_step);
}
int close_window(void *param)
{
	(void)param;
	exit(0);
}

int print_images(void *mlx, void *win, char *link_img, int x, int y, int img_width, int img_height)
{
	void *img;

	img = mlx_xpm_file_to_image(mlx, link_img, &img_width, &img_height);
	if (!img)
	{
		ft_printf("%s", "L'image ne charge pas\n");
		return (0);
	}

	mlx_put_image_to_window(mlx, win, img, x, y);
	return (1);
}

int render_game(t_game *game, void *win)
{
    int row = 0;
    int col;
    static int dragon_direction = 1;
	char *dragon_image;
    mlx_clear_window(game->mlx, win);

    while (game->map[row])
    {
        col = 0;
        while (game->map[row][col])
        {
            if (game->map[row][col] == '1')
                print_images(game->mlx, win, "./images/walls.xpm", col * 98, row * 98, 98, 98);
            else if (game->map[row][col] == 'C')
                print_images(game->mlx, win, "./images/item.xpm", col * 98, row * 98, 98, 98);
            else if (game->map[row][col] == 'E')
                print_images(game->mlx, win, "./images/exit.xpm", col * 98, row * 98, 98, 98);
            else if (game->map[row][col] == 'M')
            {
                if (dragon_direction > 0)
					dragon_image = "./images/dragon_right.xpm";
				else
                	dragon_image = "./images/dragon_left.xpm";
                
                print_images(game->mlx, win, dragon_image, col * 98, row * 98, 98, 98);
            }
            else if (game->map[row][col] == 'P')
            {
                print_images(game->mlx, win, "./images/player.xpm", col * 98, row * 98, 98, 98);
                game->player_x = col;
                game->player_y = row;
            }
            col++;
        }
        row++;
    }
    dragon_direction = -dragon_direction;
    if (col + row < 12)
        return(0);
    return(1);
}

void render_steps_with_background(void *mlx, void *win, int steps)
{
    char step_count[50];
    sprintf(step_count, "Pas: %d", steps); 

    int rect_width = 150;
    int rect_height = 50;
	int	i;
    void *bg_image = mlx_new_image(mlx, rect_width, rect_height);
    int *data = (int *)mlx_get_data_addr(bg_image, &(int){0}, &(int){0}, &(int){0});

	i = 0;
    while (i < rect_width * rect_height)
	{
		data[i] = 0x000000;
		i++;
	}

    mlx_put_image_to_window(mlx, win, bg_image, 25, 25);
    mlx_string_put(mlx, win, 40, 40, 0xFFFFFF, step_count);
    mlx_destroy_image(mlx, bg_image);
}




int handle_keypress(int keycode, void *param)
{
    t_game *game = (t_game *)param;
    int new_x = game->player_x;
    int new_y = game->player_y;
    int all_bonus;
    static int player_step = 0;
	int	old_step = player_step;
    char *player_img = "./images/player.xpm";

    all_bonus = check_objects(game->map);

    if (keycode == KEY_W)
        {new_y--;
		player_step++;}
    else if (keycode == KEY_A)
        {new_x--;
		player_step++;}
    else if (keycode == KEY_S)
    {
			new_y++;
			player_step++;
	}
    else if (keycode == KEY_D)
	{
        new_x++;
		player_step++;
	}
    else if (keycode == KEY_ESC) 
        close_window(param);
	if(old_step == player_step)
	{
		return(1);
	}
	old_step = player_step;
	move_dragons(game);
    if (new_x >= 0 && new_x < game->width && new_y >= 0 && new_y < game->height)
    {
		if (game->map[new_y][new_x] == 'E' && all_bonus != 0)
            return (0);
		if (game->map[new_y][new_x] == 'M')
        {
            printf("Malheureusement tu es mort avec %d pas\n", player_step);
            close_window(param);
            return (0);
        }
        if (all_bonus == 0 && game->map[new_y][new_x] == 'E')
        {
            display_victory_message(player_step);
            close_window(param);
            return (0);
        }
        if (game->map[new_y][new_x] != '1')
        {
            game->map[game->player_y][game->player_x] = '0'; 
            game->map[new_y][new_x] = 'P';
            if (keycode == KEY_D) {
                player_img = "./images/player.xpm";
            }
            else if (keycode == KEY_A) {
                player_img = "./images/player_left.xpm";
            }
            game->player_x = new_x;
            game->player_y = new_y;
            
            render_game(game, game->win);
            render_steps_with_background(game->mlx, game->win, player_step);
            print_images(game->mlx, game->win, player_img, game->player_x * 98, game->player_y * 98, 98, 98);
        }
    }

    return (1);
}




int main(void)
{
	void    *mlx;
	void    *win;
	char    **map;
	int row;
	int col;
	int screen_width = 2560;  
	int screen_height = 1440; 
	int game_width; 
	int game_height;
	int final_width;
	int final_height;
	int img_width = 98;
	int img_height = 98;
	int	all_bonus;
	t_game game;

	mlx = mlx_init();
	map = read_map("carte.ber");
	if (map == NULL)
	{
		ft_printf("%s", "La map n'est pas bonne", 7);
		return (0);
	}

	game_width = ft_strlen(map[0]);
	game_height = 0;
	while (map[game_height])
		game_height++;
	final_width = game_width * img_width;
	final_height = game_height * img_height;

	if (final_width > screen_width || final_height > screen_height)
	{
		write(1, "Erreur\n", 7);
		return (0);
	}

	win = mlx_new_window(mlx, final_width - 98, final_height, "So_long");

	game.mlx = mlx;
	game.map = map;
	game.player_x = 0;
	game.player_y = 0;
	game.width = game_width;
	game.height = game_height;
	game.win = win;


	if (!check_objects(map))
	{
		ft_printf("%s", "Il n'y a pas le bon nombre d'objets...\n");
		return (0);
	}
	if (!render_game(&game, win))
	{
		ft_printf("%s", "La carte est trop petite\n");
		return (0);

	}
	if (!check_borders(map))
	{
		ft_printf("%s", "Les murs ne sont pas bon\n");
		return (0);
	}
	if (!mlx_key_hook(win, handle_keypress, &game))
		return(0);
	mlx_hook(win, 17, 0, close_window, NULL);
	mlx_loop(mlx);
	return (0);
}
