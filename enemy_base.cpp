#include "enemy_base.h"


enemy_base::enemy_base(QPointF point_, qreal speed_, QGraphicsScene *scene_, QObject *parent)
    : QObject{parent}
{
    scene_->addItem(this);
    setScale(3);
    setPos(point_);
    speed=speed_;
    exp = 1;
}

void enemy_base::gain_hurt(qreal hurt_data)
{
    health-=hurt_data;
}

bool enemy_base::enemy_die()
{
    return health<=0;
}

void enemy_base::enemy_move(qreal angle)
{
    angle =M_PI/2-angle;
    qreal x1=scenePos().x(),
        y1=scenePos().y();
    qreal dx = speed*qSin(angle),
        dy = speed*qCos(angle);
    setPos(x1+dx,y1+dy);
}

qreal enemy_base::move_angle(QPointF pos)
{
    qreal dx = pos.x() - scenePos().x(),
        dy = pos.y() - scenePos().y();
    return qAtan2(dy,dx);
}

qreal enemy_base::gain_exp()
{
    return exp;
}


