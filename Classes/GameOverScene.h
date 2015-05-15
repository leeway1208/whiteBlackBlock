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

USING_NS_CC;

class MainGame;

class GameOverScene:public MyBlock {
    
private:
    Size visibleSize;
    MainGame *context;
    
public:
    static GameOverScene* createWithContext(MainGame *context);
    bool initWithContext(MainGame *context);
};


#endif /* defined(__whiteBlackBlock__GameOverScene__) */
