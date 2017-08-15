#include "GameScene.h"
#include<algorithm>
#include <string>
#include <deque>
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <stdio.h>
#include "Poker.h"
#include "Player.h"
#include "Qipan.h"
#include <SimpleAudioEngine.h>
#include "Convert.h"
#include "Script/ScriptXMLparse.h"
#include "Script/utility.h"
#include "WindowInfo.h"
#include "ResultLayer.h"

GameScene::GameScene() {
	cocos2d::ScriptXMLparse kScriptXml2("HNScriptValueStr.xml");
	m_winSize = Director::getInstance()->getWinSize();
	m_arrPokers = __Array::create();
	m_player = new Player();
	m_player->setGameMain(this);
	m_npcOne = new Player();
	m_npcOne->setGameMain(this);
	m_pBg = NULL;
	m_arrPokers->retain();
	m_iState = 0;
	m_iSendPk = 0;
	m_isSend = true;
	m_iAddHp = 0;
	m_iOutCard = 0; //电脑先出
	m_time = NULL;
	m_clock = NULL;
	m_playerOut = new Player();
	m_npcOneOut = new Player();
	m_arrPlayerOut = __Array::create(); //选的牌
	m_arrPlayerOut->retain();
	m_arrGenPk = __Array::create();
	m_arrGenPk->retain();
	m_npcattakcard = __Array::create();
	m_npcattakcard->retain();

	m_playerattackcard = __Array::create();
	m_playerattackcard->retain();
	m_fTime2 = 3;
	m_defendcar = __Array::create();
	m_defendcar->retain();
}
GameScene::~GameScene() {
	CC_SAFE_DELETE(m_player);
	CC_SAFE_DELETE(m_npcOne);
	CC_SAFE_DELETE(m_playerOut);
	CC_SAFE_DELETE(m_npcOneOut);
	CC_SAFE_RELEASE(m_arrPokers);
	CC_SAFE_RELEASE(m_arrPlayerOut);
	CC_SAFE_RELEASE(m_arrGenPk);
}

Scene* GameScene::scene() {
	Scene* scene = Scene::create();
	GameScene * gameLayer = GameScene::create();
	scene->addChild(gameLayer);
	return scene;
}

bool GameScene::init() {
	Layer::init();
	bool isRet = false;
	do
	{
		initBackGround();
		initPlayer();
		
		std::string str = utility::getScriptString("keyopen");
		if (str=="1")
		{
			loadPoker();
		}
		else
		{
			createPoker();
			xiPai();
		}
		scheduleUpdate();
		isRet = true;
	} while (0);
	return isRet;
}

void GameScene::onEnter() {
	Layer::onEnter();

}
void GameScene::onExit() {
	Layer::onExit();
}
bool GameScene::initBackGround() {

	auto rootNode = CSLoader::createNode("Layer.csb");
	addChild(rootNode);

	if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/csmj.mp3", true);
	}


	auto panel = rootNode->getChildByName("Panel_1");

	WindowInfo::Instance().changWinSize(panel);
	auto bg1 = panel->getChildByName("Image_1");

    m_player2 = (ImageView*)(cocos2d::ui::Helper::seekWidgetByName((Widget*)rootNode, "Image_6"));
    m_player1 = (ImageView*)(cocos2d::ui::Helper::seekWidgetByName((Widget*)rootNode, "Image_3"));

  
	m_pWanfa = cocos2d::ui::Helper::seekWidgetByName((Widget*)rootNode, "Panel_2");
	 Button * pSet = (Button*)(cocos2d::ui::Helper::seekWidgetByName((Widget*)m_pWanfa, "Button_1"));
	 pSet->addTouchEventListener(CC_CALLBACK_2(GameScene::setWanfaVisible, this));

	m_clock = (ImageView*)bg1->getChildByName("Image_clock");
	m_time = (Text*)m_clock->getChildByName("Text_time");
	m_clock->setVisible(false);

	m_clock2 = (ImageView*)bg1->getChildByName("Image_clock_2");
	m_time2 = (Text*)m_clock2->getChildByName("Text_time");
	m_clock2->setVisible(false);

	m_TipTetx = (Text*)(Helper::seekWidgetByName((Widget*)rootNode, "Text_tip"));

	m_pBg = Qipan::create("bk.png");
	m_pBg->setGameMain(this);
	if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		m_pBg->setScale(0.9);
	else
		m_pBg->setScale(0.9);
	bg1->addChild(m_pBg);

	m_pBg->setPosition(m_winSize.width / 2, m_winSize.height / 2);
	m_btnAttack = (Button*)bg1->getChildByName("Button_1");
	m_btnAttack->addTouchEventListener(CC_CALLBACK_2(GameScene::attacktouchEvent, this));

	m_btnQipai = (Button*)bg1->getChildByName("Button_2");
	m_btnQipai->addTouchEventListener(CC_CALLBACK_2(GameScene::tioaguotouchEvent, this));

	m_setBtn = (Button*)bg1->getChildByName("Button_set");
	m_setBtn->addTouchEventListener(CC_CALLBACK_2(GameScene::setgameEvent, this));

	m_btnYiwei = (Button*)bg1->getChildByName("Button_yiwei");
	m_btnYiwei->addTouchEventListener(CC_CALLBACK_2(GameScene::yiweiEvent, this));

	m_btnJiepai = (Button*)bg1->getChildByName("Button_jiepai");
	m_btnJiepai->addTouchEventListener(CC_CALLBACK_2(GameScene::jiepaiEvent, this));

	m_btnHuixue = (Button*)bg1->getChildByName("Button_huixue");
	m_btnHuixue->addTouchEventListener(CC_CALLBACK_2(GameScene::huixueEvent, this));

	m_btnAttack->setVisible(false);
	m_btnQipai->setVisible(false);
	m_btnYiwei->setVisible(false);
	m_btnJiepai->setVisible(false);
	m_btnHuixue->setVisible(false);

	m_bloddNum1 = (Text*)(Helper::seekWidgetByName((Widget*)rootNode, "Text_bloodNum1"));
	m_bloddNum2 = (Text*)(Helper::seekWidgetByName((Widget*)rootNode, "Text_bloodNum2"));

	return  1;
}


