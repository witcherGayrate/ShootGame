#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include<QTimer>
class QSoundEffect;
class Player : public QObject,public QGraphicsPixmapItem //多继承QObject必须在前面
{
    Q_OBJECT
public:
    Player(QGraphicsItem *parent = nullptr);

    //get playing
    bool isPlaying();

    // QGraphicsItem interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;

private:
    void enemySpawn();
    void gameOver();
    // QObject interface

    //键盘标志位
    void initiKeyState();
    std::unordered_map<Qt::Key,bool> keyStates;

    //设置射击计时器
    QTimer *shootTimer=nullptr;
    bool isTimerRunning = false;
    //准备射击
    void prepareShoot();
private slots:
    void timerTimeOut();

protected:
    virtual void timerEvent(QTimerEvent *event) override;
private:
    bool playing = true;
    QGraphicsTextItem *messageItem=nullptr;
    QSoundEffect *bulletSound=nullptr ;

    // QGraphicsItem interface
protected:
    virtual void keyReleaseEvent(QKeyEvent *event) override;
};













#endif // PLAYER_H
