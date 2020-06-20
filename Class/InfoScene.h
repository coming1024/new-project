
#ifndef __INFOSCENE_H__
#define __INFOSCENE_H__

#include "cocos2d.h"

class InfoScene :public cocos2d::Scene
{
public:
	//��Ϸ�����С����
	cocos2d::Size VisibleSize;

	//�������ʼֵ��С����
	cocos2d::Vec2 Origin;
public:
	InfoScene();
	~InfoScene();

	//������ʼ��
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(InfoScene);

	//����������
	void BackToLastScene(cocos2d::Ref* pSender);
};

#endif // !__INFOSCENE_H__