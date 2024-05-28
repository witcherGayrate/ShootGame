#include "health.h"

#include<QFont>
Health::Health(QGraphicsItem *parent):QGraphicsTextItem(parent)
{
    reset();
}

void Health:: reset()
{
    health = GameSetting::HealthStart;
    setPlainText("健康值： "+QString::number(health));
    setDefaultTextColor(Qt::red);
    setFont(QFont("Courier New",GameSetting::FontSize,QFont::Bold));
    setPos(x(),GameSetting::FontSize*2);

}

void Health::decrease()
{
    --health;
    setPlainText("健康值： "+QString::number(health));
}
