#include "player.h"
#include "health.h"
#include<QPixmap>
#include<QKeyEvent>
#include<enemy.h>
#include<QGraphicsScene>
#include<bullet.h>
#include<QFontMetrics>
#include<score.h>
#include<QSoundEffect>
//#include <synchapi.h>

using namespace GameSetting;
Player::Player(QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{
    bulletSound = new QSoundEffect;
    bulletSound->setSource(QUrl("qrc:/sound/C:/Users/wang/Desktop/sound/lasershoot.wav"));
    initiKeyState();//初始化键盘标记位
    shootTimer = new QTimer();//设置射击计时器
    shootTimer->setInterval(PlayerShootInterval);//设置计时器时间间隔
    setPixmap(QPixmap(":/object/C:/Users/wang/Desktop/demo_icons/plane.png"));
    setScale(PlayerScale);
    setPos(SceneWidth/2-boundingRect().width()*PlayerScale/2,
           SceneHeight-boundingRect().height()*PlayerScale);
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();//设置聚焦
    //连接定时器的timeOut信号到槽函数
    connect(shootTimer,&QTimer::timeout,this,&Player::timerTimeOut);
    startTimer(500); //事件监测频率
}

void Player::keyPressEvent(QKeyEvent *event)
{
    //更新键盘状态
    keyStates[Qt::Key(event->key())]=true; //event->key()的返回值是int需要转为Qt::Key类型
    //先检查组合键
    if(keyStates[Qt::Key_Up] &&keyStates[Qt::Key_Left])
    {
        if(keyStates[Qt::Key_Space])
            prepareShoot();
        if((pos().x()>0) &&(pos().y()>0))
            setPos(x()-PlayerMoveSpeed/2,y()-PlayerMoveSpeed/2);
    }
    if(keyStates[Qt::Key_Up] &&keyStates[Qt::Key_Right])
    {
        if(keyStates[Qt::Key_Space])
            prepareShoot();
        if((pos().x()<SceneWidth-boundingRect().width()*PlayerScale) &&(pos().y()>0))
            setPos(x()+PlayerMoveSpeed/2,y()-PlayerMoveSpeed/2);
    }
    if(keyStates[Qt::Key_Down] &&keyStates[Qt::Key_Left])
    {
        if(keyStates[Qt::Key_Space])
            prepareShoot();
        if((pos().x()>0) &&(pos().y()<SceneHeight-boundingRect().height()*PlayerScale))
            setPos(x()-PlayerMoveSpeed/2,y()+PlayerMoveSpeed/2);
    }
    if(keyStates[Qt::Key_Down] &&keyStates[Qt::Key_Right])
    {
        if(keyStates[Qt::Key_Space])
            prepareShoot();
        if((pos().x()<SceneWidth-boundingRect().width()*PlayerScale) &&(pos().y()<SceneHeight-boundingRect().height()*PlayerScale))
            setPos(x()+PlayerMoveSpeed/2,y()+PlayerMoveSpeed/2);
    }
    else{
        switch(event->key()) {
        case Qt::Key_Space:
            prepareShoot();
            break;
        case Qt::Key_Left:
            if(pos().x()>0)
                setPos(x()-PlayerMoveSpeed,y());
            if(keyStates[Qt::Key_Space])
                prepareShoot();
            break;
        case Qt::Key_Right:
            if(pos().x()<SceneWidth-boundingRect().width()*PlayerScale)
                setPos(x()+PlayerMoveSpeed,y());
            if(keyStates[Qt::Key_Space])
                prepareShoot();
            break;
        case Qt::Key_Up:
            if(pos().y()>0)
                setPos(x(),y()-PlayerMoveSpeed);
            if(keyStates[Qt::Key_Space])
                prepareShoot();
            break;
        case Qt::Key_Down:
            if(pos().y()<SceneHeight-boundingRect().height()*PlayerScale)
                setPos(x(),y()+PlayerMoveSpeed);
            if(keyStates[Qt::Key_Space])
                prepareShoot();
            break;
        case Qt::Key_S:
            if(playing)return;
            if(playing==false)
            {
                playing=true;
                Health::getInstance().reset();
                Score::getInstance().reset();
                messageItem->hide();
            }
            break;
        }

    }

}

void Player::keyReleaseEvent(QKeyEvent *event)
{
    //更新键盘状态
    keyStates[Qt::Key(event->key())]=false;

    //松开任意一个控制键，重新检查哪些是按下的，否则需要再次按下触发keypress才能继续响应
    if(keyStates[Qt::Key_Left] && pos().x()>0)
        setPos(x()-PlayerMoveSpeed,y());
    if(keyStates[Qt::Key_Right] && (pos().x()<SceneWidth-boundingRect().width()*PlayerScale))
        setPos(x()+PlayerMoveSpeed,y());
    if(keyStates[Qt::Key_Up] && pos().y()>0)
        setPos(x(),y()-PlayerMoveSpeed);
    if(keyStates[Qt::Key_Down] && (pos().y()<SceneHeight-boundingRect().height()*PlayerScale))
        setPos(x(),y()+PlayerMoveSpeed);
}

void Player::enemySpawn()
{

    Enemy *enemy = new Enemy();
    scene()->addItem(enemy);

}

void Player::gameOver()
{
    playing = false;
    for(auto item:scene()->items())
    {
        if(typeid(*item)==typeid(Enemy)) //注意是*item,解引用，typeid的参数是对象
        {
            scene()->removeItem(item);
            delete item;
        }
    }
    if(!messageItem)
    {
        messageItem=new QGraphicsTextItem();
        scene()->addItem(messageItem);
        QString message("Game Over !按S键重新开始!");
        messageItem->setPlainText(message);
        messageItem->setDefaultTextColor(Qt::white);
        QFont font("Courier New",GameSetting::FontSize*2,QFont::Bold);
        messageItem->setFont(font);
        QFontMetrics fm(font);//字体内容变化，所占大小会变，所以获取字体的指标
        int msgWidth=fm.horizontalAdvance(message);//字体的水平长度
        messageItem->setPos(GameSetting::SceneWidth/2-msgWidth/2,
                            GameSetting::SceneHeight/2);
    }
    else
    {
        messageItem->show();
    }

}


void Player::initiKeyState()
{
   //初始化键盘状态标志位
    keyStates[Qt::Key_Up]=false;
    keyStates[Qt::Key_Down]=false;
    keyStates[Qt::Key_Left]=false;
    keyStates[Qt::Key_Right]=false;
    keyStates[Qt::Key_Space]=false;
    keyStates[Qt::Key_S]=false;

}

void Player::timerEvent(QTimerEvent *event)
{

    Q_UNUSED(event);
    if(playing)
    {
        enemySpawn();
    }


    if(Health::getInstance().getHealth()<=0)
    {
        gameOver();
    }

}
bool Player::isPlaying()
{
    return playing;
}

//射击计时器是否到时
void Player::timerTimeOut()
{

    Bullet *bullet = new Bullet();
    int temp = x()+boundingRect().width()*PlayerScale/2;//只考虑palyer的宽度
    temp -=  bullet->boundingRect().width()*BulletScale/2;//向左移动半个子弹宽度
    bullet->setPos(temp,y());
    bulletSound->play();
    scene()->addItem(bullet);
    //重新设置key_space的bool
    //keyStates[Qt::Key_Space] = false;
    //关闭计时器，准备重新计时
    shootTimer->stop();
    //设置timer运行状态
    isTimerRunning =false;
}
//准备射击
void Player::prepareShoot()
{
    if(!isTimerRunning)
    {
        shootTimer->start();//一直按压一直重新开始计时
        isTimerRunning = true;
    }
}
