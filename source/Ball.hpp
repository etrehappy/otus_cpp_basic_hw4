#pragma once
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"

class Ball {
public:
    Ball(double& x, double& y, Point& vector, double& red, double& green,
         double& blue, double& radius);

    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;

private:
    Point m_center;
    Velocity m_velocity;    
    Color m_color;
    double m_mass;
};
