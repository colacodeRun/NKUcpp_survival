#include "game_engine.h"

#include<algorithm>
#include <QDebug>
#include <cmath>
QList<QPointF> poses={
    QPointF(879,759),
    QPointF(3770,760),
    QPointF(2321,1139),
    QPointF(880,1550),
    QPointF(3769,1550),
};
QList<QPointF> enemy_generate_poses={
    QPointF(map_left,map_top),
    QPointF(map_left,map_underneath),
    QPointF(map_right,map_top),
    QPointF(map_right,map_underneath),
    QPointF(map_right-1500,map_top),
    QPointF(map_right-3000,map_top),
    QPointF(map_right-1500,map_underneath),
    QPointF(map_right-3000,map_underneath),
};
game_engine::game_engine(QWidget *parent)
    : QGraphicsView{parent}
{
    this->setFixedSize(game_widget_width,game_widget_height);//设置窗口大小
    setStyleSheet("background-color: rgb(34,34,34);");
    QFont pixelFont;
    pixelFont.setFamily("Minecraft AE");
    QLabel *label = new QLabel("You Lose", this); // 创建一个QLabel对象，并将其添加到窗口中
    label->setStyleSheet("color: white; font-size: 100px;");
    label->setFont(pixelFont);
    label ->move(200,300);
    // //初始化视图
    // map_scene =new background_scene(this);
    // this->setScene(map_scene);
    // gun = new weapon(map_scene,map_scene->hero_item->scenePos());
    // // gun->move_gun();
    // // this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // // this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // this->centerOn(map_scene->hero_item);
    // //障碍物初始化
    // QRectF rects(0,0,150,300);
    // for(int i=0;i<5;++i){
    //     obstacles.push_back(new obstacle(map_scene,rects,poses[i]));
    // }

    // //攻击范围
    // attack_extent = 300;
    // //生命
    // health = 4;
    // heart_list.push_back(new heart_lable(this));
    // for(int i= 1;i<=3;++i){
    //     heart_list.push_back(new heart_lable(this));
    //     heart_list[i]->move(heart_list[i-1]->pos().x()-44,44);
    // }
    // //敌人数目计数器
    // enemy_num = 0;
    // //初始化计时器
    // timer =new QTimer(this);
    // timer->setInterval(200);
    // timer->start();
    // bullet_timer =new QTimer(this);
    // bullet_timer->start(400);
    // enemy_timer =new QTimer(this);
    // enemy_timer-> start(1000);

    // connect(enemy_timer,&QTimer::timeout,this,&game_engine::enemy_generate);
    // connect(bullet_timer,&QTimer::timeout,this,&game_engine::gun_fire);
    // connect(timer,&QTimer::timeout,this,&game_engine::view_update);
    // //设置聚焦
    // this->setFocus();

}

//更新视图
void game_engine::view_update()
{
    hero_update();
    map_scene_update();
    gun->setPos(map_scene->hero_item->scenePos());
    enemy_death();
    enemy_update();
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
    //边界检测
    if(map_scene->hero_item->x()-hero_width/2+dx>=map_left &&
        map_scene->hero_item->y()-hero_height/2+dy>=map_top &&
        map_scene->hero_item->x()+hero_width/2+dx<=map_right &&
        map_scene->hero_item->y()+hero_height/2+dy<=map_underneath)
    {
        map_scene->hero_item->setPos(map_scene->hero_item->x()+dx,map_scene->hero_item->y()+dy);
    }
    //人物与障碍物碰撞检测
    for(int i=0;i<5;++i){
        if(map_scene->hero_item->collidesWithItem(obstacles[i]))
        {
            map_scene->hero_item->setPos(map_scene->hero_item->x()-dx,map_scene->hero_item->y()-dy);
           // qDebug()<<"test";
        }
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

//获取坐标间角度（到正x轴)
qreal game_engine::gain_angle(QPointF a, QPointF b)
{
    qreal dx = b.x()-a.x(),
        dy = b.y()-a.y();
    return qAtan2(dy,dx);
}

//开火
void game_engine::gun_fire()
{
        if(enemy_num>0)
        {
        std::sort(enemy_list.begin(),enemy_list.end(),[](enemy_base *a,enemy_base *b){
            return a->distance_hero<=b->distance_hero;
        });
        qreal angle = gain_angle(map_scene->hero_item->scenePos(),enemy_list[0]->scenePos());
        if(enemy_list[0]-> distance_hero<=attack_extent){
            bullet_gun *bullet=new bullet_gun(map_scene->hero_item->scenePos(),angle,1,map_scene);
            gun->gain_angle(enemy_list[0]->scenePos());
            gun->move_gun();
        }
        }
}

//敌人死亡判断
void game_engine::enemy_death()
{
    QMutableListIterator<enemy_base*> it(enemy_list);
    while(it.hasNext()) {
        enemy_base* obs = it.next();
        if(obs->enemy_die()) {
            obs ->deleteLater();
            it.remove();
            --enemy_num;
        }
    }
}

//敌人自动寻路
void game_engine::enemy_update()
{
        for (QList<enemy_base*>::iterator it1 = enemy_list.begin(); it1 != enemy_list.end(); ++it1) {
            bool flag=true;
            qreal angle=(*it1)->move_angle(map_scene->hero_item->scenePos());
            for(QList<obstacle*>::iterator it2=obstacles.begin();it2 != obstacles.end();++it2){
                if(enemy_hit_obstacle_check(*it1,*it2,angle)){
                    flag=false;
                    QList<QPair<qreal,qreal>>list;
                    //dfs回溯寻找方向
                    for(int i=0;i<4;++i){
                        (*it1)->enemy_move(M_PI/2*i);
                        qreal distance = gain_points_distance((*it1)->scenePos(),map_scene->hero_item->scenePos());
                        if(!(*it1)->collidesWithItem(*it2)){
                            list.push_back({M_PI/2*i,distance});
                        }
                        (*it1)->enemy_move(M_PI/2*i-M_PI);
                    }
                    //取distance最短的路径
                    std::sort(list.begin(),list.end(),[](QPair<qreal,qreal> &a,QPair<qreal,qreal> &b){
                        return a.second<=b.second;
                    });
                    (*it1)->enemy_move(list[0].first);
                    (*it1)->distance_hero = gain_points_distance((*it1)->scenePos(),map_scene->hero_item->scenePos());
                    break;
                }
            }
            if(flag){
                (*it1)->distance_hero = gain_points_distance((*it1)->scenePos(),map_scene->hero_item->scenePos());
                (*it1)->enemy_move(angle);
            }
        }
}

//敌人生成器
void game_engine::enemy_generate()
{
    int i = QRandomGenerator::global()->bounded(8);
    if(enemy_num<=30){
        enemy_list.push_back(new enemy_1(enemy_generate_poses[i],15,map_scene));
        ++enemy_num;
    }
}

//回溯法判断敌人碰撞障碍物
bool game_engine::enemy_hit_obstacle_check(enemy_base *x, obstacle *y, qreal angle)
{
        x->enemy_move(angle);
        if(x->collidesWithItem(y)){
            x->enemy_move(angle-M_PI);
            return true;
        }
        else{
            x->enemy_move(angle-M_PI);
            return false;
        }
}



qreal game_engine::gain_points_distance(QPointF n, QPointF m)
{
    return sqrt(pow(n.x()-m.x(),2)+pow(n.y()-m.y(),2));
}

//获取键盘按下和释放，实现长按移动
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
