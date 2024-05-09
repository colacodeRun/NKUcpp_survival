#include "hero.h"

#include<QDebug>
hero::hero(QObject *parent)
    : QObject{parent}
{
    movie = new QMovie(this);
    movie->setFileName("://image/hero_stand_right.gif");
    movie->setSpeed(85);
    movie->start();
    //gif帧变化信号连接图元更新槽函数
    connect(movie, &QMovie::frameChanged, this, [this](int) {
        update();
    });
}

QRectF hero::boundingRect() const
{
    return QRectF(0, 0, hero_width, hero_height);
}

void hero::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, 0, movie->currentPixmap().scaled(hero_width, hero_height, Qt::KeepAspectRatio));
}
