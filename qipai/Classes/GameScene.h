#pragma once
#include "Global.h"
#include "vector"

#include "ui/CocosGUI.h"
using namespace cocos2d::ui;
#define DAOJISHI  3
class Poker;
class Player;
class Qipan;

//记数 排序出的牌用
struct JiShu
{
	int pkZhi;//牌值
	int num; //牌数量
	__Array* arr; //集合牌

};
//保存电脑牌型
struct PaiXing :public Ref
{
	CARD_TYPE type;
	std::vector<Poker*> vec;
};

class GameScene : public Layer
{
public:
	GameScene();
	~GameScene();
	static Scene* scene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	virtual void onEnter();
	virtual void onExit();
	void PlayerOutPaiXu(__Array* m_arrPlayerOut);
	bool Isdefend();
	bool Isdefend(bool bnpc);
	bool Isyiwei();
	void bianpai();
	bool Isjiepai(Poker *p1);
	bool IsHuixue();
	bool IsHuixue(Poker *pk);
	bool IsDefendPoker(Poker *pk, bool bnpc = false);
	bool IsAttackPoker(Poker *pk, bool bnpc = false);
	void ChoseJinmu(Poker *pk);
	void RefreshBloodNum(int iPlayer, int iBlood);
	Button* m_btnAttack; //攻击
	Button* m_btnQipai; //弃牌
	Button * m_btnYiwei;//移位	
	Button * m_btnJiepai;//截牌
	Button * m_btnHuixue;//回血
	__Array* m_npcattakcard;//电脑攻击牌组合
	__Array * m_playerattackcard;//玩家攻击卡牌
	__Array * m_defendcar;
	int m_iOutCard;//轮到谁出牌，电脑0，玩家1
private:
	void setWanfaVisible(Ref *pSender, Widget::TouchEventType type);

	void attacktouchEvent(Ref *pSender, Widget::TouchEventType type);
	void tioaguotouchEvent(Ref *pSender, Widget::TouchEventType type);
	void setgameEvent(Ref *pSender, Widget::TouchEventType type);
	void yiweiEvent(Ref *pSender, Widget::TouchEventType type);
	void jiepaiEvent(Ref *pSender, Widget::TouchEventType type);
	void huixueEvent(Ref *pSender, Widget::TouchEventType type);
	void QiPai(bool bchu, bool bhui = false, Poker *pJiedepai = NULL);
	void GiveUppai();
	void func(Node* pSender, void* pData);
	void update(float delta);
	void MovePk(Player* play, Poker* pk);
	bool xiPai();
	bool initBackGround();//加载背景
	bool initPlayer();//初始化玩家信息
	bool createPoker();
	bool loadPoker();

	void sendPk();
	void OutCard(float delta);//出牌
	void RobootAction();

	void feizi(bool bMine, const char *name, int icostblood = 0);
	void buPai(bool bnpc);
	void buPai(bool bnpc, Poker *pk); //补一张牌
	void checkCard();
	Poker *m_pBianpk;

private:
	bool m_battk;//攻击模式还是防守模式
	Text * m_time;
	Text * m_time2;
	int  m_iBianIndex;
	Node * m_pWanfa;
	ImageView * m_clock;
	ImageView * m_clock2;

    ImageView * m_player1;
    ImageView * m_player2;
    
    Text* m_TipTetx;
	float m_fTime;
	float m_fTime2;
	int m_iAddHp;
	Button *m_setBtn;
	Text *m_bloddNum1; //我方血量
	Text *m_bloddNum2; //电脑血量
	int m_iSendPk;//已发出第几张牌
	CC_SYNTHESIZE(Player*, m_player, player);//玩家
	CC_SYNTHESIZE(Player*, m_playerOut, PlayerOut);//玩家出的牌
	CC_SYNTHESIZE(__Array*, m_arrPlayerOut, ArrPlayerOut);//玩家选的要出的牌

	Player* m_npcOne;//电脑
	Player* m_npcOneOut;//电脑出的牌

	__Array* m_arrGenPk;//要跟的牌

	bool m_isSend;
	int m_iState;//当前状态 0：发牌状态  2：出牌状态 3：结果状态
	Qipan *m_pBg;
	__Array* m_arrPokers;//所有的牌
	__Array* m_arrResulst;//除去玩家手上剩余的牌
	Size m_winSize;


};
