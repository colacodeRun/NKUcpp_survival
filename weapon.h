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
private:
    qreal move_angle;
    QPixmap pixmap;
signals:
};

#endif // WEAPON_H
