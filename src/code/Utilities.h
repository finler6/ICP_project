#pragma once
#include <string>
#include <cmath>

namespace Utilities {

    // Расчет расстояния между двумя точками на плоскости
    double calculateDistance(double x1, double y1, double x2, double y2);

    // Преобразование угла из градусов в радианы
    double degreesToRadians(double degrees);

    // Преобразование угла из радиан в градусы
    double radiansToDegrees(double radians);

    // Форматирование времени в читаемый вид
    std::string formatTime(double timeInSeconds);
}
