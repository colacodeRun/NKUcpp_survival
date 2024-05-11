#include "bullet_gun.h"
#include "global.h"
#include <cmath>
bullet_gun::bullet_gun(QPointF pos_, qreal angle_, qreal damage_, QGraphicsScene *scene_, QObject *parent)
    :bullet_base(pos_, angle_, damage_, scene_, parent)
{
    bullet_pixmap.load("://image/weapon/gun_bullet.png");
    //bullet_pixmap.load("://image/weapon/wp_dmr_bullet.png");
}

QRectF bullet_gun::boundingRect() const
{
    return QRectF(0, 0, bullet_width, bullet_height);
}

void bullet_gun::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0, bullet_pixmap);
}
