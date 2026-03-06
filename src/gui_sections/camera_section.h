#ifndef CAMERA_SECTION_H
#define CAMERA_SECTION_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>

namespace LunarRoverUI {

class CameraSection : public QGroupBox
{
    Q_OBJECT

public:
    explicit CameraSection(QWidget *parent = nullptr);

private:
    void setupCameraLayout();
};

}

#endif