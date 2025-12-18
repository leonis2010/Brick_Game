#include "snake_view.h"

#include <string>

#include "../../../brick_game/snake/model/snake_model.h"
#ifdef TEST_MODE
namespace s21 {
SnakeView::SnakeView(WINDOW* game_win, WINDOW* win_next_figure,
                     WINDOW* win_score_level, WINDOW* win_high_score) {
  (void)game_win;
  (void)win_next_figure;
  (void)win_score_level;
  (void)win_high_score;
}
void SnakeView::Draw(const SnakeModel& model) { (void)model; }
void SnakeView::DisplayPause() {}
void SnakeView::DisplayGameOver(const SnakeModel& model) { (void)model; }
void SnakeView::DrawGameWindow(const SnakeModel& model) { (void)model; }
void SnakeView::DrawScoreWindow(const SnakeModel& model) { (void)model; }
void SnakeView::DrawHighScoreWindow(const SnakeModel& model) { (void)model; }
void SnakeView::DrawTitleWindow() {}
}  // namespace s21
#else
namespace s21 {
SnakeView::SnakeView(WINDOW* game_win, WINDOW* win_next_figure,
                     WINDOW* win_score_level, WINDOW* win_high_score)
    : win_game_(game_win),
      win_next_figure_(win_next_figure),
      win_score_level_(win_score_level),
      win_high_score_(win_high_score) {}

void SnakeView::Draw(const SnakeModel& model) {
  if (model.IsPause()) {
    DisplayPause();
    return;
  }
  DrawGameWindow(model);
  DrawScoreWindow(model);
  DrawHighScoreWindow(model);
  DrawTitleWindow();
  doupdate();
}

void SnakeView::DisplayPause() {
  werase(win_game_);
  box(win_game_, 0, 0);
  std::string msg = "PAUSED";
  mvwprintw(win_game_, HEIGHT / 2, (WIDTH * 2 - msg.size() + 1) / 2, "%s",
            msg.c_str());
  wnoutrefresh(win_game_);
  doupdate();
}

void SnakeView::DisplayGameOver(const SnakeModel& model) {
  werase(win_game_);
  box(win_game_, 0, 0);
  std::string msg = model.GetScore() >= 200 ? "You Win!" : "Game Over!";
  mvwprintw(win_game_, HEIGHT / 2, (WIDTH * 2 - msg.size() + 1) / 2, "%s",
            msg.c_str());
  wnoutrefresh(win_game_);
  doupdate();
}

void SnakeView::DrawGameWindow(const SnakeModel& model) {
  werase(win_game_);
  box(win_game_, 0, 0);
  for (int y = 0; y < HEIGHT; ++y) {
    for (int x = 0; x < WIDTH; ++x) {
      int sym = 31;
      std::pair<int, int> cell = std::make_pair(y, x);
      if (cell == model.GetFood()) {
        sym = 33;
      } else if (std::find(model.GetSnake().begin(), model.GetSnake().end(),
                           cell) != model.GetSnake().end()) {
        sym = 32;
      }
      wattron(win_game_, COLOR_PAIR(sym));
      mvwaddch(win_game_, y + 1, x * 2 + 1, ' ');
      mvwaddch(win_game_, y + 1, x * 2 + 2, ' ');
      wattroff(win_game_, COLOR_PAIR(sym));
    }
  }
  wnoutrefresh(win_game_);
}

void SnakeView::DrawScoreWindow(const SnakeModel& model) {
  werase(win_score_level_);
  box(win_score_level_, 0, 0);
  wattron(win_score_level_, COLOR_PAIR(34));
  mvwprintw(win_score_level_, 1, 1, "Score: %d", model.GetScore());
  mvwprintw(win_score_level_, 2, 1, "Level: %d", model.GetLevel());
  wattroff(win_score_level_, COLOR_PAIR(34));
  wnoutrefresh(win_score_level_);
}

void SnakeView::DrawHighScoreWindow(const SnakeModel& model) {
  werase(win_high_score_);
  box(win_high_score_, 0, 0);
  wattron(win_high_score_, COLOR_PAIR(35));
  mvwprintw(win_high_score_, 1, 1, "High Score: %d", model.GetHighScore());
  wattroff(win_high_score_, COLOR_PAIR(35));
  wnoutrefresh(win_high_score_);
}

void SnakeView::DrawTitleWindow() {
  werase(win_next_figure_);
  box(win_next_figure_, 0, 0);
  std::string title = "Snake Game";
  int title_length = title.length();
  int win_width = getmaxx(win_next_figure_);
  int centered_x = (win_width - title_length) / 2;
  mvwprintw(win_next_figure_, 2, centered_x, "%s", title.c_str());
  wnoutrefresh(win_next_figure_);
}

}  // namespace s21
#endif  // TEST_MODE
