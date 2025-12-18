#include "../s21_tetris_game_core.h"

void free_tetris_figures_template(
    Tetris_Figures_Template* tetris_figures_template) {
  if (tetris_figures_template) {
    free(tetris_figures_template);
  }
}
