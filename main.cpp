#include <QApplication>
#include "connection.h"
#include "bins.h"

int main(int argc, char *argv[])
{
    if (!createConnection())
        return 1;///@todo qualcosa
    QApplication a(argc, argv);
    bins w;
    w.show();

    return a.exec();
}