void GameScene::RefreshBloodNum(int iPlayer, int iBlood)
{
	char a[10] = { 0 };
	sprintf(a,"%d", iBlood);
	if (iPlayer == 0)
	{
		m_bloddNum1->setString(a);
	}
	else
	{
		m_bloddNum2->setString(a);
	}
}
void GameScene::GiveUppai()
{
	Ref* object = NULL;

	CCARRAY_FOREACH(m_arrPlayerOut, object) {
		Poker* pk = (Poker *)object;   //移位逻辑
		pk->SelectPkSuoTou(1);
	}
	int iresult = 0;
	iresult = m_npcattakcard->count();

	CCARRAY_FOREACH(m_npcattakcard, object) {
		Poker* pk = (Poker*)object;
		if (pk->getNum() == 9)
		{
			iresult++;
		}
	}
	if (iresult >= 4) iresult = 6;
	else  if (iresult == 0) iresult = 0;
	else iresult = iresult + 1;
	int iBlood = m_player->getBloodNum();

	iBlood -= iresult;
	m_arrPlayerOut->removeAllObjects();
	if (iBlood <= 0)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/fail.mp3");
		iBlood = 0;
		unscheduleUpdate();
		ResultLayer *player = ResultLayer::create();
		player->setLayer(false);
	    //setLayer
		addChild(player, 10000);
	}
	m_player->setBloodNum(iBlood);
	char a[2] = { 0 };
	sprintf(a, "%d", iBlood);
	m_bloddNum1->setString(a);

	std::string name = utility::a_u8(utility::getScriptString("attack1"));

	if (!m_battk)
		feizi(1, name.c_str(), iresult);

	m_btnAttack->setVisible(false);
	m_btnQipai->setVisible(false);
	m_btnYiwei->setVisible(false);
	m_btnJiepai->setVisible(false);
	m_btnHuixue->setVisible(false);
	++m_iOutCard;
}


void GameScene::QiPai(bool bchu, bool bhui, Poker *pJiedepai)
{
	Ref* object = NULL;

	if (pJiedepai)
	{
		if (bchu)
		{
			m_playerOut->getArrPk()->removeObject(pJiedepai);
		}
		else
		{
			m_npcOneOut->getArrPk()->removeObject(pJiedepai);
		}
	}

	CCARRAY_FOREACH(m_playerOut->getArrPk(), object) {
		Poker* pk = (Poker*)object;
		pk->removeFromParent();
	}
	m_playerOut->getArrPk()->removeAllObjects();
	m_playerOut->getArrPk()->addObjectsFromArray(m_arrPlayerOut);
	m_playerattackcard->removeAllObjects();
	if (m_battk&&bchu)
	{
		m_playerattackcard->addObjectsFromArray(m_arrPlayerOut);
		std::string str = utility::a_u8(utility::getScriptString("mattack"));

		feizi(0, str.c_str(), 0);
	}

	m_arrPlayerOut->removeAllObjects();
	m_playerOut->updatePkWeiZhi();
	m_player->setIsOutPk(true);

	CCARRAY_FOREACH(m_playerOut->getArrPk(), object) {
		Poker* pk = (Poker *)object;
		Point tt = m_player->getPt();
		pk->setDianJi(false);
		pk->setPositionY(tt.y + PKCHUHEIGHT);

		m_player->getArrPk()->removeObject(pk);
		m_player->updatePkWeiZhi();
		if (bhui)
		{
			buPai(0, pJiedepai);
		}
		else
		{
			buPai(0);
		}

	}

	m_btnAttack->setVisible(false);
	m_btnQipai->setVisible(false);
	m_btnYiwei->setVisible(false);
	m_btnJiepai->setVisible(false);
	m_btnHuixue->setVisible(false);

	//要做大小牌的判断
	++m_iOutCard;
}


