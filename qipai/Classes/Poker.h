#pragma once
#include "cocos2d.h"
#include "Global.h"
#include "Poker.h"
USING_NS_CC;
class GameScene;
class Poker : public Sprite
{

public:
	Poker();
	~Poker();
	static Poker* create(const char *pszFileName);
	void showFront();
	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	virtual void onTouchCancelled(Touch *pTouch, Event *pEvent);
	private:
	EventListenerTouchOneByOne* touchListener;
};