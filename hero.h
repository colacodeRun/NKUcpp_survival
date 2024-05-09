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

private:
    QMovie *movie;
    QTimer *timer;

signals:
};

#endif // HERO_H
