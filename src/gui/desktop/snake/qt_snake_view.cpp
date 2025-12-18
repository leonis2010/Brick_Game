#include "qt_snake_view.h"

namespace s21 {

QtSnakeView::QtSnakeView(QWidget* parent) : QWidget(parent) {
  setFocusPolicy(Qt::StrongFocus);
  setFocus();
}

void QtSnakeView::draw(const SnakeDrawData& data) {
  draw_data_ = data;
  update();
}

void QtSnakeView::paintEvent(QPaintEvent* event) {
  Q_UNUSED(event);
  QPainter painter(this);
  painter.fillRect(rect(), QColor("#FFFACD"));

  if (draw_data_.start_screen) {
    draw_welcome_screen(painter);
    return;
  }

  // Рисуем игровое поле
  painter.fillRect(0, 0, 400, 800, QColor("#E6F7FF"));  // нежно-голубой
  drawSnake(painter);
  drawApple(painter);
  drawScoreLevelPause(painter);

  if (draw_data_.game_over) {
    drawGameOverWin(painter);
  }

}  // paintEvent

void QtSnakeView::draw_welcome_screen(QPainter& painter) {
  painter.fillRect(rect(), QColor("skyblue"));
  // Солнце
  painter.setBrush(Qt::yellow);
  painter.drawEllipse(350, 20, 30, 30);
  for (int i = 0; i < 12; ++i) {
    painter.save();
    painter.translate(365, 35);
    painter.rotate(i * 30);
    painter.drawLine(0, -20, 0, -35);
    painter.restore();
  }

  // Текст "ЗМЕЙКА"
  painter.setPen(QColor("#FF1493"));
  painter.setFont(QFont("Comic Sans MS", 48, QFont::Bold));
  QRect titleRect(0, 200, width(), 100);
  painter.drawText(titleRect, Qt::AlignCenter, "ЗМЕЙКА");

  // Подпись
  painter.setPen(QColor("#228B22"));
  painter.setFont(QFont("Comic Sans MS", 18));
  QRect subtitleRect(0, 800, width(), 50);
  painter.drawText(subtitleRect, Qt::AlignCenter, "Нажмите Enter для старта");

  // Змейка (картинка)
  QImage snake(":/resourses_files/images/snake.png");
  if (!snake.isNull()) {
    int imgWidth = 250;
    int imgHeight = 250;
    QImage scaledSnake = snake.scaled(imgWidth, imgHeight, Qt::KeepAspectRatio,
                                      Qt::SmoothTransformation);
    int imageX = (rect().width() - imgWidth) / 2;
    painter.drawImage(imageX, 380, scaledSnake);
  } else {
    qDebug() << "[ERROR] Welcome image not found!";
    // Буква S (жирная)
    QPen sPen;
    sPen.setColor(QColor("#32CD32"));  // Лаймово-зелёный
    sPen.setWidth(15);  // Толщина линии — делаем жирнее!
    sPen.setCapStyle(Qt::RoundCap);  // Скругление концов — красивее
    sPen.setJoinStyle(Qt::RoundJoin);  // Скругление углов соединений
    painter.setPen(sPen);
    painter.setBrush(Qt::NoBrush);

    QRect s_rect(140, 400, 120, 60);  // x, y, ширина, высота
    painter.drawArc(s_rect, 90 * 16, 180 * 16);  // верхняя половина
    painter.drawArc(s_rect.adjusted(0, 60, 0, 60), 90 * 16,
                    -180 * 16);  // нижняя половина
  }
}

void QtSnakeView::drawSnake(QPainter& painter) {
  int segmentIndex = 0;
  int totalSegments = draw_data_.snake.size();

  for (const auto& dot : draw_data_.snake) {
    // Вычисляем интенсивность зелёного цвета в зависимости от позиции
    // от 50 до 250
    int greenValue = 50 + (200 * segmentIndex) / totalSegments;
    // RGB: только зелёный канал меняется
    painter.setBrush(QColor(0, greenValue, 0));
    // Рисуем блок
    painter.drawRect(dot.second * 40, dot.first * 40, 40, 40);
    segmentIndex++;
  }
}

void QtSnakeView::drawApple(QPainter& painter) {
  const auto& food = draw_data_.food;
  QImage apple(":/resourses_files/images/apple.jpg");

  if (!apple.isNull()) {
    // Масштабируем изображение под размер блока (40x40)
    QImage scaledApple =
        apple.scaled(40, 40, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Рисуем яблоко на координатах еды
    painter.drawImage(food.second * 40, food.first * 40, scaledApple);
  } else {
    qDebug() << "Ошибка: Изображение не загружено из .qrc!";
    painter.setBrush(QColor("#FFD700"));  // Золотистый цвет
    painter.drawEllipse(food.second * 40 + 5, food.first * 40 + 5, 30, 30);

    // Глазки
    painter.setBrush(Qt::white);
    painter.drawEllipse(food.second * 40 + 12, food.first * 40 + 12, 5, 5);
    painter.drawEllipse(food.second * 40 + 23, food.first * 40 + 12, 5, 5);
  }
}

void QtSnakeView::drawScoreLevelPause(QPainter& painter) {
  // Рисуем уровень
  painter.setFont(QFont("Comic Sans MS", 24, QFont::Bold));
  painter.setPen(QColor("#4B0082"));  // Темно-фиолетовый
  painter.drawText(30, 840, QString("Уровень: %1").arg(draw_data_.level));

  // Рисуем счёт
  painter.setFont(QFont("Comic Sans MS", 24, QFont::Bold));
  painter.setPen(QColor("#FF69B4"));  // розовый
  painter.drawText(30, 880, QString("Очки: %1").arg(draw_data_.score));

  // Рисуем рекорд
  painter.setFont(QFont("Comic Sans MS", 24, QFont::Bold));
  painter.setPen(QColor("#00CED1"));  //  тёмно-циан
  painter.drawText(230, 840, QString("Рекорд: %1").arg(draw_data_.high_score));

  // Рисуем паузу
  if (draw_data_.paused) {
    painter.fillRect(rect(), QColor(0, 0, 0, 180));  // затемнение
    painter.setPen(Qt::red);
    painter.setFont(QFont("Comic Sans MS", 34, QFont::Bold));
    painter.drawText(rect(), Qt::AlignCenter, "ПАУЗА");
    //    qDebug() << "зашли в метод отрисовки паузы";
  }
}

void QtSnakeView::drawGameOverWin(QPainter& painter) {
  painter.fillRect(rect(), QColor(0, 0, 0, 180));  // затемнение
  painter.setPen(Qt::red);
  painter.setFont(QFont("Comic Sans MS", 24, QFont::Bold));

  if (draw_data_.win) {
    painter.drawText(rect(), Qt::AlignCenter,
                     "🎉 ПОБЕДА 🎉\n\nПоздравляем!\nВы собрали 200 очков!");
  } else {
    painter.drawText(rect(), Qt::AlignCenter, "ИГРА ОКОНЧЕНА");
    // Подпись
    painter.setPen(QColor("#FF1493"));
    painter.setFont(QFont("Comic Sans MS", 18));
    QRect subtitleRect(0, 700, width(), 50);
    painter.drawText(subtitleRect, Qt::AlignCenter,
                     "Enter - Попробовать ещё раз.\nEscape - Выход.");
  }

  painter.setPen(Qt::white);
  painter.setFont(QFont("Arial", 16));
  QString scoreText = QString("Score: %1").arg(draw_data_.score);
  painter.drawText(rect(), Qt::AlignBottom | Qt::AlignHCenter, scoreText);

  painter.setFont(QFont("Arial", 12));
  QString highScoreText = QString("High Score: %1").arg(draw_data_.high_score);
  painter.drawText(rect(), Qt::AlignBottom | Qt::AlignLeft, highScoreText);

  QString restartText = "Press any key to restart";
  painter.drawText(rect(), Qt::AlignBottom | Qt::AlignRight, restartText);
}

void QtSnakeView::keyPressEvent(QKeyEvent* event) { emit keyPressed(event); }

void QtSnakeView::keyReleaseEvent(QKeyEvent* event) { emit keyReleased(event); }
}  // namespace s21
