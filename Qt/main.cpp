#include <QApplication>
#include <QMainWindow>
#include <QBackingStore>
//#include <QDebug>
#include "MainWindow.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setEffectEnabled(Qt::UI_AnimateMenu,false);
    app.setEffectEnabled(Qt::UI_AnimateCombo,false);
    app.setEffectEnabled(Qt::UI_AnimateToolBox, false);

    //qputenv("QSG_RENDER_LOOP", QByteArray("basic"));

    MainWindow window;
    window.setWindowTitle(QString::fromUtf8("Dynamic Interaction Graph"));
    window.Execute();

    int ret = app.exec();

    return ret;

}
