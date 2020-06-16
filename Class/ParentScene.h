#ifndef __PARENTSCENE_H__//���г����ĸ���
#define __PARENTSCENE_H__

#include "cocos2d.h"

class ParentScene : public cocos2d::Scene
{
public:
	//��Ϸ�����С����
	cocos2d::Size VisibleSize;

	//�������ʼֵ��С����
	cocos2d::Vec2 Origin;

	//��������
	const char* BGM;

	//������������
	float BGMvolume;

	//���������Ƿ񲥷�
	bool BGMisPlay;

public:
	ParentScene();
	~ParentScene();

	//������Ϸ�����С
	cocos2d::Size GetVisibleSize();

	//���غ������ʼֵ��С
	cocos2d::Vec2 GetOrigin();

	//���ر�������������С
	float GetBGMvolume();

	//�ı䱳������������С
	void SetBGMvolume(float NewVolume);

	//���ر��������Ƿ񲥷�
	bool GetBGMisPlay();

	//�ı䱳�����ֲ���״̬
	void SetBGMisPlay(bool isPlay);

};

#endif // !__PARENTSCENE_H__

