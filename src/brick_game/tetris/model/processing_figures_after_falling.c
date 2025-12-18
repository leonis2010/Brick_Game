#include "s21_tetris_game_core.h"

int erasse_lines(Tetris_Game* tetg);
void drop_line(int i, Tetris_Field* tfl);

void plant_figure(Tetris_Game* tetris_game) {
  Tetris_Figure* tetris_figure = tetris_game->figure;
  for (int i = 0; i < tetris_figure->size; i++) {
    for (int j = 0; j < tetris_figure->size; j++) {
      if (tetris_figure->blocks[i * tetris_figure->size + j].b != 0) {
        int fx = tetris_figure->x + j;
        int fy = tetris_figure->y + i;
        tetris_game->field->blocks[fy * tetris_game->field->width + fx].b =
            tetris_figure->blocks[i * tetris_figure->size + j].b;
      }
    }
  }
}

int line_filled(int i, Tetris_Field* tfl) {
  for (int j = 0; j < tfl->width; j++) {
    if (tfl->blocks[i * tfl->width + j].b == 0) {
      return 0;
    }
  }
  return 1;
}

int erasse_lines(Tetris_Game* tetg) {
  Tetris_Field* tfl = tetg->field;
  int count = 0;
  for (int i = tfl->height - 1; i >= 0; i--) {
    while (line_filled(i, tfl)) {
      drop_line(i, tfl);
      count++;
    }
  }
  return count;
}

void drop_line(int i, Tetris_Field* tfl) {
  if (i == 0) {
    for (int j = 0; j < tfl->width; j++) {
      tfl->blocks[j].b = 0;
    }
  } else {
    for (int k = i; k > 0; k--) {
      for (int j = 0; j < tfl->width; j++) {
        tfl->blocks[k * tfl->width + j].b =
            tfl->blocks[(k - 1) * tfl->width + j].b;
      }
    }
  }
}
