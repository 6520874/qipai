#include "Poker.h"
#include "Player.h"
#include "GameScene.h"


Poker::Poker() :m_isSelect(false), m_isDianJi(false) {
	m_bEnable = true;
}

Poker::~Poker() {

}


Poker* Poker::create(const char *pszFileName) {
	Poker* pk = new Poker();
	//pk->setScale(0.9);
	if (pk && pk->initWithFile(pszFileName))
	{
		pk->autorelease();
		return pk;
	}
	CC_SAFE_DELETE(pk);
	return pk;
}
void Poker::onEnter() {
	Sprite::onEnter();
	touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(Poker::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Poker::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Poker::onTouchEnded, this);
	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}
void Poker::onExit() {
	_eventDispatcher->removeEventListenersForTarget(this);
	Sprite::onExit();
}
bool Poker::onTouchBegan(Touch *pTouch, Event *pEvent) {

	Size size = getContentSize();
	Rect rect(-size.width / 2, -size.height / 2, size.width, size.height);
	Point ptouch = convertTouchToNodeSpaceAR(pTouch); //”…”¢Œƒ÷Æ“‚◊™ªª ¥•√˛ µΩ Ω⁄µ„ø’º‰

	if (rect.containsPoint(ptouch) && m_isDianJi)
	{
		if (!m_isSelect) {
			SelectPkLuTou();
		}
		else {

			SelectPkSuoTou(1);
		}
		return true;
	}

	return false;

}
void Poker::onTouchMoved(Touch *pTouch, Event *pEvent) {

}
void Poker::onTouchEnded(Touch *pTouch, Event *pEvent) {

}
void Poker::onTouchCancelled(Touch *pTouch, Event *pEvent) {

}

void Poker::showFront() {
	this->initWithFile(name.getCString());
}

void Poker::showLast()
{
	this->initWithFile("cardbg.png");
}

