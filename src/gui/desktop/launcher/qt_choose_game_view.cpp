#include "qt_choose_game_view.h"

QtChooseGameView::QtChooseGameView(QWidget* parent) : QWidget(parent) {
  setWindowTitle("Выбор игры");
  resize(400, 300);

  QVBoxLayout* layout = new QVBoxLayout(this);

  QLabel* label = new QLabel("Выберите игру:", this);
  label->setAlignment(Qt::AlignCenter);
  layout->addWidget(label);

  QPushButton* tetrisButton = new QPushButton("Тетрис", this);
  QPushButton* snakeButton = new QPushButton("Змейка", this);

  layout->addWidget(tetrisButton);
  layout->addWidget(snakeButton);

  connect(tetrisButton, &QPushButton::clicked, [this]() {
    emit gameSelected(0);  // Тетрис
  });

  connect(snakeButton, &QPushButton::clicked, [this]() {
    emit gameSelected(1);  // Змейка
  });
}
