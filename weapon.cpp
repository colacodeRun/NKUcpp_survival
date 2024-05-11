#include "weapon.h"

weapon::weapon(QGraphicsScene *scene_, QPointF center, QObject *parent)
    : QObject{parent}
{
    scene_->addItem(this);
    pixmap.load("://image/AGun.png");
    setPos(center);
    setScale(2);
}

void weapon::move_gun()
{
     setRotation(move_angle);
}

void weapon::gain_angle(QPointF pos)
{
    qreal dx = pos.x()-scenePos().x(),
        dy = pos.y() - scenePos().y();
    move_angle = qRadiansToDegrees(qAtan2(dy,dx));
}

QRectF weapon::boundingRect() const
{
    return QRectF(-gun_width/2, -gun_height/2, gun_width, gun_height);
}

void weapon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-gun_width/2, -gun_height/2, pixmap);
}
