#include "miniword.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MiniWord w;
    w.show();

    return a.exec();
}
