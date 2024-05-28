#include "bullet.h"
#include<GameSettings.h>
#include<QGraphicsScene>
#include<QPixmap>
Bullet::Bullet(QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/object/C:/Users/wang/Desktop/demo_icons/laser.png"));
    this->setScale(GameSetting::BulletScale);
    startTimer(GameSetting::BulletMoveTime);
}

void Bullet::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    setPos(x(),y()-GameSetting::BulletMoveSpeed);
    if(y()+boundingRect().height()*GameSetting::BulletScale<0)
    {
        scene()->removeItem(this);
        delete this;
    }
}
