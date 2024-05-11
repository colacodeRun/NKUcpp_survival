#include "bullet_base.h"

bullet_base::bullet_base(QPointF pos_, qreal angle_, qreal damage_, QGraphicsScene *scene_, QObject *parent)
    : QObject{parent},bullet_point(pos_),bullet_angle(angle_),bullet_damage(damage_)
{
    scene_->addItem(this);
    setPos(bullet_point.x(),bullet_point.y());
    // qreal angle_degrees = qRadiansToDegrees(angle_);
    // setRotation(angle_degrees);
    setScale(4);
    bullet_timer =new QTimer(this);
    bullet_timer->start(15);
    connect(bullet_timer,&QTimer::timeout,this,&bullet_base::bullet_move);
    connect(bullet_timer,&QTimer::timeout,this,&bullet_base::hit_enemy_check);
}

void bullet_base::hit_enemy_check()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();

    for(QGraphicsItem* item : colliding_items) {
        enemy_base* enemy = dynamic_cast<enemy_base*>(item);
        if(enemy != nullptr) {
            deleteLater();
            enemy->gain_hurt(bullet_damage);
        }
        }
    if (x() < 0 || x() > 4800 || y() < 0 || y() > 2700)
        deleteLater();
}

void bullet_base::bullet_move()
{
    bullet_speed=bullet_gun_speed;
    qreal distance=bullet_speed;
    qreal dx=distance*qSin(bullet_angle);
    qreal dy=distance*qCos(bullet_angle);
    setPos(x()+dx,y()+dy);
}
