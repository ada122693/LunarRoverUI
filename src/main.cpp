#include <QApplication>
#include <QFile>
#include <QTextStream>
#include "mainwindow.h"

QString loadStyleSheet(const QString& filename)
{
    QFile file(filename);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        return QString();
    }

    QTextStream stream(&file);
    QString stylesheet = stream.readAll();
    file.close();
    return stylesheet;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // load stylesheet
    QString stylesheet = loadStyleSheet(":/styles.qss");
    if (!stylesheet.isEmpty()) {
        app.setStyleSheet(stylesheet);
    }

    LunarRoverUI::MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
