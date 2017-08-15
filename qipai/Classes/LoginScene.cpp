#include "LoginScene.h"
#include "GameScene.h"
#include<algorithm>
#include <string>
#include <deque>
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <stdio.h>
#include <SimpleAudioEngine.h>
#include "Convert.h"
#include "Script/ScriptXMLparse.h"
#include "Script/utility.h"
#include "WindowInfo.h"

LoginScene::LoginScene() {
	cocos2d::ScriptXMLparse kScriptXml2("HNScriptValueStr.xml");
	m_winSize = Director::getInstance()->getWinSize();
	
}
LoginScene::~LoginScene() {
	
}

Scene* LoginScene::scene() {
	Scene* scene = Scene::create();
	LoginScene * gameLayer = LoginScene::create();
	scene->addChild(gameLayer);
	return scene;
}

bool LoginScene::init() {
	Layer::init();
	bool isRet = true;
	auto rootNode = CSLoader::createNode("LoginLayer.csb");
	addChild(rootNode);


	Button * p1 = (Button*)(cocos2d::ui::Helper::seekWidgetByName((Widget*)rootNode, "Button_1"));
	p1->addTouchEventListener(CC_CALLBACK_2(LoginScene::LogintouchEvent, this));


	if (CC_TARGET_PLATFORM != CC_PLATFORM_WIN32)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music/csmj.mp3", true);
	}
	return isRet;
}

void  LoginScene::LogintouchEvent(Ref *pSender, Widget::TouchEventType type)
{

	switch (type)
	{
	case Widget::TouchEventType::BEGAN: 
		
		break;
	case Widget::TouchEventType::MOVED: 
		break;
	case Widget::TouchEventType::ENDED:

		auto scene = GameScene::scene();

		// run
		auto director = Director::getInstance();
		director->runWithScene(scene);
		break;
	}

}


void LoginScene::onEnter() {
	Layer::onEnter();

}
void LoginScene::onExit() {
	Layer::onExit();
}
