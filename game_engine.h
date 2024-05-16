#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include"background_scene.h"
#include"global.h"
#include"bullet_gun.h"
#include "enemy_1.h"
#include "obstacle.h"
#include "weapon.h"
#include "heart_lable.h"
#include "enemy_2.h"
#include "enemy_3.h"
#include "bullet_enemy_3.h"
#include <QPushButton>
#include <QWidget>
#include<QGraphicsView>
#include<QTimer>
#include<QMap>
#include<QKeyEvent>
#include<cmath>
#include <QRandomGenerator>
#include <QSoundEffect>
class game_engine : public QGraphicsView
{
    friend class background_scene;
    friend class hero;
    Q_OBJECT
public:
    explicit game_engine(QWidget *parent = nullptr);
    //人物和敌人动画更新
    void view_update();
    void hero_update();
    void hero_run_stand();
    //计时器停止，开始以及清理内存
    void timer_stop();
    void timer_start();
    void time_change();
    void delete_item();

    void map_scene_update();
    qreal gain_angle(QPointF a,QPointF b);

    //开火
    void gun_fire();

    //敌人生成，敌人自动寻路，敌人死亡，敌人子弹生成
    void enemy_death();
    void enemy_update();
    void enemy_generate();
    void enemy_bullet_generate();
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
    //音乐
    QSoundEffect *soundEffect;
    //计时器
    QTimer *timer;
    QTimer *bullet_timer;
    QTimer *enemy_timer;
    QTimer *hurt_timer;
    QTimer *bullet_enemy_generate_timer;
    QTimer *main_timer;
    int time_len;

    //字体和各种文字
    QFont font;
    QLabel *loser_end;
    QLabel *winer_end;
    QLabel *time_now;
    QLabel *exp;

    int health_now;//生命值
    int health_total;

    int exp_num;
    int level;
    //存储生命值按钮和文字
    QList<QPushButton*> up_buttons;
    QList<QLabel*>up_introductions;

    QList<heart_lable *>heart_list;//存储生命贴图
    qreal attack_extent;//攻击范围
    QList<obstacle*> obstacles ;
    background_scene *map_scene;

    int lastkey=Qt::Key_D;//用于加载贴图
    double dx=0,dy=0;//用于移动hero
    //用于移动
    QMap<int,bool> keymap=
    {
        {Qt::Key_W,false},
        {Qt::Key_A,false},
        {Qt::Key_S,false},
        {Qt::Key_D,false}
    };
<<<<<<< HEAD
    QMap<int,bool>check_key_map=
        {
            {Qt::Key_W,false},
            {Qt::Key_A,false},
            {Qt::Key_S,false},
            {Qt::Key_D,false}
        };
=======

>>>>>>> 8e9afc1ed8e787583f1fcdd594eba75c256b7e81
    //存储敌人的链表
    QList<enemy_base*>enemy_list;
    qreal enemy_num;
    weapon *gun;
signals:
    void up_selection_make();

};

#endif // GAME_ENGINE_H
