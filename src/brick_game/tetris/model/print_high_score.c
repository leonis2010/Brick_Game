#include "s21_tetris_game_core.h"

void print_high_score(Tetris_Game *tetris_game) {
  if (tetris_game->score > tetris_game->high_score) {
    tetris_game->high_score = tetris_game->score;
  }
}