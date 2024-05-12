#include "enemy_1.h"

enemy_1::enemy_1(QPointF point_, qreal speed, QGraphicsScene *scene_, QObject *parent)
    : enemy_base(point_,speed,scene_)
{
    pixmap.load("://image/enemy/en_float_elite.png");
    health = 3;
    speed =17;
}
QRectF enemy_1::boundingRect() const
{
    return QRectF(-enemy_1_width/2, -enemy_1_height/2, enemy_1_width, enemy_1_height);
}

void enemy_1::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-enemy_1_width/2, -enemy_1_height/2, pixmap);
}
