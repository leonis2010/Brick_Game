QT += core gui widgets

TARGET = GameLauncher
TEMPLATE = app

# --- Подключение заголовков ---
INCLUDEPATH += \
    ../tetris \
    ../snake \
    ../../../brick_game \
    ../../../brick_game/common/high_score \
    ../../../brick_game/tetris/model \
    ../../../brick_game/snake/model \
    ../../../brick_game/tetris/qt_controller \
    ../../../brick_game/snake/qt_controller \
    .

# --- Источники игр snake ---

SOURCES += \
    ../snake/main_window_snake.cpp \
        ../snake/qt_snake_view.cpp \

HEADERS += \
        ../snake/main_window_snake.h \
        ../snake/qt_snake_view.h

# Источники из библиотеки model common
SOURCES += \
        ../../../brick_game/snake/qt_controller/qt_snake_controller.cpp \
        ../../../brick_game/snake/model/snake_model.cpp

HEADERS += \
        ../../../brick_game/snake/qt_controller/qt_snake_controller.h \
        ../../../brick_game/snake/model/snake_model.h

RESOURCES += ../snake/resource.qrc


# --- Источники игр tetris ---

# Источники GUI
SOURCES += \
        ../tetris/main_window_tetris.cpp \
        ../tetris/qt_tetris_view.cpp


HEADERS += \
        ../tetris/main_window_tetris.h \
        ../tetris/qt_tetris_view.h

# Источники из модели и контроллера
SOURCES += \
        ../../../brick_game/tetris/qt_model/qt_tetris_model.cpp \
        ../../../brick_game/tetris/qt_controller/qt_tetris_controller.cpp \
        ../../../brick_game/tetris/model/calculate.c \
        ../../../brick_game/tetris/model/collision.c \
        ../../../brick_game/tetris/model/creating_memory_game_objects.c \
        ../../../brick_game/tetris/model/drop_new_figure.c \
        ../../../brick_game/tetris/model/templates.c \
        ../../../brick_game/tetris/model/free_memory/free_figure_bag.c \
        ../../../brick_game/tetris/model/free_memory/free_memory_game.c \
        ../../../brick_game/tetris/model/free_memory/free_tetris_field.c \
        ../../../brick_game/tetris/model/free_memory/free_tetris_figure.c\
        ../../../brick_game/tetris/model/free_memory/free_tetris_figures_template.c\
        ../../../brick_game/tetris/model/move_figure.c\
        ../../../brick_game/tetris/model/speed_from_level.c \
        ../../../brick_game/tetris/model/processing_figures_after_falling.c \
        ../../../brick_game/tetris/model/print_high_score.c\
        ../../../brick_game/tetris/model/reset_game.c

HEADERS += \
        ../../../brick_game/tetris/qt_model/qt_tetris_model.h \
        ../../../brick_game/tetris/qt_controller/qt_tetris_controller.h \
        ../../../brick_game/tetris/model/s21_tetris_game_core.h

# Ресурсы (изображения)
RESOURCES += ../tetris/resource_tetris.qrc


# --- Общие утилиты ---
SOURCES += \
    main.cpp \
    qt_choose_game_view.cpp \
    ../../../brick_game/common/high_score/load_high_score.c \
    ../../../brick_game/common/high_score/save_high_score.c

HEADERS += \
    ../../../brick_game/common/high_score/high_score.h \
    qt_choose_game_view.h


# --- SDK warning ---
CONFIG += sdk_no_version_check
