#include "status_section.h"
#include <QFont>

namespace LunarRoverUI {

StatusSection::StatusSection(QWidget *parent)
    : QFrame(parent)
{
    setupStatusLayout();
}

void StatusSection::setupStatusLayout()
{
    // set frame properties
    setObjectName("statusFrame");
    setFrameShape(QFrame::StyledPanel);
    setFrameShadow(QFrame::Raised);

    // create horizontal layout
    QHBoxLayout *statusLayout = new QHBoxLayout(this);
    statusLayout->setSpacing(20);

    // battery status
    QLabel *batteryLabel = new QLabel(tr("Battery: 100%"), this);
    batteryLabel->setObjectName("batteryLabel");
    batteryLabel->setFont(QFont("Arial", 12, QFont::Bold));

    // connection status
    QLabel *connectionLabel = new QLabel(tr("Connection: Connected to LunarNet"), this);
    connectionLabel->setObjectName("connectionLabel");
    connectionLabel->setFont(QFont("Arial", 12, QFont::Bold));

    statusLayout->addWidget(batteryLabel);
    statusLayout->addWidget(connectionLabel);
}

}