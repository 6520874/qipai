#include "GameScene.h"
#include<algorithm>
#include <string>
#include <deque>
#include "Poker.h"
GameScene::GameScene(){

	m_arrPokers = __Array::create();
	m_arrPokers->retain();
}
GameScene::~GameScene(){
	
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
	createPoker();
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
				pk->setScale(0.2);
				pk->setPosition(Vec2(size.width/2,size.height/2));
				this->addChild(pk);
				this->m_arrPokers->addObject(pk);
			}
		}
		
		//创建道阴阳三张牌
		this->m_arrPokers->addObject(pk);
		isRet = true;
	} while (0);
	return isRet;
}

