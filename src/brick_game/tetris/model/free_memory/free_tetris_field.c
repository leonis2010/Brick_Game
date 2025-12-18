#include "../s21_tetris_game_core.h"

void free_tetris_field(Tetris_Field* tetris_field) {
  if (tetris_field) {
    if (tetris_field->blocks) {
      free(tetris_field->blocks);
    }
    free(tetris_field);
  }
}