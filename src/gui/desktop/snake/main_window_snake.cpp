#include "main_window_snake.h"

namespace s21 {

MainWindowSnake::MainWindowSnake(QWidget* parent)
    : QMainWindow(parent), view_(this), controller_(model_, view_) {
  connect(&controller_, &QtSnakeController::requestReturnToMenu, this,
          &MainWindowSnake::restartSelection);

  setCentralWidget(&view_);
  resize(400, 900);
  setWindowTitle("Snake Game");
  show();
}

}  // namespace s21
