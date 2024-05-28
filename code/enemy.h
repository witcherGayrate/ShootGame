#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Enemy : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Enemy(QGraphicsItem *parent = nullptr);
    ~Enemy(){};

    // QObject interface
protected:
    virtual void timerEvent(QTimerEvent *event) override;
};



#endif // ENEMY_H
