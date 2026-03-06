#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gui_manager.h"

namespace LunarRoverUI {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onManualOverridesRequested();

private:
    GUIManager *m_guiManager;
};

}

#endif
