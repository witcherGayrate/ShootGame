#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>
#include <QObject>
#include<GameSettings.h>
class Health : public QGraphicsTextItem
{
    Q_OBJECT
public:
    Health(QGraphicsItem *parent = nullptr);
    static Health& getInstance(){
        static Health obj;
        return obj; //需要时创建单例
    }
    int getHealth(){return health;};
    void decrease();
    void reset();
private:
    int health = GameSetting::HealthStart;


};



#endif // HEALTH_H
