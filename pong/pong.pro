TEMPLATE += app
QT += gui declarative
QMAKE_CXXFLAGS += -std=c++11

SOURCES += pong.cpp \
src/window.cpp \
src/game.cpp \
src/player.cpp \
src/ball.cpp \
src/tcp/client.cpp \
src/tcp/server.cpp \
src/tcp/tcpstream.cpp \
src/tcp/tcpacceptor.cpp \
src/tcp/tcpconnector.cpp 

HEADERS += src/window.h \
src/window-sp.h \
src/game.h \
src/player.h \
src/ball.h \
src/tcp/client.h \
src/tcp/server.h \
src/tcp/tcpstream.h \
src/tcp/tcpacceptor.h \
src/tcp/tcpconnector.h 
