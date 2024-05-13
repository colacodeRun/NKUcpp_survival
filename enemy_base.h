#ifndef ENEMY_BASE_H
#define ENEMY_BASE_H

#include "global.h"
#include "hero.h"
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <cmath>
class enemy_base : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit enemy_base(QPointF point_, qreal speed_, QGraphicsScene *scene_,QObject *parent = nullptr);
    void gain_hurt(qreal);
    bool enemy_die();
    void enemy_move(qreal angle);
    qreal move_angle(QPointF pos);
    qreal distance_hero;
    qreal gain_exp();
protected:
    qreal health;
    qreal damage;
    qreal speed;
    qreal exp;
signals:
};

#endif // ENEMY_BASE_H
