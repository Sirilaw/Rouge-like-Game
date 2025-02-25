#include "VampireSurvivors.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VampireSurvivors w;
    w.show();
    return a.exec();
}
