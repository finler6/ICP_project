#include "ObstacleView.h"

ObstacleView::ObstacleView(SimulationEngine* engine, int id, const QRectF &initialBounds, QGraphicsItem *parent)
    : bounds(initialBounds), engine(engine), id(id) {
}
QRectF ObstacleView::boundingRect() const {
    return bounds;
}

void ObstacleView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setBrush(Qt::black);
    painter->drawRect(bounds);
}


void ObstacleView::setBounds(const QRectF &newBounds) {
    prepareGeometryChange();  
    bounds = newBounds;
    update(); 
}

double ObstacleView::getSize() const {
    return bounds.width();  
}

void ObstacleView::setSize(double size) {
    QPointF center = bounds.center();  
    bounds = QRectF(center.x() - size / 2, center.y() - size / 2, size, size);  
    prepareGeometryChange();  
    update();  
}

int ObstacleView::getId() const {
    return id;
}

void ObstacleView::setId(int newId) {
    id = newId;
}

void ObstacleView::updateObstacleView() {
    Obstacle* obstacle = engine->getObstacleById(id);
    if (obstacle) {
        setBounds(obstacle->getBounds());
    }
}