void GameScene::huixueEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN: break;
	case Widget::TouchEventType::MOVED: break;
	case Widget::TouchEventType::ENDED:
	{
		int iBloodNum = m_player->getBloodNum();

		iBloodNum += m_iAddHp;

		if (iBloodNum > 5)
		{
			iBloodNum = 5;
		}
		m_player->setBloodNum(iBloodNum);

		char a[2] = { 0 };
		sprintf(a, "%d", iBloodNum);
		m_bloddNum1->setString(a);
		QiPai(false);

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/energy.mp3");
	}

	break;
	default:break;

	}
}


void GameScene::jiepaiEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN: break;
	case Widget::TouchEventType::MOVED: break;
	case Widget::TouchEventType::ENDED:
	{
		Poker *pk = (Poker *)m_arrGenPk->getObjectAtIndex(0);
		pk->setVisible(true);
		QiPai(0, 1, pk);
	}
	break;
	default:break;
	}
}

void GameScene::yiweiEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN: break;
	case Widget::TouchEventType::MOVED: break;
	case Widget::TouchEventType::ENDED:

		checkCard();
		break;
	default:break;
	}

}

void GameScene::setgameEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN: break;
	case Widget::TouchEventType::MOVED: break;
	case Widget::TouchEventType::ENDED:

	{
		m_pWanfa->setPosition(Vec2(0, 100));
		m_pWanfa->setVisible(true);

		Ref* object = NULL;

		CCARRAY_FOREACH(m_player->getArrPk(), object)
		{
			Poker* pk = (Poker*)object;
			pk->setVisible(false);

		}

		CCARRAY_FOREACH(m_playerOut->getArrPk(), object)
		{
			Poker* pk = (Poker*)object;
			pk->setVisible(false);
		}


		CCARRAY_FOREACH(m_npcOne->getArrPk(), object)
		{
			Poker* pk = (Poker*)object;
			pk->setVisible(false);

		}
		CCARRAY_FOREACH(m_npcOneOut->getArrPk(), object)
		{
			Poker* pk = (Poker*)object;
			pk->setVisible(false);

		}
	}

	break;
	default:break;
	}

}

void GameScene::tioaguotouchEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN: break;
	case Widget::TouchEventType::MOVED: break;
	case Widget::TouchEventType::ENDED:
		m_fTime = 25;
		if (m_npcattakcard->count() > 0) GiveUppai();
		else 		QiPai(false);
		break;
	default:break;
	}

}

void GameScene::setWanfaVisible(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN: break;
	case Widget::TouchEventType::MOVED: break;
	case Widget::TouchEventType::ENDED:
		m_pWanfa->setVisible(false);
		Ref* object = NULL;

		CCARRAY_FOREACH(m_player->getArrPk(), object)
		{
			Poker* pk = (Poker*)object;
			pk->setVisible(true);
		}
		
		CCARRAY_FOREACH(m_playerOut->getArrPk(), object)
		{
			Poker* pk = (Poker*)object;
			pk->setVisible(true);
		}


		CCARRAY_FOREACH(m_npcOne->getArrPk(), object)
		{
			Poker* pk = (Poker*)object;
			pk->setVisible(true);

		}
		CCARRAY_FOREACH(m_npcOneOut->getArrPk(), object)
		{
			Poker* pk = (Poker*)object;
			pk->setVisible(true);

		}



	}
	

}
void GameScene::attacktouchEvent(Ref *pSender, Widget::TouchEventType type)
{
	if (m_arrPlayerOut->count() <= 0)
	{
		return;
	}
	switch (type)
	{
	case Widget::TouchEventType::BEGAN: break;
	case Widget::TouchEventType::MOVED: break;
	case Widget::TouchEventType::ENDED:
		QiPai(true);
		break;
	default:break;
	}
}


