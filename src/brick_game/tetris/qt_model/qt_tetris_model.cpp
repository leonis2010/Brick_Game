#include "qt_tetris_model.h"

namespace s21 {

TetrisModel::TetrisModel() {
  srand(time(nullptr));
  game_ = create_memory_game(10, 20, 4, 7, figures_template);
  game_->player = new Tetris_Player();
  game_->player->action = PLAYER_NOP;
  game_->high_score = LoadHighScore();
  drop_new_figure(game_);
}

TetrisModel::~TetrisModel() {
  if (game_->player) {
    delete game_->player;
  }
  free_memory_game(game_);
}

void TetrisModel::StartGame() {
  reset_game(game_);
  drop_new_figure(game_);
}

void TetrisModel::ResetGame() {
  reset_game(game_);
  drop_new_figure(game_);
  SaveHighScore(game_->high_score);
}

bool TetrisModel::Update(Action action) {
  bool state_changed = false;

  switch (action) {
    case MOVE_LEFT:
      moveFigureLeft(game_);
      if (collision(game_)) moveFigureRight(game_);
      state_changed = true;
      break;

    case MOVE_RIGHT:
      moveFigureRight(game_);
      if (collision(game_)) moveFigureLeft(game_);
      state_changed = true;
      break;

    case MOVE_DOWN:
      moveFigureDown(game_);
      if (collision(game_)) moveFigureUp(game_);
      state_changed = true;
      break;

    case ROTATE: {
      Tetris_Figure* rotated = rotTetFigure(game_);
      Tetris_Figure* old = game_->figure;
      game_->figure = rotated;
      if (collision(game_)) {
        game_->figure = old;
        free_tetris_figure(rotated);
      } else {
        free_tetris_figure(old);
      }
      state_changed = true;
      break;
    }

    case PAUSE:
      // Это лучше управлять в контроллере
      state_changed = true;
      break;

    case QUIT:
      game_->playing = GAME_OVER;
      state_changed = true;
      break;

    default:
      break;
  }

  return state_changed;
}

bool TetrisModel::Tick() {
  bool state_changed = calculate(game_);
  if (state_changed) {
    print_high_score(game_);
  }
  return state_changed;
}

int TetrisModel::GetScore() const { return game_->score; }
int TetrisModel::GetHighScore() const { return game_->high_score; }
int TetrisModel::GetLevel() const { return game_->level; }

bool TetrisModel::IsGameOver() const { return game_->playing == GAME_OVER; }
bool TetrisModel::IsPaused() const { return false; }  // TODO: add pause logic

std::vector<std::vector<int>> TetrisModel::GetField() const {
  std::vector<std::vector<int>> field(game_->field->height,
                                      std::vector<int>(game_->field->width));
  for (int i = 0; i < game_->field->height; ++i)
    for (int j = 0; j < game_->field->width; ++j)
      field[i][j] = game_->field->blocks[i * game_->field->width + j].b;
  return field;
}

std::pair<int, int> TetrisModel::GetFigurePosition() const {
  return {game_->figure->y, game_->figure->x};
}

std::vector<std::vector<int>> TetrisModel::GetCurrentFigure() const {
  std::vector<std::vector<int>> figure(game_->figure->size,
                                       std::vector<int>(game_->figure->size));
  for (int i = 0; i < game_->figure->size; ++i)
    for (int j = 0; j < game_->figure->size; ++j)
      figure[i][j] = game_->figure->blocks[i * game_->figure->size + j].b;
  return figure;
}

std::vector<std::vector<int>> TetrisModel::GetNextFigure() const {
  std::vector<std::vector<int>> next(
      game_->next_figure->size, std::vector<int>(game_->next_figure->size));
  for (int i = 0; i < game_->next_figure->size; ++i)
    for (int j = 0; j < game_->next_figure->size; ++j)
      next[i][j] =
          game_->next_figure->blocks[i * game_->next_figure->size + j].b;
  return next;
}

int TetrisModel::LoadHighScore() {
  return load_high_score(1);  // 1 - flag for tetris
}

void TetrisModel::SaveHighScore(int score) { save_high_score(score, 1); }

int TetrisModel::GetDelay() const {
  int base_delay_ns = 33000000;       // 33 мс
  int reduction_per_level = 3000000;  // 3 мс
  long long level_delay =
      base_delay_ns - ((long long)game_->level) * reduction_per_level;

  if (level_delay < 4500000) {  // 4.5 мс
    level_delay = 4500000;
  }

  // Переводим наносекунды в миллисекунды
  return level_delay / 1000000;
}

}  // namespace s21
