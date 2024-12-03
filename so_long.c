#include "so_long.h"

int close_window(void *param)
{
    (void)param;
    exit(0);
}

int handle_keypress(int keycode, void *param)
{
    if (keycode == 65307)
        exit(0);
    return (0);
}

int print_images(void *mlx, void *win,char *link_img, int x, int y, int img_width, int img_height)
{
    void *img;

    img = mlx_xpm_file_to_image(mlx, link_img, &img_width, &img_height);
    if (!img)
    {
        write(2, "Failed to load image\n", 21);
        exit(1);
    }

    mlx_put_image_to_window(mlx, win, img, x, y);
    return (0);
}

int main(void)
{
    void *mlx;
    void *win;
    char **map;
    int row;
    int col;
    int screen_width = 3840;  
    int screen_height = 2160; 
    int game_width; 
    int game_height;
	int	final_width;
	int	final_height;
    int img_width = 98;
    int img_height = 98;

    mlx = mlx_init();
    map = read_map("carte.ber");
    if (!map)
        return (1);
    
    game_width = strlen(map[0]);
    game_height = 0;
    while (map[game_height])
        game_height++;
	final_width = game_width * img_width;
	final_height = game_height * img_height;
	if (final_width > screen_width || final_height > screen_height)
	{
		write(1, "Erreur\n", 7);
		return(0);
	}
    win = mlx_new_window(mlx, final_width, final_height, "So_long");

    row = 0;
    while (map[row])
    {
        col = 0;
        while (map[row][col])
        {
            if (map[row][col] == '1')
            {
                print_images(mlx, win, "./images/walls.xpm", col * img_width, row * img_height, img_width, img_height);
            }
			if (map[row][col] == 'C')
            {
                print_images(mlx, win,"./images/walls.xpm", col * img_width, row * img_height, img_width, img_height);
            }
			if (map[row][col] == 'E')
            {
                print_images(mlx, win,"./images/walls.xpm", col * img_width, row * img_height, img_width, img_height);
            }
			if (map[row][col] == 'P')
            {
                print_images(mlx, win,"./images/player.xpm", col * img_width, row * img_height, img_width, img_height);
            }
            col++;
        }
        row++;
    }

    free_map(map);
    mlx_hook(win, 17, 0, close_window, NULL);
    mlx_key_hook(win, handle_keypress, NULL);
    mlx_loop(mlx);

    return (0);
}