//加载配置扑克
bool GameScene::loadPoker()
{
	Poker* pk;
	int a[200] = { };

	 std::string str = utility::getScriptString("handpk");
	 char* c_s = (char*)str.c_str();

	 char *p[200];
	 char *buf;
	 p[0] = strtok_r(c_s, ",", &buf);
	 int i = 0;
	 while (p[i])
	 {
		 i++;
		 p[i] = strtok_r(NULL, ",", &buf);
	 }
	 p[i] = "\0";
	 int j = i;

	 for (int i = 0; i < j; i++)
	 {
		 a[i] = atoi(p[i]);

	 }


	for (int i = 0; i <sizeof(a)/4; i++)
	{
		__String *s = nullptr;
		if (a[i]/10<=0)
		{
			s = __String::createWithFormat("%d.png", a[i]);
		}
		else
		{
			s = __String::createWithFormat("%d%d.png", a[i]/10, a[i]%10);
		}

		pk = pk->create(s->getCString());
		pk->setNum(a[i]%10);
		if (a[i] / 10== 5 && a[i] % 10==0) pk->setNum(11);
		else if(a[i] / 10 == 5) pk->setNum(10);

		pk->setPicture(s->getCString());
		pk->setGameMain(this);
		pk->setHuaSe(a[i]/10);
		pk->setScale(0.5);
		pk->setPosition(Vec2(m_winSize.width / 2, m_winSize.height / 2));
		this->addChild(pk);
		pk->setVisible(false);
		this->m_arrPokers->addObject(pk);
	}

	return true;
}
bool GameScene::createPoker()
{
	bool isRet = false;
	do
	{
		Poker* pk;
		//¥¥Ω®50∏ˆ≈∆ 
		for (int t = 0; t < 2; t++)
		{
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j <= 9; j++)
				{
					__String *s = nullptr;
					if (i == 0)
					{
						s = __String::createWithFormat("%d.png", j);
					}
					else
					{
						s = __String::createWithFormat("%d%d.png", i, j);
					}

					
					pk = pk->create(s->getCString());
					if (i == 50) pk->setNum(11);
					//else pk->setNum(10);
					pk->setNum(j);
					pk->setPicture(s->getCString());
					pk->setGameMain(this);
					pk->setHuaSe(i);
					pk->setScale(0.5);
					pk->setPosition(Vec2(m_winSize.width / 2, m_winSize.height / 2));
					this->addChild(pk);
					pk->setVisible(false);
					this->m_arrPokers->addObject(pk);
				}
			}
		}
		//dao yinyang  
		for (int t = 0; t < 2; t++)
			for (int i = 50; i <= 52; i++)
			{
				__String *s = __String::createWithFormat("%d.png", i);
				pk = pk->create(s->getCString());
				if (i == 50) pk->setNum(11);
				else pk->setNum(10);

				pk->setHuaSe(5);
				pk->setPicture(s->getCString());
				pk->setVisible(false);
				pk->setScale(0.5);
				pk->setGameMain(this);
				pk->setPosition(Vec2(m_winSize.width / 2, m_winSize.height / 2));
				this->addChild(pk);
				this->m_arrPokers->addObject(pk);
			}

		isRet = true;
	} while (0);

	return isRet;
}


bool GameScene::xiPai() {
	bool isRet = false;

	m_arrPokers = m_arrPokers;


    __Array* pPlayer = m_player->getArrPk();
	__Array* pNpcOne = m_npcOne->getArrPk();

	m_arrPokers->removeObjectsInArray(pPlayer);
	m_arrPokers->removeObjectsInArray(pNpcOne);

	do
	{
		srand((unsigned int)time(0));
		for (int i = 0; i < 1000; ++i)
		{
			Poker* pk1 = (Poker*)m_arrPokers->getObjectAtIndex(random(0, 105));
			Poker* pk2 = (Poker*)m_arrPokers->getObjectAtIndex(random(0, 105));
			m_arrPokers->exchangeObject(pk1, pk2);
		}
		isRet = true;
	} while (0);

	
	return isRet;
}

bool GameScene::initPlayer() {
	//设置主玩家的位置
	srand((unsigned int)time(0));

	m_pBg->removeAllChildren();
	m_player->setPt(Vec2(m_winSize.width / 2, m_winSize.height*0.1));
	//if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	{
		m_player->setPt(Vec2(m_winSize.width / 2, m_winSize.height*0.05));
	}
	m_player->setPlayerClass(0);
	m_player->initPlayerPlace(m_pBg, random(1, 9));


	//设置电脑的位置
	m_npcOne->setPt(Vec2(m_winSize.width / 2, m_winSize.height*0.95));
	m_npcOne->setPlayerClass(1);
	m_npcOne->initPlayerPlace(m_pBg, random(1, 9));

	m_pBg->setplayer(m_npcOne);

	if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	{
		m_npcOne->setPt(Vec2(m_winSize.width / 2, m_winSize.height*0.95));
	}
	return true;
}


void GameScene::update(float delta)
{

	switch (m_iState)
	{
	case 0:if (m_isSend) sendPk(); break;

	case 1:
		scheduleOnce(schedule_selector(GameScene::OutCard), 0.5); break;
	default:
		break;
	}

}

void  GameScene::buPai(bool bnpc, Poker *pk)
{
	if (m_iSendPk >= 106)
	{
		//除去玩家手上的牌进行洗牌
		xiPai();
		m_iSendPk = 1;

		return;
	}
	pk->setVisible(true);
	if (bnpc)
	{
		m_npcOne->getArrPk()->addObject(pk);
		MovePk(m_npcOne, pk);
	}
	else
	{
		pk->setDianJi(true);
		m_player->getArrPk()->addObject(pk);
		MovePk(m_player, pk);
	}

}

void GameScene::buPai(bool bnpc)
{
	if (m_iSendPk >= 106)
	{
		return;
	}

	Poker* pk = nullptr;

	if (bnpc)
	{
		pk = (Poker*)m_arrPokers->getObjectAtIndex(m_iSendPk++);
		pk->setFlippedY(1);
		pk->showLast();
		pk->setVisible(true);
		m_npcOne->getArrPk()->addObject(pk);
		MovePk(m_npcOne, pk);
	}
	else
	{
		pk = (Poker*)m_arrPokers->getObjectAtIndex(m_iSendPk++);
		pk->setVisible(true);
		pk->setDianJi(true);
		m_player->getArrPk()->addObject(pk);
		MovePk(m_player, pk);
	}
}