void Poker::PkSuoTou()
{
	Ref* object;
	m_gameMain->m_btnAttack->setVisible(false);
	m_gameMain->m_btnQipai->setVisible(false);
	m_gameMain->m_btnYiwei->setVisible(false);
	m_gameMain->m_btnJiepai->setVisible(false);
	m_gameMain->m_btnHuixue->setVisible(false);

	m_isSelect = false;


	CCARRAY_FOREACH(m_gameMain->getArrPlayerOut(), object) {
		Poker* pk = (Poker*)object;
		pk->setPosition(Vec2(pk->getPositionX(), pk->getPositionY() - 5));
	}

	m_gameMain->getArrPlayerOut()->removeObject(this);

}
void Poker::SelectPkLuTou() {
	//ÃÌº”“™≥ˆµƒ≈∆

	Ref* object;

	int huase = 0;

	CCARRAY_FOREACH(m_gameMain->getArrPlayerOut(), object) {
		Poker* pk = (Poker*)object;
		huase = pk->getHuaSe();


		if (this->getHuaSe() != huase && pk->getNum()!= 10)
		{
			if (pk->getSelect())
			{
				pk->SelectPkSuoTou(1);
			}
		}
		else
		{
			if ((!m_gameMain->IsAttackPoker(pk)&&!m_gameMain->IsDefendPoker(pk))&& pk->getNum()!=10)
			{
				pk->SelectPkSuoTou(1);
			}
		}
	}

	m_gameMain->m_btnQipai->setVisible(true);
	int iState = 0;
	this->m_isSelect = true;
	this->setPosition(Vec2(this->getPositionX(), this->getPositionY() + 10));
	m_gameMain->getArrPlayerOut()->addObject(this);

	bool bYiwei = false;
	bool bAttack = false;
	bool bJiepai = false;
	bool bHuixue = false;

	CCARRAY_FOREACH(m_gameMain->getArrPlayerOut(), object) {
		Poker* pk = (Poker*)object;
		//阴阳攻击，防守，回血，截牌，除了移位都可以，点数为5
		if (pk->getNum() == 10)
		{
			//m_gameMain->m_btnAttack->setVisible(true);
			//m_gameMain->m_btnQipai->setVisible(true);
			//m_gameMain->m_btnJiepai->setVisible(true);

		}

	}

	if (m_gameMain->m_npcattakcard->count() > 0)
	{
		m_gameMain->m_btnQipai->loadTextureNormal("res/giveup.png");

		if (m_gameMain->Isdefend())
		{
			m_gameMain->m_btnAttack->loadTextureNormal("res/defend.png");
			m_gameMain->m_btnAttack->setVisible(true);
			bAttack = true;
		}
	}
	else
	{
		m_gameMain->m_btnAttack->loadTextureNormal("res/atkpress.png");
		m_gameMain->m_btnQipai->loadTextureNormal("res/give.png");

	
		if (m_gameMain->Isyiwei())
		{
			bYiwei = true;
			m_gameMain->m_btnYiwei->setVisible(true);
		}

		if (m_gameMain->IsHuixue())
		{
			bHuixue = true;
			m_gameMain->m_btnHuixue->setVisible(true);
		}

		if (m_gameMain->IsAttackPoker(this))
		{
			bAttack = true;
			m_gameMain->m_btnAttack->setVisible(true);
		}

		if (m_gameMain->Isjiepai(this))
		{
			bJiepai = true;
			m_gameMain->m_btnJiepai->setVisible(true);
		}
	}

	if (m_gameMain->getArrPlayerOut()->count() > 1) // 多张牌选择不能显示弃牌
	{
		m_gameMain->m_btnQipai->setVisible(false);
	}  

	if (m_gameMain->getplayer()->getIsJiaoseTouch() == true) //如果已经点击，就不能攻击防守，截牌，移位
	{
		m_gameMain->m_btnAttack->setVisible(false);
		m_gameMain->m_btnYiwei->setVisible(false);
		m_gameMain->m_btnJiepai->setVisible(false);
	}
	else
	{
		printf("123122");
	}
	Size  winSize = Director::getInstance()->getWinSize();
	//1          2     3           4  
   if(bAttack&&bYiwei&&bJiepai&&bHuixue)
	{ 
		m_gameMain->m_btnAttack->setPositionX(winSize.width*0.1);
		m_gameMain->m_btnYiwei->setPositionX(winSize.width*0.3);
		m_gameMain->m_btnJiepai->setPositionX(winSize.width*0.5);
		m_gameMain->m_btnHuixue->setPositionX(winSize.width*0.7);
		m_gameMain->m_btnQipai->setPositionX(winSize.width*0.9);
	}
   else if (!bAttack && !bYiwei && !bJiepai && !bHuixue)
   {
	   m_gameMain->m_btnQipai->setPositionX(winSize.width*0.5);
   }
   else if (bAttack&&bYiwei&&bJiepai && !bHuixue)
   {
	   m_gameMain->m_btnAttack->setPositionX(winSize.width*0.2);
	   m_gameMain->m_btnYiwei->setPositionX(winSize.width*0.4);
	   m_gameMain->m_btnJiepai->setPositionX(winSize.width*0.6);
	   m_gameMain->m_btnQipai->setPositionX(winSize.width*0.8);
   }
   else if (bAttack&&bYiwei&&!bJiepai && bHuixue)
   {
	   m_gameMain->m_btnAttack->setPositionX(winSize.width*0.2);
	   m_gameMain->m_btnYiwei->setPositionX(winSize.width*0.4);
	   m_gameMain->m_btnHuixue->setPositionX(winSize.width*0.8);
	   m_gameMain->m_btnQipai->setPositionX(winSize.width*0.6);
   }
   else if (bAttack&&!bYiwei && bJiepai && bHuixue)
   {
	   m_gameMain->m_btnAttack->setPositionX(winSize.width*0.2);
	   m_gameMain->m_btnJiepai->setPositionX(winSize.width*0.4);
	   m_gameMain->m_btnHuixue->setPositionX(winSize.width*0.6);
	   m_gameMain->m_btnQipai->setPositionX(winSize.width*0.8);
   }
   else if (!bAttack && bYiwei && bJiepai && bHuixue)
   {
	   m_gameMain->m_btnYiwei->setPositionX(winSize.width*0.2);
	   m_gameMain->m_btnJiepai->setPositionX(winSize.width*0.4);
	   m_gameMain->m_btnHuixue->setPositionX(winSize.width*0.6);
	   m_gameMain->m_btnQipai->setPositionX(winSize.width*0.8);
   }
   //12
   else if(bAttack && bYiwei && !bJiepai && !bHuixue)
   {
	   m_gameMain->m_btnAttack->setPositionX(winSize.width*0.3);
	   m_gameMain->m_btnYiwei->setPositionX(winSize.width*0.5);
	   m_gameMain->m_btnQipai->setPositionX(winSize.width*0.7);
   }
   //13
   else if (bAttack && !bYiwei && bJiepai && !bHuixue)
   {
	   m_gameMain->m_btnAttack->setPositionX(winSize.width*0.3);
	     m_gameMain->m_btnJiepai->setPositionX(winSize.width*0.5);
	   m_gameMain->m_btnQipai->setPositionX(winSize.width*0.7);
   }//14
   else if (bAttack && !bYiwei && !bJiepai && bHuixue)
   {
	   m_gameMain->m_btnAttack->setPositionX(winSize.width*0.3);
	   m_gameMain->m_btnJiepai->setPositionX(winSize.width*0.5);
	   m_gameMain->m_btnQipai->setPositionX(winSize.width*0.7);
   }//23
   else if (!bAttack && bYiwei && !bJiepai && bHuixue)
   {
	   m_gameMain->m_btnYiwei->setPositionX(winSize.width*0.3);
	   m_gameMain->m_btnHuixue->setPositionX(winSize.width*0.5);
		   m_gameMain->m_btnQipai->setPositionX(winSize.width*0.7);
   }//24
   else if (!bAttack && bYiwei && bJiepai && !bHuixue)
   {
	   m_gameMain->m_btnYiwei->setPositionX(winSize.width*0.3);
	   m_gameMain->m_btnJiepai->setPositionX(winSize.width*0.5);
	   m_gameMain->m_btnQipai->setPositionX(winSize.width*0.7);
   }//34
   else if (!bAttack && bYiwei && bJiepai && !bHuixue)
   {
	   m_gameMain->m_btnYiwei->setPositionX(winSize.width*0.3);
	   m_gameMain->m_btnJiepai->setPositionX(winSize.width*0.5);
	   m_gameMain->m_btnQipai->setPositionX(winSize.width*0.7);
   }///1
   else if (bAttack && !bYiwei && !bJiepai && !bHuixue)
   {
	   m_gameMain->m_btnAttack->setPositionX(winSize.width*0.4);
	   m_gameMain->m_btnQipai->setPositionX(winSize.width*0.6);
   }//2
   else if (!bAttack && bYiwei && !bJiepai && !bHuixue)
   {
	   m_gameMain->m_btnYiwei->setPositionX(winSize.width*0.4);
	   m_gameMain->m_btnQipai->setPositionX(winSize.width*0.6);
   }
   //3
   else if (!bAttack && !bYiwei && bJiepai && !bHuixue)
   {
	   m_gameMain->m_btnJiepai->setPositionX(winSize.width*0.4);
	   m_gameMain->m_btnQipai->setPositionX(winSize.width*0.6);
   }
   //4
   else if (!bAttack && !bYiwei && !bJiepai && bHuixue)
   {
	   m_gameMain->m_btnHuixue->setPositionX(winSize.width*0.4);
	   m_gameMain->m_btnQipai->setPositionX(winSize.width*0.6);
   }

}


void Poker::SelectPkSuoTou(bool b) {
	//¥”≥ˆ≈∆÷–“∆≥˝∏√≈∆
	m_gameMain->m_btnAttack->setVisible(false);
	m_gameMain->m_btnQipai->setVisible(false);
	m_gameMain->m_btnYiwei->setVisible(false);
	m_gameMain->m_btnJiepai->setVisible(false);
	m_gameMain->m_btnHuixue->setVisible(false);

	m_isSelect = false;

	if (b)
	{
		this->setPosition(Vec2(getPositionX(), getPositionY() - 10));
	}
	m_gameMain->getArrPlayerOut()->removeObject(this);
}


