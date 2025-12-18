#include "snake_controller.h"

#include <sys/time.h>
#include <unistd.h>

#include <iostream>

#include "../../../gui/cli/snake/snake_view.h"
#include "../model/snake_model.h"

namespace s21 {
SnakeController::SnakeController(SnakeModel& model, SnakeView& view)
    : model_(model), view_(view), is_boost_key_down_(false) {}

void SnakeController::HandleInput(int ch) {
  if (ch == 27) {
    model_.TogglePause();
    return;
  }
  if (model_.IsPause()) return;

  switch (ch) {
    case KEY_UP:
      if (model_.GetDirection() != DOWN) model_.SetDirection(UP);
      break;
    case KEY_DOWN:
      if (model_.GetDirection() != UP) model_.SetDirection(DOWN);
      break;
    case KEY_LEFT:
      if (model_.GetDirection() != RIGHT) model_.SetDirection(LEFT);
      break;
    case KEY_RIGHT:
      if (model_.GetDirection() != LEFT) model_.SetDirection(RIGHT);
      break;
    case ' ':
      is_boost_key_down_ = true;
      model_.SetBoost(true);
      break;
    case 'q':
    case 'Q':
      model_.SetGameOver(true);
      break;
    default:
      is_boost_key_down_ = false;
      break;
  }
}

void SnakeController::sleeping_game() {
  int delay_ms = model_.GetDelay();

  struct timeval start_time;
  gettimeofday(&start_time, NULL);

  // Опрос клавиатуры во время ожидания
  while (true) {
    int ch = getch();
    if (ch != ERR) {
      HandleInput(ch);
    }

    // Вычисляем прошедшее время
    struct timeval now;
    gettimeofday(&now, NULL);
    long elapsed_ms = (now.tv_sec - start_time.tv_sec) * 1000 +
                      (now.tv_usec - start_time.tv_usec) / 1000;

    if (elapsed_ms >= delay_ms) break;
    // короткая пауза
    usleep(1000);
  }
}
void SnakeController::checkingBoost() {
  // После завершения задержки проверяем: удерживается ли пробел
  if (!is_boost_key_down_) {
    model_.SetBoost(false);
    is_boost_key_down_ = false;
  }
}

void SnakeController::Update() {
  sleeping_game();
  checkingBoost();
  model_.Move();
  view_.Draw(model_);
}

bool SnakeController::IsGameOver() const { return model_.IsGameOver(); }

}  // namespace s21
