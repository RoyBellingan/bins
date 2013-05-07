#include "bins.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bins w;
    w.show();
    
    return a.exec();
}
