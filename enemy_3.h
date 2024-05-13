#ifndef ENEMY_3_H
#define ENEMY_3_H

#include "enemy_base.h"
#include <QObject>

class enemy_3 : public enemy_base
{
    Q_OBJECT
public:
    explicit enemy_3(QPointF point_, qreal speed_, QGraphicsScene *scene_,QObject *parent = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPixmap pixmap;
signals:
};

#endif // ENEMY_3_H
