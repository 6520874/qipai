#include "ResultLayer.h"
#include "LoginScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

ResultLayer::ResultLayer()
{
	m_bWin = false;

}


ResultLayer::~ResultLayer()
{
}


void ResultLayer::setLayer(bool bfalse)
{
	m_bWin = bfalse;
}

bool ResultLayer::init()
{
	auto rootNode = CSLoader::createNode("result.csb");
	addChild(rootNode,100);
    
    auto panel = cocos2d::ui::Helper::seekWidgetByName((Widget*)rootNode, "Panel_1");
    //rootNode:setScale(0);


	m_pImg = (ImageView *)panel->getChildByName("Image_2");
	
	Button* back = (Button*)panel->getChildByName("Button_back");
	back->addTouchEventListener(CC_CALLBACK_2(ResultLayer::backtouchEvent, this));
	return true;
}


void ResultLayer::backtouchEvent(Ref *pSender, Widget::TouchEventType type)
{
	switch (type)
	{
	case Widget::TouchEventType::BEGAN: break;
	case Widget::TouchEventType::MOVED: break;
	case Widget::TouchEventType::ENDED:
    auto scene = LoginScene::scene();
		auto director = Director::getInstance();
		director->runWithScene(scene);
		break;

	}
}

void ResultLayer::onEnter() {
	Layer::onEnter();
	//´¥ÃþÏìÓ¦×¢²á
   
	if (m_bWin)
	{
		m_pImg->loadTexture("res/WinBack.png");

	}
	else
	{
		m_pImg->loadTexture("res/LoseBack.png");

	}
	m_pImg->setScale(0);

	m_pImg->runAction(ScaleTo::create(1, 1));

	touchListener = EventListenerTouchOneByOne::create();//´´½¨µ¥µã´¥ÃþÊÂ¼þ¼àÌýÆ÷
	touchListener->onTouchBegan = CC_CALLBACK_2(ResultLayer::onTouchBegan, this);//´¥Ãþ¿ªÊ¼
	touchListener->onTouchMoved = CC_CALLBACK_2(ResultLayer::onTouchMoved, this);//´¥ÃþÒÆ¶¯
	touchListener->onTouchEnded = CC_CALLBACK_2(ResultLayer::onTouchEnded, this);//´¥Ãþ½áÊø
	touchListener->setSwallowTouches(true);//²»ÏòÏÂÍÌ²¢´¥Ãþ
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);//×¢²á·Ö·¢Æ÷
}
void ResultLayer::onExit() {
	//ÒÆ³ý´¥ÃþÏìÓ¦
	_eventDispatcher->removeEventListenersForTarget(this);
	Layer::onExit();
}



bool ResultLayer::onTouchBegan(Touch *pTouch, Event *pEvent) {

	return false;


}
void ResultLayer::onTouchMoved(Touch *pTouch, Event *pEvent) {

}
void ResultLayer::onTouchEnded(Touch *pTouch, Event *pEvent) {

}
void ResultLayer::onTouchCancelled(Touch *pTouch, Event *pEvent) {

}

