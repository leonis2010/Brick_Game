#ifndef S21_SNAKE_CONTROLLER_H
#define S21_SNAKE_CONTROLLER_H

#include "s21_cli_snake.h"

namespace s21 {

class SnakeController {
 public:
  SnakeController(SnakeModel& model, SnakeView& view);
  void HandleInput(int ch);
  void Update();
  bool IsGameOver() const;
  void sleeping_game();
  void checkingBoost();

 private:
  SnakeModel& model_;
  SnakeView& view_;
  bool is_boost_key_down_;
};

}  // namespace s21

#endif  // S21_SNAKE_CONTROLLER_H
