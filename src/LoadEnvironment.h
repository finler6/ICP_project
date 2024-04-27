#include <QObject>
#include "Environment.h"


class LoadEnvironment : public QObject {
    Q_OBJECT

public:
    explicit LoadEnvironment(Environment* environment, QObject* parent = nullptr);

public slots:
    void loadNewConfiguration();

signals:
    void stopEngine();

private:
    Environment* environment;
};
