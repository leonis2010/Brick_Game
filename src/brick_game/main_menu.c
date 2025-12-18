#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tetris/model/s21_tetris_cli.h"

// Объявления функций из других файлов
extern void tetris_main();
extern void snake_main();

void StartTetrisGame() {
  endwin();
  tetris_main();
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
}

void StartSnakeGame() {
  endwin();
  snake_main();
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
}

int DisplayGameSelectionMenu() {
  initscr();
  noecho();
  cbreak();
  keypad(stdscr, TRUE);
  curs_set(0);
  initialization_of_colors();

  // Создаем окна
  WINDOW* win_game = NULL;
  WINDOW* win_next_figure = NULL;
  WINDOW* win_score_level = NULL;
  WINDOW* win_high_score = NULL;
  if (cli_create_frames_for_game(&win_game, &win_next_figure, &win_score_level,
                                 &win_high_score) != 0) {
    endwin();
    return -1;
  }

  const char* choices[] = {"Play Tetris", "Play Snake", "Exit"};
  int num_choices = sizeof(choices) / sizeof(choices[0]);
  int current_choice = 0;  // Индекс текущего выбранного пункта
  refresh();
  while (1) {
    // Очищаем и рисуем рамки для всех окон
    werase(win_game);
    box(win_game, 0, 0);
    werase(win_next_figure);
    box(win_next_figure, 0, 0);
    werase(win_score_level);
    box(win_score_level, 0, 0);
    werase(win_high_score);
    box(win_high_score, 0, 0);

    // Заголовок в верхнем окне
    wattron(win_next_figure, COLOR_PAIR(10));
    mvwprintw(win_next_figure, 2, 9, "Menu");
    mvwprintw(win_next_figure, 3, 6, "Brick Game");
    wattroff(win_game, COLOR_PAIR(10));
    // Рекорд в нижнем правом окне
    mvwprintw(win_score_level, 1, 1, "Tetris High Sc: %d", load_high_score(1));
    mvwprintw(win_score_level, 2, 1, "Snake  High Sc: %d", load_high_score(2));
    // Меню в игровом поле
    int max_x = 22;
    mvwprintw(win_game, 1, (max_x - strlen("Use arrow keys:")) / 2,
              "Use arrow keys:");
    for (int i = 0; i < num_choices; ++i) {
      int y = 7 + i * 2;
      if (i == current_choice) {
        wattron(win_game, COLOR_PAIR(11));
        mvwprintw(win_game, y, (max_x - strlen(choices[i])) / 2, "%s",
                  choices[i]);
        wattroff(win_game, COLOR_PAIR(11));
      } else {
        mvwprintw(win_game, y, (max_x - strlen(choices[i])) / 2, "%s",
                  choices[i]);
      }
    }

    // Обновляем все окна
    wnoutrefresh(win_game);
    wnoutrefresh(win_next_figure);
    wnoutrefresh(win_score_level);
    wnoutrefresh(win_high_score);
    doupdate();

    // Обработка ввода
    int ch = getch();
    switch (ch) {
      case KEY_UP:
        if (current_choice > 0) {
          current_choice--;
        }
        break;
      case KEY_DOWN:
        if (current_choice < num_choices - 1) {
          current_choice++;
        }
        break;
      case '\n':  // Клавиша Enter
        delwin(win_game);
        delwin(win_next_figure);
        delwin(win_score_level);
        delwin(win_high_score);
        endwin();
        return current_choice;  // Возвращаем выбранный индекс
      default:
        break;
    }
  }
}

int main() {
  while (1) {
    int choice = DisplayGameSelectionMenu();

    switch (choice) {
      case 0:  // Play Tetris
        StartTetrisGame();
        break;
      case 1:  // Play Snake
        StartSnakeGame();
        break;
      case 2:      // Exit
        return 0;  // Завершаем программу
      default:
        break;
    }
  }

  return 0;
}