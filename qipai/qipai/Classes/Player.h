#pragma once
#include "cocos2d.h"
#include "GameScene.h"
USING_NS_CC;
class Player : public Sprite
{
public:
	Player();
	~Player();
	void updatePkWeiZhi();//设置牌的位置
	void  initPlayerPlace(Node *parent, int random); //初始化玩家角色位置
	void showFront();
	void  setRolePlace(int index);
	int getRolePlaceHuase(int index); //根据位置获取五行属性
	void yiwei();
private:

	void yiweiEvent(Ref *pSender, Widget::TouchEventType type);
	Node *	m_parent;
	CC_SYNTHESIZE(GameScene*, m_gameMain, GameMain);
	CC_SYNTHESIZE(__Array*, m_arrPk, ArrPk);//手里拥有的扑克牌
	CC_SYNTHESIZE(Point, m_point, Pt);//牌在桌面的初始位置
	CC_SYNTHESIZE(bool, m_iPlayerClass, PlayerClass);//玩家种类:0为玩家，1为电脑
	std::vector<PaiXing> m_vecPX;//保存牌型
	CC_SYNTHESIZE(bool, m_isOutPk, IsOutPk);//玩家是否出牌true:出 false:不出
	CC_SYNTHESIZE(int, m_jiaoIndex, JiaoIndex);//角色在第几宫格
	CC_SYNTHESIZE(Button*, m_role, Role);//角色代表头像
	CC_SYNTHESIZE(int, m_iBloodNum, BloodNum);//玩家血值



};

//水1火2木3木4土5金6金7水8火9