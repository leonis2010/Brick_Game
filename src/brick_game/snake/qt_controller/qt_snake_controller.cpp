#include "qt_snake_controller.h"

#include "qtimer.h"

namespace s21 {

QtSnakeController::QtSnakeController(SnakeModel& model, QtSnakeView& view)
    : QObject(nullptr), model_(model), view_(view) {
  // Основные соединения
  connect(&timer_, &QTimer::timeout, this, &QtSnakeController::onTimeout);
  connect(&view_, &QtSnakeView::keyPressed, this,
          &QtSnakeController::handleKeyPress);
  connect(&view_, &QtSnakeView::keyReleased, this,
          &QtSnakeController::handleKeyRelease);

  model_.SetStartScreen(true);
  timer_.stop();

  if (!model_.IsStartScreen()) {
    timer_.start(model_.GetDelay());
  }
}

SnakeDrawData QtSnakeController::get_data_from_model(SnakeModel& model) {
  SnakeDrawData data;
  data.snake = model.GetSnake();
  data.food = model.GetFood();
  data.score = model.GetScore();
  data.paused = model.IsPause();
  data.game_over = model_.IsGameOver();
  data.win = model_.IsWin();
  data.high_score = model_.GetHighScore();
  data.level = model_.GetLevel();
  data.start_screen = model_.IsStartScreen();
  return data;
}

void QtSnakeController::onTimeout() {  // сердце игры
  model_.Move();
  refresh_timer();
  view_.draw(get_data_from_model(model_));
  if (model_.IsGameOver()) {
    timer_.stop();
    save_high_score(model_.GetHighScore(), 2);
  }
}

void QtSnakeController::handleKeyPress(QKeyEvent* event) {
  qDebug() << "Key pressed:" << event->key()
           << "Pause state before:" << model_.IsPause();
  if (model_.IsStartScreen() || model_.IsGameOver()) {
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return) {
      startGame();
    } else if (event->key() == Qt::Key_Escape) {
      emit requestReturnToMenu();
    }
    return;
  }

  // Логика во время игры
  if (event->key() == Qt::Key_Escape) {
    qDebug() << "Escape processing started";
    model_.TogglePause();
    qDebug() << "Pause state after toggle:" << model_.IsPause();
    if (model_.IsPause()) {
      view_.draw(get_data_from_model(model_));
      timer_.stop();
      qDebug() << "Timer stopped";
    } else {
      refresh_timer();
      qDebug() << "Timer restarted";
    }
    return;
  }

  if (model_.IsPause()) {
    return;
  }

  switch (event->key()) {
    case Qt::Key_Up:
      if (model_.GetDirection() != DOWN) model_.SetDirection(UP);
      break;
    case Qt::Key_Down:
      if (model_.GetDirection() != UP) model_.SetDirection(DOWN);
      break;
    case Qt::Key_Left:
      if (model_.GetDirection() != RIGHT) model_.SetDirection(LEFT);
      break;
    case Qt::Key_Right:
      if (model_.GetDirection() != LEFT) model_.SetDirection(RIGHT);
      break;
    case Qt::Key_Space:
      model_.SetBoost(true);
      break;
    default:
      model_.SetBoost(false);
      break;
  }
  view_.update();
}

// Отпускание клавишы
void QtSnakeController::handleKeyRelease(QKeyEvent* event) {
  if (event->key() == Qt::Key_Space) {
    model_.SetBoost(false);
  }
}

void QtSnakeController::startGame() {
  model_.Reset();
  model_.SetStartScreen(false);
  refresh_timer();
}

void QtSnakeController::refresh_timer() {
  if (timer_.isActive()) {
    timer_.stop();
  }
  timer_.start(model_.GetDelay());

  // qDebug() << "SPEED_DELAY: " << model_.GetDelay();  // дебаг
}

}  // namespace s21
