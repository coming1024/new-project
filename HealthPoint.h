#ifndef __HEALTHPOINT_H__
#define __HEALTHPOINT_H__

#include "cocos2d.h"
using namespace cocos2d;

class HealthPoint : public CCNode
{
public:
    HealthPoint();

public:
    //设置血条背景
    void setBackgroundTexture(const char* pName);
    //设置血条前景
    void setForegroundTexture(const char* pName);
    //设置总血量
    void setTotalHealth(float total);
    //设置当前血量
    void setCurrentHealth(float health);
    //得到当前血量
    float getCurrentHealth() const;
    //得到总血量
    float getTotalHealth() const;

private:
    //设置前景血条显示的长度
    void setForegroundTextureRect(const CCRect& rect);

private:
    CCSprite* m_progressBackground;//背景血条
    CCSprite* m_progressForeground;//前景血条
    float m_totalHealth;//总血量
    float m_currentHealth;//当前血量
    float m_scale;//放大倍数
};

#endif#pragma once
