#include "Poker.h"
#include "Player.h"
#include "GameScene.h"


Poker::Poker(){

}

Poker::~Poker(){

}


Poker* Poker::create(const char *pszFileName){
	Poker* pk = new Poker();
	if (pk && pk->initWithFile(pszFileName))
	{
		pk->autorelease();
		return pk;
	}
	CC_SAFE_DELETE(pk);
	return pk;
}
void Poker::onEnter(){
	Sprite::onEnter();
	//触摸响应注册
	touchListener = EventListenerTouchOneByOne::create();//创建单点触摸事件监听器
	touchListener->onTouchBegan = CC_CALLBACK_2(Poker::onTouchBegan, this);//触摸开始
	touchListener->onTouchMoved = CC_CALLBACK_2(Poker::onTouchMoved, this);//触摸移动
	touchListener->onTouchEnded = CC_CALLBACK_2(Poker::onTouchEnded, this);//触摸结束
	touchListener->setSwallowTouches(true);//不向下吞并触摸
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);//注册分发器
}
void Poker::onExit(){
	//移除触摸响应
	_eventDispatcher->removeEventListenersForTarget(this);
	Sprite::onExit();
}
bool Poker::onTouchBegan(Touch *pTouch, Event *pEvent){
	Size size = getContentSize();
	Rect rect(-size.width/2,-size.height/2,size.width,size.height);
	Point ptouch = convertTouchToNodeSpaceAR(pTouch); //由英文之意转换 触摸 到 节点空间

	return false;
	//如果这里返回false触摸不被吞掉
}
void Poker::onTouchMoved(Touch *pTouch, Event *pEvent){

}
void Poker::onTouchEnded(Touch *pTouch, Event *pEvent){

}
void Poker::onTouchCancelled(Touch *pTouch, Event *pEvent){

}
