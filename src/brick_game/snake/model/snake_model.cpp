#include "snake_model.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>
extern "C" {
#include "../../common/high_score/high_score.h"
}

namespace s21 {
const std::string SnakeModel::HIGH_SCORE_FILE = "snake_high_score.txt";
SnakeModel::SnakeModel()
    : direction_(DOWN),
      game_over_(false),
      win_(false),
      score_(0),
      level_(1),
      speed_delay_(SPEED_DELAY),
      boost_(false),
      start_screen_(true) {
  high_score_ = load_high_score(2);  // Загружаем рекорд из Си
  int center_x = WIDTH / 2;
  int start_y = HEIGHT / 3;
  for (int i = 3; i >= 0; --i) {
    snake_.emplace_back(start_y + i, center_x);
  }
  GenerateFood();
}

void SnakeModel::Move() {
  std::pair<int, int> head = snake_.front();
  switch (direction_) {
    case UP:
      head.first--;
      break;
    case DOWN:
      head.first++;
      break;
    case LEFT:
      head.second--;
      break;
    case RIGHT:
      head.second++;
      break;
  }
  if (head.first < 0 || head.first >= HEIGHT || head.second < 0 ||
      head.second >= WIDTH ||
      std::find(snake_.begin(), snake_.end(), head) != snake_.end()) {
    game_over_ = true;
    win_ = false;
    return;
  }

  snake_.push_front(head);

  if (head == food_) {
    score_ += SCORE;
    if (score_ > high_score_) high_score_ = score_;
    if (score_ >= 200) {
      win_ = true;
      game_over_ = true;
    }
    UpdateLevel();
    GenerateFood();
  } else {
    snake_.pop_back();
  }
}

bool SnakeModel::IsStartScreen() const { return start_screen_; }
void SnakeModel::SetStartScreen(bool state) { start_screen_ = state; }
bool SnakeModel::IsWin() const { return win_; }
void SnakeModel::SetDirection(Direction dir) { direction_ = dir; }
Direction SnakeModel::GetDirection() const { return direction_; }
void SnakeModel::SetGameOver(bool game_over) { game_over_ = game_over; }
bool SnakeModel::IsGameOver() const { return game_over_; }
bool SnakeModel::IsPause() const { return pause_; }
void SnakeModel::TogglePause() { pause_ = !pause_; }
int SnakeModel::GetScore() const { return score_; }
int SnakeModel::GetLevel() const { return level_; }
int SnakeModel::GetHighScore() const { return high_score_; }

const std::deque<std::pair<int, int>>& SnakeModel::GetSnake() const {
  return snake_;
}

const std::pair<int, int>& SnakeModel::GetFood() const { return food_; }
void SnakeModel::SetBoost(bool isActive) { boost_ = isActive; }

int SnakeModel::GetDelay() const {
  return boost_ ? speed_delay_ / 2.5 : speed_delay_;
}

void SnakeModel::UpdateLevel() {
  level_ = std::min(10, score_ / 5 + 1);
  speed_delay_ = SPEED_DELAY - (level_ - 1) * 15;
}

void SnakeModel::GenerateFood() {
  int x, y;
  do {
    x = rand() % WIDTH;
    y = rand() % HEIGHT;
  } while (std::find(snake_.begin(), snake_.end(), std::make_pair(y, x)) !=
           snake_.end());
  food_ = std::make_pair(y, x);
}

void SnakeModel::Reset() {
  snake_.clear();
  // Устанавливаем начальную позицию
  int center_x = WIDTH / 2;
  int start_y = HEIGHT / 3;
  for (int i = 3; i >= 0; --i) {
    snake_.emplace_back(start_y + i, center_x);
  }

  direction_ = DOWN;
  score_ = 0;
  level_ = 1;
  speed_delay_ = SPEED_DELAY;
  boost_ = false;
  game_over_ = false;

  // Новое яблоко
  GenerateFood();
  UpdateLevel();
}

// Только для тестов следующие функции
void SnakeModel::PlaceFoodInFront() {
  auto head = snake_.front();
  switch (direction_) {
    case UP:
      food_ = std::make_pair(head.first - 1, head.second);
      break;
    case DOWN:
      food_ = std::make_pair(head.first + 1, head.second);
      break;
    case LEFT:
      food_ = std::make_pair(head.first, head.second - 1);
      break;
    case RIGHT:
      food_ = std::make_pair(head.first, head.second + 1);
      break;
  }
}
void SnakeModel::FeedSnake(int bites) {
  for (int i = 0; i < bites; ++i) {
    PlaceFoodInFront();
    Move();
  }
}

bool SnakeModel::GetBoost() const { return boost_; }

}  // namespace s21
