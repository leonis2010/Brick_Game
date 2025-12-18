#include "../model/s21_tetris_cli.h"
void buttons_reaction(int ch, Tetris_Game *tetris_game) {
  switch (ch) {
    case ERR:
      tetris_game->player->action = PLAYER_NOP;
      break;
      // 32 - Пробел поворот фигуры
    case 32:
      tetris_game->player->action = PLAYER_UP;
      break;
    case 's':
    case KEY_DOWN:
      tetris_game->player->action = PLAYER_DOWN;
      break;
    case 'a':
    case KEY_LEFT:
      tetris_game->player->action = PLAYER_LEFT;
      break;
    case 'd':
    case KEY_RIGHT:
      tetris_game->player->action = PLAYER_RIGHT;
      break;
      // 81 - 'q'
      // 113 - 'Q'
    case 81:
    case 113:
      tetris_game->player->action = PLAYER_QUIT;
      tetris_game->playing = GAME_OVER;
      break;
      // 27 - ESC
    case 27:
      tetris_game->player->action = PLAYER_PAUSE;
      break;
    default:
      tetris_game->player->action = PLAYER_NOP;
      break;
  }
}
