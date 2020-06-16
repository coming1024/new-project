#ifndef __PARENTSCENE_H__//所有场景的父类
#define __PARENTSCENE_H__

#include "cocos2d.h"

class ParentScene : public cocos2d::Scene
{
public:
	//游戏界面大小声明
	cocos2d::Size VisibleSize;

	//横纵轴初始值大小声明
	cocos2d::Vec2 Origin;

	//背景音乐
	const char* BGM;

	//背景音乐音量
	float BGMvolume;

	//背景音乐是否播放
	bool BGMisPlay;

public:
	ParentScene();
	~ParentScene();

	//返回游戏界面大小
	cocos2d::Size GetVisibleSize();

	//返回横纵轴初始值大小
	cocos2d::Vec2 GetOrigin();

	//返回背景音乐音量大小
	float GetBGMvolume();

	//改变背景音乐音量大小
	void SetBGMvolume(float NewVolume);

	//返回背景音乐是否播放
	bool GetBGMisPlay();

	//改变背景音乐播放状态
	void SetBGMisPlay(bool isPlay);

};

#endif // !__PARENTSCENE_H__

