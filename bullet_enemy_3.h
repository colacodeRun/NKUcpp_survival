#ifndef BULLET_ENEMY_3_H
#define BULLET_ENEMY_3_H

#include "background_scene.h"
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsObject>

class bullet_enemy_3 : public QObject ,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit bullet_enemy_3(QPointF pos_,hero *hero_,QGraphicsScene *scene_,QObject*parent = nullptr);
    void bullet_move();
    void bullet_hit_check();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private:
    QTimer *timer;
    QPointF bullet_pos;
    qreal angle;
    qreal speed;
    hero *my_hero;
    QGraphicsScene *map_scene;
    QPixmap pixmap;
    ~bullet_enemy_3();

signals:
    void hurt_hero();
};

#endif // BULLET_ENEMY_3_H
