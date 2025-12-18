
#include "../model/s21_tetris_cli.h"

void pause_processing(Tetris_Game* tetris_game, bool* paused,
                      WINDOW* win_game) {
  if (tetris_game->player->action == PLAYER_PAUSE) {
    *paused = !(*paused);
    if (*paused) {
      cli_print_pause(win_game);
    }
  }
  curs_set(0);
}