#include <QApplication>

#include "qt_choose_game_view.h"

// Подключаем главные окна игр
#include "../snake/main_window_snake.h"
#include "../tetris/main_window_tetris.h"

int main(int argc, char* argv[]) {
  QApplication app(argc, argv);

  QtChooseGameView chooseView;
  chooseView.resize(400, 300);  // Размер меню выбора

  QObject::connect(
      &chooseView, &QtChooseGameView::gameSelected, [&](int gameIndex) {
        chooseView.hide();

        if (gameIndex == 0) {  // Тетрис
          s21::MainWindowTetris* window = new s21::MainWindowTetris();
          window->show();
          // Подключаем сигнал для возврата к меню
          QObject::connect(window, &s21::MainWindowTetris::restartSelection,
                           [window, &chooseView]() {
                             chooseView.show();
                             window->setAttribute(Qt::WA_DeleteOnClose);
                             window->close();
                           });

        } else if (gameIndex == 1) {  // Змейка
          s21::MainWindowSnake* window = new s21::MainWindowSnake();
          window->show();
          // Подключаем сигнал для возврата к меню
          QObject::connect(window, &s21::MainWindowSnake::restartSelection,
                           [window, &chooseView]() {
                             chooseView.show();
                             window->setAttribute(Qt::WA_DeleteOnClose);
                             window->close();
                           });
        }
      });

  chooseView.show();
  return app.exec();
}
