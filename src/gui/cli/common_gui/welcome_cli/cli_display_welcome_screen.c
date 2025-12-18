#include "../../../../brick_game/tetris/model/s21_tetris_cli.h"
#ifdef TEST_MODE
void display_welcome_screen(int high_score, WINDOW* win_game,
                            WINDOW* win_next_figure, WINDOW* win_score_level,
                            WINDOW* win_high_score, int brick_game) {
  (void)high_score;
  (void)win_game;
  (void)win_next_figure;
  (void)win_score_level;
  (void)win_high_score;
  (void)brick_game;
}
#else
void display_welcome_screen(int high_score, WINDOW* win_game,
                            WINDOW* win_next_figure, WINDOW* win_score_level,
                            WINDOW* win_high_score, int brick_game) {
  refresh();
  initialization_of_colors();
  int max_y, max_x;
  getmaxyx(win_game, max_y, max_x);

  const char* messages_tetris[] = {
      " ", "[][][][]", "[]",          "[]",         "[]", " ",
      " ", " ",        "Press Enter", " to start",  " ",  " ",
      " ", " ",        " ",           "High Score", " ",  "====="};
  const char* messages_snake[] = {
      " ",          "  [][]  ", "[]    []", "  []    ",    "    []  ",
      "[]    []",   "  [][]  ", " ",        "Press Enter", " to start",
      " ",          " ",        " ",        " ",           " ",
      "High Score", " ",        "====="};
  const char** messages;
  int number_of_elements_array = 0;
  switch (brick_game) {
    case 1:
      messages = messages_tetris;
      number_of_elements_array = sizeof(messages_tetris) / sizeof(messages[0]);
      break;
    case 2:
      messages = messages_snake;
      number_of_elements_array = sizeof(messages_snake) / sizeof(messages[0]);
      break;
    default:
      break;
  }
  int start_x_messages[number_of_elements_array];
  int start_y = (max_y - number_of_elements_array) / 2;
  int number = high_score;
  int length_number = 0;
  if (number == 0)
    length_number = 1;
  else
    length_number = (int)log10(number) + 1;
  for (int message_index = 0; message_index < number_of_elements_array;
       message_index++) {
    start_x_messages[message_index] =
        (max_x - (int)strlen(messages[message_index])) / 2;
    if (message_index == number_of_elements_array - 1) {
      start_x_messages[message_index] =
          (max_x - (int)strlen(messages[message_index]) * 2 - length_number) /
          2;
      wattron(win_game, COLOR_PAIR(11));
      mvwprintw(win_game, start_y + message_index,
                start_x_messages[message_index], "%s %d %s",
                messages[message_index], number, "=====");
      wattroff(win_game, COLOR_PAIR(11));
    } else {
      wattron(win_game, COLOR_PAIR(10));
      mvwprintw(win_game, start_y + message_index,
                start_x_messages[message_index], "%s", messages[message_index]);
      wattroff(win_game, COLOR_PAIR(10));
    }
  }

  box(win_next_figure, 0, 0);
  box(win_game, 0, 0);
  box(win_score_level, 0, 0);
  box(win_high_score, 0, 0);
  wnoutrefresh(win_next_figure);
  wnoutrefresh(win_game);
  wnoutrefresh(win_score_level);
  wnoutrefresh(win_high_score);
  curs_set(0);

  doupdate();
}
#endif