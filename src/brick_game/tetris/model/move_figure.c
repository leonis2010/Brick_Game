#include "s21_tetris_game_core.h"

void moveFigureDown(Tetris_Game* tetg) { tetg->figure->y++; }

void moveFigureUp(Tetris_Game* tetg) { tetg->figure->y--; }

void moveFigureRight(Tetris_Game* tetg) { tetg->figure->x++; }

void moveFigureLeft(Tetris_Game* tetg) { tetg->figure->x--; }

Tetris_Figure* rotTetFigure(Tetris_Game* tetg) {
  Tetris_Figure* t = create_memory_figure(tetg);
  Tetris_Figure* told = tetg->figure;
  t->x = told->x;
  t->y = told->y;
  t->color_pair = told->color_pair;
  for (int i = 0; i < t->size; i++) {
    for (int j = 0; j < t->size; j++) {
      t->blocks[i * t->size + j].b =
          told->blocks[(t->size - 1 - j) * t->size + i].b;
    }
  }
  return t;
}