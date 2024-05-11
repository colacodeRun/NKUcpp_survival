#include "background_scene.h"

background_scene::background_scene(QObject *parent)
    : QGraphicsScene{parent}
{
    QPixmap pixmap("://image/background_gameplay.png");
    this->setBackgroundBrush(pixmap);
    this->setSceneRect(0,0,map_width,map_height);

    hero_item = new hero(this);
    this->addItem(hero_item);
    hero_item->setPos(map_width/2-hero_width/2,200+map_height/2-hero_height/2);
}
