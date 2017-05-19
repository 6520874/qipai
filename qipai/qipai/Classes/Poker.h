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
	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	virtual void onTouchCancelled(Touch *pTouch, Event *pEvent);
	void showFront();//��ʾ����
	void showLast();//��ʾ����
	void PkSuoTou();
	void SelectPkLuTou();//���ѡ�����ƾ�¶��ͷ
	void SelectPkSuoTou(bool b);//���ѡ�����ƾ���ͷ


private:
	CC_SYNTHESIZE(bool, m_isDianJi, DianJi);//�Ƿ��ܱ����
	CC_SYNTHESIZE(bool, m_isSelect, Select);//�Ƿ���ѡ
	CC_SYNTHESIZE(bool, m_bEnable, EnableNum);//�Ƿ���ѡ

	CC_SYNTHESIZE(int, m_huaSe, HuaSe);//��ɫ
	CC_SYNTHESIZE(int, m_num, Num);//��ֵ
	CC_SYNTHESIZE(__String, name, Picture);
	CC_SYNTHESIZE(GameScene*, m_gameMain, GameMain);
	EventListenerTouchOneByOne* touchListener;
};