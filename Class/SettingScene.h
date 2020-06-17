#ifndef __SETTINGSCENE_H__
#define __SETTINGSCENE_H__

#include "cocos2d.h"


//������������
extern float BGMvolume;

//���������Ƿ񲥷�
extern bool BGMisPlay;

class SettingScene :public cocos2d::Scene
{
public:
	//��Ϸ�����С����
	cocos2d::Size VisibleSize;

	//�������ʼֵ��С����
	cocos2d::Vec2 Origin;
public:
	SettingScene();
	~SettingScene();

	//������ʼ��
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SettingScene);
	
	//void BGMControl1(Ref* pSender, Control::EventType event);
	//���ֿ���
	void BGMControl(cocos2d::Ref* pSender);

	//��������
	void VolumeControl(cocos2d::Ref* pSender);
	//������һ������
	void BackToLastScene(cocos2d::Ref* pSender);
};

#endif // !__INFOSCENE_H__


