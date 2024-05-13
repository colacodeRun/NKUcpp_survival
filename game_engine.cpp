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
QList<QString> level_up_button_normal ={
    "://image/icons/upgrades/u_hollowpoint_idle.png",
    "://image/icons/upgrades/u_streamline_idle.png",
    "://image/icons/upgrades/u_inthewind_idle.png",
    "://image/icons/upgrades/u_heavybarrel_idle.png",
    "://image/icons/upgrades/u_vitality_idle.png"
};
QList<QString> level_up_button_hovered ={
    "://image/icons/upgrades/u_hollowpoint_hover.png",
    "://image/icons/upgrades/u_streamline_hover.png",
    "://image/icons/upgrades/u_inthewind_hover.png",
    "://image/icons/upgrades/u_heavybarrel_hover.png",
    "://image/icons/upgrades/u_vitality_hover.png"
};
QList<QString> level_up_introduce ={
    "子弹速度提高35%",
    "射速提高30%",
    "人物移动速度提高25%",
    "伤害提高50%",
    "生命值上限提高1"
};

game_engine::game_engine(QWidget *parent)
    : QGraphicsView{parent}
{

    //音乐配置
    soundEffect = new QSoundEffect;
    soundEffect->setSource(QUrl::fromLocalFile("://bgm/infinite night sky - DDRKirby(ISQ).wav"));
    soundEffect->setLoopCount(QSoundEffect::Infinite);
    soundEffect->setVolume(0.35f);
    soundEffect->play();

    //this->setFixedSize(game_widget_width,game_widget_height);
    //窗口配置
    resize(game_widget_width,game_widget_height);
    setWindowIcon(QIcon("://image/icons/Myicon.ico"));
    setWindowTitle("Survival");
    //初始化视图
    map_scene =new background_scene(this);
    this->setScene(map_scene);
    gun = new weapon(map_scene,map_scene->hero_item->scenePos());
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->centerOn(map_scene->hero_item);

    //设置字体
    font.setFamily("Minecraft AE");

    //结束语
    loser_end = new QLabel(this);
    loser_end -> move(225,300);
    loser_end -> setFont(font);
    loser_end -> setText("You  Lose");
    loser_end -> setStyleSheet("QLabel { color : red; font : 100pt }");
    loser_end -> hide();
    winer_end =new QLabel(this);
    winer_end -> move(300,300);
    winer_end -> setFont(font);
    winer_end -> setText("You Win");
    winer_end -> setStyleSheet("QLabel { color : white; font : 100pt }");
    winer_end -> hide();

    //初始化游戏时间
    time_len = 300;
    time_now = new QLabel(this);
    time_now -> move(44,44);
    time_now -> setText(QString("Time :  %1:%2").arg(time_len/60).arg(time_len%60,2,10,QChar('0')));
    time_now -> setFont(font);
    time_now -> setStyleSheet("QLabel {color : white ; font : 20pt}");
    //初始化经验值
    exp_num = 0;
    level =1;
    exp = new QLabel(this);
    exp -> move(44,75);
    exp -> setText(QString("Level %1 :  %2/%3").arg(level).arg(exp_num).arg(pow(level-1,2)+10));
    exp -> setFont(font);
    exp -> setStyleSheet("QLabel {color : white ; font : 20pt}");
    //初始化升级buttons和label
    for(int i=0;i<3;++i){
        up_buttons.append(new QPushButton(this));
        up_introductions.append(new QLabel(this));
        up_buttons[i] -> move(252.5+300*i,350);
        up_buttons[i] -> setFixedSize(up_button_width,up_button_height);
        up_buttons[i] ->setFlat(true);
        up_introductions[i] -> setFont(font);
        up_introductions[i] -> setStyleSheet("QLabel { color : white; font : 15pt }");
        up_introductions[i] -> hide();
        up_buttons[i] -> hide();
    }
    //障碍物初始化
    QRectF rects(0,0,150,300);
    for(int i=0;i<5;++i){
        obstacles.push_back(new obstacle(map_scene,rects,poses[i]));
    }

    //攻击范围
    attack_extent = 450;
    //生命初始化
    health_total = health_now = 4;
    heart_list.push_back(new heart_lable(this));
    for(int i= 1;i<=3;++i){
        for(auto &heart : heart_list){
            heart -> move(heart->pos().x()-44,44);
        }
        heart_list.push_back(new heart_lable(this));
    }
    //敌人数目计数器
    enemy_num = 0;
    //初始化计时器
    timer =new QTimer(this);
    timer->setInterval(200);
    timer->start();
    bullet_timer =new QTimer(this);
    bullet_timer->start(400);
    enemy_timer =new QTimer(this);
    enemy_timer-> start(1000);
    hurt_timer = new QTimer(this);
    hurt_timer -> start(1000);
    main_timer = new QTimer(this);
    main_timer -> start(1000);
    bullet_enemy_generate_timer = new QTimer(this);
    bullet_enemy_generate_timer->start(4000);

    connect(hurt_timer,&QTimer::timeout,this ,&game_engine::hero_gain_hurt);
    connect(enemy_timer,&QTimer::timeout,this,&game_engine::enemy_generate);
    connect(bullet_timer,&QTimer::timeout,this,&game_engine::gun_fire);
    connect(timer,&QTimer::timeout,this,&game_engine::view_update);
    connect(main_timer,&QTimer::timeout,this,&game_engine::time_change);
    connect(bullet_enemy_generate_timer,&QTimer::timeout,this,&game_engine::enemy_bullet_generate);

    connect(this ,&game_engine :: up_selection_make,this,&game_engine::up_hide);
    //设置聚焦
    this->setFocus();

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
    qreal hero_speed = map_scene -> hero_item -> gain_move_speed();
    qreal width = map_scene->hero_item->boundingRect().width();
    qreal height = map_scene ->hero_item->boundingRect().height();
    if(map_scene->hero_item->x()-width/2+dx>=map_left &&
        map_scene->hero_item->y()-height/2+dy>=map_top &&
        map_scene->hero_item->x()+width/2+dx<=map_right &&
        map_scene->hero_item->y()+height/2+dy<=map_underneath)
    {
        map_scene->hero_item->setPos(map_scene->hero_item->x()+dx*hero_speed,map_scene->hero_item->y()+dy*hero_speed);
    }
    //人物与障碍物碰撞检测
    for(int i=0;i<5;++i){
        if(map_scene->hero_item->collidesWithItem(obstacles[i]))
        {
            map_scene->hero_item->setPos(map_scene->hero_item->x()-dx*hero_speed,map_scene->hero_item->y()-dy*hero_speed);
           // qDebug()<<"test";
        }
    }
    map_scene->hero_item->movie->start();
    dx=0;
    dy=0;
}

