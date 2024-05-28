#include "enemy.h"
#include "health.h"
//#include<GameSettings.h>
#include<QRandomGenerator>
#include<QGraphicsScene>
#include<player.h>
#include<bullet.h>
#include<score.h>

class Health;
using namespace GameSetting;
Enemy::Enemy(QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/object/C:/Users/wang/Desktop/demo_icons/UFO1.png"));
    setScale(EnemyScale);
    int max = SceneWidth-boundingRect().width()*EnemyScale;
    int randomNumber = QRandomGenerator::global()->bounded(1,max); //随机位置
    setPos(randomNumber,0);
    startTimer(EnemyMoveTime);
}

void Enemy::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);
    //进行碰撞监测
    QList<QGraphicsItem *> collidingItems = Enemy::collidingItems();
    for (auto item :collidingItems) {
        if(typeid(*item)==typeid(Player))
        {
            //健康值需要decrease
            Health::getInstance().decrease();
            scene()->removeItem(this);
            delete this;
            return;
        }
        if(typeid(*item)==typeid(Bullet))
        {
            //需要加分
            Score::getInstance().increase();
            scene()->removeItem(item);
            scene()->removeItem(this);
            delete item;
            delete this;
            return;
        }
    }


    setPos(x(),y()+EnemyMoveSpeed);
    if(y()>SceneHeight){
        scene()->removeItem(this);
        delete this;
    }
}
