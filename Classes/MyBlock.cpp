//
//  Block.cpp
//  whiteBlackBlock
//
//  Created by liwei wang on 14/5/15.
//
//

#include "MyBlock.h"
USING_NS_CC;

Vector<MyBlock*> * MyBlock::blocks = new Vector<MyBlock*>;



Vector<MyBlock*> * MyBlock::getBlocks(){
    return MyBlock::blocks;
}

bool MyBlock::initBlocks(Color3B blockColor, Size blockSize, string label, float fontSize, Color4B textColor){
    
    Sprite::init();
    whichLines = 0;
    
    setContentSize(blockSize);
    //anchor point is 0.0
    setAnchorPoint(Point::ZERO);
    //create the block
    setTextureRect(Rect(0, 0, blockSize.width, blockSize.height));
    setColor(blockColor);
    
    
    auto myLabel = Label::create();
    myLabel -> setString(label);
    myLabel -> setSystemFontSize(fontSize);
    myLabel -> setTextColor(textColor);
    addChild(myLabel);
    myLabel -> setPosition(blockSize.width/2, blockSize.height/2);
    
    return true;
}



MyBlock *MyBlock::createBlocks(Color3B blockColor, Size blockSize, string label, float fontSize, Color4B textColor){
    
    
    auto myblock = new MyBlock();
    
    //init the block , use block function
    myblock -> initBlocks(blockColor, blockSize, label, fontSize, textColor);
    myblock -> autorelease();
    
    //vector blocks
    //push the block to the end
    blocks -> pushBack(myblock);
    
    
    
    
    
    return myblock;
    
}


void MyBlock::setLineIndex(int lineIndex){
    this->whichLines = lineIndex;
}

int MyBlock::getLineIndex(){
    return this->whichLines;
}


void MyBlock::removeAllBlocks(){
    while (getBlocks()->size()) {
        getBlocks()->back()->removeFromParent();
        getBlocks()->popBack();
    }
    
}



void MyBlock::moveDown(){
    
    whichLines--;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    runAction(Sequence::create(MoveTo::create(0.1f, Point(getPositionX(), whichLines*visibleSize.height/4)),
                               CallFunc::create([this](){
        
        if (whichLines<0) {
            this->removeBlocks();
        }
        
    }), NULL));
    
    
}



void MyBlock::removeBlocks(){
    removeFromParent();
    //Remove a certain object in Vector.
    blocks->eraseObject(this);
}




