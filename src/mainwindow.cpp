#include "mainwindow.h"

namespace LunarRoverUI {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Lunar Rover UI"));
    resize(800, 700);

    m_guiManager = new GUIManager(this);
    if (m_guiManager) {
        QWidget *uiWidget = m_guiManager->createUI(this);
        setCentralWidget(uiWidget);
    } else {
        setWindowTitle(tr("Lunar Rover UI - Error"));
        QLabel *errorLabel = new QLabel(tr("Failed to initialize UI"), this);
        setCentralWidget(errorLabel);
    }

    // connect signals
    connect(m_guiManager, &GUIManager::manualOverridesRequested, this, &MainWindow::onManualOverridesRequested);
}

void MainWindow::onManualOverridesRequested()
{
}
}
