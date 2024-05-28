#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include <QObject>

class Score : public QGraphicsTextItem
{
    Q_OBJECT
public:
    Score(QGraphicsItem *parent = nullptr);

    static Score& getInstance(){
        static Score obj;
        return obj; //在需要时创建一个静态的单例
    }
    void increase();
    void reset();
private:
    int score=0;
};




#endif // SCORE_H
