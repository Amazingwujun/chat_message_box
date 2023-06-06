#include <QApplication>
#include <QListWidget>
#include "chatwidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ChatWidget w;
    w.resize(1190, 1200);
    w.show();
    return QApplication::exec();
}