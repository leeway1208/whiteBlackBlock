//
//  GameOverScene.h
//  whiteBlackBlock
//
//  Created by liwei wang on 15/5/15.
//
//

#ifndef __whiteBlackBlock__GameOverScene__
#define __whiteBlackBlock__GameOverScene__

#include <stdio.h>
#include "MyBlock.h"
#include "MainGameScene.h"
#include <iostream>

#define GAME_OVER_BROADCAST "GAME_OVER" 

USING_NS_CC;

class MainGame;

class GameOverScene:public MyBlock {
    
private:
    Size visibleSize;
    MainGame *context;

    
public:
    static GameOverScene* createWithContext(MainGame *context,string label, float fontSize, Color3B textColor);
    bool initWithContext(MainGame *context,string label, float fontSize, Color3B textColor);
           static void updateGameOverView(float dt);
    void updateView(CCObject* obj);

};


#endif /* defined(__whiteBlackBlock__GameOverScene__) */
