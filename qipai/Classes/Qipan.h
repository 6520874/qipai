#pragma once
#include "cocos2d.h"
#include "Global.h"

#include "GameScene.h"

USING_NS_CC;
class Poker;
class Qipan :public Sprite
{
public:
	Qipan();
	~Qipan();
	virtual void onEnter();
	virtual void onExit();
	void setplayer(Player *p);
	void setTouchTure(int huase);
	static Qipan* create(const char *pszFileName);
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	virtual void onTouchCancelled(Touch *pTouch, Event *pEvent);
	EventListenerTouchOneByOne* touchListener;
private:
	void restoreGame();
	CC_SYNTHESIZE(GameScene*, m_game, GameMain);
	bool m_bTouch;
	int m_bHuase;
	Player *m_p;

};

