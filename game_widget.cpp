#include "game_widget.h"

game_widget::game_widget(QObject *parent)
    : QObject{parent}
{
    QFont font;
    font.setPointSize(100);
    font.setFamily("Minecraft AE");

    loser_end = new QWidget();
    loser_end -> resize(game_widget_width,game_widget_height);
    loser_end->setStyleSheet("background-color: rgb(34,34,34);");
    loser_notice = new QLabel(loser_end);
    loser_notice -> move(200,300);
    loser_notice->setText("You  Lose");
    loser_notice->setStyleSheet("QLabel { color : red; }");
    loser_notice -> setFont(font);

}
