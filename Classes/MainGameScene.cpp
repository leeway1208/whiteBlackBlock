
#include "MainGameScene.h"
USING_NS_CC;

Scene* MainGame::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainGame::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainGame::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    gameLayer = Node::create();
    addChild(gameLayer);
    
    
    
    //time label
    timerLabel = Label::create();
    timerLabel->setTextColor(Color4B::RED);
    timerLabel->setSystemFontSize(65);
    timerLabel->setPosition(visibleSize.width/2, visibleSize.height-100);
    addChild(timerLabel);
    //start line
    startGame();
    //add listener
    auto listener = EventListenerTouchOneByOne::create();
    listener -> onTouchBegan = [this](Touch* t,Event* e){
      
        auto getBlocks = MyBlock::getBlocks();
        MyBlock *myBlock;
        
        for (auto it = getBlocks->begin(); it!=getBlocks->end(); it++) {
            
            myBlock = *it;
            
            if (myBlock->getLineIndex()==1&&
                myBlock->getBoundingBox().containsPoint(t->getLocation())) {
                
                if (myBlock->getColor()==Color3B::BLACK) {
                    if (!isTimerRunning) {
                        this->startTimer();
                        
                    }
                    
                   
                    this->moveDown();
                    curentLineClicked ++;
                    CCLOG("%d",curentLineClicked);
                    myBlock->setColor(Color3B::GRAY);
                    
                    if(curentLineClicked == gameTotalLines){
                        this->stopTimer();
                        this->moveDown();
                    }
                    
                }else if (myBlock->getColor()==Color3B::GREEN){
                    
                }else{
                    MessageBox("你点错了", "点错了");
                    myBlock->setColor(Color3B::RED);
                    this->stopTimer();
                }
                
                break;
            }
        }
        
        return false;

        
    };
    
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}



void MainGame::update(float dt){
    
    long offset = clock()- startTime;
  
    string time = StringUtils::format("%f",int((((double)offset)/100000+0.005)*100) / 100.0);
 
    
    
    timerLabel->setString (time.substr(0,time.length() - 4));
}


void MainGame::moveDown(){

    //init 50 lines
    if(linesCount < gameTotalLines){
        addGameLine(4);
    }else if (!showEnd){
        
        addEndLine();
        showEnd = true;
  
    }
    
    
    auto bs = MyBlock::getBlocks();
    
    for (auto it = bs->begin(); it!=bs->end(); it++) {
       
        //if(curentLineClicked != gameTotalLines){
            (*it)->moveDown();
        //}
    }
    
    if (gameOver!=NULL) {
        
        if (gameOver->getLineIndex()==1) {
            //Game end
           
            stopTimer();
        }
    }

}


void MainGame::addEndLine(){
    auto b = GameOverScene::createWithContext(this);
    b->setLineIndex(4);
    b->setPositionY(b->getLineIndex()*visibleSize.height/4);
    gameLayer->addChild(b);
    
    gameOver = b;
}


void MainGame::addStartLine(){
    auto block = MyBlock::createBlocks(Color3B::YELLOW, Size(visibleSize.width, visibleSize.height/4), "开始", 55, Color4B::BLACK);
    gameLayer->addChild(block);
    //block->setLineIndex(0);
    
    
}


void MainGame::startGame(){
    
     //nobody click the blocks
     curentLineClicked = 0;
     gameTotalLines = 5;
    
     stopTimer();
     linesCount = 0;
     isTimerRunning = false;
     showEnd = false;
     timerLabel->setString("0.00");
     gameOver = NULL;
    
     //init blocks
     MyBlock::removeAllBlocks();
    
     //game logic
     addStartLine();
     addGameLine(1);
     addGameLine(2);
     addGameLine(3);
    
    
}


void MainGame::addGameLine(int blockNum){
    MyBlock *myBlock;
    int blackIndex = rand()%4;
    
    
    for (int i=0; i<4; i++) {
        myBlock = MyBlock::createBlocks(blackIndex==i?Color3B::BLACK:Color3B::WHITE,Size(visibleSize.width/4-1, visibleSize.height/4-1),"",20,Color4B::BLACK);
        gameLayer->addChild(myBlock);
        
        //each line * height
        myBlock->setPosition(i*visibleSize.width/4, blockNum*visibleSize.height/4);
        myBlock->setLineIndex(blockNum);
    }
    
    // add one line
    linesCount++;
}


void MainGame::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


#pragma mark - timer
void MainGame::startTimer(){
    if (!isTimerRunning) {
        scheduleUpdate();
        startTime = clock();
        
        isTimerRunning = true;
    }
}


void MainGame::stopTimer(){
    if(isTimerRunning){
        unscheduleUpdate();
        
        isTimerRunning = false;
    }
}


