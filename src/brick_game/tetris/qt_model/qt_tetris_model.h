#ifndef TETRIS_MODEL_H
#define TETRIS_MODEL_H

#include <cstdlib>
#include <utility>
#include <vector>

extern "C" {
#include "../../../brick_game/tetris/model/s21_tetris_game_core.h"
}

namespace s21 {

class TetrisModel {
 public:
  enum Direction { LEFT, RIGHT, DOWN, UP };
  enum Action {
    NOP = 0,
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_DOWN,
    ROTATE,
    PAUSE,
    QUIT
  };

  TetrisModel();
  ~TetrisModel();

  void StartGame();
  void ResetGame();
  bool Update(Action action);
  bool Tick();

  int GetScore() const;
  int GetHighScore() const;
  int GetLevel() const;
  bool IsGameOver() const;
  bool IsPaused() const;
  int GetDelay() const;

  std::vector<std::vector<int>> GetField() const;
  std::pair<int, int> GetFigurePosition() const;
  std::vector<std::vector<int>> GetCurrentFigure() const;
  std::vector<std::vector<int>> GetNextFigure() const;
  Tetris_Game* game_;

 private:
  int LoadHighScore();
  void SaveHighScore(int score);
};

}  // namespace s21

#endif  // TETRIS_MODEL_H
