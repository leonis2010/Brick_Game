#ifndef QT_TETRIS_CONTROLLER_H
#define QT_TETRIS_CONTROLLER_H

// #include <QKeyEvent>
#include <QObject>
#include <QTimer>

#include "../../../gui/desktop/tetris/qt_tetris_view.h"
#include "../qt_model/qt_tetris_model.h"

namespace s21 {

class QtTetrisController : public QObject {
  Q_OBJECT

 public:
  QtTetrisController(TetrisModel& model, QtTetrisView& view);
  void refresh_timer();
  TetrisDrawData get_data_from_model(TetrisModel& model);

 private slots:
  void onTimeout();
  void handleKeyPress(QKeyEvent* event);
  void handleKeyRelease(QKeyEvent* event);
  void startGame();
  void handleRestartRequest();

 private:
  TetrisModel& model_;
  QtTetrisView& view_;
  QTimer timer_;
  bool paused_ = false;
};

}  // namespace s21

#endif  // QT_TETRIS_CONTROLLER_H
