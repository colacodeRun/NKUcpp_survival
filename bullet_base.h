#ifndef BULLET_BASE_H
#define BULLET_BASE_H

#include "global.h"
#include "enemy_base.h"
#include "weapon.h"

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QTimer>

class bullet_base : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit bullet_base(QPointF pos_,qreal angle_,weapon *weapon_,QGraphicsScene *scene_,QObject *parent = nullptr);
    void hit_enemy_check();
    void bullet_move();

    QTimer* bullet_timer;

protected:
    QPointF bullet_point;
    qreal bullet_angle;
    qreal bullet_damage;
    qreal bullet_speed;
    weapon *hero_weapon;
signals:
};

#endif // BULLET_BASE_H
