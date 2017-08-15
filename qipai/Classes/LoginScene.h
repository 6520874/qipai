#pragma once
#include "Global.h"
#include "vector"

#include "ui/CocosGUI.h"
using namespace cocos2d::ui;


class LoginScene : public Layer
{
public:
	LoginScene();
	~LoginScene();
	static Scene* scene();
	virtual bool init();
	void   LogintouchEvent(Ref *pSender, Widget::TouchEventType type);

	CREATE_FUNC(LoginScene);
	virtual void onEnter();
	virtual void onExit();
	Size m_winSize;
};
