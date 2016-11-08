#include "Player.h"
#include "Poker.h"


Player::Player()
{
	m_arrPk = __Array::create();
	m_arrPk->retain();

}

Player::~Player()
{
	CC_SAFE_RELEASE(m_arrPk);

}


void Player::updatePkWeiZhi()
{
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
	int x,y;
	if(m_iPlayerClass == 0 || m_iPlayerClass == 3)
	{
		x = size.width/2-((m_arrPk->count()-1)*pkJianJu+pkWidth)/2;
		y = m_point.y;
	}
	else if(m_iPlayerClass == 1 || m_iPlayerClass == 4 || m_iPlayerClass == 5)
	{
		x =size.width/2-((m_arrPk->count()-1)*pkJianJu+pkWidth)/2;
		y = m_point.y;
	}
	else if(m_iPlayerClass == 2)
	{
		x = size.width/2-(m_arrPk->count()*pkWidth+(m_arrPk->count()-1)*pkJianJu)/2;
		y = m_point.y;
	}
	int num = 0;
	CCObject* object;


 
	//更新位置
	CCARRAY_FOREACH(m_arrPk,object){
		Poker* pk = (Poker*)object;
		if (m_iPlayerClass == 0 || m_iPlayerClass == 3)
		{
			//pk->showFront();
			pk->setPosition(ccp(x+num*pkJianJu+pkWidth/2,y));
		}
		else if(m_iPlayerClass == 1)
		{
			//pk->showFront();
			//	pk->showLast();
			pk->setTexture("cardbg.png");
			pk->setPosition(ccp(x+num*pkJianJu+pkWidth/2,y));
		}
		else if(m_iPlayerClass == 2)
		{
			pk->setPosition(ccp(x+num*pkJianJu+num*pkWidth+pkWidth/2,y));
		}
		++num;
	}
	//改变牌的z值或牌的触摸优先
  
	 /*int i=m_arrPk->count()-1;
	CCARRAY_FOREACH(m_arrPk,object){
		Poker* pk = (Poker*)object;
		//改变z值
		if (m_iPlayerClass == 1 || m_iPlayerClass == 4 || m_iPlayerClass == 5)
			pk->setZOrder(size.height - pk->getPositionY());
		if (m_iPlayerClass == 0 || m_iPlayerClass == 3)
			pk->setZOrder(pk->getPositionX());
	

	}*/

}
