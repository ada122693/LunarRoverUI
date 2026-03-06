#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <QObject>
#include "gui_sections/status_section.h"
#include "gui_sections/camera_section.h"
#include "gui_sections/objectives_section.h"
#include "gui_sections/location_section.h"
#include "gui_sections/overrides_section.h"
namespace LunarRoverUI {

class GUIManager : public QObject
{
    Q_OBJECT

public:
    explicit GUIManager(QObject *parent = nullptr);
    QWidget* createUI(QWidget *parent);

private:
    StatusSection *m_statusSection;
    CameraSection *m_cameraSection;
    ObjectivesSection *m_objectivesSection;
    LocationSection *m_locationSection;
    OverridesSection *m_overridesSection;

signals:
    void manualOverridesRequested();

private slots:
    void onManualOverridesClicked();
};

}

#endif