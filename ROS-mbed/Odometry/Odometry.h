#ifndef ODOMETRY_H
#define ODOMETRY_H

#include "mbed.h"
#include "QEI.h"

class Odometry
{
    public:
        Odometry(QEI *qei_left, QEI *qei_right, float radius_left, float radius_right, float v);
        
        void setPos(float x, float y, float theta);
        void setX(float x);
        void setY(float Y);
        void setTheta(float theta);
        
        float getX() {return x;}
        float getY() {return y;}
        float getTheta() {return theta;}
        
        void reset();
    
    private:
        QEI* m_qei_left;
        int m_pulses_left;
        QEI* m_qei_right;
        int m_pulses_right;
        
        float x, y, theta;
        
        float m_radiusPerTick_left, m_radiusPerTick_right, m_v;
        
        Ticker updater;
        
        void update();
};

#endif
