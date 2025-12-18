#include "../tetris/model/s21_tetris_cli.h"
#ifdef TEST_MODE
#else
void waiting_Enter() {
  int ch;
  while ((ch = getch()) != KEY_ENTER && ch != '\n') {
  }
}
#endif