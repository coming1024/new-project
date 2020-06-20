#include "ParentScene.h"

USING_NS_CC;

ParentScene::ParentScene()
{
	this->VisibleSize = Director::getInstance()->getVisibleSize();//x=1024 y=768
	this->Origin = Director::getInstance()->getVisibleOrigin();//origin��x,yֵ��Ϊ0
	this->BGMvolume = 0.5;
	this->BGMisPlay = true;
}

ParentScene::~ParentScene() {};

//������Ϸ�����С
cocos2d::Size ParentScene::GetVisibleSize()
{
	return this->VisibleSize;
}

//���غ������ʼֵ��С
cocos2d::Vec2 ParentScene::GetOrigin()
{
	return this->Origin;
}

//���ر�������������С
float ParentScene::GetBGMvolume()
{
	return this->BGMvolume;
}

//�ı䱳������������С
void ParentScene::SetBGMvolume(float NewVolume)
{
	this->BGMvolume = NewVolume;
}

//���ر��������Ƿ񲥷�
bool ParentScene::GetBGMisPlay()
{
	return this->BGMisPlay;
}

//�ı䱳�����ֲ���״̬
void ParentScene::SetBGMisPlay(bool isPlay)
{
	this->BGMisPlay = isPlay;
}