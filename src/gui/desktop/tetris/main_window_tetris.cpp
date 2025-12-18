#include "main_window_tetris.h"

namespace s21 {

MainWindowTetris::MainWindowTetris(QWidget* parent)
    : QMainWindow(parent), view_(this), controller_(model_, view_) {
  connect(&view_, &QtTetrisView::gameOver, this,
          [this]() { emit restartSelection(); });
  setCentralWidget(&view_);
  resize(400, 900);
  setWindowTitle("Tetris Game");

  show();
}

}  // namespace s21
