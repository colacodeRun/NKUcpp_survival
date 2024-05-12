#ifndef BULLET_GUN_H
#define BULLET_GUN_H

#include"bullet_base.h"

#include <QObject>
#include <QPainter>

class bullet_gun : public bullet_base
{
    Q_OBJECT
public:
    explicit bullet_gun(QPointF pos_,qreal angle_,weapon *weapon_,QGraphicsScene *scene_,QObject *parent = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QPixmap bullet_pixmap;
signals:
};

#endif // BULLET_GUN_H
