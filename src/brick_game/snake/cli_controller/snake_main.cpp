#include <unistd.h>

#include "../../../gui/cli/snake/snake_view.h"
#include "../model/snake_model.h"
#include "snake_controller.h"
#ifdef TEST_MODE
#else
extern "C" {
#include "../../tetris/model/s21_tetris_cli.h"  // Для внешних функций
void snake_main() {
  noecho();
  cbreak();
  initialization_of_colors();
  WINDOW *win_game, *win_next_figure, *win_score_level, *win_high_score;
  if (cli_create_frames_for_game(&win_game, &win_next_figure, &win_score_level,
                                 &win_high_score) != 0) {
    endwin();
    return;
  }

  s21::SnakeModel model;
  s21::SnakeView view(win_game, win_next_figure, win_score_level,
                      win_high_score);
  s21::SnakeController controller(model, view);
  nodelay(stdscr, FALSE);
  keypad(stdscr, TRUE);
  curs_set(0);
  refresh();
  display_welcome_screen(model.GetHighScore(), win_game, win_next_figure,
                         win_score_level, win_high_score, 2);
  int ch;
  waiting_Enter();
  nodelay(stdscr, TRUE);
  while (!controller.IsGameOver()) {
    ch = getch();
    controller.HandleInput(ch);
    if (model.IsPause()) {
      view.DisplayPause();
      continue;
    }
    controller.Update();
  }

  save_high_score(model.GetHighScore(), 2);
  view.DisplayGameOver(model);
  nodelay(stdscr, FALSE);
  getch();

  delwin(win_game);
  delwin(win_next_figure);
  delwin(win_score_level);
  delwin(win_high_score);
  endwin();
}
}
#endif
