#include "bullet_enemy_3.h"


bullet_enemy_3::bullet_enemy_3(QPointF pos_, hero *hero_, QGraphicsScene *scene_,  QObject *parent)
    : QObject(parent),bullet_pos(pos_),my_hero(hero_),map_scene(scene_)
{
    pixmap.load("://image/enemy/en_bullet.png");
    map_scene ->addItem(this);
    setPos(bullet_pos);
    qreal dx = my_hero ->scenePos().x() - bullet_pos.x(),
        dy = my_hero -> scenePos().y() - bullet_pos.y();
    angle = M_PI/2 - qAtan2(dy,dx);
    setScale(2);
    speed = 5.2;
    timer = new QTimer(this);
    timer -> start(40);
    connect(timer,&QTimer::timeout,this,&bullet_enemy_3::bullet_hit_check);
    connect(timer,&QTimer::timeout,this,&bullet_enemy_3::bullet_move);
}

void bullet_enemy_3::bullet_move()
{
    qreal dx=speed*qSin(angle);
    qreal dy=speed*qCos(angle);
    setPos(x()+dx,y()+dy);
}

void bullet_enemy_3::bullet_hit_check()
{
    if(collidesWithItem(my_hero)&&my_hero->can_hurt){
        emit hurt_hero();
        deleteLater();
        //this->disconnect();
    }
    if (x() < 0 || x() > 4800 || y() < 0 || y() > 2700)
        deleteLater();
}

QRectF bullet_enemy_3::boundingRect() const
{
    return QRectF(-enemy_bullet_width/2,-enemy_bullet_height/2, enemy_bullet_width, enemy_bullet_height);
}

void bullet_enemy_3::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-enemy_bullet_width/2,-enemy_bullet_height/2, pixmap);
}

bullet_enemy_3::~bullet_enemy_3()
{
    delete timer;
}

