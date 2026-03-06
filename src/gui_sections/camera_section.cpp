#include "camera_section.h"

namespace LunarRoverUI {

CameraSection::CameraSection(QWidget *parent)
    : QGroupBox(parent)
{
    setupCameraLayout();
}

void CameraSection::setupCameraLayout()
{
    // set group box properties
    setTitle(tr("Camera Feed"));
    setObjectName("cameraGroupBox");

    // create vertical layout
    QVBoxLayout *cameraLayout = new QVBoxLayout(this);

    // camera placeholder
    QLabel *cameraPlaceholder = new QLabel(tr("Camera Feed Placeholder"), this);
    cameraPlaceholder->setObjectName("cameraPlaceholder");
    cameraPlaceholder->setAlignment(Qt::AlignCenter);
    cameraPlaceholder->setMinimumSize(0, 300);

    cameraLayout->addWidget(cameraPlaceholder);
}

}