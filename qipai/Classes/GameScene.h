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
	bool initBackGround();//���ر���
	bool initPlayer();//��ʼ�������Ϣ
	bool createPoker();
	
private:
	__Array* m_arrPokers;//���е���

};