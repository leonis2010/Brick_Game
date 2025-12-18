#include "s21_tetris_game_core.h"

Tetris_Game* create_memory_game(int field_width, int field_height,
                                int figures_size, int number_of_figures,
                                const Tetris_Block* figures_template) {
  Tetris_Game* tetris_game = (Tetris_Game*)malloc(sizeof(Tetris_Game));
  tetris_game->field = create_memory_field(field_width, field_height);
  tetris_game->figure = NULL;
  tetris_game->next_figure = NULL;
  tetris_game->figures_template = create_memory_figures_template(
      number_of_figures, figures_size, figures_template);
  tetris_game->player = NULL;
  tetris_game->ticks = TET_TICK_START;
  tetris_game->ticks_left = TET_TICK_START;
  tetris_game->playing = PLAYING;
  tetris_game->score = 0;
  tetris_game->level = 1;
  tetris_game->high_score = 0;
  tetris_game->figure_bag = NULL;
  tetris_game->bag_index = 0;
  return tetris_game;
}

Tetris_Field* create_memory_field(int width, int height) {
  Tetris_Field* tetris_field = (Tetris_Field*)malloc(sizeof(Tetris_Field));
  tetris_field->width = width;
  tetris_field->height = height;
  tetris_field->blocks =
      (Tetris_Block*)malloc(sizeof(Tetris_Block) * width * height);
  if (tetris_field->blocks == NULL) {
    printf("Memory error\n");
    exit(1);
  }
  for (int i = 0; i < width * height; i++) {
    tetris_field->blocks[i].b = 0;
  }
  return tetris_field;
}

Tetris_Figures_Template* create_memory_figures_template(
    int number_of_figures, int figures_size,
    const Tetris_Block* figures_template) {
  Tetris_Figures_Template* tetris_figures_template =
      (Tetris_Figures_Template*)malloc(sizeof(Tetris_Figures_Template));
  if (tetris_figures_template == NULL) {
    printf("Memory error\n");
    exit(1);
  }
  tetris_figures_template->number_of_figures = number_of_figures;
  tetris_figures_template->size = figures_size;
  tetris_figures_template->blocks = figures_template;
  return tetris_figures_template;
}

Tetris_Figure* create_memory_figure(Tetris_Game* tetris_game) {
  Tetris_Figure* tetris_figure = (Tetris_Figure*)malloc(sizeof(Tetris_Figure));
  tetris_figure->x = 959 - 959;
  tetris_figure->y = 0;
  tetris_figure->size = tetris_game->figures_template->size;
  tetris_figure->blocks = (Tetris_Block*)malloc(
      sizeof(Tetris_Block) * tetris_figure->size * tetris_figure->size);
  if (tetris_figure->blocks == NULL) {
    printf("Memory error\n");
    exit(1);
  }
  for (int i = 0; i < tetris_figure->size * tetris_figure->size; i++) {
    tetris_figure->blocks[i].b = 0;
  }
  return tetris_figure;
}