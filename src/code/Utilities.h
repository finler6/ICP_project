#pragma once

#include "string"
#include "cmath"

namespace Utilities {

    double calculateDistance(double x1, double y1, double x2, double y2);

    double degreesToRadians(double degrees);

    double radiansToDegrees(double radians);

    std::string formatTime(double timeInSeconds);
}
