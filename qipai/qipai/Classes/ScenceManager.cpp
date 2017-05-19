#include "ScenceManager.h"


FV_SINGLETON_STORAGE(HNScenceManager);


HNScenceManager::HNScenceManager(cocos2d::Node* pNode)
	:m_pRootNode(NULL)
	,m_bInBackground(false)
	,m_iScenceTimeID(0)
{
	m_pRootNode = cocos2d::Node::create();
	pNode->addChild(m_pRootNode);
	init();
}
HNScenceManager::HNScenceManager()
	:m_pRootNode(NULL)
	,m_bInBackground(false)
{
	CCAssert(false,"");
	init();
}
HNScenceManager::~HNScenceManager(void)
{
}

void HNScenceManager::init()
{
	/*new HNGameManager;

	new HNHomeScence;
	m_pRootNode->addChild(HNHomeScence::pInstance(),-2);

	new HNLogonScence;
	m_pRootNode->addChild(HNLogonScence::pInstance());

	new HNPrivateScenceHN;
	m_pRootNode->addChild(HNPrivateScenceHN::pInstance());

	new HNNewsScence;
	m_pRootNode->addChild(HNNewsScence::pInstance());

	new HNHelpScence;
	m_pRootNode->addChild(HNHelpScence::pInstance());
	
	new HNSetScence;
	m_pRootNode->addChild(HNSetScence::pInstance());
	
	new PopScence;
	m_pRootNode->addChild(PopScence::pInstance());

	new EffectScence();
	m_pRootNode->addChild(EffectScence::pInstance());
	
	new NoticeMsg();
	m_pRootNode->addChild(NoticeMsg::pInstance());


	new HNGameRecord;
	m_pRootNode->addChild(HNGameRecord::pInstance());

	new ShopScene;
	m_pRootNode->addChild(ShopScene::pInstance());

	InLogonScence();*/
}
void HNScenceManager::HideAll(cocos2d::Node* pActShowNode)
{
	/*HNLogonScence::Instance().setVisible(false);
	HNHomeScence::Instance().setVisible(false);
	HNPrivateScenceHN::Instance().hideAll();
	HNGameRecord::Instance().hideAll();
	HNGameManager::Instance().HideAll();
	HNSetScence::Instance().hideAll(0, Widget::TouchEventType::ENDED);
	HNNewsScence::Instance().hideAll(NULL, Widget::TouchEventType::ENDED);
	HNHelpScence::Instance().hideAll(NULL, Widget::TouchEventType::ENDED);*/
}
cocos2d::Node* HNScenceManager::getRootNode()
{
	return m_pRootNode;
}
void HNScenceManager::addGameNode(cocos2d::Node* pNode)
{
	m_pRootNode->addChild(pNode,-1);
}
void HNScenceManager::InLogonScence()
{
	/*HideAll(HNLogonScence::pInstance());
	HNLogonScence::Instance().setVisible(true);
	HNLogonScence::Instance().EnterScence();*/
}
void HNScenceManager::InHomeScence()
{
	//HideAll(HNLogonScence::pInstance());
	//HNHomeScence::Instance().setVisible(true);
	//HNHomeScence::Instance().EnterScence();
}
void HNScenceManager::InPlayerInfoScence()
{
}
void HNScenceManager::update(float fTime)
{
}
void HNScenceManager::GameBackScence()
{
	//InHomeScence();
}
