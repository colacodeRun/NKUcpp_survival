#ifndef GAME_WIDGET_H
#define GAME_WIDGET_H

#include "global.h"

#include <QWidget>
#include <QLabel>
class game_widget : public QObject
{
    Q_OBJECT
public:
    explicit game_widget(QObject *parent = nullptr);
    QWidget *winer_end;
    QWidget *loser_end;
    QLabel *winer_notice;
    QLabel *loser_notice;
signals:
};

#endif // GAME_WIDGET_H
