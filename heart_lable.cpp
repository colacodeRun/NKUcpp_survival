#include "heart_lable.h"

heart_lable::heart_lable(QGraphicsView *view,QLabel *parent)
    :QLabel{parent}
{

    full_heart.load("://image/icons/heart_full.png");
    empty_heart.load("://image/icons/heart_empty.png");
    is_full =true;
    setPixmap(full_heart);
    setParent(view);
    setGeometry(1200-44-32,44,32,32);
}

void heart_lable::lose_heart()
{
    setPixmap(empty_heart);
    is_full =false;
}

bool heart_lable::check_full()
{
    return is_full;
}
