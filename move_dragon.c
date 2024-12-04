#include "so_long.h"

void move_dragons(t_game *game)
{
    int row, col;
    static int direction = 1;

    for (row = 0; row < game->height; row++)
    {
        for (col = 0; col < game->width; col++)
        {
            if (game->map[row][col] == 'M')
            {
                int new_col = col + direction;

                if (new_col >= 0 && new_col < game->width && game->map[row][new_col] != '1')
                {
                    if (game->map[row][new_col] != '0')
                    {
                        direction = -direction;
                        return;
                    }
                    game->map[row][col] = '0';
                    game->map[row][new_col] = 'M';
                    render_game(game, game->win);
                    return;
                }
                else
                {
                    direction = -direction;
                    return;
                }
            }
        }
    }
}