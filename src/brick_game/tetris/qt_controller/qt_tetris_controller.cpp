#include "qt_tetris_controller.h"

namespace s21 {

QtTetrisController::QtTetrisController(TetrisModel& model, QtTetrisView& view)
    : QObject(nullptr), model_(model), view_(view) {
  connect(&timer_, &QTimer::timeout, this, &QtTetrisController::onTimeout);
  connect(&view_, &QtTetrisView::keyPressed, this,
          &QtTetrisController::handleKeyPress);
  connect(&view_, &QtTetrisView::startGame, this,
          &QtTetrisController::startGame);
  connect(&view_, &QtTetrisView::keyReleased, this,
          &QtTetrisController::handleKeyRelease);
  connect(&view_, &QtTetrisView::restartRequested, this,
          &QtTetrisController::handleRestartRequest);
}

TetrisDrawData QtTetrisController::get_data_from_model(TetrisModel& model_) {
  TetrisDrawData data;
  data.field = model_.GetField();
  data.currentFigure = model_.GetCurrentFigure();
  data.nextFigure = model_.GetNextFigure();
  data.figurePos = model_.GetFigurePosition();
  data.score = model_.GetScore();
  data.highScore = model_.GetHighScore();
  data.level = model_.GetLevel();
  data.gameOver = model_.IsGameOver();
  data.paused = paused_;
  return data;
}

// сердце игры
void QtTetrisController::onTimeout() {
  model_.Tick();
  refresh_timer();
  view_.draw(get_data_from_model(model_));

  if (model_.IsGameOver()) {
    timer_.stop();
    save_high_score(model_.GetHighScore(), 1);
    // Ждём нажатия клавиши — сигнал будет из keyPressEvent
  }
}

void QtTetrisController::handleKeyPress(QKeyEvent* event) {
  if (model_.IsGameOver()) {
    model_.ResetGame();
    timer_.start(10);
    return;
  }

  if (event->key() == Qt::Key_Escape) {
    paused_ = !paused_;
    if (paused_) {
      view_.draw(get_data_from_model(model_));
      timer_.stop();
    } else
      timer_.start(500);
    return;
  }

  if (paused_) return;

  switch (event->key()) {
    case Qt::Key_Left:
      model_.Update(TetrisModel::MOVE_LEFT);
      break;
    case Qt::Key_Right:
      model_.Update(TetrisModel::MOVE_RIGHT);
      break;
    case Qt::Key_Down:
      model_.Update(TetrisModel::MOVE_DOWN);
      break;
    case Qt::Key_Up:
    case Qt::Key_Space:
      model_.Update(TetrisModel::ROTATE);
      break;
    case Qt::Key_Q:
      model_.Update(TetrisModel::QUIT);
      break;
    default:
      break;
  }

  onTimeout();
}

void QtTetrisController::handleKeyRelease(QKeyEvent* event) { Q_UNUSED(event); }

void QtTetrisController::handleRestartRequest() {
  emit view_.gameOver();  // теперь можно закрыть окно и вернуться в меню
}

void QtTetrisController::refresh_timer() {
  if (timer_.isActive()) {
    timer_.stop();
  }
  timer_.start(model_.GetDelay());
}

void QtTetrisController::startGame() {
  model_.ResetGame();
  timer_.start(model_.GetDelay());
}
}  // namespace s21
