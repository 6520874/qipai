#pragma once
#include "cocos2d.h"
#include "Global.h"

#include "GameScene.h"

USING_NS_CC;

class ResultLayer :public Layer
{
public:
	ResultLayer();
	~ResultLayer();
	virtual void onEnter();
	void backtouchEvent(Ref *pSender, Widget::TouchEventType type);

	virtual void onExit();
	virtual bool init();

	void setLayer(bool bfalse);

	CREATE_FUNC(ResultLayer);
	//static ResultLayer* create(const char *pszFileName);
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	virtual void onTouchCancelled(Touch *pTouch, Event *pEvent);
	EventListenerTouchOneByOne* touchListener;
private:
	bool m_bWin;
	ImageView *  m_pImg;

};

