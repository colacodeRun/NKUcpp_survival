#ifndef BACKGROUND_SCENE_H
#define BACKGROUND_SCENE_H

#include"global.h"
#include"hero.h"

#include <QObject>
#include<QGraphicsScene>
class background_scene : public QGraphicsScene
{
    friend class game_engine;
    Q_OBJECT
public:
    explicit background_scene(QObject *parent = nullptr);
private:
    hero *hero_item;

signals:
};

#endif // BACKGROUND_SCENE_H
