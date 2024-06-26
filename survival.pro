QT       += core gui
 QT      += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    background_scene.cpp \
    bullet_base.cpp \
    bullet_enemy_3.cpp \
    bullet_gun.cpp \
    enemy_1.cpp \
    enemy_2.cpp \
    enemy_3.cpp \
    enemy_base.cpp \
    game_engine.cpp \
    heart_lable.cpp \
    hero.cpp \
    main.cpp \
    obstacle.cpp \
    weapon.cpp

HEADERS += \
    background_scene.h \
    bullet_base.h \
    bullet_enemy_3.h \
    bullet_gun.h \
    enemy_1.h \
    enemy_2.h \
    enemy_3.h \
    enemy_base.h \
    game_engine.h \
    global.h \
    heart_lable.h \
    hero.h \
    obstacle.h \
    weapon.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
