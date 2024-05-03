#pragma once
#include <utility>  

class Robot {
public:
    Robot(int id, std::pair<double, double> position, double velocity, double orientation, double sensorRange);
    virtual ~Robot() = default;
    bool isTaskCompleted() const;
    virtual void move(double maxWidth, double maxHeight) = 0;
    virtual void rotate(double angle) = 0;
    virtual void handleCollision() = 0;
    int getID() const { return id; }
    std::pair<double, double> getPosition() const;
    double getRange() const;
    double getSensorRange() const {
        return sensorRange;
    }
    double getOrientation() const;
    double getSpeed() const;
    void setSpeed(double speed);
    void setOrientation(double orientation);
    void setSensorSize(double sensorSize);

private:
    bool taskCompleted = false;  
protected:
    int id;
    std::pair<double, double> position; 
    double velocity; 
    double orientation; 
    double sensorRange; 
};
