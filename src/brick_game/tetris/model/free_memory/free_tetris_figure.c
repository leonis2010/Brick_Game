#include "../s21_tetris_game_core.h"

void free_tetris_figure(Tetris_Figure* tetris_figure) {
  if (tetris_figure) {
    if (tetris_figure->blocks) {
      free(tetris_figure->blocks);
    }
    free(tetris_figure);
  }
}