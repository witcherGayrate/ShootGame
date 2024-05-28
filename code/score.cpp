#include "score.h"
#include "GameSettings.h"
#include <QFont>

Score::Score(QGraphicsItem *parent):QGraphicsTextItem(parent)
{
    reset();

}

void Score::reset()
{
    score=0;
    setPlainText("分 数："+QString::number(score));
    setDefaultTextColor(Qt::green);
    setFont(QFont("Courier New",GameSetting::FontSize,QFont::Bold));
}


void Score::increase()
{
    ++score;
    setPlainText("分 数："+QString::number(score));
}
