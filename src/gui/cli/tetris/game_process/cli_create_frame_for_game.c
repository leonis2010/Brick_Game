#include "../../../../brick_game/tetris/model/s21_tetris_cli.h"
#ifdef TEST_MODE
int cli_create_frames_for_game(WINDOW** win_game, WINDOW** win_next_figure,
                               WINDOW** win_score_level,
                               WINDOW** win_high_score) {
  (void)win_game;
  (void)win_next_figure;
  (void)win_score_level;
  (void)win_high_score;
  return 0;
}
#else
// Создаем окно для игрового поля
int cli_create_frames_for_game(WINDOW **win_game, WINDOW **win_next_figure,
                               WINDOW **win_score_level,
                               WINDOW **win_high_score) {
  int max_y, max_x;
  getmaxyx(stdscr, max_y, max_x);  // Получаем размеры экрана

  int width_game = 22;
  int height_game = 22;
  int height_top = 5;     // высота верхнего окна
  int height_bottom = 4;  // высота нижнего окна

  // Вычисляем координаты центрального окна
  int start_x_game = (max_x - width_game) / 2;
  int start_y_game = (max_y - height_game) / 2;

  // Вычисляем координаты верхнего окна
  int start_x_top = start_x_game;
  int start_y_top = start_y_game - height_top;

  // Вычисляем координаты нижнего окна
  int start_x_bottom = start_x_game;
  int start_y_bottom = start_y_game + height_game;

  // Вычисляем координаты самого нижнего окна
  int start_x_bottom_bottom = start_x_bottom;
  int start_y_bottom_bottom = start_y_bottom + 4;

  // Создаем окна
  *win_game = newwin(height_game, width_game, start_y_game, start_x_game);
  *win_next_figure = newwin(height_top, width_game, start_y_top, start_x_top);
  *win_score_level =
      newwin(height_bottom, width_game, start_y_bottom, start_x_bottom);
  *win_high_score =
      newwin(3, width_game, start_y_bottom_bottom, start_x_bottom_bottom);

  // Проверка на ошибки при создании окон
  if (*win_game == NULL || *win_next_figure == NULL ||
      *win_score_level == NULL || *win_high_score == NULL) {
    return 1;  // Возвращаем ошибку
  }

  return 0;
}
#endif