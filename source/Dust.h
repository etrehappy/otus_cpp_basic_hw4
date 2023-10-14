#pragma once
#include "Point.h"
#include "Painter.h"
#include "Velocity.h"

class Dust {
  public:
    Dust();
    Dust(const Point& vector, Velocity& ball_velocity, double radius);
    ~Dust();
    Velocity getVelocity() const;
    Point getCenter() const;
    void setCenter(const Point& center);
    void draw(Painter& painter) const;
    void setDurationDisplay(double step);
    double getDurationDisplay();

  private:
    Point m_center;
    Velocity m_velocity;
    Color m_color;
    double m_durationDisplay;
    double m_radius; 

    double random_color();

};

