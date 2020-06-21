#include "Prop.h"
Prop* Prop::create(int addNum, int type, SpriteFrame* spriteframe)
{
	Prop* prop = new Prop();
	if (prop && prop->initWithSpriteFrame(spriteframe))
	{
		prop->_addNum = addNum;
		prop->_type = type;
	}
	return prop;
}
int Prop::getAddNum()
{
	return this->_addNum;
}
void Prop::setAddNum(int addNum)
{
	this->_addNum = addNum;
}
int Prop::getType()
{
	return this->_type;
}
void Prop::setType(int type)
{
	this->_type = type;
}