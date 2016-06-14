#include "src/window.h"

//NOTE: copy constructors are disabled in the Qt Object Model; must use pointers

int main(int argc, char **argv)
{
 QApplication app (argc, argv);
 Window window;
 // place players, ball on window
 window.show();
 return app.exec();
}
