#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include"background_scene.h"
#include"global.h"
#include"bullet_gun.h"
#include "enemy_1.h"
#include "obstacle.h"
#include "weapon.h"
#include "heart_lable.h"

#include <QPushButton>
#include <QWidget>
#include<QGraphicsView>
#include<QTimer>
#include<QMap>
#include<QKeyEvent>
#include<cmath>
#include <QRandomGenerator>
class game_engine : public QGraphicsView
{
    friend class background_scene;
    friend class hero;
    Q_OBJECT
public:
    explicit game_engine(QWidget *parent = nullptr);
    void view_update();
    void hero_update();

    void timer_stop();
    void timer_start();
    void time_change();
    void delete_item();

    void map_scene_update();
    qreal gain_angle(QPointF a,QPointF b);
    void gun_fire();

    void enemy_death();
    void enemy_update();
    void enemy_generate();
    bool enemy_hit_obstacle_check(enemy_base *x,obstacle *y,qreal angle);
    qreal gain_points_distance(QPointF n,QPointF m);

    //升级
    void exp_up();
    void level_up();
    void up_bullet_generate_speed();
    void up_health();
    void up_select();
    void up_function_select(int num);
    void up_hide();


    //英雄受伤和死亡判断
    void hero_gain_hurt();
    void lose_heart();
    void hero_die();
    //胜利
    void win();
protected:
    void wheelEvent(QWheelEvent *event){}
    void keyPressEvent(QKeyEvent *eyent);
    void keyReleaseEvent(QKeyEvent *event);
private:
    int cnt=0;
    QTimer *timer;
    QTimer *bullet_timer;
    QTimer *enemy_timer;
    QTimer *hurt_timer;
    QTimer *main_timer;
    int time_len;

    QFont font;
    QLabel *loser_end;
    QLabel *winer_end;
    QLabel *time_now;
    QLabel *exp;

    int health_now;//生命值
    int health_total;

    int exp_num;
    int level;
    QList<QPushButton*> up_buttons;
    QList<QLabel*>up_introductions;

    QList<heart_lable *>heart_list;
    qreal attack_extent;
    QList<obstacle*> obstacles ;
    background_scene *map_scene;
    int lastkey=Qt::Key_D;
    double dx=0,dy=0;
    QMap<int,bool> keymap=
    {
        {Qt::Key_W,false},
        {Qt::Key_A,false},
        {Qt::Key_S,false},
        {Qt::Key_D,false}
    };
    QList<enemy_base*>enemy_list;
    qreal enemy_num;
    weapon *gun;
signals:
    void up_selection_make();

};

#endif // GAME_ENGINE_H
