#include "GameScene.h"
#include<algorithm>
#include <string>
#include <deque>

GameScene::GameScene(){

	m_arrPokers = __Array::create();
	m_player = new Player();
	m_npcOne = new Player();

	m_arrPokers->retain();
	m_iState = 0;
	m_iSendPk = 0;

}
GameScene::~GameScene(){
	CC_SAFE_DELETE(m_player);
	CC_SAFE_DELETE(m_npcOne);
	CC_SAFE_RELEASE(m_arrPokers);

}


Scene* GameScene::scene(){
	Scene* scene = Scene::create();
	GameScene * gameLayer = GameScene::create();
	scene->addChild(gameLayer);
	return scene;
}

bool GameScene::init(){
	CCLayer::init();
	bool isRet = false;
	do 
	{
	initBackGround();
	initPlayer();
	createPoker();
	scheduleUpdate();
		isRet = true;
	} while (0);
	return isRet;
}

void GameScene::onEnter(){
	CCLayer::onEnter();

}
void GameScene::onExit(){
	CCLayer::onExit();
}
bool GameScene::initBackGround(){
	bool isRet = false;
	do 
	{	
		Sprite* bk = Sprite::create("res/bk.png");
		this->addChild(bk,0);
		bk->setAnchorPoint(Vec2(0,0));
		isRet = true;
	} while (0);
	return isRet;
}

bool GameScene::createPoker()
{
	bool isRet = false;
	do 
	{
		Size size = Director::getInstance()->getWinSize();
		Poker* pk;
		//创建50个牌
		for (int i=0; i<5; ++i)
		{
			for (int j=0; j<10; ++j)
			{
			
				pk = pk->create("res/1.png");
				pk->setScale(0.1);
				pk->setPosition(Vec2(size.width/2,size.height/2));
				this->addChild(pk);
				this->m_arrPokers->addObject(pk);
			}
		}
		
		//创建道阴阳三张牌
		//this->m_arrPokers->addObject(pk);
		isRet = true;
	} while (0);
	return isRet;
}


bool GameScene::initPlayer(){
	Size size = Director::getInstance()->getVisibleSize();
	//设置主玩家的位置
	m_player->setPoint(ccp(size.width/2,size.height/6));
	m_player->setPlayerClass(0);

	//设置电脑1的位置
	m_npcOne->setPoint(ccp(65,504));
	m_npcOne->setPlayerClass(1);
	
	return true;

}


void GameScene::update(float delta)
{

	switch (m_iState)
	{
	case 0:
		SendPk();
		break;

	default:
		break;
	}

}

void GameScene::SendPk(){
	Poker* pk;

	CCMoveTo* move;
	CCCallFuncND* func;
	float time = 0.05;

	pk = (Poker*)m_arrPokers->objectAtIndex(m_iSendPk++);
	MovePk(m_player,pk);
}


void GameScene::MovePk(Player* play,Poker* pk)
{
	CCMoveTo* move;
	CCCallFuncND* func;
	float time = 0.05;
    play->getArrPk()->addObject(pk);
	move = CCMoveTo::create(time,play->getPoint());
	func = CCCallFuncND::create(this,callfuncND_selector(GameScene::func),play);
	CCSequence* sequence = CCSequence::create(move,func,NULL);
	pk->runAction(sequence);
}

void GameScene::func(CCNode* pSender, void* pData){
	//Player* play = (Player*)pData;
	//play->updatePkWeiZhi();
	//m_isSend = true;

}