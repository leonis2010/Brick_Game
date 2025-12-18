#include "s21_tetris_game_core.h"

void reset_game(Tetris_Game* tetris_game) {
  for (int i = 0; i < tetris_game->field->width * tetris_game->field->height;
       i++) {
    tetris_game->field->blocks[i].b = 0;
  }
  tetris_game->playing = PLAYING;
  tetris_game->score = 0;
  tetris_game->level = 1;
  drop_new_figure(tetris_game);
}