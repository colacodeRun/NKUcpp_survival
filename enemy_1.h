#ifndef ENEMY_1_H
#define ENEMY_1_H

#include "enemy_base.h"
#include "hero.h"
#include "obstacle.h"
#include <QObject>

class enemy_1 : public enemy_base
{
    Q_OBJECT
public:
    explicit enemy_1(QPointF point_, qreal speed, QGraphicsScene *scene_,QObject *parent = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    // void enemy_1_move(hero *player);
private:
    QPixmap pixmap;
signals:
};

#endif // ENEMY_1_H
