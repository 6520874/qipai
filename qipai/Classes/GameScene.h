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
	CC_SYNTHESIZE(Player*,m_player,Player);//���
	int m_iSendPk;//�ѷ����ڼ�����
	Player* m_npcOne;//����1
	bool initBackGround();//���ر���
	bool initPlayer();//��ʼ�������Ϣ
	bool createPoker();
	void SendPk();
	int m_iState;//��ǰ״̬ 0������״̬  2������״̬ 3�����״̬

	__Array* m_arrPokers;//���е���

};