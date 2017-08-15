#include "Player.h"
#include "Poker.h"
#include <stdio.h>
#include "Script/utility.h"

Player::Player() :m_isOutPk(false)
{
	m_arrPk = __Array::create();
	m_jiaoIndex = 1;
	m_arrPk->retain();
}

Player::~Player()
{
	CC_SAFE_RELEASE(m_arrPk);

}


int Player::getRolePlaceHuase(int index)
{
	if (index == 1 || index == 8) return HuaSe::SHUI;
	else if (index == 2 || index == 9) return HUO;
	else if (index == 3 || index == 4) return MU;
	else if (index == 5) return TU;
	else if (index == 6 || index == 7) return JIN;
	else return -1;
}


void  Player::setRolePlace(int index)
{
	Size size = m_parent->getContentSize();

	m_jiaoIndex = index;
	Vec2 t;

	//1/6,0.5,5/6

	switch (index)
	{
	case 1:  t = Vec2(size.width*0.5, size.height*1/6); break; //水1
	case 2:  t = Vec2(size.width*5/6, size.height*5/6);  break;  //火2
	case 3:  t = Vec2(size.width*1/6, size.height*0.5); break;//木3
	case 4:  t = Vec2(size.width*1/6, size.height*5/6);  break; //木4
	case 5:  t = Vec2(size.width*0.5, size.height*0.5); break;  //土5
	case 6:  t = Vec2(size.width*5/6, size.height*1/6); break;  //金6
	case 7:  t = (Vec2(size.width*5/6, size.height*0.5)); break; //金7
	case 8:  t = (Vec2(size.width*1/6, size.height*1/6)); break; // 水8
	case 9:  t = (Vec2(size.width*0.5, size.height*5/6));  break;  //火9

	default:
		//t = Vec2(size.width*0.5, size.height*0.2);
		break;
	}

	m_role->stopAllActions();
	m_role->runAction(MoveTo::create(0.5, t));

	m_role->setEnabled(false);

}


void Player::yiwei()
{
	if (m_jiaoIndex >= 9 && m_jiaoIndex <= 0)
	{
		m_jiaoIndex = 1;
	}
	else
	{
		m_jiaoIndex += 1;
	}
	setRolePlace(m_jiaoIndex);

}
void Player::yiweiEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN: break;
	case Widget::TouchEventType::MOVED: break;
	case Widget::TouchEventType::ENDED:  yiwei();
		
		if (m_iPlayerClass == 0)
		{
			m_bJiaoseTouch = true;
		}

		for (int i = 0; i < m_arrPk->count() - 1; ++i)
		{
			Poker* pk1 = (Poker*)m_arrPk->getObjectAtIndex(i);
			pk1->PkSuoTou();

		}
	default:break;

		break;
	}

}

void Player::initPlayerPlace(Node *parent, int random2)
{
	__String name = "q1.png";

	if (m_iPlayerClass == 1)
	{
		name = "q2.png";
	}

	m_role = Button::create(name.getCString());

	std::string strhp1 = utility::getScriptString("hp1");
	std::string strhp2 = utility::getScriptString("hp2");
	if (m_iPlayerClass == 0)
	{
		m_iBloodNum = atoi(strhp1.c_str());
	}
	else
	{
		m_iBloodNum = atoi(strhp2.c_str());
	}

	  m_gameMain->RefreshBloodNum(m_iPlayerClass,m_iBloodNum);


	if (m_iPlayerClass == 1)
	{
		m_role->setColor(Color3B(127, 127, 127));
	}
	m_role->addTouchEventListener(CC_CALLBACK_2(Player::yiweiEvent, this));

	if (m_iPlayerClass)
	{
		m_role->setEnabled(false);
	}
	m_jiaoIndex = random2;

	m_parent = parent;

	std::string str = utility::getScriptString("keyopen");
	if (str != "1")
	{ 
		setRolePlace(random2);
	}
	else
	{ 
	std::string str1 = utility::getScriptString("weizhi1");
	std::string str2 = utility::getScriptString("weizhi2");
	
	int iweizhi1 = atoi(str1.c_str());
	int iweizhi2 = atoi(str2.c_str());

	if(m_iPlayerClass == 0) setRolePlace(iweizhi1);
	else setRolePlace(iweizhi2);
	}
	parent->addChild(m_role);

}

void Player::updatePkWeiZhi()
{
	Size size = Director::getInstance()->getWinSize();

	if (m_iPlayerClass == 1)	return;

	int x, y;
	//排序
	{
		for (int i = 0; i < m_arrPk->count() - 1; ++i)
		{
			for (int j = 0; j < m_arrPk->count() - 1 - i; ++j)
			{
				Poker* pk1 = (Poker*)m_arrPk->getObjectAtIndex(j);
				Poker* pk2 = (Poker*)m_arrPk->getObjectAtIndex(j + 1);

				if (pk1->getHuaSe() < pk2->getHuaSe())
				{
					m_arrPk->exchangeObjectAtIndex(j, j + 1);
				}
				else if (pk1->getHuaSe() == pk2->getHuaSe())
				{
					if (pk1->getNum() < pk2->getNum())
					{
						m_arrPk->exchangeObjectAtIndex(j, j + 1);
					}
				}

			}
		}
	}

	x = size.width / 2 - ((m_arrPk->count() - 1)*pkJianJu + pkWidth) / 2;
	y = m_point.y;

	int  cnt = m_arrPk->count();
	{
		//更新位置
		for (int i = 0; i < cnt; i++)
		{
			Poker* pk = (Poker*)m_arrPk->getObjectAtIndex(i);
			pk->setVisible(true);
			pk->setPosition(Vec2(x + i*pkJianJu + pkWidth / 2, y));
		}
	}
}



