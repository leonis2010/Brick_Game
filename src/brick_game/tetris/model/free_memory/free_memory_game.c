#include "../s21_tetris_game_core.h"

void free_memory_game(Tetris_Game* tetris_game) {
  if (tetris_game) {
    free_tetris_figure(tetris_game->figure);
    free_tetris_figure(tetris_game->next_figure);
    free_figure_bag(tetris_game->figure_bag);
    free_tetris_field(tetris_game->field);
    free_tetris_figures_template(tetris_game->figures_template);
    free(tetris_game);
  }
}