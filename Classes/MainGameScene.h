#ifndef __MAINGAME_SCENE_H__
#define __MAINGAME_SCENE_H__

#include "cocos2d.h"
#include "MyBlock.h"
#include "GameOverScene.h"

using namespace std;
USING_NS_CC;

class GameOverScene;

class MainGame : public cocos2d::Layer
{
private:
    Size visibleSize;
    Node *gameLayer;
    int linesCount;
    bool showEnd;
    bool isTimerRunning;
    long startTime;
    Label *timerLabel;
    int gameTotalLines;
    int curentLineClicked;
    GameOverScene *gameOver;
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainGame);
    
    
    void addStartLine();
    void addGameLine(int whichBlockShouldBeClicked);
    void startGame();
    void addEndLine();
    
    void moveDown();
    
    
    //timer
    void startTimer();
    void stopTimer();
    
    virtual void update(float dt);
    
};

#endif // __MainGame_SCENE_H__
