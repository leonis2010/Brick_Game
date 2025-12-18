#include "../model/s21_tetris_cli.h"

void game_over(Tetris_Game* tetris_game, WINDOW* win_game,
               int (*input_func)(void)) {
  curs_set(0);
  cli_game_over(tetris_game, win_game);
  int character;

  int enter = 10;
  int esc = 27;
  while ((character = input_func()) != 88) {
    if (character == esc) {
      tetris_game->playing = GAME_OVER;
      break;
    }
    if (character == enter) {
      reset_game(tetris_game);
      break;
    }
  }
}
#ifdef TEST_MODE
// Заглушка для тестирования
int input_func(void) {
  return 10;  // Возвращаем фиксированное значение, например, Enter
}
#else
int input_func(void) { return getch(); }
#endif