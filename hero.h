#ifndef HERO_H
#define HERO_H

#include "global.h"

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QMovie>
#include <QPainter>
#include <QTimer>
class hero : public QObject,public QGraphicsItem
{
    Q_OBJECT
    friend class game_engine;
    friend class background_scene;
public:
    explicit hero(QObject *parent = nullptr);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    qreal gain_move_speed();
    void up_move_speed();

private:
    qreal move_speed;
    QMovie *movie;
    QTimer *timer;//动画播放计时器

signals:
};

#endif // HERO_H
