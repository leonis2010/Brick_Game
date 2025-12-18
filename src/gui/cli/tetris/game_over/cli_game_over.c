#include "../../../../brick_game/tetris/model/s21_tetris_cli.h"
#ifdef TEST_MODE
void cli_game_over(Tetris_Game* tetris_game, WINDOW* win_game) {
  (void)tetris_game;
  (void)win_game;
}
#else
void cli_game_over(Tetris_Game* tetris_game, WINDOW* win_game) {
  int max_y, max_x;
  getmaxyx(win_game, max_y, max_x);  // Получаем размеры окна
  const char* messages[] = {"Congratulations!!",
                            " ",
                            "You have ",
                            "a new record!!",
                            " ",
                            "Record",
                            "",
                            "Game over!",
                            "Score: ",
                            "Level: ",
                            "Again?",
                            "(Enter/Esc)"};
  int number_of_elements_array = sizeof(messages) / sizeof(messages[0]);
  int start_x_messages[number_of_elements_array];
  int start_y = (max_y - number_of_elements_array + 2) / 2;
  int number = 0;
  int length_number = 0;

  int old_high_score = load_high_score(1);
  wattron(win_game, COLOR_PAIR(PAUSE_COLOR_PAIR));

  for (int message_index = 0; message_index < number_of_elements_array;
       message_index++) {
    if (tetris_game->score > old_high_score && tetris_game->score > 0) {
      if (message_index == 7) message_index = message_index + 2;
    } else {
      if (message_index == 0) {
        message_index = message_index + number_of_elements_array - 5;
        start_y = start_y - 5;
      }
    }
    start_x_messages[message_index] =
        (max_x - (int)strlen(messages[message_index])) / 2;
    number = (message_index == 6)   ? tetris_game->high_score
             : (message_index == 8) ? tetris_game->score
             : (message_index == 9) ? tetris_game->level
                                    : number;
    if (number == 0)
      length_number = 1;
    else
      length_number = (int)log10(number) + 1;
    if (message_index == number_of_elements_array - 6 ||
        message_index == number_of_elements_array - 4 ||
        message_index == number_of_elements_array - 3) {
      start_x_messages[message_index] =
          (max_x - (int)strlen(messages[message_index]) - length_number) / 2;
      mvwprintw(win_game, start_y + message_index,
                start_x_messages[message_index], "%s %d",
                messages[message_index], number);
    } else
      mvwprintw(win_game, start_y + message_index,
                start_x_messages[message_index], "%s", messages[message_index]);
  }
  wattroff(win_game, COLOR_PAIR(PAUSE_COLOR_PAIR));
  wrefresh(win_game);
}
#endif