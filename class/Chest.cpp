#include "Chest.h"
Chest* Chest::creat(SpriteFrameCache* cache, char* s, Vector<SpriteFrame*> vector_frame_open, equipment* equip)
{
	Chest* chest = new Chest();
	if (chest && chest->initWithSpriteFrame(cache->getSpriteFrameByName(s)))
	{
		chest->includeEquip = equip;
		chest->vector_frame = vector_frame_open;
	}
	return chest;
}

equipment* Chest::getEquipment()
{
	return this->includeEquip;
}