#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "global.h"
#include "hero.h"
//#include "enemy_base.h"

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsItem>
class obstacle : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit obstacle(QGraphicsScene *scene_,QRectF rect_,QPointF pos_,QObject *parent = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){};
private:
    QRectF rects_;
signals:
};

#endif // OBSTACLE_H
