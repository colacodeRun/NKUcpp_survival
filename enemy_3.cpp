#include "enemy_3.h"


enemy_3::enemy_3(QPointF point_, qreal speed_, QGraphicsScene *scene_, QObject *parent)
    :enemy_base(point_,speed_,scene_)
{
    pixmap.load("://image/enemy/en_float.png");
    health =3;
}

QRectF enemy_3::boundingRect() const
{
    qreal width = pixmap.width();
    qreal height = pixmap.height();
    return QRectF(-width/2, -height/2, width, height);
}

void enemy_3::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qreal width = pixmap.width();
    qreal height = pixmap.height();
    painter->drawPixmap(-width/2, -height/2, pixmap);
}
