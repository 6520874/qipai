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
	//������Ӧע��
	touchListener = EventListenerTouchOneByOne::create();//�������㴥���¼�������
	touchListener->onTouchBegan = CC_CALLBACK_2(Poker::onTouchBegan, this);//������ʼ
	touchListener->onTouchMoved = CC_CALLBACK_2(Poker::onTouchMoved, this);//�����ƶ�
	touchListener->onTouchEnded = CC_CALLBACK_2(Poker::onTouchEnded, this);//��������
	touchListener->setSwallowTouches(true);//�������̲�����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);//ע��ַ���
}
void Poker::onExit(){
	//�Ƴ�������Ӧ
	_eventDispatcher->removeEventListenersForTarget(this);
	Sprite::onExit();
}
bool Poker::onTouchBegan(Touch *pTouch, Event *pEvent){
	Size size = getContentSize();
	Rect rect(-size.width/2,-size.height/2,size.width,size.height);
	Point ptouch = convertTouchToNodeSpaceAR(pTouch); //��Ӣ��֮��ת�� ���� �� �ڵ�ռ�

	return false;
	//������ﷵ��false���������̵�
}
void Poker::onTouchMoved(Touch *pTouch, Event *pEvent){

}
void Poker::onTouchEnded(Touch *pTouch, Event *pEvent){

}
void Poker::onTouchCancelled(Touch *pTouch, Event *pEvent){

}
