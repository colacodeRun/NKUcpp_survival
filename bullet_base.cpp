#include "bullet_base.h"

bullet_base::bullet_base(QPointF pos_, qreal angle_, weapon *weapon_, QGraphicsScene *scene_, QObject *parent)
    : QObject{parent},bullet_point(pos_),bullet_angle(angle_),hero_weapon(weapon_)
{
    bullet_damage = hero_weapon ->gain_damage();
    bullet_speed =hero_weapon -> gain_bullet_speed();
    scene_->addItem(this);
    setPos(bullet_point.x(),bullet_point.y());
    qreal angle_degrees = qRadiansToDegrees(angle_);
    setRotation(angle_degrees);
    setScale(4);
    bullet_timer =new QTimer(this);
    bullet_timer->start(35/bullet_speed);
    connect(bullet_timer,&QTimer::timeout,this,&bullet_base::bullet_move);
    connect(bullet_timer,&QTimer::timeout,this,&bullet_base::hit_enemy_check);
}
//子弹碰撞和边界检查
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
//子弹移动函数
void bullet_base::bullet_move()
{
    qreal angle =M_PI/2-bullet_angle;
    //bullet_speed=bullet_gun_speed;
    qreal distance=bullet_gun_speed ;
    qreal dx=distance*qSin(angle);
    qreal dy=distance*qCos(angle);
    setPos(x()+dx,y()+dy);
}

bullet_base::~bullet_base()
{
    delete bullet_timer;
}

