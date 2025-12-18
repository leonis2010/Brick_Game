# tetris_gui.pro

QT += core gui widgets

TARGET = TetrisGame
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++20

# Отключаем устаревшие предупреждения Qt
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000
CONFIG += sdk_no_version_check

# Источники GUI
SOURCES += \
        qt_tetris_view.cpp \
        main_window.cpp \
        main.cpp


HEADERS += \
        qt_tetris_view.h \
        main_window.h

# Источники из модели и контроллера
SOURCES += \
        ../../../brick_game/common/high_score/load_high_score.c \
        ../../../brick_game/common/high_score/save_high_score.c \
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
        ../../../brick_game/tetris/model/s21_tetris_game_core.h \
        ../../../brick_game/common/high_score/high_score.h

# Ресурсы (например, изображения)
RESOURCES += resource_tetris.qrc
