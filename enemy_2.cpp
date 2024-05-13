#include "enemy_2.h"

enemy_2::enemy_2( QPointF point_, qreal speed_, QGraphicsScene *scene_, QObject *parent)
    : enemy_base(point_,speed_,scene_)
{
    damage = 1;
    health = 4;
    movie = new QMovie(this);
    movie -> setFileName("://image/enemy/en_bot.gif");
    movie ->setSpeed(50);
    movie ->start();
    connect(movie, &QMovie::frameChanged, this, [this](int) {
        update();
    });
}

QRectF enemy_2::boundingRect() const
{
    QPixmap pixmap = movie ->currentPixmap();
    qreal width = pixmap.width();
    qreal height = pixmap.height();
    return QRectF(-width/2, -height/2, width, height);
}

void enemy_2::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap pixmap = movie ->currentPixmap();
    qreal width = pixmap.width();
    qreal height = pixmap.height();
    painter->drawPixmap(-width/2, -height/2, movie->currentPixmap());
}

