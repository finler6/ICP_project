#include "Utilities.h"

namespace Utilities {
    double calculateDistance(double x1, double y1, double x2, double y2) {
        return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    }

    double degreesToRadians(double degrees) {
        return degrees * M_PI / 180.0;
    }

    double radiansToDegrees(double radians) {
        return radians * 180.0 / M_PI;
    }

    std::string formatTime(double timeInSeconds) {
        int hours = static_cast<int>(timeInSeconds / 3600);
        int minutes = static_cast<int>((timeInSeconds - hours * 3600) / 60);
        int seconds = static_cast<int>(timeInSeconds - hours * 3600 - minutes * 60);
        char buffer[80];
        std::sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);
        return std::string(buffer);
    }
}
