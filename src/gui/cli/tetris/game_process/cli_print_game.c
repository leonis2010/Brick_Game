#include "../../../../brick_game/tetris/model/s21_tetris_cli.h"
#ifdef TEST_MODE
void initialization_of_colors() { (void)0; }
#else

void cli_print_game(Tetris_Game* tetris_game, WINDOW* win_game,
                    WINDOW* win_next_figure, WINDOW* win_score_level,
                    WINDOW* win_high_score) {
  wclear(win_game);
  initialization_of_colors();
  Tetris_Field* tetris_field = tetris_game->field;
  Tetris_Figure* tetris_figure = tetris_game->figure;
  for (int i = 0; i < tetris_field->height; i++) {
    for (int j = 0; j < tetris_field->width; j++) {
      int sym = color_field;
      if (tetris_field->blocks[i * tetris_field->width + j].b != 0) {
        sym = color_figure;
      } else {
        int x = j - tetris_figure->x;
        int y = i - tetris_figure->y;
        if (x >= 0 && x < tetris_figure->size && y >= 0 &&
            y < tetris_figure->size) {
          if (tetris_figure->blocks[y * tetris_figure->size + x].b != 0) {
            sym = tetris_game->figure->color_pair;
          }
        }
      }
      wattron(win_game, COLOR_PAIR(sym));
      mvwaddch(win_game, i + 1, j * 2 + 1, ' ');
      mvwaddch(win_game, i + 1, j * 2 + 2, ' ');
      wattroff(win_game, COLOR_PAIR(sym));
    }
  }

  wclear(win_next_figure);
  Tetris_Figure* next_figure = tetris_game->next_figure;
  int offset_x = (getmaxx(win_next_figure) - next_figure->size * 2) / 2;
  int offset_y = 1;
  cli_draw_figure(next_figure, offset_x, offset_y, win_next_figure);

  wclear(win_score_level);
  wattron(win_score_level, COLOR_PAIR(10));
  mvwprintw(win_score_level, 1, 1, "Score: %d", tetris_game->score);
  mvwprintw(win_score_level, 2, 1, "Level: %d", tetris_game->level);
  wattroff(win_score_level, COLOR_PAIR(10));

  wclear(win_high_score);
  wattron(win_high_score, COLOR_PAIR(11));
  mvwprintw(win_high_score, 1, 1, "High score: %d", tetris_game->high_score);
  wattroff(win_high_score, COLOR_PAIR(11));

  box(win_game, 0, 0);
  box(win_next_figure, 0, 0);
  box(win_score_level, 0, 0);
  box(win_high_score, 0, 0);
  wnoutrefresh(win_game);
  wnoutrefresh(win_next_figure);
  wnoutrefresh(win_score_level);
  wnoutrefresh(win_high_score);
  curs_set(0);

  doupdate();
}

void cli_draw_figure(Tetris_Figure* figure, int offset_x, int offset_y,
                     WINDOW* win_next_figure) {
  for (int i = 0; i < figure->size; i++) {
    for (int j = 0; j < figure->size; j++) {
      int sym = color_field_next_figure;
      if (figure->blocks[i * figure->size + j].b != 0) {
        sym = figure->color_pair;
      }
      wattron(win_next_figure, COLOR_PAIR(sym));
      mvwaddch(win_next_figure, offset_y + i, offset_x + j * 2, ' ');
      mvwaddch(win_next_figure, offset_y + i, offset_x + j * 2 + 1, ' ');
      wattroff(win_next_figure, COLOR_PAIR(sym));
    }
  }
}

void initialization_of_colors() {
  start_color();
  init_pair(1, COLOR_RED, COLOR_RED);  // Цвет для фигуры с индексом 0
  init_pair(2, COLOR_CYAN, COLOR_CYAN);  // Цвет для фигуры с индексом 1
  init_pair(3, COLOR_YELLOW, COLOR_YELLOW);  // Цвет для фигуры с индексом 2
  init_pair(4, COLOR_WHITE, COLOR_MAGENTA);  // Цвет для фигуры с индексом 3
  init_pair(5, COLOR_GREEN, COLOR_GREEN);  // Цвет для фигуры с индексом 4
  init_pair(6, COLOR_BLUE, COLOR_BLUE);  // Цвет для фигуры с индексом 5
  init_pair(7, COLOR_MAGENTA, COLOR_MAGENTA);  // Цвет для фигуры с индексом 6

  init_pair(color_field, COLOR_BLACK, COLOR_WHITE);  // Поле основное
  init_pair(color_field_next_figure, COLOR_BLACK,
            COLOR_BLACK);  // Поле доп. фигуры

  init_pair(color_figure, COLOR_GREEN, COLOR_GREEN);  // Фигуры на поле
  init_pair(10, COLOR_YELLOW, COLOR_BLACK);           // Цвет шрифта
  init_pair(11, COLOR_CYAN, COLOR_BLACK);  // Цвет шрифта рекорда
  init_pair(13, COLOR_BLACK, COLOR_CYAN);  // Цвет шрифта рекорда

  init_pair(PAUSE_COLOR_PAIR, COLOR_RED, COLOR_WHITE);
  //     COLOR_BLACK
  //     COLOR_RED
  //     COLOR_GREEN
  //     COLOR_YELLOW
  //     COLOR_BLUE
  //     COLOR_MAGENTA
  //     COLOR_CYAN
  //     COLOR_WHITE

  init_pair(31, COLOR_WHITE, COLOR_WHITE);
  init_pair(32, COLOR_GREEN, COLOR_GREEN);
  init_pair(33, COLOR_RED, COLOR_RED);
  init_pair(34, COLOR_YELLOW, COLOR_BLACK);
  init_pair(35, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(310, COLOR_CYAN, COLOR_BLACK);
  init_pair(311, COLOR_YELLOW, COLOR_BLACK);
}
#endif