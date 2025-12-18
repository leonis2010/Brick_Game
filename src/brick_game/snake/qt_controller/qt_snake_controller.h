#ifndef QT_SNAKE_CONTROLLER_H
#define QT_SNAKE_CONTROLLER_H
#include <QKeyEvent>
#include <QTimer>

#include "../model/snake_model.h"
#include "qt_snake_view.h"
extern "C" {
#include "../../common/high_score/high_score.h"
}
namespace s21 {

class QtSnakeController : public QObject {
  Q_OBJECT
 public:
  QtSnakeController(SnakeModel& model, QtSnakeView& view);
  void UpdateTimer();
  void refresh_timer();
  SnakeDrawData get_data_from_model(SnakeModel& model);
  void handleKeyPress(QKeyEvent* event);
  void handleKeyRelease(QKeyEvent* event);
  void startGame();

 signals:
  void requestStartGame();
  void requestReturnToMenu();
  void gameStateChanged();

 private slots:
  void onTimeout();

 private:
  SnakeModel& model_;
  QtSnakeView& view_;
  QTimer timer_;
};

}  // namespace s21

#endif  // QT_SNAKE_CONTROLLER_H
