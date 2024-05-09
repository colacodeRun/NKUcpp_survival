#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include"background_scene.h"
#include"global.h"


#include <QWidget>
#include<QGraphicsView>
#include<QTimer>
#include<QMap>
#include<QKeyEvent>

class game_engine : public QGraphicsView
{
    friend class background_scene;
    friend class hero;
    Q_OBJECT
public:
    explicit game_engine(QWidget *parent = nullptr);
    void view_update();
    void hero_update();
    void map_scene_update();
protected:
    void wheelEvent(QWheelEvent *event){}
    void keyPressEvent(QKeyEvent *eyent);
    void keyReleaseEvent(QKeyEvent *event);
private:
    background_scene *map_scene;
    QTimer *timer;
    int lastkey=Qt::Key_D;
    int dx=0,dy=0;
    QMap<int,bool> keymap=
    {
        {Qt::Key_W,false},
        {Qt::Key_A,false},
        {Qt::Key_S,false},
        {Qt::Key_D,false}
    };
signals:
};

#endif // GAME_ENGINE_H
