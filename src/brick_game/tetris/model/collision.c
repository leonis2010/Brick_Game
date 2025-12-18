#include "s21_tetris_game_core.h"

int collision(Tetris_Game* tetris_game) {
  int output = 0;
  Tetris_Figure* t = tetris_game->figure;
  Tetris_Field* tf = tetris_game->field;
  for (int i = 0; i < t->size; i++) {
    for (int j = 0; j < t->size; j++) {
      if (t->blocks[i * t->size + j].b != 0) {
        int fx = t->x + j;
        int fy = t->y + i;
        if (fx < 0 || fx >= tf->width || fy < 0 || fy >= tf->height ||
            tf->blocks[fy * tf->width + fx].b != 0) {
          output = 1;
          break;
        }
      }
    }
    if (output == 1) break;
  }
  return output;
}