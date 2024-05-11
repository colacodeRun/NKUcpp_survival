#include "obstacle.h"

obstacle::obstacle(QGraphicsScene *scene_, QRectF rect_, QPointF pos_, QObject *parent)
    : QObject{parent},rects_(rect_)
{
    scene_->addItem(this);
    setPos(pos_);
}

QRectF obstacle::boundingRect() const
{
    return QRectF(rects_);
}
