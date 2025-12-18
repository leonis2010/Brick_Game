#ifndef QT_CHOOSE_GAME_VIEW_H
#define QT_CHOOSE_GAME_VIEW_H

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class QtChooseGameView : public QWidget {
  Q_OBJECT

 public:
  explicit QtChooseGameView(QWidget *parent = nullptr);

 signals:
  void gameSelected(int gameIndex);  // 0 - Tetris, 1 - Snake
};

#endif  // QT_CHOOSE_GAME_VIEW_H
