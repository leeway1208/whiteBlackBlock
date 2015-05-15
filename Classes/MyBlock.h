//
//  Block.h
//  whiteBlackBlock
//
//  Created by liwei wang on 14/5/15.
//
//

#ifndef __whiteBlackBlock__Block__
#define __whiteBlackBlock__Block__

//#include <stdio.h>
#include "cocos2d.h"
#include <iostream>

USING_NS_CC;
using namespace std;

class MyBlock: public Sprite{

private:
    //blocks object
    static Vector<MyBlock*> * blocks;
    //1 ,2 ,3 or 4
    int whichLines;
    
public:
    static Vector<MyBlock*> * getBlocks();
    
    static MyBlock* createBlocks(Color3B blockColor, Size blockSize, string label, float fontSize, Color4B textColor);
    
    static void removeAllBlocks();
    
    virtual bool initBlocks(Color3B blockColor, Size blockSize, string label, float fontSize, Color4B textColor);
    
    void setLineIndex(int lineIndex);
    
    int getLineIndex();
    
    //use to remove the block which be clicked
    void moveDown();
    
    void removeBlocks();
    
};





#endif /* defined(__whiteBlackBlock__Block__) */
