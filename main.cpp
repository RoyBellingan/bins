#include <QApplication>
#include "connection.h"
#include "bins.h"

#define null 0
bins* bins::instance_ptr = null;

int main(int argc, char *argv[])
{
    if (!createConnection())
        return 1;///@todo qualcosa
    QApplication a(argc, argv);
    bins* w=bins::get_instance ();
    w->show();

    return a.exec();
}
