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
		xiPai();
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

			for (int j=1; j<54; ++j)
			{
				__String *s = __String::createWithFormat("%d.png",j);
				pk = pk->create(s->getCString());
				pk->setScale(0.1);
				pk->setPosition(Vec2(size.width/2,size.height/2));
				this->addChild(pk);
				this->m_arrPokers->addObject(pk);
			}
		
		
		//创建道阴阳三张牌
		isRet = true;
	} while (0);
	return isRet;
}

bool GameScene::xiPai(){
	bool isRet = false;
	do 
	{
		for(int i=0; i<53; ++i)
		{
			Poker* pk1 = (Poker*)m_arrPokers->randomObject();
			Poker* pk2 = (Poker*)m_arrPokers->randomObject();
			m_arrPokers->exchangeObject(pk1,pk2);
		}
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
	m_npcOne->setPoint(ccp(size.width/2,size.height*0.97));
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

	if(m_iSendPk<10)
	{
		pk = (Poker*)m_arrPokers->objectAtIndex(++m_iSendPk);
		MovePk(m_player,pk);
		
		pk = (Poker*)m_arrPokers->objectAtIndex(++m_iSendPk);
		pk->setFlipY(1);
		MovePk(m_npcOne,pk);

	}
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
	Player* play = (Player*)pData;
	play->updatePkWeiZhi();
	//m_isSend = true;

}