#include "manframe.h"
#include <DApplication>
#include <DWidgetUtil>

DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();
    DApplication a(argc, argv);
    ManFrame w;
    w.show();
    moveToCenter(&w);

    return a.exec();
}
