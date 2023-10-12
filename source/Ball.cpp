#include "Ball.hpp"
#include <cmath>

Ball::Ball(double& x, double& y, Point& vector, double& red, double& green,
    double& blue, double& radius) 
   : m_center(x, y), m_velocity(vector), m_color(red, green, blue), m_radius(radius) 
{
    m_mass = M_PI * pow(m_radius, 3) * 4. / 3.;
}

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) {
    // TODO: место для доработки
    m_velocity = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const {
    // TODO: место для доработки
    return m_velocity;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const {
    // TODO: место для доработки
    painter.draw(m_center, m_radius, m_color);
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) {
    // TODO: место для доработки
    m_center = center;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const {
    // TODO: место для доработки
    return m_center;
    }

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const {
    // TODO: место для доработки
    return m_radius;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const {
    // TODO: место для доработки
    return m_mass;
}
