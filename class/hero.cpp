#include "hero.h"
USING_NS_CC;
hero* hero::create(SpriteFrameCache* cache, char* s)
{
	hero* player = new hero();
	Size visibleSize = Director::sharedDirector()->getVisibleSize();
	if (player && player->initWithSpriteFrame(cache->spriteFrameByName(s)))
	{
		player->autorelease();
		return player;
	}
	CC_SAFE_DELETE(player);
	return NULL;
}
bool hero::attack(Touch* pTouch, Event* pEvent)
{
	return true;
}
bool hero::heroMove(EventKeyboard::KeyCode keycode, Event* event)
{
	return true;
}
bool hero::heroStopMove(EventKeyboard::KeyCode keycode, Event* event)
{
	return true;
}
bool hero::take_buff(Buff* buff)
{
	return true;
}
bool hero::clear_buff()
{
	return true;
}
void hero::take_damage()
{}
void hero::die_animation()
{}
void hero::die()
{}
