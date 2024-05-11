#ifndef HEART_LABLE_H
#define HEART_LABLE_H
#include "global.h"

#include <QObject>
#include <QLabel>
#include <QGraphicsView>
#include <QPainter>
class heart_lable : public QLabel
{
    Q_OBJECT
public:
    explicit heart_lable(QGraphicsView *view, QLabel *parent = nullptr);
    void lose_heart();
    bool check_full();
private:
    bool is_full;
    QPixmap full_heart;
    QPixmap empty_heart;
signals:
};

#endif // HEART_LABLE_H
