#include <QApplication>
#include "src/window.h"

int main(int argc, char **argv)
{
 QApplication app (argc, argv);
 Window window;
 // place players, ball on window
 window.show();
 return app.exec();
}