void GameScene::sendPk() {

	if (m_iSendPk < 8)
	{
		Poker* pk = nullptr;
		pk = (Poker*)m_arrPokers->getObjectAtIndex(m_iSendPk++);
		pk->setVisible(true);
		m_player->getArrPk()->addObject(pk);
		pk->setDianJi(true);
		MovePk(m_player, pk);

		pk = (Poker*)m_arrPokers->getObjectAtIndex(m_iSendPk++);
		pk->setFlippedY(1);
		pk->showLast();
		pk->setVisible(true);
		m_npcOne->getArrPk()->addObject(pk);
		MovePk(m_npcOne, pk);
		m_isSend = false;
	}
	else
	{
		m_iState = 1;
	}

}


bool GameScene::IsDefendPoker(Poker *pk, bool bnpc)
{
	int index = 0;
	if (pk->getNum() == 10)
	{
		return true;
	}

	if (m_npcattakcard->count() <= 0)
	{
		return false;
	}

	Poker* pk1 = (Poker*)m_npcattakcard->getLastObject();
	int huase = pk1->getHuaSe();

	int keHuase = 0;
	//相生
	if (huase == TU)
	{
		keHuase = MU;
	}
	else if (huase == HUO)
	{
		keHuase = SHUI;
	}
	else if (huase == MU)  keHuase = JIN;
	else if (huase == SHUI) keHuase = TU;
	else if (huase == JIN)  keHuase = HUO;

	if (pk->getHuaSe() == keHuase)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool GameScene::IsAttackPoker(Poker *pk, bool bnpc)
{
	int index = 0;
	int huase = 0;
	if (pk->getNum() == 10)
	{
		return true;
	}
	if (bnpc)
	{
		index = m_player->getJiaoIndex();
		huase = m_player->getRolePlaceHuase(index);
	}
	else
	{
		index = m_npcOne->getJiaoIndex();
		huase = m_npcOne->getRolePlaceHuase(index);
	}

	int keHuase = 0;

	if (huase == TU)
	{
		keHuase = MU;
	}
	else if (huase == HUO)
	{
		keHuase = SHUI;
	}
	else if (huase == MU)  keHuase = JIN;
	else if (huase == SHUI) keHuase = TU;
	else if (huase == JIN)  keHuase = HUO;

	if (keHuase == pk->getHuaSe())
	{
		return true;
	}


	return false;
}


bool GameScene::IsHuixue(Poker *pk)
{
	if (m_player->getBloodNum() > 4)
	{
		return false;
	}

	int index = m_player->getJiaoIndex();
	int huase = m_player->getRolePlaceHuase(index);
	int keHuase = 0;
	//œ‡…˙
	if (huase == TU)
	{
		keHuase = HUO;
	}
	else if (huase == HUO)
	{
		keHuase = MU;
	}
	else if (huase == MU)  keHuase = SHUI;
	else if (huase == SHUI) keHuase = JIN;
	else if (huase == JIN)  keHuase = TU;

	int cout = 0;

	if (pk->getHuaSe() == keHuase)
	{
		cout++;
		if (pk->getNum() == 9)
		{
			cout++;
		}
	}

	if (cout >= 1)
	{
		return true;
	}

	return false;
}

bool GameScene::IsHuixue()
{
	if (m_player->getBloodNum() > 4)
	{
		return false;
	}

	Ref * object;

	int index = m_player->getJiaoIndex();
	int huase = m_player->getRolePlaceHuase(index);
	int keHuase = 0;
	//相生
	if (huase == TU)
	{
		keHuase = HUO;
	}
	else if (huase == HUO)
	{
		keHuase = MU;
	}
	else if (huase == MU)  keHuase = SHUI;
	else if (huase == SHUI) keHuase = JIN;
	else if (huase == JIN)  keHuase = TU;

	//两张以上才弹
	int cout = 0;

	CCARRAY_FOREACH(getArrPlayerOut(), object) {
		Poker* pk = (Poker *)object;

		if (pk->getHuaSe() == keHuase)
		{
			cout++;
			if (pk->getNum() == 9)
			{
				cout++;
			}
		}

	}

	if (cout >= 2)
	{
		m_iAddHp = cout;
		return true;
	}

	return false;
}


bool GameScene::Isdefend(bool bnpc)
{
	if (m_playerattackcard->count() <= 0)
	{
		return false;
	}

	else
	{ //此时只能防守或者弃牌
		Ref * object = NULL;

		m_defendcar->removeAllObjects();

		int attknum = 0;

		CCARRAY_FOREACH(m_playerattackcard, object) {
			Poker* pk = (Poker *)object;
			if (pk->getNum() == 9)//为神兽加1
			{
				attknum++;
			}
			attknum++;
		}

		Poker* pk1 = (Poker*)m_playerattackcard->getLastObject();
		int huase = pk1->getHuaSe();

		int iNum = 0;

		CCARRAY_FOREACH(m_npcOne->getArrPk(), object) {
			Poker* pk = (Poker *)object;
			int keHuase = 0;
			if (huase == TU)
			{
				keHuase = MU;
			}
			else if (huase == HUO)
			{
				keHuase = SHUI;
			}
			else if (huase == MU)  keHuase = JIN;
			else if (huase == SHUI) keHuase = TU;
			else if (huase == JIN)  keHuase = HUO;


			if (pk->getHuaSe() == keHuase)
			{
				m_defendcar->addObject(pk);
				if (pk->getNum() == 9)
				{
					iNum++;
				}
				iNum++;
			}
		}

		if (iNum >= attknum)
		{
			m_npcOneOut->getArrPk()->addObjectsFromArray(m_defendcar);
			m_npcOne->getArrPk()->removeObjectsInArray(m_defendcar);
			Point tt = m_npcOne->getPt();
			//ø€—™
			CCARRAY_FOREACH
			(m_npcOneOut->getArrPk(), object) {
				Poker* pk = (Poker *)object;
				pk->showFront();
				pk->setPosition(Vec2(m_winSize.width / 2, tt.y - PKCHUHEIGHT));
				buPai(1);
			}

			return true;
		}

	}


	return false;

}

bool GameScene::Isdefend()
{

	if (m_npcattakcard->count() <= 0)
	{
		return false;
	}

	else
	{ //此时只能防守或者弃牌
		Ref * object = NULL;
		int attknum = 0;
		CCARRAY_FOREACH(m_npcattakcard, object) {
			Poker* pk = (Poker *)object;
			if (pk->getNum() == 9)
			{
				attknum++;
			}
			attknum++;
		}

		Poker* pk1 = (Poker*)m_npcattakcard->getLastObject();
		int huase = pk1->getHuaSe();

		int iNum = 0;

		CCARRAY_FOREACH(m_arrPlayerOut, object) {
			Poker* pk = (Poker *)object;   //“移位逻辑
			int keHuase = 0;
			//相生
			if (huase == TU)
			{
				keHuase = MU;
			}
			else if (huase == HUO)
			{
				keHuase = SHUI;
			}
			else if (huase == MU)  keHuase = JIN;
			else if (huase == SHUI) keHuase = TU;
			else if (huase == JIN)  keHuase = HUO;

			if (pk->getHuaSe() == keHuase)
			{
				if (pk->getNum() == 9)
				{
					iNum++;
				}

				iNum++;
			}
		}

		if (iNum >= attknum)
		{ 
			//可以防御比大小，防守我方大就是我方出牌，我方小是对方出牌
 
			//m_iSendPk - = 1;

			return true;
		}
	}

	return false;
}

bool GameScene::Isjiepai(Poker *pk)
{
	if (pk->getNum() == 10)
	{
		return true;
	}

	if (m_arrPlayerOut->count() > 1) //多张牌的话不能显示截牌按钮
	{
		return false;
	}
	Poker* pk1 = (Poker*)m_arrGenPk->getLastObject();

	if (pk1 == NULL || pk->getNum()==11 ||pk1->getNum()==11)
	{
		return false;
	}
	int keHuase = 0;

	{
		int huase = pk1->getHuaSe();

		//œ‡…˙
		if (huase == TU)
		{
			keHuase = HUO;
		}
		else if (huase == HUO)
		{
			keHuase = MU;
		}
		else if (huase == MU)  keHuase = SHUI;
		else if (huase == SHUI) keHuase = JIN;
		else if (huase == JIN)  keHuase = TU;

		if (keHuase == pk->getHuaSe())
		{
			return true;
		}

	}

	return false;
}


bool GameScene::Isyiwei()
{
	Ref * object = NULL;


	CCARRAY_FOREACH(m_arrPlayerOut, object) {
		Poker* pk = (Poker *)object;   //“∆Œª¬ﬂº≠

		if (pk->getNum() == 11 ||pk->getNum() == 9)  //道随意变化
		{
			return true;
		}
		else
		{
			int index = m_npcOne->getJiaoIndex();
			int huase = m_npcOne->getRolePlaceHuase(index);

			if (pk->getHuaSe() == huase) //“∆Œªµ–»À
			{
				return true;
			}

		}
	}

	return false;
}


void GameScene::checkCard()
{
	Ref * object = NULL;

	CCARRAY_FOREACH(m_playerOut->getArrPk(), object) {
		Poker* pk = (Poker*)object;
		pk->removeFromParent();
	}

	m_playerOut->getArrPk()->removeAllObjects();
	m_playerOut->getArrPk()->addObjectsFromArray(m_arrPlayerOut);
	m_playerOut->updatePkWeiZhi();

	bool bshenpai = false;

	int shuase = 0;

	CCARRAY_FOREACH(m_playerOut->getArrPk(), object) {
		Poker* pk = (Poker *)object;   //“∆Œª¬ﬂº≠

		shuase = pk->getHuaSe();

		if (pk->getHuaSe() == 5 || pk->getNum() == 9)  //≈–∂œ≈∆–ÕŒªµ¿“ı—Ù
		{
			bshenpai = true;

		}
		else
		{
			int index = m_npcOne->getJiaoIndex();
			int huase = m_npcOne->getRolePlaceHuase(index);
			if (pk->getHuaSe() == huase&&pk->getHuaSe() != 5) //“∆Œªµ–»À
			{
				int iNum = pk->getNum() + 1;
				m_npcOne->setRolePlace(iNum);
			}

			//ª10
		}
		Point tt = m_player->getPt();
		pk->setDianJi(false);
		pk->setPositionY(tt.y + PKCHUHEIGHT);
		m_player->getArrPk()->removeObject(pk);

	}

	m_btnAttack->setVisible(false);
	m_btnQipai->setVisible(false);
	m_btnYiwei->setVisible(false);
	m_btnHuixue->setVisible(false);
	m_btnJiepai->setVisible(false);

	m_player->updatePkWeiZhi();
	buPai(0);


	if (bshenpai)
	{
		m_pBg->setTouchTure(shuase);

		CCARRAY_FOREACH(m_player->getArrPk(), object) {
			Poker* pk = (Poker*)object;
			pk->setEnableNum(false);
		}
		
	}
	else
	{
		++m_iOutCard;
	}
}

void GameScene::feizi(bool bMine, const char *name, int i)
{
	__String  str;

	str.initWithFormat(name, i);

	Label* showFenShu = Label::create(str.getCString(), "Aril", 120);
	if (!bMine)
		showFenShu->setColor(Color3B(0, 128, 0));
	else
		showFenShu->setColor(Color3B(255, 0, 0));

	showFenShu->setPosition(Vec2(m_winSize.width / 2, m_winSize.height / 2));
	m_pBg->addChild(showFenShu, 100);



	if (!bMine)
	{
		showFenShu->runAction(MoveTo::create(3, Vec2(m_winSize.width / 2, m_winSize.height * 2)));
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/attack1.mp3");
	}
	else
	{
		showFenShu->runAction(MoveTo::create(3, Vec2(m_winSize.width / 2, m_winSize.height * -2.5)));
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/cut.mp3");
	}

}

void GameScene::RobootAction()
{
	Ref * object = NULL;

	m_fTime = 25;

	 
	CCARRAY_FOREACH(m_npcOneOut->getArrPk(), object) {
		Poker* pk = (Poker*)object;
		pk->setVisible(false);
	}
	m_npcOneOut->getArrPk()->removeAllObjects();

	if (m_playerattackcard->count() > 0) //防守
	{
		if (Isdefend(0)) //可防守
		{
			m_arrGenPk->removeAllObjects();

		}
		else //扣血
		{
			Poker* pk1 = (Poker*)m_npcOne->getArrPk()->getObjectAtIndex(random(0, 3));
			pk1->showFront();

			m_arrGenPk->removeAllObjects();
			m_arrGenPk->addObject(pk1);
			m_npcOneOut->getArrPk()->addObject(pk1);
			m_npcOne->getArrPk()->removeObject(pk1);
			Point tt = m_npcOne->getPt();
			//ø€—™
			int iresult = 0;

			if (m_playerattackcard->count() > 0)
			{
				iresult = m_playerattackcard->count();
				//if shenshoupai
				CCARRAY_FOREACH(m_playerattackcard, object)
				{
					Poker* pk = (Poker*)object;
					if (pk->getNum() == 9)
					{
						iresult++;
					}
				}

			}

			int iBlood = m_npcOne->getBloodNum();

			if (iresult >= 4) iresult = 6;
			else  if (iresult == 0) iresult = 0;
			else iresult = iresult + 1;

			iBlood -= iresult;

			if (iBlood <= 0)
			{
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/win.mp3");
				iBlood = 0;
				unscheduleUpdate();
				ResultLayer *player = ResultLayer::create();
				player->setLayer(true);
				addChild(player,10000);

			}

			m_npcOne->setBloodNum(iBlood);

			char a[2] = { 0 };
			sprintf(a, "%d", iBlood);
			m_bloddNum2->setString(a);
			feizi(0, utility::a_u8(utility::getScriptString("weizhi1")).c_str(), iresult);
			pk1->setPosition(Vec2(m_winSize.width / 2, tt.y - PKCHUHEIGHT));
			buPai(1);


		}
	}
	else
	{
		Poker *attkPk = NULL;

		bool battak = false;
		bool bcanattak = false;

		//ª˙∆˜»À¬ﬂº≠≈–∂œÕÊº“ «∑Òƒ‹π•ª˜◊‘º∫
		CCARRAY_FOREACH(m_player->getArrPk(), object)
		{
			Poker* pk = (Poker*)object;
			if (IsAttackPoker(pk, false))
			{
				bcanattak = true;
			}
		}
		//if (bcanattak) m_npcOne->yiwei();

		m_npcattakcard->removeAllObjects();

		CCARRAY_FOREACH(m_npcOne->getArrPk(), object)
		{
			Poker* pk = (Poker*)object;
			if (IsAttackPoker(pk, true))
			{
				battak = true;
				m_npcattakcard->addObject(pk);
			}
		}
		srand((unsigned int)time(0)); //…Ë÷√ÀÊª˙÷÷◊”

									  //ƒ‹π•ª˜æÕπ•ª˜

		if (m_npcattakcard->count() <= 0)
		{
			int count = m_npcOne->getArrPk()->count() - 1;
			Poker* pk1 = (Poker*)m_npcOne->getArrPk()->getObjectAtIndex(random(0, count));
			pk1->showFront();
			m_player->getRole()->setEnabled(true);
			m_arrGenPk->removeAllObjects();
			m_arrGenPk->addObject(pk1);
			m_npcOneOut->getArrPk()->addObject(pk1);
			m_npcOne->getArrPk()->removeObject(pk1);
			Point tt = m_npcOne->getPt();
			pk1->setPosition(Vec2(m_winSize.width / 2, tt.y - PKCHUHEIGHT));
			buPai(1);
		}
		else
		{
			float x = m_winSize.width / 2 - ((m_npcattakcard->count() - 1)*pkJianJu + pkWidth) / 2;
			Point tt = m_npcOne->getPt();
			for (int i = 0; i < m_npcattakcard->count(); i++)
			{
				Poker* pk = (Poker*)m_npcattakcard->getObjectAtIndex(i);
				pk->setVisible(true);
				pk->setPosition(Vec2(x + i*pkJianJu + pkWidth / 2, tt.y));
			}

			CCARRAY_FOREACH(m_npcattakcard, object)
			{
				Poker* pk1 = (Poker*)object;
				m_npcOneOut->getArrPk()->addObject(pk1);
				pk1->showFront();
				Point tt = m_npcOne->getPt();
				m_npcOne->getArrPk()->removeObject(pk1);
				pk1->setPositionY(tt.y - PKCHUHEIGHT);
				buPai(1);
			}
			std::string strName = utility::a_u8(utility::getScriptString("eattack"));

			feizi(1, strName.c_str(), 0);
		}

	}
	CCARRAY_FOREACH(m_player->getArrPk(), object) {

		Poker* pk = (Poker*)object;
		pk->setDianJi(true);
	}
	++m_iOutCard;
	this->stopAllActions();
	//scheduleOnce(schedule_selector(GameScene::OutCard), 0.5);
}

void GameScene::OutCard(float delta)
{

	Ref * object = NULL;
	switch (m_iOutCard % 2)
	{
	case 0:
	{
		m_player->setIsJiaoseTouch(false);
		m_fTime2 -= delta;
		if (m_fTime2 <= 0)
		{
			m_fTime2 = 0;
		}
		__String *ss = __String::createWithFormat(" %d", (int)m_fTime2 % 60);
		m_time2->setString(ss->getCString());
		m_clock->setVisible(false);
		m_clock2->setVisible(true);
      
		CCARRAY_FOREACH(m_player->getArrPk(), object) {
	
			Poker* pk = (Poker*)object;
			pk->setDianJi(false);
		}
		this->runAction(Sequence::create(DelayTime::create(2), CallFunc::create(CC_CALLBACK_0
         (GameScene::RobootAction, this)),nullptr));

	}
	break;

	case 1:

		Ref* object;


		if (m_npcattakcard->count() <= 0)
		{
			m_battk = true;

		}
		else {
			m_battk = false;
			m_player->getRole()->setEnabled(false);

		}
		CCARRAY_FOREACH(m_playerOut->getArrPk(), object) {
			Poker* pk = (Poker*)object;
			pk->removeFromParent();
		}
		m_playerOut->getArrPk()->removeAllObjects();

	  
		m_fTime -= delta;
		if (m_fTime <= 0)
		{
			m_fTime = 0;
			srand((unsigned int)time(0)); 
			for (int i = 0; i < m_player->getArrPk()->count() - 1; ++i)
			{
				Poker* pk1 = (Poker*)m_player->getArrPk()->getObjectAtIndex(i);
				pk1->PkSuoTou();
			}

			m_arrPlayerOut->removeAllObjects();
            

			if (m_npcattakcard->count() > 0) GiveUppai();
		
			else
			{
				__Array* poker = m_player->getArrPk();
				Poker* pk1 = (Poker*)poker->getObjectAtIndex(random(0, 3));
				m_arrPlayerOut->addObject(pk1);
				QiPai(false);
			}
		}

		__String *ss = __String::createWithFormat(" %d", (int)m_fTime % 60);

		m_time->setString(ss->getCString());
		m_clock2->setVisible(false);
		m_clock->setVisible(true);

		m_fTime2 = 3;
		break;
	}

}



void GameScene::MovePk(Player* play, Poker* pk)
{
	MoveTo* move;
	__CCCallFuncND* func;
	float time = 0.2;
	move = MoveTo::create(time, play->getPt());
	func = __CCCallFuncND::create(this, callfuncND_selector(GameScene::func), play);
	Sequence* sequence = Sequence::create(move, func, NULL);
	pk->runAction(sequence);
}

void GameScene::func(Node* pSender, void* pData) {
	Player* play = (Player*)pData;
	play->updatePkWeiZhi();
	m_isSend = true;
}

