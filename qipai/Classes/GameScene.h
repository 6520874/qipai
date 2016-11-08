#pragma once
#include "Global.h"
#include "vector"
#
class GameScene : public Layer
{
public:
	GameScene();
	~GameScene();
	static Scene* scene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	virtual void onEnter();
	virtual void onExit();
private:
	bool initBackGround();//加载背景
	bool initPlayer();//初始化玩家信息
	bool createPoker();
	
private:
	__Array* m_arrPokers;//所有的牌

};