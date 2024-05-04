#include "RemoteControlledRobot.h"

RemoteControlledRobot::RemoteControlledRobot(int id, std::pair<double, double> position, double velocity, double orientation, double sensorRange, double maxWidth, double maxHeight, Environment* env)
        : Robot(id, position, velocity, orientation, sensorRange), avoidanceAngle(orientation), environment(env), currentSpeed(0),movingForward(false), movingBackward(false), turningLeft(false), turningRight(false) {
    qDebug() << "RemoteControlledRobot constructor called with orientation: " << orientation;
    qDebug() << "RemoteControlledRobot constructor called with avoidance: " << avoidanceAngle;
    if (!environment) {
        std::cerr << "Environment pointer is null" << std::endl;
    }
}

void RemoteControlledRobot::move(double maxWidth, double maxHeight) {
    double radianOrientation = orientation * M_PI / 180.0;
    double newX = position.first + cos(radianOrientation) * currentSpeed;
    double newY = position.second + sin(radianOrientation) * currentSpeed;

    bool canMoveX = canMoveTo(newX, position.second, maxWidth, maxHeight);
    bool canMoveY = canMoveTo(position.first, newY, maxWidth, maxHeight);

    if (canMoveX && canMoveY) {
        updatePosition(newX, newY, maxWidth, maxHeight);
    } else if (canMoveX) {
        updatePosition(newX, position.second, maxWidth, maxHeight);
    } else if (canMoveY) {
        updatePosition(position.first, newY, maxWidth, maxHeight);
    } else {
        qDebug() << "Robot ID:" << id << " is blocked and cannot move.";
    }
}

void RemoteControlledRobot::rotate(double angle) {
    orientation += angle;
    orientation = fmod(orientation, 360.0);
}

void RemoteControlledRobot::handleCollision() {
    // Обработка столкновений может быть реализована здесь
}

void RemoteControlledRobot::processCommand(const QString &command) {
    if (command == "start_move_forward") {
        movingForward = true;
    } else if (command == "stop_move_forward") {
        movingForward = false;
    } else if (command == "start_move_backward") {
        movingBackward = true;
    } else if (command == "stop_move_backward") {
        movingBackward = false;
    } else if (command == "start_turn_left") {
        turningLeft = true;
    } else if (command == "stop_turn_left") {
        turningLeft = false;
    } else if (command == "start_turn_right") {
        turningRight = true;
    } else if (command == "stop_turn_right") {
        turningRight = false;
    }
}

void RemoteControlledRobot::update() {
    if (movingForward) {
        moveForward();
    } else if (movingBackward) {
        moveBackward();
    } else {
        currentSpeed = 0;  // Сбрасываем скорость, если не движемся вперед/назад
    }

    if (turningLeft) {
        turnLeft();
    } else if (turningRight) {
        turnRight();
    }
}

void RemoteControlledRobot::moveForward() {
    currentSpeed = velocity;  // Устанавливаем текущую скорость вперед
}

void RemoteControlledRobot::moveBackward() {
    currentSpeed = -velocity;  // Устанавливаем текущую скорость назад
}

void RemoteControlledRobot::turnLeft() {
    //avoidanceAngle = -1;  // Поворот влево
    qDebug() << "Turning left with angle: " << avoidanceAngle;
    rotate(-1 * avoidanceAngle);
}

void RemoteControlledRobot::turnRight() {
    //avoidanceAngle = 1;  // Поворот вправо
    qDebug() << "Turning right with angle: " << avoidanceAngle;
    rotate(avoidanceAngle);
}

void RemoteControlledRobot::updatePosition(double newX, double newY, double maxWidth, double maxHeight) {
    position.first = std::max(0.0, std::min(newX, maxWidth));
    position.second = std::max(0.0, std::min(newY, maxHeight));
}

void RemoteControlledRobot::tryMove(double maxWidth, double maxHeight) {
    double radianOrientation = orientation * M_PI / 180.0;
    double newX = position.first + velocity * cos(radianOrientation);
    double newY = position.second + velocity * sin(radianOrientation);

    bool canMoveX = canMoveTo(newX, position.second, maxWidth, maxHeight);
    bool canMoveY = canMoveTo(position.first, newY, maxWidth, maxHeight);

    if (canMoveX && canMoveY) {
        updatePosition(newX, newY, maxWidth, maxHeight);
    } else if (canMoveX) {
        updatePosition(newX, position.second, maxWidth, maxHeight);
    } else if (canMoveY) {
        updatePosition(position.first, newY, maxWidth, maxHeight);
    } else {
        qDebug() << "Robot ID:" << id << " is blocked and cannot move.";
    }
}

bool RemoteControlledRobot::canMoveTo(double x, double y, double maxWidth, double maxHeight) {
    if (x < 0 || x > maxWidth || y < 0 || y > maxHeight) {
        return false;
    }
    qDebug() << "Trying to move to: (" << x << ", " << y << ")";
    if (isObstacleAt(x, y)) {
        qDebug() << "Obstacle detected at new position!";
        return false;
    }
    for (const auto& otherRobot : environment->getRobots()) {
        if (otherRobot->getID() != this->id) {
            QRectF otherRobotBounds(
                    otherRobot->getPosition().first - 20,
                    otherRobot->getPosition().second - 20,
                    40, 40);
            if (otherRobotBounds.contains(x, y)) {
                qDebug() << "Collision with another robot at new position!";
                return false;
            }
        }
    }
    return true;
}



bool RemoteControlledRobot::isObstacleAt(double x, double y) {
    double robotRadius = 10.0;
    for (const auto& obstacle : environment->getObstacles()) {
        QRectF bounds = obstacle->getBounds().adjusted(-robotRadius, -robotRadius, robotRadius, robotRadius);
        if (bounds.contains(x, y)) {
            return true;
        }
    }
    return false;
}



bool RemoteControlledRobot::lineIntersectsRect(double x1, double y1, double x2, double y2, const QRectF& rect) {
    double left = rect.left();
    double right = rect.right();
    double top = rect.top();
    double bottom = rect.bottom();

    return (lineIntersectsLine(x1, y1, x2, y2, left, top, right, top) ||
            lineIntersectsLine(x1, y1, x2, y2, left, bottom, right, bottom) ||
            lineIntersectsLine(x1, y1, x2, y2, left, top, left, bottom) ||
            lineIntersectsLine(x1, y1, x2, y2, right, top, right, bottom));
}

bool RemoteControlledRobot::lineIntersectsLine(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    double denominator = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);

    if (fabs(denominator) < 1e-6) {

        if ((y4 - y3) == 0) {
            if (y1 != y3) return false;
            return std::max(x1, x2) >= std::min(x3, x4) && std::min(x1, x2) <= std::max(x3, x4);
        } else if ((x4 - x3) == 0) {
            if (x1 != x3) return false;
            return std::max(y1, y2) >= std::min(y3, y4) && std::min(y1, y2) <= std::max(y3, y4);
        }
        return false;
    }

    double ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denominator;
    double ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denominator;

    return ua >= 0 && ua <= 1 && ub >= 0 && ub <= 1;
}