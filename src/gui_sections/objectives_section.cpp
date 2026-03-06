#include "objectives_section.h"

namespace LunarRoverUI {

ObjectivesSection::ObjectivesSection(QWidget *parent)
    : QGroupBox(parent)
{
    setupObjectivesLayout();
}

void ObjectivesSection::setupObjectivesLayout()
{
    // set group box properties
    setTitle(tr("Objectives"));
    setObjectName("objectivesGroupBox");

    // create vertical layout
    QVBoxLayout *objectivesLayout = new QVBoxLayout(this);

    // current goal
    QLabel *currentGoalLabel = new QLabel(tr("Current Goal: Collect rock samples"), this);
    currentGoalLabel->setObjectName("currentGoalLabel");
    currentGoalLabel->setFont(QFont("Arial", 11));

    // ETA
    QLabel *etaLabel = new QLabel(tr("ETA: 15 minutes"), this);
    etaLabel->setObjectName("etaLabel");
    etaLabel->setFont(QFont("Arial", 11));

    objectivesLayout->addWidget(currentGoalLabel);
    objectivesLayout->addWidget(etaLabel);
}

}