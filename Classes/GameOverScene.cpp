//
//  GameOverScene.cpp
//  whiteBlackBlock
//
//  Created by liwei wang on 15/5/15.
//
//

#include "GameOverScene.h"
USING_NS_CC;

GameOverScene* GameOverScene::createWithContext(MainGame *context,string labelStr, float fontSize, Color3B textColor){
    auto el = new GameOverScene();
    el->initWithContext(context,labelStr,fontSize,textColor);
    //el->autorelease();
    
    MyBlock::getBlocks()->pushBack(el);
    return el;
}


bool GameOverScene::initWithContext(MainGame *context,string labelStr, float fontSize, Color3B textColor){
    
    NotificationObserver(this, callfuncO_selector(GameOverScene::updateView), GAME_OVER_BROADCAST, NULL);
    
    CCNotificationCenter::sharedNotificationCenter()->addObserver(this, callfuncO_selector(GameOverScene::updateView), GAME_OVER_BROADCAST, NULL);
    
    this->context = context;
    visibleSize = Director::getInstance()->getVisibleSize();
    MyBlock::initBlocks(textColor, Size(visibleSize.width,visibleSize.height + visibleSize.height/4), "", 55, Color4B::BLACK);
    //createBlocks(Color3B::GREEN, Size(visibleSize.width, visibleSize.height), "游戏结束", 55, Color4B::BLACK);

    auto gameOverlabel = Label::create();
    gameOverlabel->setString(labelStr);
    gameOverlabel->setSystemFontSize(fontSize);
    gameOverlabel->setPosition(visibleSize.width/2, gameOverlabel->getContentSize().height +  visibleSize.height/2 +  visibleSize.height/4);
    gameOverlabel->setTextColor(Color4B::BLACK);
    addChild(gameOverlabel);
    

    //addChild(recordTimelbl);
    
    auto label = Label::create();
    label->setString("再玩一次");
    label->setSystemFontSize(55);
    label->setPosition(visibleSize.width/2, label->getContentSize().height/2 + 50  +  visibleSize.height/4);
    label->setTextColor(Color4B::BLUE);
    addChild(label);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch* t,Event * e){
        
        if (e->getCurrentTarget()->getBoundingBox().containsPoint(t->getLocation()-e->getCurrentTarget()->getParent()->getPosition())) {
            
            this->context->startGame();
        }
        return false;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, label);
    
    return true;
}

void GameOverScene::updateView(CCObject* obj){
    auto recordTimelbl = Label::create();
    //recordTimelbl -> setTag(100);

   // Label* recordTimelbl = (Label* )this->getChildByTag(100);
   
    float newTime =  LoadFloatFromXML("record_timer");
    cout<<"--"<<newTime<<endl;
    float time = LoadFloatFromXML("game_over_time",2000.0f);
    if (time == 1) {
        SaveFloatToXML("game_over_time",2000.0f);
        UserdefaultFlush;
    }
    cout<<"---"<<time<<endl;
    string congratulationStr = "";
    string mtime = "";
   
    

    if(newTime < time){
        
        string mtime = StringUtils::format("%f",newTime);
        SaveFloatToXML("game_over_time",newTime);
        UserdefaultFlush;
        
        congratulationStr = "Congratulations !!";
        
        recordTimelbl->setString("best time: " + mtime.substr(0,mtime.length() - 4) + "\n" + congratulationStr);
    }else{
        string mtime = StringUtils::format("%f",time);
        recordTimelbl->setString("Last best time: " + mtime.substr(0,mtime.length() - 4));
    }
    
    
    
    
    
    
   
    recordTimelbl->setSystemFontSize(55);
    recordTimelbl->setPosition(visibleSize.width/2, recordTimelbl->getContentSize().height +  visibleSize.height/2 +  visibleSize.height/4 - 150);
    recordTimelbl->setTextColor(Color4B::RED);
    
       addChild(recordTimelbl);
}
