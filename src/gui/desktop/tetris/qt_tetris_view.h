#ifndef QT_TETRIS_VIEW_H
#define QT_TETRIS_VIEW_H

#include <QDebug>
#include <QKeyEvent>
#include <QPainter>
#include <QWidget>
#include <utility>
#include <vector>

namespace s21 {

struct TetrisDrawData {
  std::vector<std::vector<int>> field;
  std::vector<std::vector<int>> currentFigure;
  std::vector<std::vector<int>> nextFigure;
  std::pair<int, int> figurePos;
  int score = 0;
  int highScore = 0;
  int level = 1;
  bool gameOver = false;
  bool paused = false;
};

class QtTetrisView : public QWidget {
  Q_OBJECT

 public:
  explicit QtTetrisView(QWidget* parent = nullptr);
  void draw(const TetrisDrawData& data);
  void DrawWelcomeScreen(QPainter& painter);

 signals:
  void keyPressed(QKeyEvent*);
  void keyReleased(QKeyEvent*);
  void startGame();
  void restartRequested();
  void gameOver();

 protected:
  void paintEvent(QPaintEvent*) override;
  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;

 private:
  TetrisDrawData draw_data_;
  QImage blockImage_;
  std::vector<QImage> figureImages_;
  bool gameStarted_ = false;
};

}  // namespace s21

#endif  // QT_TETRIS_VIEW_H
