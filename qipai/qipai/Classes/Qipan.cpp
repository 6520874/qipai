#include "Qipan.h"

#include "Poker.h"
#include "Player.h"
Qipan::Qipan()
{
	m_bTouch = false;
	m_bHuase = 0;

}


Qipan::~Qipan()
{
}

void Qipan::setplayer(Player *player)
{
	m_p = player;

}
void Qipan::onEnter() {
	Sprite::onEnter();
	//触摸响应注册
	touchListener = EventListenerTouchOneByOne::create();//创建单点触摸事件监听器
	touchListener->onTouchBegan = CC_CALLBACK_2(Qipan::onTouchBegan, this);//触摸开始
	touchListener->onTouchMoved = CC_CALLBACK_2(Qipan::onTouchMoved, this);//触摸移动
	touchListener->onTouchEnded = CC_CALLBACK_2(Qipan::onTouchEnded, this);//触摸结束
	touchListener->setSwallowTouches(true);//不向下吞并触摸
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);//注册分发器
}
void Qipan::onExit() {
	//移除触摸响应
	_eventDispatcher->removeEventListenersForTarget(this);
	Sprite::onExit();
}


Qipan* Qipan::create(const char *pszFileName) {
	Qipan* pk = new Qipan();

	pk->initWithFile(pszFileName);

	return pk;
}

void Qipan::setTouchTure(int huase)
{
	m_bTouch = true;
	m_bHuase = huase;

}
bool Qipan::onTouchBegan(Touch *pTouch, Event *pEvent) {

	if (!m_bTouch)
	{
		return false;
	}
	//tu  5        1
	 //huo    2 9  2
   //mu    3 4    3
//shui  1 8   4

//jin    6 7   5

	int istate = m_bHuase + 1;

	bool bdao = false;

	if (istate >= 6)
	{
		bdao = true;

	}

	Size size = getContentSize();

	Point ptouch = convertTouchToNodeSpaceAR(pTouch); //由英文之意转换 触摸 到 节点空间

	Rect rect9(-size.width / 6, size.height / 6, size.width / 3, size.height / 3);
	Rect rect8(-size.width / 2, -size.height / 2, size.width / 3, size.height / 3);
	Rect rect7(size.width / 6, -size.width / 6, size.width / 3, size.height / 3);
	Rect rect6(size.width / 6, -375, size.width / 3, size.height / 3);
	Rect rect5(-size.width / 6, -125, size.width / 3, size.height / 3);
	Rect rect4(-size.width / 2, size.width / 6, size.width / 3, size.height / 3);
	Rect rect3(-size.width / 2, -size.width / 6, size.width / 3, size.height / 3);
	Rect rect2(size.width / 6, 125, size.width / 3, size.height / 3);
	Rect rect1(-size.width / 6, -size.width / 2, size.width / 3, size.height / 3);



	if (rect9.containsPoint(ptouch) && (istate == 2 || bdao))
	{
		m_p->setRolePlace(9);
		restoreGame();
		return true;
	}
	else if (rect8.containsPoint(ptouch) && (istate == 4 || bdao))
	{
		m_p->setRolePlace(8);
		restoreGame();
		return true;
	}
	else if (rect7.containsPoint(ptouch) && (istate == 5 || bdao))
	{
		m_p->setRolePlace(7);
		restoreGame();
		return true;
	}
	else if (rect6.containsPoint(ptouch) && (istate == 5 || bdao))
	{
		m_p->setRolePlace(6);
		restoreGame();
		return true;
	}
	else if (rect5.containsPoint(ptouch) && (istate == 1 || bdao))
	{
		m_p->setRolePlace(5);
		restoreGame();
		return true;
	}
	else if (rect4.containsPoint(ptouch) && (istate == 3 || bdao))
	{
		m_p->setRolePlace(4);
		restoreGame();
		return true;
	}
	else if (rect3.containsPoint(ptouch) && (istate == 3 || bdao))
	{
		m_p->setRolePlace(3);
		restoreGame();
		return true;
	}
	else if (rect2.containsPoint(ptouch) && (istate == 2 || bdao))
	{
		m_p->setRolePlace(2);
		restoreGame();
		return true;
	}
	else if (rect1.containsPoint(ptouch) && (istate == 4 || bdao))
	{
		m_p->setRolePlace(1);
		restoreGame();
		return true;
	}


	return false;

}

void Qipan::restoreGame()
{
	Ref *object;

	CCARRAY_FOREACH(m_game->getPlayer()->getArrPk(), object) {
		Poker* pk = (Poker*)object;
		pk->setEnableNum(true);
	}
	m_bTouch = false;
	m_game->m_iOutCard++;

}
void Qipan::onTouchMoved(Touch *pTouch, Event *pEvent) {

}
void Qipan::onTouchEnded(Touch *pTouch, Event *pEvent) {

}
void Qipan::onTouchCancelled(Touch *pTouch, Event *pEvent) {

}

