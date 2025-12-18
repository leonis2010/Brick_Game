#include "qt_tetris_view.h"

namespace s21 {

QtTetrisView::QtTetrisView(QWidget* parent)
    : QWidget(parent), blockImage_(":/tetris_images/images/green_block.png") {
  if (!blockImage_.isNull()) {
    blockImage_ = blockImage_.scaled(30, 30, Qt::KeepAspectRatio,
                                     Qt::SmoothTransformation);
  }
  figureImages_.resize(4);
  QString imagePaths[4] = {":/tetris_images/images/blue_block.png",
                           ":/tetris_images/images/orange_block.png",
                           ":/tetris_images/images/red_block.png",
                           ":/tetris_images/images/green_block.png"};
  for (int i = 0; i < 4; ++i) {
    QImage img(imagePaths[i]);
    if (!img.isNull()) {
      img = img.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    figureImages_[i] = img;
  }
  setFocusPolicy(Qt::StrongFocus);
}  // конец конструктора

void QtTetrisView::draw(const TetrisDrawData& data) {
  draw_data_ = data;
  gameStarted_ = true;
  update();  // вызывает paintEvent
}
////////////////////////////////////////////////////////////////////////
void QtTetrisView::paintEvent(QPaintEvent*) {
  QPainter painter(this);

  const int cellSize = 30;
  const int offsetX = 49;
  const int offsetY = 20;

  // Цвета
  QColor bgColor("#87CEFA");  // Небесно-голубой фон всего экрана

  // 1. Заливаем весь экран небесно-голубым
  painter.fillRect(rect(), bgColor);

  if (!gameStarted_) {
    DrawWelcomeScreen(painter);
    return;
  }

  // 2. Рисуем градиент только в области игрового поля
  QRect gameArea(offsetX - 5, offsetY - 5, (cellSize * 10) + 10,
                 (cellSize * 20) + 10);
  QLinearGradient gradient(gameArea.topLeft(), gameArea.bottomRight());
  gradient.setColorAt(0, QColor("#FFD700"));  // золотой
  gradient.setColorAt(1, QColor("#87CEEB"));  // голубой

  painter.fillRect(gameArea, QBrush(gradient));

  // Рамка вокруг основного поля
  QRect frameRect(offsetX - 5, offsetY - 5, (cellSize * 10) + 10,
                  (cellSize * 20) + 10);
  QPen borderPen(QColor("#00CED1"), 3);  // тёмно-циан
  painter.setPen(borderPen);
  painter.drawRect(frameRect);

  // 3. Рисуем игровое поле — все блоки зелёные
  for (size_t i = 0; i < draw_data_.field.size(); ++i) {
    for (size_t j = 0; j < draw_data_.field[i].size(); ++j) {
      if (draw_data_.field[i][j]) {
        painter.drawImage(offsetX + j * cellSize, offsetY + i * cellSize,
                          figureImages_[3]);  // green_block.png
      }
    }
  }

  // 4. Рисуем текущую (падающую) фигуру синим цветом
  auto [y, x] = draw_data_.figurePos;
  for (size_t i = 0; i < draw_data_.currentFigure.size(); ++i) {
    for (size_t j = 0; j < draw_data_.currentFigure[i].size(); ++j) {
      if (draw_data_.currentFigure[i][j]) {
        painter.drawImage(offsetX + (x + j) * cellSize,
                          offsetY + (y + i) * cellSize,
                          figureImages_[0]);  // blue_block.png
      }
    }
  }

  // 5. Рисуем следующую фигуру оранжевым цветом
  int nextOffsetX = 140;
  int nextOffsetY = 640;
  for (size_t i = 0; i < draw_data_.nextFigure.size(); ++i) {
    for (size_t j = 0; j < draw_data_.nextFigure[i].size(); ++j) {
      if (draw_data_.nextFigure[i][j]) {
        painter.drawImage(nextOffsetX + j * cellSize,
                          nextOffsetY + i * cellSize,
                          figureImages_[1]);  // orange_block.png
      }
    }
  }
  ///////////////////////////////////////////////////

  // Установка общих параметров
  painter.setFont(QFont("Comic Sans MS", 24, QFont::Bold));

  // Рисуем уровень
  painter.setPen(QColor("#4B0082"));  // Темно-фиолетовый
  painter.drawText(30, 840, QString("Уровень: %1").arg(draw_data_.level));

  // Рисуем счёт
  painter.setPen(QColor("#FF69B4"));  // розовый
  painter.drawText(30, 880, QString("Очки: %1").arg(draw_data_.score));

  // Рисуем рекорд
  painter.setPen(QColor("#FFD700"));  // золотой
  painter.drawText(230, 840, QString("Рекорд: %1").arg(draw_data_.highScore));

  // Рисуем паузу
  if (draw_data_.paused) {
    painter.fillRect(rect(), QColor(0, 0, 0, 180));  // затемнение
    painter.setPen(Qt::red);
    painter.setFont(QFont("Comic Sans MS", 34, QFont::Bold));
    painter.drawText(rect(), Qt::AlignCenter, "ПАУЗА");
    //    qDebug() << "зашли в метод отрисовки паузы";
  }

  if (draw_data_.gameOver) {
    painter.fillRect(rect(), QColor(0, 0, 0, 180));  // затемнение
    painter.setPen(QColor("#FFD700"));
    painter.setFont(QFont("Comic Sans MS", 24, QFont::Bold));

    if (draw_data_.highScore == draw_data_.score && draw_data_.highScore != 0) {
      painter.drawText(rect(), Qt::AlignCenter,
                       QString("🎉 ПОБЕДА 🎉\n\nПоздравляем!\n У вас новый "
                               "РЕКОРД!\n\n\n Рекорд: %1")
                           .arg(draw_data_.highScore));

    } else {
      painter.setPen(Qt::red);
      painter.drawText(rect(), Qt::AlignCenter,
                       QString("ИГРА ОКОНЧЕНА").arg(draw_data_.highScore));
      // Подпись
      painter.setPen(QColor("#FF1493"));
      painter.setFont(QFont("Comic Sans MS", 18));
      QRect subtitleRect(0, 550, width(), 50);
      painter.drawText(subtitleRect, Qt::AlignCenter,
                       "Enter - Попробовать ещё раз.\nEscape - Выход.");
    }
  }
}

void QtTetrisView::DrawWelcomeScreen(QPainter& painter) {
  // Фон
  QLinearGradient gradient(rect().topLeft(), rect().bottomRight());
  gradient.setColorAt(0, QColor("#87CEFA"));  // Небесно-голубой
  gradient.setColorAt(1, QColor("#E0FFFF"));  // Светло-голубой
  painter.fillRect(rect(), QBrush(gradient));

  // Рисуем букву "Т" из кубиков
  const int cellSize = 30;
  int startX = rect().width() / 2 - 2 * cellSize - 4;
  int startY = 100;

  for (int j = 0; j < 5; ++j) {
    painter.drawImage(startX + j * cellSize, startY,
                      figureImages_[(j % 4)]);  // разные цвета
  }
  for (int i = 1; i < 6; ++i) {
    painter.drawImage(startX + 2 * cellSize, startY + i * cellSize,
                      figureImages_[1]);  // оранжевый столбик
  }

  // Заголовок
  painter.setFont(QFont("Comic Sans MS", 28, QFont::Bold));
  painter.setPen(QColor("#4B0082"));  // темно-фиолетовый
  QString title = "Добро пожаловать\nв Тетрис!";
  int textX = (rect().width() - 300) / 2;  // примерная ширина текста
  int textY = startY + 8 * cellSize - 30;

  painter.drawText(QRect(textX, textY, 300, 100), Qt::AlignCenter, title);

  // картинка тетриса
  QImage welcomeImage(":/tetris_images/images/tetris_image.jpeg");
  if (!welcomeImage.isNull()) {
    // Масштабируем изображение под нужный размер
    int imgWidth = 250;
    int imgHeight = 250;
    welcomeImage = welcomeImage.scaled(imgWidth, imgHeight, Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation);

    int imageX = (rect().width() - imgWidth) / 2;
    painter.drawImage(imageX, 450, welcomeImage);
  } else {
    qDebug() << "[ERROR] Welcome image not found!";
  }

  // Инструкция
  painter.setFont(QFont("Comic Sans MS", 20));
  painter.setPen(Qt::darkBlue);
  QString instruction = "Нажмите Enter, чтобы начать";
  int instrWidth = QFontMetrics(painter.font()).horizontalAdvance(instruction);
  painter.drawText((rect().width() - instrWidth) / 2, startY + 25 * cellSize,
                   instruction);
}

void QtTetrisView::keyPressEvent(QKeyEvent* event) {
  const auto key = event->key();
  const bool isEnterOrReturn = key == Qt::Key_Enter || key == Qt::Key_Return;

  if ((draw_data_.gameOver || !gameStarted_)) {
    if (isEnterOrReturn) {
      emit startGame();
      gameStarted_ = true;
      update();
      return;
    } else if (key == Qt::Key_Escape) {
      emit restartRequested();
      return;
    }
  } else
    emit keyPressed(event);
}

void QtTetrisView::keyReleaseEvent(QKeyEvent* event) {
  emit keyReleased(event);
}

}  // namespace s21
