#include "ParentScene.h"

USING_NS_CC;

ParentScene::ParentScene()
{
	this->VisibleSize = Director::getInstance()->getVisibleSize();//x=1024 y=768
	this->Origin = Director::getInstance()->getVisibleOrigin();//origin的x,y值都为0
	this->BGMvolume = 0.5;
	this->BGMisPlay = true;
}

ParentScene::~ParentScene() {};

//返回游戏界面大小
cocos2d::Size ParentScene::GetVisibleSize()
{
	return this->VisibleSize;
}

//返回横纵轴初始值大小
cocos2d::Vec2 ParentScene::GetOrigin()
{
	return this->Origin;
}

//返回背景音乐音量大小
float ParentScene::GetBGMvolume()
{
	return this->BGMvolume;
}

//改变背景音乐音量大小
void ParentScene::SetBGMvolume(float NewVolume)
{
	this->BGMvolume = NewVolume;
}

//返回背景音乐是否播放
bool ParentScene::GetBGMisPlay()
{
	return this->BGMisPlay;
}

//改变背景音乐播放状态
void ParentScene::SetBGMisPlay(bool isPlay)
{
	this->BGMisPlay = isPlay;
}