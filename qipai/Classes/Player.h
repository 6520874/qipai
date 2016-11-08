#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Player : public Sprite
{
public:
	Player();
	~Player();
	void updatePkWeiZhi();//设置牌的位置
	void  initPlayerPlace(Node *parent,int random); //初始化玩家角色位置

private:
	CC_SYNTHESIZE(int,m_iWeizhi,playerweizhi);//玩家在期盼位置 
	CC_SYNTHESIZE(__Array*,m_arrPk,ArrPk);//手里拥有的扑克牌
	CC_SYNTHESIZE(Point,m_point,Point);//牌在桌面的初始位置
	CC_SYNTHESIZE(bool,m_iPlayerClass ,PlayerClass);//玩家种类:0为玩家，1为电脑
	CC_SYNTHESIZE(bool,m_isOutPk,IsOutPk);//玩家是否出牌true:出 false:不出
};

