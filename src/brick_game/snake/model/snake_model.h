#ifndef S21_SNAKE_MODEL_H
#define S21_SNAKE_MODEL_H
#include "../cli_controller/s21_cli_snake.h"

namespace s21 {

inline constexpr int WIDTH = 10;
inline constexpr int HEIGHT = 20;
inline constexpr int SPEED_DELAY = 400;
inline constexpr int SCORE = 1;

class SnakeModel {
 public:
  SnakeModel();
  void Move();
  void SetDirection(Direction dir);
  Direction GetDirection() const;
  void SetGameOver(bool game_over);
  bool IsGameOver() const;
  bool IsPause() const;
  void TogglePause();
  int GetScore() const;
  int GetLevel() const;
  int GetHighScore() const;
  const std::deque<std::pair<int, int>>& GetSnake() const;
  const std::pair<int, int>& GetFood() const;
  void SetBoost(bool boost);
  int GetDelay() const;
  void Reset();
  bool IsWin() const;
  bool IsStartScreen() const;
  void SetStartScreen(bool state);
  void PlaceFoodInFront();
  void FeedSnake(int bites);
  bool GetBoost() const;

 private:
  std::deque<std::pair<int, int>> snake_;
  std::pair<int, int> food_;
  Direction direction_;
  bool game_over_;
  bool win_;
  int score_;
  int high_score_;
  int level_;
  int speed_delay_;
  bool boost_;
  bool pause_ = false;
  static const std::string HIGH_SCORE_FILE;
  bool start_screen_;

  void UpdateLevel();
  void GenerateFood();
};

}  // namespace s21

#endif  // S21_SNAKE_MODEL_H
