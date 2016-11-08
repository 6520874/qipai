#pragma once
#include "Global.h"
#include "vector"
#include "Poker.h"
#include "Player.h"

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
	void func(CCNode* pSender, void* pData);
    void update(float delta);
	void MovePk(Player* play,Poker* pk);
	bool xiPai();
	CC_SYNTHESIZE(Player*,m_player,Player);//玩家
	int m_iSendPk;//已发出第几张牌
	Player* m_npcOne;//电脑1
	bool initBackGround();//加载背景
	bool initPlayer();//初始化玩家信息
	bool createPoker();
	void SendPk();
	int m_iState;//当前状态 0：发牌状态  2：出牌状态 3：结果状态

	__Array* m_arrPokers;//所有的牌

};