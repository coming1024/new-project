

#ifndef __HEROSHOME_SCENE_H__
#define __HEROSHOME_SCENE_H__


#include "cocos2d.h"
#include "ParentScene.h"
//Ӣ�۴���
#include "qishi.h"
#include "Bullet.h"
#include "equipment.h"
#include "hero.h"
#include "Buff.h"

class HerosHome :public ParentScene
{//Ӣ��ѡ�����

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
};


#endif 


