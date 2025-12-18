#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

#include "../../../brick_game/tetris/qt_controller/qt_tetris_controller.h"
#include "qt_tetris_view.h"

namespace s21 {

class MainWindowTetris : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindowTetris(QWidget* parent = nullptr);

 signals:
  void restartSelection();

 private:
  TetrisModel model_;
  QtTetrisView view_;
  QtTetrisController controller_;
};

}  // namespace s21

#endif  // MAIN_WINDOW_H
