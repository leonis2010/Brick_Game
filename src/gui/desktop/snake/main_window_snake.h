#ifndef MAIN_WINDOW_SNAKE_H
#define MAIN_WINDOW_SNAKE_H

#include <QMainWindow>

#include "../../../brick_game/snake/model/snake_model.h"
#include "../../../brick_game/snake/qt_controller/qt_snake_controller.h"
#include "qt_snake_view.h"

namespace s21 {

class MainWindowSnake : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindowSnake(QWidget* parent = nullptr);

 signals:
  void restartSelection();

 private:
  SnakeModel model_;
  QtSnakeView view_;
  QtSnakeController controller_;
};

}  // namespace s21

#endif  // MAIN_WINDOW_SNAKE_H
