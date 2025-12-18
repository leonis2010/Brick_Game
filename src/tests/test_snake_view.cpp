#include <gtest/gtest.h>
#include <ncurses.h>

#include <cstdlib>
#include <filesystem>
#include <fstream>

#include "../brick_game/snake/model/snake_model.h"
#include "../gui/cli/snake/snake_view.h"

namespace s21 {

// Класс для тестирования приватных членов
class SnakeViewTest : public ::testing::Test {
 protected:
  WINDOW* game_win;
  WINDOW* next_fig_win;
  WINDOW* score_win;
  WINDOW* high_score_win;
  SnakeView* view;
  SnakeModel model;

  void SetUp() override {
    initscr();  // Инициализация ncurses
    game_win = newwin(10, 20, 0, 0);
    next_fig_win = newwin(5, 20, 10, 0);
    score_win = newwin(5, 20, 15, 0);
    high_score_win = newwin(5, 20, 20, 0);
    view = new SnakeView(game_win, next_fig_win, score_win, high_score_win);
  }

  void TearDown() override {
    delwin(game_win);
    delwin(next_fig_win);
    delwin(score_win);
    delwin(high_score_win);
    delete view;
    endwin();
  }
};

TEST_F(SnakeViewTest, PrivateDrawMethods) {
  EXPECT_NO_THROW(view->Test_DrawGameWindow(model));
  EXPECT_NO_THROW(view->Test_DrawScoreWindow(model));
  EXPECT_NO_THROW(view->Test_DrawHighScoreWindow(model));
  EXPECT_NO_THROW(view->Test_DrawTitleWindow());
  EXPECT_NO_THROW(view->DisplayGameOver(model));
  EXPECT_NO_THROW(view->Draw(model));
  EXPECT_NO_THROW(view->DisplayPause());
}

}  // namespace s21