void game_engine::timer_stop()
{
        timer -> stop();
        hurt_timer -> stop();
        enemy_timer -> stop();
        bullet_timer -> stop();
        main_timer -> stop();
        bullet_enemy_generate_timer ->stop();
        map_scene->hero_item->can_hurt=false;
}



void game_engine::timer_start()
{
    timer -> start();
    hurt_timer -> start();
    enemy_timer -> start();
    bullet_timer -> start();
    main_timer -> start();
    bullet_enemy_generate_timer ->start();
    map_scene->hero_item->can_hurt=true;
}
//游戏时间字面更改
void game_engine::time_change()
{
    --time_len;
    time_now -> setText(QString("Time :  %1:%2").arg(time_len/60).arg(time_len%60,2,10,QChar('0')));
    if(time_len == 0){
        win();
    }

}

void game_engine::delete_item()
{
    delete map_scene;
    for(auto heart:heart_list){
        delete heart;
    }
    delete time_now;
    delete exp;
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
        if(!enemy_list.empty())
        {
            enemy_base* target_enemy = enemy_list[0];
        for(auto enemy:enemy_list){
                if(enemy->distance_hero<target_enemy->distance_hero){
                target_enemy = enemy;
            }
        }
        qreal angle = gain_angle(map_scene->hero_item->scenePos(),target_enemy->scenePos());
        if(target_enemy->distance_hero<=attack_extent){
            bullet_gun *bullet=new bullet_gun(map_scene->hero_item->scenePos(),angle,gun,map_scene);
            gun->gain_angle(target_enemy->scenePos());
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
            it.remove();
            obs ->deleteLater();
            --enemy_num;
            exp_up();
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
    int i = QRandomGenerator::global()->bounded(8);//随机出生点
    int x = QRandomGenerator::global()->bounded(3);//随机出生敌人
    if(enemy_num<=enemy_num_top){
        switch (x) {
        case 0:
            enemy_list.push_back(new enemy_1(enemy_generate_poses[i],18,map_scene));
            break;
        case 1:
            enemy_list.push_back(new enemy_2(enemy_generate_poses[i],20,map_scene));
            break;
        case 2:
            enemy_list.push_back(new enemy_3(enemy_generate_poses[i],16,map_scene));
            break;
        default:
            break;
        }
        qreal dx = map_scene->hero_item->x()-enemy_list.last()->x(),
            dy =map_scene->hero_item->y()-enemy_list.last()->y();
        enemy_list.last()->distance_hero =sqrt(pow(dx,2)+pow(dy,2));
        ++enemy_num;
    }
}

//生成敌人子弹
void game_engine::enemy_bullet_generate()
{
    if(!enemy_list.empty()){
        for(enemy_base* enemy : enemy_list) {
            enemy_3* enemy3 = dynamic_cast<enemy_3*>(enemy);
            if(enemy3 != nullptr){//只有enemy_3能发射子弹
                bullet_enemy_3*new_bullet =new bullet_enemy_3(enemy3->scenePos(),map_scene->hero_item,map_scene);
                connect(new_bullet,&bullet_enemy_3::hurt_hero,[=](){
                    if(health_now > 0){//防止越界访问
                        lose_heart();
                    }
                    if(health_now == 0)hero_die();
                });
            }
        }
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

//升级
void game_engine::exp_up()
{
    ++exp_num;
    level_up();
    exp -> setText(QString("Level %1 :  %2/%3").arg(level).arg(exp_num).arg(pow(level-1,2)+10));
    exp -> adjustSize();
}
//字面升级
void game_engine::level_up()
{
    if(exp_num >= pow(level-1,2)+10){
        ++level;
        exp_num = 0;
        up_select();
    }
}

//射速提高up
void game_engine::up_bullet_generate_speed()
{
    gun ->up_generate_speed();
    bullet_timer -> setInterval(400/gun ->gain_generate_speed());
}

//增加生命值up
void game_engine::up_health()
{
    ++health_now;
    ++health_total;
    for(auto &heart : heart_list){
        heart -> move(heart->pos().x()-44,44);
    }
    heart_list.push_back(new heart_lable(this));
    heart_list[health_total-1]->show();
}

//产生升级选项
void game_engine::up_select()
{
    timer_stop();
    QList<int> numbers;
    while (numbers.size() < 3) {
        int number = QRandomGenerator::global()->bounded(5);
        if (!numbers.contains(number)) {
            numbers.append(number);
        }
    }
    for(int i=0;i<3;++i){
        QPixmap pixmap_normal = level_up_button_normal[numbers[i]];
        pixmap_normal.scaled(up_button_width,up_button_height,Qt::IgnoreAspectRatio);
        up_buttons[i]->setStyleSheet(QString("QPushButton{border-image:url(%1);}"//用样式表设置按钮形式，实现鼠标悬浮效果
                                       "QPushButton:hover{border-image:url(%2);}")
                                         .arg(level_up_button_normal[numbers[i]])
                                         .arg(level_up_button_hovered[numbers[i]])
                               );
        up_buttons[i] -> show();
        up_introductions[i] -> setText(level_up_introduce[numbers[i]]);
        up_introductions[i] ->adjustSize();
        up_introductions[i] ->move(up_buttons[i]->pos().x()+up_button_width/2-up_introductions[i]->width()/2,
                                  up_buttons[i]->pos().y()+up_button_height+8);
        up_introductions[i] ->show();
        connect(up_buttons[i],&QPushButton::pressed,[=](){
            up_function_select(numbers[i]);
            emit up_selection_make();
        });
        }
}

//升级选择处理
void game_engine::up_function_select(int num)
{
    switch (num) {
    case 0:
        gun->up_bullet_speed();
        break;
    case 1:
        up_bullet_generate_speed();
        break;
    case 2:
        map_scene -> hero_item ->up_move_speed();
        break;
    case 3:
        gun -> up_damage();
        break;
    case 4:
        up_health();
        break;
    default:
        break;
    }
}
//升级结束处理
void game_engine::up_hide()
{
    for(int i=0;i<3;++i){
        up_buttons[i]-> hide();
        up_introductions[i] -> hide();
    }
    for(auto button:up_buttons){
        button->disconnect();
    }
    timer_start();
}

//人物受伤和死亡判断
void game_engine::hero_gain_hurt()
{
    if(health_now > 0){//防止越界访问
    for(auto enemy: enemy_list){
        if(enemy->collidesWithItem(map_scene->hero_item)){
            lose_heart();
        }
    }
    if(health_now <= 0)hero_die();
    }
}
//生命图标改变
void game_engine::lose_heart()
{
    heart_list[health_total-health_now] -> lose_heart();
    --health_now;
}
//出现失败画面
void game_engine::hero_die()
{
    timer_stop();
    // delete_item();
    loser_end -> show();
    setStyleSheet("background-color: rgb(34,34,34);");
}
//出现胜利画面
void game_engine::win()
{
    timer_stop();
    // delete_item();
    winer_end -> show();
    setStyleSheet("background-color: rgb(34,34,34);");
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
