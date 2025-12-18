#include "s21_tetris_game_core.h"

bool calculate(Tetris_Game* tetris_game) {
  bool state_changed = false;
  if (tetris_game->ticks_left <= 0) {
    tetris_game->ticks_left = tetris_game->ticks;
    moveFigureDown(tetris_game);
    if (collision(tetris_game)) {
      moveFigureUp(tetris_game);
      plant_figure(tetris_game);
      int lines = erasse_lines(tetris_game);
      counting_score_and_level(tetris_game, lines);
      drop_new_figure(tetris_game);
      if (collision(tetris_game)) {
        tetris_game->playing = GAME_OVER;
        state_changed = true;  // Произошло изменение состояния
      }
      state_changed = true;  // Произошло изменение состояния
    }
    state_changed = true;  // Произошло изменение состояния
  }
  execute_player_command(tetris_game->player->action, tetris_game,
                         &state_changed);
  tetris_game->ticks_left--;
  return state_changed;
}

void counting_score_and_level(Tetris_Game* tetris_game, int lines) {
  tetris_game->score += (lines == 1   ? score_for_1_line
                         : lines == 2 ? 300
                         : lines == 3 ? 700
                         : lines == 4 ? 1500
                                      : 0);
  tetris_game->level =
      tetris_game->level >= 10 ? 10 : tetris_game->score / 600 + 1;
}

void execute_player_command(int action, Tetris_Game* tetris_game,
                            bool* state_changed) {
  switch (action) {
    case PLAYER_RIGHT:
      *state_changed = true;  // Произошло изменение состояния
      moveFigureRight(tetris_game);
      if (collision(tetris_game)) {
        moveFigureLeft(tetris_game);
      }
      break;
    case PLAYER_LEFT:
      *state_changed = true;  // Произошло изменение состояния
      moveFigureLeft(tetris_game);
      if (collision(tetris_game)) {
        moveFigureRight(tetris_game);
      }
      break;
    case PLAYER_DOWN:
      *state_changed = true;  // Произошло изменение состояния
      moveFigureDown(tetris_game);
      if (collision(tetris_game)) {
        moveFigureUp(tetris_game);
      }
      break;
    case PLAYER_UP: {
      *state_changed = true;  // Произошло изменение состояния
      Tetris_Figure* t = rotTetFigure(tetris_game);
      Tetris_Figure* told = tetris_game->figure;
      tetris_game->figure = t;
      if (collision(tetris_game)) {
        tetris_game->figure = told;
        free_tetris_figure(t);
        t = NULL;
      } else {
        free_tetris_figure(told);
        told = NULL;
      }
    } break;
    case PLAYER_QUIT:
      *state_changed = true;  // Произошло изменение состояния
      tetris_game->playing = GAME_OVER;
      break;
    case PLAYER_PAUSE:
      *state_changed = true;  // Произошло изменение состояния
      tetris_game->playing = PLAYING;
      break;
    case PLAYER_NOP:
    default:
      break;
  }
}
