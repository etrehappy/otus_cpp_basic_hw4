#include "Dust.h"
#include <random>
#include <chrono>

Dust::Dust() {}

Dust::~Dust() {}

Dust::Dust(const Point& vector, Velocity& ball_velocity, double radius) 
    : m_center(vector), m_velocity(ball_velocity),
      m_color(random_color(), random_color(), random_color()),
      m_durationDisplay(1.), m_radius(radius) {}

Velocity Dust::getVelocity() const {
    // TODO: место для доработки
    return m_velocity;
}


Point Dust::getCenter() const {
    // TODO: место для доработки
    return m_center;
}

void Dust::setCenter(const Point& center) {
    // TODO: место для доработки
    m_center = center;
}

/** 
@brief Рисует частицы
 */
void Dust::draw(Painter& painter) const {    
    painter.draw(m_center, m_radius, m_color);
}


///@brief уменьшаем время отображения
void Dust::setDurationDisplay(double step) {
    m_durationDisplay -= step;
}

double Dust::getDurationDisplay() {
    
    return m_durationDisplay;
}



double Dust::random_color() {
    std::random_device rd;
    std::mt19937 mersenne(rd()); 

    std::uniform_int_distribution die{10, 100};

       int a_random_double = die(mersenne);

    return (double) a_random_double / 100.0;
}