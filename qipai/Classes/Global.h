#pragma once
#include "cocos2d.h"
#include <vector>
USING_NS_CC;

const int pkWidth = 71;//牌的宽
const int pkHeight = 96;//牌的高
const int pkJianJu = 100;//牌与牌之间的间距
const int PKCHUHEIGHT = 205;

//花色
enum HuaSe	
{
	TU = 0,
	HUO,
	MU,
	SHUI,
	JIN,
	DAO,
	HuaSeBM = 6     //花色背面
};


//牌号
enum PaiHao
{
	Yi = 0,Er,San,Si,Wu,Liu,Qi,Ba,Jiu,Shi,Dao,Yin,Yan,
	PaiHaoBM=2 //牌号背面

};


enum CARD_TYPE
{
	SINGLE_CARD = 1,		//单牌-
	DOUBLE_CARD,			//对子-
	THRID_CARD,             //阴阳张牌
	ERROR_CARD				//错误的牌型
};


