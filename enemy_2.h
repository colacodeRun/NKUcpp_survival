#ifndef ENEMY_2_H
#define ENEMY_2_H

#include "enemy_base.h"
#include <QObject>
#include <QMovie>
class enemy_2 : public enemy_base
{
    Q_OBJECT
public:
    explicit enemy_2(QPointF point_, qreal speed_, QGraphicsScene *scene_,QObject *parent = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QMovie *movie;
signals:
};

#endif // ENEMY_2_H
