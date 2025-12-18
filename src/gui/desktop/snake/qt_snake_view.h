#ifndef QT_SNAKE_VIEW_H
#define QT_SNAKE_VIEW_H

#include <QKeyEvent>
#include <QPainter>
#include <QWidget>
#include <deque>
#include <utility>

#include "../../../brick_game/snake/model/snake_model.h"
namespace s21 {

struct SnakeDrawData {
  std::deque<std::pair<int, int>> snake;
  std::pair<int, int> food;
  int score = 0;
  bool paused = false;
  bool game_over = false;
  bool win = false;
  bool start_screen = true;
  int high_score = 0;
  int level = 1;
};

class QtSnakeView : public QWidget {
  Q_OBJECT
 public:
  explicit QtSnakeView(QWidget* parent = nullptr);
  void draw(const SnakeDrawData& data);  // Принимаем структуру для отрисовки

 signals:
  void keyPressed(QKeyEvent* event);
  void keyReleased(QKeyEvent* event);

 protected:
  void paintEvent(QPaintEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;

 private:
  SnakeDrawData draw_data_;  // Храним данные для отрисовки
  void draw_welcome_screen(QPainter& painter);
  void drawSnake(QPainter& painter);
  void drawApple(QPainter& painter);
  void drawScoreLevelPause(QPainter& painter);
  void drawGameOverWin(QPainter& painter);
};

}  // namespace s21

#endif  // QT_SNAKE_VIEW_H
