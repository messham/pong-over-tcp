TEMPLATE += app
QT += gui declarative

SOURCES += pong.cpp \
src/window.cpp \
src/game.cpp \
src/player.cpp \
src/ball.cpp

HEADERS += src/qtlibs.h \
src/window.h \
src/game.h \
src/player.h \
src/ball.h
