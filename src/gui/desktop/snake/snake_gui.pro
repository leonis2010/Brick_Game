# snake_gui.pro

QT += core gui widgets

TARGET = SnakeGame
TEMPLATE = app

# Указываем стандарт C++20
QMAKE_CXXFLAGS += -std=c++20

# Отключаем устаревшие предупреждения Qt
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000

# Источники
SOURCES += \
        qt_snake_view.cpp \
        main_window.cpp \
        main.cpp \


HEADERS += \
        qt_snake_view.h \
        main_window.h


# Источники из библиотеки model common
SOURCES += \
        ../../../brick_game/snake/qt_controller/qt_snake_controller.cpp \
        ../../../brick_game/snake/model/snake_model.cpp \
        ../../../brick_game/common/high_score/load_high_score.c \
        ../../../brick_game/common/high_score/save_high_score.c
HEADERS += \
        ../../../brick_game/snake/qt_controller/qt_snake_controller.h \
        ../../../brick_game/snake/model/snake_model.h \
        ../../../brick_game/common/high_score/high_score.h

RESOURCES += resource.qrc
