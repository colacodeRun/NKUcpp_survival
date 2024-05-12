#ifndef WEAPON_H
#define WEAPON_H

#include "global.h"
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>

class weapon : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit weapon(QGraphicsScene *scene_,QPointF center,QObject *parent = nullptr);
    void move_gun();
    void gain_angle(QPointF);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    qreal gain_bullet_speed();
    qreal gain_generate_speed();
    qreal gain_damage();
    void up_bullet_speed();
    void up_generate_speed();
    void up_damage();
private:
    qreal move_angle;
    QPixmap pixmap;
    qreal bullet_speed;
    qreal generate_speed;
    qreal damage;
signals:
};

#endif // WEAPON_H
