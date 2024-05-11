#include "enemy_base.h"


enemy_base::enemy_base(QPointF point_, qreal speed_, QGraphicsScene *scene_, QObject *parent)
    : QObject{parent}
{
    scene_->addItem(this);
    setScale(3);
    setPos(point_);
    speed=speed_;
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
    qreal x1=scenePos().x(),
        y1=scenePos().y();
    qreal dx = speed*qSin(angle),
        dy = speed*qCos(angle);
    setPos(x1+dx,y1+dy);
}

qreal enemy_base::move_angle(QPointF pos)
{
    qreal x1=scenePos().x(),
        y1=scenePos().y(),
        x2=pos.x(),
        y2=pos.y();
    qreal angle;
    if(y2!=y1){
        angle = qAtan((x2-x1)/(y2-y1));
        if(y2<y1){
            angle+=M_PI;
        }
    }
    else{
        if(x2>=x1)angle=M_PI/2;
        if(x2<x1)angle=M_PI*1.5;
    }
    return angle;
}


