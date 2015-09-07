#include "Odometry.h"

Odometry::Odometry(QEI *qei_left, QEI *qei_right, float radius_left, float radius_right, float v)
{
    m_qei_left = qei_left;
    m_qei_right = qei_right;
    m_radiusPerTick_left = radius_left/qei_left->getPulsesPerRev();
    m_radiusPerTick_right = radius_right/qei_right->getPulsesPerRev();
    m_v = v;

    m_pulses_left = qei_left->getPulses();
    m_pulses_right = qei_right->getPulses();

    setPos(0,0,0);
 
    updater.attach(this, &Odometry::update, 0.1);
}

void Odometry::setPos(float x, float y, float theta)
{
    this->x = x;
    this->y = y;
    this->theta = theta;
}

void Odometry::setX(float x)
{
    this->x = x;
}

void Odometry::setY(float Y)
{
    this->y = y;
}

void Odometry::setTheta(float theta)
{
    this->theta = theta;
}

void Odometry::reset()
{
    setPos(0,0,0);
    m_pulses_left = m_qei_left->getPulses();
    m_pulses_right = m_qei_right->getPulses();
}

void Odometry::update()
{
    int delta_left = m_qei_left->getPulses() - m_pulses_left;
    m_pulses_left = m_qei_left->getPulses();
    int delta_right = m_qei_right->getPulses() - m_pulses_right;
    m_pulses_right = m_qei_right->getPulses();

    float deltaS = (m_radiusPerTick_left*delta_left + m_radiusPerTick_right*delta_right) / 2.0;
    float deltaTheta = (m_radiusPerTick_right*delta_right - m_radiusPerTick_left*delta_left) / m_v;

    x += deltaS * cos(theta);
    y += deltaS * sin(theta);
    theta += deltaTheta;
}
