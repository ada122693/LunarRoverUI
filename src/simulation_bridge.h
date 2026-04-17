#ifndef SIMULATION_BRIDGE_H
#define SIMULATION_BRIDGE_H

#include <QObject>
#include <QTimer>
#include <string>

namespace LunarRoverUI {

class SimulationBridge : public QObject
{
    Q_OBJECT
public:
    explicit SimulationBridge(QObject *parent = nullptr);
    ~SimulationBridge();

    bool connectToGazebo(const std::string &worldName = "default");
    void disconnect();
    bool isConnected() const;

public slots:
    void sendVelocityCommand(double linear, double angular);
    void pauseSimulation();
    void resumeSimulation();
    void resetSimulation();

signals:
    void connectionStatusChanged(bool connected);
    void positionUpdated(double x, double y, double z);
    void orientationUpdated(double roll, double pitch, double yaw);
    void velocityUpdated(double linear, double angular);
    void batteryLevelUpdated(double percentage);
    void cameraFrameReceived(const unsigned char *data, int width, int height);
    void simulationTimeUpdated(double timeSeconds);

private slots:
    void simulationUpdateTick();

private:
    bool m_connected;
    QTimer *m_updateTimer;

    // Simulation state
    double m_simTime;
    double m_posX, m_posY, m_posZ;
    double m_roll, m_pitch, m_yaw;
    double m_linearVel, m_angularVel;
    double m_batteryLevel;
};

}

#endif // SIMULATION_BRIDGE_H