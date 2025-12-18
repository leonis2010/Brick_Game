#ifndef S21_SNAKE_VIEW_H
#define S21_SNAKE_VIEW_H
extern "C" {
#include "../../../brick_game/tetris/model/s21_tetris_cli.h"
}
#include <ncurses.h>

#include "../../../brick_game/snake/cli_controller/s21_cli_snake.h"

namespace s21 {

class SnakeViewTest;
class SnakeView {
  friend class SnakeViewTest;

 public:
  SnakeView(WINDOW* game_win, WINDOW* win_next_figure, WINDOW* win_score_level,
            WINDOW* win_high_score);
  void Draw(const SnakeModel& model);
  void DisplayGameOver(const SnakeModel& model);
  void DisplayPause();

#ifdef TEST_MODE
  void Test_DrawGameWindow(const SnakeModel& model) { DrawGameWindow(model); }
  void Test_DrawScoreWindow(const SnakeModel& model) { DrawScoreWindow(model); }
  void Test_DrawHighScoreWindow(const SnakeModel& model) {
    DrawHighScoreWindow(model);
  }
  void Test_DrawTitleWindow() { DrawTitleWindow(); }
#endif

 private:
  WINDOW* win_game_;
  WINDOW* win_next_figure_;
  WINDOW* win_score_level_;
  WINDOW* win_high_score_;

  void DrawGameWindow(const SnakeModel& model);
  void DrawScoreWindow(const SnakeModel& model);
  void DrawHighScoreWindow(const SnakeModel& model);
  void DrawTitleWindow();
};

}  // namespace s21

#endif  // S21_SNAKE_VIEW_H
