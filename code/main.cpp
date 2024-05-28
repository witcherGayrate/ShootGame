#include<QGraphicsView>
#include<QGraphicsScene>
//#include<GameSettings.h>
#include <QApplication>
#include<player.h>
#include<score.h>
#include<health.h>
#include<QtMultimedia>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationDisplayName("星球大战");
    QApplication::setWindowIcon(QIcon(":/object/C:/Users/wang/Desktop/demo_icons/plane.png"));

    //创建Player
    Player* player = new Player();
    //创建场景
    QGraphicsScene* scene = new QGraphicsScene();
    scene->addItem(player);//graphics item加到场景里面
    scene->setSceneRect(0,0,GameSetting::SceneWidth,GameSetting::SceneHeight);
    scene->setBackgroundBrush(QImage(":/object/C:/Users/wang/Desktop/demo_icons/cosmicbackground.jpg"));
    //创建分数文字item
    scene->addItem(&Score::getInstance());
    //创建健康值文字item
    scene->addItem(&Health::getInstance());
    scene->setStickyFocus(true);//不会在被点击时，取消player的focus状态
    QGraphicsView view(scene);//相机视图
    view.setFixedSize(GameSetting::SceneWidth,GameSetting::SceneHeight);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.show();

    //添加背景音乐
    QMediaPlayer bgMusic;
    QAudioOutput *audio = new QAudioOutput();
    bgMusic.setAudioOutput(audio);
    bgMusic.setSource(QUrl("qrc:/sound/C:/Users/wang/Desktop/sound/background.mp3"));
    bgMusic.play();

    return a.exec();
}
