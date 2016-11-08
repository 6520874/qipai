#include "Player.h"
#include "Poker.h"


Player::Player()
{
	m_arrPk = __Array::create();
	m_arrPk->retain();

}

Player::~Player()
{
	CC_SAFE_RELEASE(m_arrPk);

}
void Player::updatePkWeiZhi()
{

}
