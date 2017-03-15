#include "selector.h"
#include <QApplication>
#include<QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString strPath = QCoreApplication::applicationDirPath();
    //qDebug()<<strPath;
    QString strCssFile = strPath + "/qss/skin.qss";
    QFile fCss(strCssFile);
    if( !fCss.open(QFile::ReadOnly))
    {
            //qDebug("css File %s load false",strCssFile);

    }
    QString strCssContent(fCss.readAll());
    a.setStyleSheet(strCssContent);
    fCss.close();

    Selector w;
    w.show();

    return a.exec();
}
