#pragma once
#include <utility>  // For std::pair

class Robot {
public:
    Robot(int id, std::pair<double, double> position, double velocity, double orientation, double size);
    virtual ~Robot() = default;
    bool isTaskCompleted() const;
    // Основные действия, которые должен выполнять каждый робот
    virtual void move(double maxWidth, double maxHeight) = 0;
    virtual void rotate(double angle) = 0;
    virtual void handleCollision() = 0;

    // Геттеры для получения состояния робота
    std::pair<double, double> getPosition() const;
    double getSize() const;
    double getOrientation() const;
private:
    bool taskCompleted;  // Переменная для хранения статуса задачи
protected:
    int id;
    std::pair<double, double> position; // Координаты (x, y)
    double velocity; // Скорость
    double orientation; // Угол в градусах
    double size; // Размер робота
};
