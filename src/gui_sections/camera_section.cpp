#include "camera_section.h"

#include <QPixmap>

namespace LunarRoverUI {

CameraSection::CameraSection(QWidget *parent)
    : QGroupBox(parent),
      capture(nullptr),
      timer(nullptr)
{
    setupCameraLayout();

    capture = new cv::VideoCapture(0);

    if (capture->isOpened()) {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &CameraSection::updateFrame);
        timer->start(33); // ~30 FPS
    } else {
        cameraLabel->setText(tr("No camera detected"));
        delete capture;
        capture = nullptr;
    }
}

CameraSection::~CameraSection()
{
    if (timer) {
        timer->stop();
    }
    if (capture) {
        capture->release();
        delete capture;
    }
}

void CameraSection::updateFrame()
{
    cv::Mat frame;
    if (capture && capture->read(frame) && !frame.empty()) {
        cv::Mat rgb;
        cv::cvtColor(frame, rgb, cv::COLOR_BGR2RGB);

        QImage img(rgb.data, rgb.cols, rgb.rows, static_cast<int>(rgb.step),
                   QImage::Format_RGB888);
        cameraLabel->setPixmap(
            QPixmap::fromImage(img).scaled(
                cameraLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
}

void CameraSection::setupCameraLayout()
{
    // set group box properties
    setTitle(tr("Camera Feed"));
    setObjectName("cameraGroupBox");

    // create vertical layout
    QVBoxLayout *cameraLayout = new QVBoxLayout(this);

    // camera display label
    cameraLabel = new QLabel(this);
    cameraLabel->setObjectName("cameraDisplay");
    cameraLabel->setAlignment(Qt::AlignCenter);
    cameraLabel->setMinimumSize(320, 240);
    cameraLabel->setText(tr("Initializing camera..."));

    cameraLayout->addWidget(cameraLabel);
}

}
