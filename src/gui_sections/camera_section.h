#ifndef CAMERA_SECTION_H
#define CAMERA_SECTION_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>

#include <opencv2/opencv.hpp>

namespace LunarRoverUI {

class CameraSection : public QGroupBox
{
    Q_OBJECT

public:
    explicit CameraSection(QWidget *parent = nullptr);
    ~CameraSection();

private slots:
    void updateFrame();

private:
    void setupCameraLayout();

    QLabel *cameraLabel;
    QTimer *timer;
    cv::VideoCapture *capture;
};

}

#endif
