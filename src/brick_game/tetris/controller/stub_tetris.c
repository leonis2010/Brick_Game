#include "../../common/high_score/high_score.h"
#include "../model/s21_tetris_cli.h"
#ifdef TEST_MODE
#else

void tetris_main() {
  printf(
      "\n\n\n                       Я запустился!!\nНо у вас слишком маленький "
      "экранчик, я не помещаюсь :(\n\n\n");
  int error = 0;
  srand(time(NULL));
  struct timespec sp_start, sp_end, ts2 = {0, 0};

  // initscr();
  start_color();
  cbreak();  // не перехватывать нажатия клавиш
  setenv("TERM", "xterm-256color", 1);
  noecho();              // не печатать нажатые клавиши
  keypad(stdscr, TRUE);  // для работы стрелок клавиатуры
  nodelay(stdscr, TRUE);   // не ждать нажатия клавиши
  scrollok(stdscr, TRUE);  // отключение прокрутки окна

  int field_width = 10;
  int field_height = 20;
  int figures_size = 4;
  int number_of_figures = 7;
  Tetris_Game *tetris_game =
      create_memory_game(field_width, field_height, figures_size,
                         number_of_figures, figures_template);
  Tetris_Player player;
  player.action = PLAYER_NOP;
  tetris_game->player = &player;
  int flag_one_for_tetris = 1;
  int high_score = load_high_score(flag_one_for_tetris);
  tetris_game->high_score = high_score;
  drop_new_figure(tetris_game);
  WINDOW *win_game = NULL;
  WINDOW *win_next_figure = NULL;
  WINDOW *win_score_level = NULL;
  WINDOW *win_high_score = NULL;
  error = cli_create_frames_for_game(&win_game, &win_next_figure,
                                     &win_score_level, &win_high_score);
  if (error) {
    endwin();
    return;
  }
  display_welcome_screen(high_score, win_game, win_next_figure, win_score_level,
                         win_high_score, 1);
  waiting_Enter();
  int button = 0;
  bool paused = false;

  while (tetris_game->playing != GAME_OVER) {
    clock_gettime(CLOCK_MONOTONIC, &sp_start);
    button = getch();
    buttons_reaction(button, tetris_game);
    pause_processing(tetris_game, &paused, win_game);
    if (paused) continue;
    bool game_state_changed = calculate(tetris_game);
    if (game_state_changed) {
      print_high_score(tetris_game);
      cli_print_game(tetris_game, win_game, win_next_figure, win_score_level,
                     win_high_score);
      if (tetris_game->playing == GAME_OVER) {
        game_over(tetris_game, win_game, input_func);
        save_high_score(tetris_game->high_score, flag_one_for_tetris);
      }
    }

    clock_gettime(CLOCK_MONOTONIC, &sp_end);
    speed_from_level(*tetris_game, sp_start, sp_end, &ts2);
  }
  delwin(win_game);
  delwin(win_next_figure);
  delwin(win_score_level);
  delwin(win_high_score);
  endwin();
  free_memory_game(tetris_game);
  return;
}
#endif