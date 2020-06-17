

#ifndef __HEROSHOME_SCENE_H__
#define __HEROSHOME_SCENE_H__


#include "cocos2d.h"
//Ӣ�۴���
#include "qishi.h"
#include "Bullet.h"
#include "equipment.h"
#include "hero.h"
#include "Buff.h"

class HerosHome :public cocos2d::Scene
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
    HerosHome();
    ~HerosHome();

    //������ʼ��
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(HerosHome);
    
    //Ӣ�۴���
    static qishi* hero_qishi;


    //����������
    void BackToHomeScene(cocos2d::Ref* pSender);

    //������Ϸ����
    void GoToGameScene(cocos2d::Ref* pSender);

    //���ر�������������С
    float GetBGMvolume();

    //�ı䱳������������С
    void SetBGMvolume(float NewVolume);

    //���ر��������Ƿ񲥷�
    bool GetBGMisPlay();

    //�ı䱳�����ֲ���״̬
    void SetBGMisPlay(bool isPlay);
};


#endif 


