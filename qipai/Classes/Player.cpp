#include "Player.h"
#include "Poker.h"
#include <stdio.h>

Player::Player()
{
	m_arrPk = __Array::create();
	m_arrPk->retain();

}

Player::~Player()
{
	CC_SAFE_RELEASE(m_arrPk);

}

void Player::initPlayerPlace(Node *parent,int random2)
{

	__String  str = "1.png";

	if(m_iPlayerClass==1)
	{
		str = "2.png";
	}
	Sprite *pPlayer = Sprite::create(str.getCString());
	pPlayer->setScale(0.1);

	 Size size = parent->getContentSize();

	 m_iWeizhi = random2;

	 switch (random2)
	 {
	 case 1:  
		 pPlayer->setPosition(size.width*0.2,size.height*0.8);  break;
	 case 2: pPlayer->setPosition(size.width*0.5,size.height*0.8);  break; break;
	 case 3:  pPlayer->setPosition(size.width*0.8,size.height*0.8);  break;break;
	 case 4:  pPlayer->setPosition(size.width*0.2,size.height*0.6);break;
     case 5:  pPlayer->setPosition(size.width*0.5,size.height*0.6);break;
	 case 6:  pPlayer->setPosition(size.width*0.8,size.height*0.6);break;
	 case 7:  pPlayer->setPosition(size.width*0.2,size.height*0.2);break;
	 case 8:  pPlayer->setPosition(size.width*0.5,size.height*0.2);break;
	 case 9:  pPlayer->setPosition(size.width*0.8,size.height*0.2);break;
	 default:
		 break;
	 }



	 parent->addChild(pPlayer);


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

	//¸üÐÂÎ»ÖÃ
	CCARRAY_FOREACH(m_arrPk,object){
		Poker* pk = (Poker*)object;
		if (m_iPlayerClass == 0 || m_iPlayerClass == 3)
		{
			pk->setPosition(ccp(x+num*pkJianJu+pkWidth/2,y));
		}
		else if(m_iPlayerClass == 1)
		{	
			pk->setTexture("cardbg.png");
			pk->setPosition(ccp(x+num*pkJianJu+pkWidth/2,y));
		}
		else if(m_iPlayerClass == 2)
		{
			pk->setPosition(ccp(x+num*pkJianJu+num*pkWidth+pkWidth/2,y));
		}
		++num;
	}

}
