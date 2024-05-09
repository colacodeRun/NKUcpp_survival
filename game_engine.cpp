#include "game_engine.h"
#include <QDebug>

game_engine::game_engine(QWidget *parent)
    : QGraphicsView{parent}
{
    this->setFixedSize(game_widget_width,game_widget_height);//设置大小

    //初始化视图
    map_scene =new background_scene(this);
    this->setScene(map_scene);
    // this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->centerOn(map_scene->hero_item);

    //初始化计时器
    timer =new QTimer(this);
    timer->setInterval(200);
    timer->start();
    connect(timer,&QTimer::timeout,this,&game_engine::view_update);
    //设置聚焦
    this->setFocus();
}

//更新视图
void game_engine::view_update()
{w
    this->hero_update();
    this->map_scene_update();
}

//更新hero位置与贴图
void game_engine::hero_update()
{
    map_scene->hero_item->movie->stop();
    bool flag=false;
    for (QMap<int, bool>::iterator it = keymap.begin(); it != keymap.end(); ++it)
    {
        if(it.value())
        {
            flag=true;
            if(it.key()==Qt::Key_W || it.key()==Qt::Key_S)
            {
                if(lastkey==Qt::Key_D)
                {
                    map_scene->hero_item->movie->setFileName("://image/hero_run_right.gif");
                }
                if(lastkey==Qt::Key_A)
                {
                    map_scene->hero_item->movie->setFileName("://image/hero_run_left.gif");
                }
                if(it.key()==Qt::Key_W)dy-=mobile_step;
                if(it.key()==Qt::Key_S)dy+=mobile_step;
            }
            if(it.key()==Qt::Key_D)
            {
                map_scene->hero_item->movie->setFileName("://image/hero_run_right.gif");
                dx+=mobile_step;
            }
            if(it.key()==Qt::Key_A){
                map_scene->hero_item->movie->setFileName("://image/hero_run_left.gif");
                dx-=mobile_step;
            }
        }
    }
    if(!flag)
    {
        for (QMap<int, bool>::iterator it = keymap.begin(); it != keymap.end(); ++it)
        {
            if(!it.value()){
                if(lastkey==Qt::Key_D){
                    map_scene->hero_item->movie->setFileName("://image/hero_stand_right.gif");
                }
                else if(lastkey==Qt::Key_A){
                    map_scene->hero_item->movie->setFileName("://image/hero_stand_left.gif");
                }
            }
        }
    }
    if(map_scene->hero_item->x()+dx>=map_left &&
        map_scene->hero_item->y()+dy>=map_top &&
        map_scene->hero_item->x()+hero_width+dx<=map_right &&
        map_scene->hero_item->y()+hero_height+dy<=map_underneath)
    {
        map_scene->hero_item->setPos(map_scene->hero_item->x()+dx,map_scene->hero_item->y()+dy);
    }
    map_scene->hero_item->movie->start();
    dx=0;
    dy=0;
}

//更新视口中心位置
void game_engine::map_scene_update()
{
    this->centerOn(map_scene->hero_item);
}

void game_engine::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W || event->key()==Qt::Key_A || event->key()==Qt::Key_S || event->key()==Qt::Key_D)
    {
        keymap[event->key()]=true;
        if(event->key()==Qt::Key_D||event->key()==Qt::Key_A)lastkey=event->key();
    }
}

void game_engine::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W || event->key()==Qt::Key_A || event->key()==Qt::Key_S || event->key()==Qt::Key_D)
    {
        keymap[event->key()]=false;
    }
}

