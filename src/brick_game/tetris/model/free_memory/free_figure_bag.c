#include "../s21_tetris_game_core.h"

void free_figure_bag(int* bag) {
  if (bag) {
    free(bag);
  }
}