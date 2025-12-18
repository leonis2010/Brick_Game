#include "../../../../brick_game/tetris/model/s21_tetris_cli.h"
#ifdef TEST_MODE
void cli_print_pause(WINDOW* win_game) { (void)win_game; }
#else

void cli_print_pause(WINDOW* win_game) {
  wattron(win_game, COLOR_PAIR(PAUSE_COLOR_PAIR));
  int max_y, max_x;
  getmaxyx(win_game, max_y, max_x);  // Получаем размеры окна

  const char* messages[] = {"Game paused.", "Press 'Esc'", "to resume.", " ",
                            "Press Q to quit."};
  int number_of_elements_array = sizeof(messages) / sizeof(messages[0]);
  int start_x_messages[number_of_elements_array];
  int start_y = (max_y - number_of_elements_array) / 2;
  for (int message_index = 0; message_index < number_of_elements_array;
       message_index++) {
    start_x_messages[message_index] =
        (max_x - (int)strlen(messages[message_index])) / 2;
    mvwprintw(win_game, start_y + message_index,
              start_x_messages[message_index], "%s", messages[message_index]);
  }

  wattroff(win_game, COLOR_PAIR(PAUSE_COLOR_PAIR));
  wrefresh(win_game);
}
#endif