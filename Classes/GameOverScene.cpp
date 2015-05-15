//
//  GameOverScene.cpp
//  whiteBlackBlock
//
//  Created by liwei wang on 15/5/15.
//
//

#include "GameOverScene.h"
USING_NS_CC;

GameOverScene* GameOverScene::createWithContext(MainGame *context){
    auto el = new GameOverScene();
    el->initWithContext(context);
    el->autorelease();
    
    MyBlock::getBlocks()->pushBack(el);
    return el;
}


bool GameOverScene::initWithContext(MainGame *context){
    this->context = context;
    visibleSize = Director::getInstance()->getVisibleSize();
    MyBlock::initBlocks(Color3B::GREEN, Size(visibleSize.width,visibleSize.height + visibleSize.height/4), "", 55, Color4B::BLACK);
    //createBlocks(Color3B::GREEN, Size(visibleSize.width, visibleSize.height), "游戏结束", 55, Color4B::BLACK);

    auto gameOverlabel = Label::create();
    gameOverlabel->setString("游戏结束");
    gameOverlabel->setSystemFontSize(55);
    gameOverlabel->setPosition(visibleSize.width/2, gameOverlabel->getContentSize().height +  visibleSize.height/2 +  visibleSize.height/4);
    gameOverlabel->setTextColor(Color4B::BLACK);
    addChild(gameOverlabel);
    
    auto label = Label::create();
    label->setString("再玩一次");
    label->setSystemFontSize(55);
    label->setPosition(visibleSize.width/2, label->getContentSize().height/2 + 50  +  visibleSize.height/4);
    label->setTextColor(Color4B::RED);
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