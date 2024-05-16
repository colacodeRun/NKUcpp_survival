#include "hero.h"

#include<QDebug>
hero::hero(QObject *parent)
    : QObject{parent}
{
    can_hurt =true;
    movie = new QMovie(this);
    movie->setFileName("://image/hero_stand_right.gif");
    movie->setSpeed(45);
    movie->start();
    setScale(3.5);
    //gif帧变化信号连接图元更新槽函数
    connect(movie, &QMovie::frameChanged, this, [this](int) {
        update();
    });
    move_speed =1;
}

QRectF hero::boundingRect() const
{
    QPixmap pixmap = movie ->currentPixmap();
    qreal width = pixmap.width();
    qreal height = pixmap.height();
    return QRectF(-width/2, -height/2, width, height);
}

void hero::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap = movie ->currentPixmap();
    qreal width = pixmap.width();
    qreal height = pixmap.height();
    painter->drawPixmap(-width/2, -height/2, movie->currentPixmap());
}

qreal hero::gain_move_speed()
{
    return move_speed;
}

void hero::up_move_speed()
{
    move_speed *= 1.25;
}


