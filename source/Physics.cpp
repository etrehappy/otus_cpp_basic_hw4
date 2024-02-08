#include "Physics.h"

double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Physics::Physics(double timePerTick) : timePerTick{timePerTick} {}

void Physics::setWorldBox(const Point& _topLeft, const Point& _bottomRight) {
    this->topLeft = _topLeft;
    this->bottomRight = _bottomRight;
}

void Physics::update(std::vector<Ball>& balls, std::vector<Dust>& dusts,
                     const size_t ticks, double totalTime) const {

    for (size_t i = 0; i < ticks; ++i) {
        move(balls);
        collideWithBox(balls, dusts);
        collideBalls(balls, dusts);
        move(dusts);
        cleanDusts(dusts, totalTime);
    }
}

void Physics::collideBalls(std::vector<Ball>& balls, std::vector<Dust>& dusts) const {
   
        for (auto a = balls.begin(); a != balls.end(); ++a) {
            for (auto b = std::next(a); b != balls.end(); ++b) {
                
                // Доп.задание 2, обработка столкновений
                if (a->isCollidable() == false || b->isCollidable() == false)
                    continue;                

                const double distanceBetweenCenters2 =
                    distance2(a->getCenter(), b->getCenter());
                const double collisionDistance =
                    a->getRadius() + b->getRadius();
                const double collisionDistance2 =
                    collisionDistance * collisionDistance;

                if (distanceBetweenCenters2 < collisionDistance2) {
                    processCollision(*a, *b, distanceBetweenCenters2, dusts); 
                }
                
            }
        }
   
}

void Physics::collideWithBox(std::vector<Ball>& balls, std::vector<Dust>& dusts) const {
    for (Ball& ball : balls) {
        
        //Доп.задание 2, обработка столкновений
        if (ball.isCollidable() == false )
            continue; 

        const Point p = ball.getCenter();
        const double r = ball.getRadius();
        // определяет, находится ли v в диапазоне (lo, hi) (не включая границы)
        auto isOutOfRange = [](double v, double lo, double hi) {
            return v < lo || v > hi;
        };

        
        Point dust_position = p;        

        if (isOutOfRange(p.x, topLeft.x + r, bottomRight.x - r)) 
        {
            Point vector = ball.getVelocity().vector();
            vector.x = -vector.x;            
           
                // Доп. задание 3, отражение от стен (простая логика без доп. расчётов)
                dust_position.y -= r;
                Dust dust(dust_position, ball.getVelocity(), r * 0.3);
                dusts.push_back(dust);

            ball.setVelocity(vector); 

        } 
        else if (isOutOfRange(p.y, topLeft.y + r, bottomRight.y - r)) 
        {
            Point vector = ball.getVelocity().vector();
            vector.y = -vector.y;
            
                // Доп. задание 3, отражение от стен (простая логика без доп. расчётов)
                dust_position.y -= r;
                Dust dust(dust_position, ball.getVelocity(), r * 0.3);
                dusts.push_back(dust);

            ball.setVelocity(vector);
        }      
            
    }
}

void Physics::move(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        Point newPos =
            ball.getCenter() + ball.getVelocity().vector() * timePerTick;
        ball.setCenter(newPos);
    }
}

void Physics::processCollision(Ball& a, Ball& b, 
                                double distanceBetweenCenters2, std::vector<Dust>& dusts) const {
    // нормированный вектор столкновения
    const Point normal =
        (b.getCenter() - a.getCenter()) / std::sqrt(distanceBetweenCenters2);

    // получаем скорость в векторном виде
    const Point aV = a.getVelocity().vector();
    const Point bV = b.getVelocity().vector();

    // коэффициент p учитывает скорость обоих мячей
    const double p =
        2 * (dot(aV, normal) - dot(bV, normal)) / (a.getMass() + b.getMass());

    // задаем новые скорости мячей после столкновения
    a.setVelocity(Velocity(aV - normal * p * a.getMass()));
    b.setVelocity(Velocity(bV + normal * p * b.getMass()));

    //Доп. задание 3
    //ищем точку столкновения между шарами по векторно-параметрическому уравнению прямой
    double radius_a = a.getRadius();
    double radius_b = b.getRadius();    
    double segment_b = (radius_b * radius_b - radius_a * radius_a + distanceBetweenCenters2 * distanceBetweenCenters2) / (2 * distanceBetweenCenters2);
    double segment_a = distanceBetweenCenters2 - segment_b;
    Point dust_position = ((b.getCenter() - a.getCenter()) * segment_a / distanceBetweenCenters2) + a.getCenter();

    //добавляем частицы
    Dust dust(dust_position, a.getVelocity(), a.getRadius()*0.3 );
    dusts.push_back(dust);
}




// Доп. задание 3
void Physics::move(std::vector<Dust>& dusts) const {
    for (Dust& dust : dusts) {
        Point newPos = dust.getCenter() - dust.getVelocity().vector() * timePerTick;
        dust.setCenter(newPos);
    }
}

void Physics::cleanDusts(std::vector<Dust>& dusts, double totalTime) const {
    double amount_time = 0.0005;
    
    /*Когда вызывается cleanDusts, то вызывается и setDurationDisplay(),
        чтобы уменьшить время отображения частицы.Если время закончилось,
        удаляется экзмепляр класса Balls, а потом и элемент вектора dusts*/    
    int i = 0;
    for (auto it = dusts.begin(); it != dusts.end(); ++it) {

        if (it->getDurationDisplay() <= 0.) {
            dusts[i].~Dust();
            dusts.erase(it);

            if (dusts.empty() )
                    return;

            // После удаления  первого элемента нужно уменьшить время у других частицы,
            // задаем it для корректной работы цикла
            it = dusts.begin(); 
            continue;
        }

        it->setDurationDisplay(amount_time);
        ++i;        
    }

    //Удаляем все частицы с экрана, когда картинка собрана на 10ой секунде
    if (totalTime > 9.99)
        dusts.clear();
}


