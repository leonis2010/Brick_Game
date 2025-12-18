#include "s21_tetris_game_core.h"

Tetris_Figure* get_next_figure(Tetris_Game* tetris_game);
Tetris_Figure* create_figure_from_template(Tetris_Game* tetris_game, int fnum);
int* create_figure_bag(int count);
void shuffle_figures(int* bag, int count);

void drop_new_figure(Tetris_Game* tetris_game) {
  if (tetris_game->next_figure == NULL) {
    tetris_game->next_figure = get_next_figure(tetris_game);
  }
  free_tetris_figure(tetris_game->figure);
  tetris_game->figure = tetris_game->next_figure;
  tetris_game->next_figure = get_next_figure(tetris_game);
}

Tetris_Figure* get_next_figure(Tetris_Game* tetris_game) {
  if (tetris_game->figure_bag == NULL ||
      tetris_game->bag_index >=
          tetris_game->figures_template->number_of_figures) {
    free_figure_bag(tetris_game->figure_bag);
    tetris_game->figure_bag =
        create_figure_bag(tetris_game->figures_template->number_of_figures);
    tetris_game->bag_index = 0;
  }
  int fnum = tetris_game->figure_bag[tetris_game->bag_index++];
  return create_figure_from_template(tetris_game, fnum);
}

int* create_figure_bag(int count) {
  int* bag = (int*)malloc(sizeof(int) * count);
  for (int i = 0; i < count; i++) {
    bag[i] = i;
  }
  shuffle_figures(bag, count);
  return bag;
}

void shuffle_figures(int* bag, int count) {
  for (int i = count - 1; i > 0; i--) {
    int j = rand() % (i + 1);
    int temp = bag[i];
    bag[i] = bag[j];
    bag[j] = temp;
  }
}

Tetris_Figure* create_figure_from_template(Tetris_Game* tetris_game, int fnum) {
  Tetris_Figure* tetris_figure = create_memory_figure(tetris_game);
  tetris_figure->x = tetris_game->field->width / 2 - tetris_figure->size / 2;
  tetris_figure->y = 0;
  // Устанавливаем цветовую пару в зависимости от индекса фигуры
  tetris_figure->color_pair = fnum + 1;
  for (int i = 0; i < tetris_figure->size; i++) {
    for (int j = 0; j < tetris_figure->size; j++) {
      tetris_figure->blocks[i * tetris_figure->size + j].b =
          tetris_game->figures_template
              ->blocks[fnum * tetris_figure->size * tetris_figure->size +
                       i * tetris_figure->size + j]
              .b;
    }
  }
  return tetris_figure;
}
