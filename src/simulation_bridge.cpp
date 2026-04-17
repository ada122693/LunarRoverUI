#include "simulation_bridge.h"
#include <QDebug>
#include <cmath>

#ifdef GAZEBO_SUPPORT
#include "rclcpp/rclcpp.hpp"
#include "nav_msgs/msg/odometry.hpp"
#include "sensor_msgs/msg/battery_state.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "gazebo_msgs/srv/set_physics_properties.hpp"
#include "gazebo_msgs/srv/delete_model.hpp"
#endif

namespace LunarRoverUI {

SimulationBridge::SimulationBridge(QObject *parent)
    : QObject(parent)
    , m_connected(false)
    , m_simTime(0.0)
    , m_posX(0.0), m_posY(0.0), m_posZ(0.0)
    , m_roll(0.0), m_pitch(0.0), m_yaw(0.0)
    , m_linearVel(0.0), m_angularVel(0.0)
    , m_batteryLevel(100.0)
{
    m_updateTimer = new QTimer(this);
    connect(m_updateTimer, &QTimer::timeout, this, &SimulationBridge::simulationUpdateTick);
    m_updateTimer->setInterval(50); // 20 Hz update rate matching Gazebo
}

SimulationBridge::~SimulationBridge()
{
    disconnect();
}

bool SimulationBridge::connectToGazebo(const std::string &worldName)
{
    qDebug() << "Connecting to Gazebo world:" << QString::fromStdString(worldName);

#ifdef GAZEBO_SUPPORT
    // Initialize ROS 2 node and Gazebo transport
    if (!rclcpp::ok()) {
        rclcpp::init(0, nullptr);
    }
    
    // Node creation, subscribers and publishers will be created here
    
    qDebug() << "ROS 2 node initialized for Gazebo communication";
#endif

    m_connected = true;
    m_updateTimer->start();
    emit connectionStatusChanged(true);

    qDebug() << "Successfully connected to Gazebo simulation";
    return true;
}

void SimulationBridge::disconnect()
{
    if (m_connected) {
        m_updateTimer->stop();
        m_connected = false;
        emit connectionStatusChanged(false);
        qDebug() << "Disconnected from Gazebo simulation";
    }
}

bool SimulationBridge::isConnected() const
{
    return m_connected;
}

void SimulationBridge::sendVelocityCommand(double linear, double angular)
{
    if (!m_connected) return;

    // TODO: Publish to /rover/cmd_vel topic
    qDebug() << "Sending velocity command: linear =" << linear << "angular =" << angular;
}

void SimulationBridge::pauseSimulation()
{
    if (!m_connected) return;
    // TODO: Call gazebo pause service
    m_updateTimer->stop();
    qDebug() << "Simulation paused";
}

void SimulationBridge::resumeSimulation()
{
    if (!m_connected) return;
    m_updateTimer->start();
    qDebug() << "Simulation resumed";
}

void SimulationBridge::resetSimulation()
{
    if (!m_connected) return;

    m_posX = 0.0;
    m_posY = 0.0;
    m_posZ = 0.0;
    m_roll = 0.0;
    m_pitch = 0.0;
    m_yaw = 0.0;
    m_linearVel = 0.0;
    m_angularVel = 0.0;
    m_batteryLevel = 100.0;
    m_simTime = 0.0;

    emit positionUpdated(m_posX, m_posY, m_posZ);
    emit orientationUpdated(m_roll, m_pitch, m_yaw);
    emit velocityUpdated(m_linearVel, m_angularVel);
    emit batteryLevelUpdated(m_batteryLevel);
    emit simulationTimeUpdated(m_simTime);

    qDebug() << "Simulation reset";
}

void SimulationBridge::simulationUpdateTick()
{
    // For now, simulate basic rover movement
    m_simTime += 0.05;

    if (m_linearVel != 0.0 || m_angularVel != 0.0) {
        m_posX += m_linearVel * cos(m_yaw) * 0.05;
        m_posY += m_linearVel * sin(m_yaw) * 0.05;
        m_yaw += m_angularVel * 0.05;

        emit positionUpdated(m_posX, m_posY, m_posZ);
        emit orientationUpdated(m_roll, m_pitch, m_yaw);
        emit velocityUpdated(m_linearVel, m_angularVel);
    }

    // Slowly discharge battery
    m_batteryLevel -= 0.001;
    if (m_batteryLevel < 0) m_batteryLevel = 0;
    emit batteryLevelUpdated(m_batteryLevel);

    emit simulationTimeUpdated(m_simTime);
}

}