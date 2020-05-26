#include "HealthPoint.h"

HealthPoint::HealthPoint()
    : m_progressBackground(NULL)
    , m_progressForeground(NULL)
    , m_totalHealth(0.0f)
    , m_currentHealth(0.0f)
    , m_scale(1.0f)
{

}
void HealthPoint::setBackgroundTexture(const char* pName)
{
    m_progressBackground = CCSprite::create(pName);
    this->addChild(m_progressBackground);
}

void HealthPoint::setForegroundTexture(const char* pName)
{
    m_progressForeground = CCSprite::create(pName);
    m_progressForeground->setAnchorPoint(ccp(0.0f, 0.5f));//设置锚点
    m_progressForeground->setPosition(ccp(-m_progressForeground->getContentSize().width * 0.5f, 0));
    this->addChild(m_progressForeground);
}

void HealthPoint::setTotalHealth(float total)
{
    if (m_progressForeground == NULL) { return; }
    m_scale = m_progressForeground->getContentSize().width / total;
    m_totalHealth = total;
}

void HealthPoint::setCurrentHealth(float progress)
{
    if (m_progressForeground == NULL) { return; }
    if (progress < 0.0f) { progress = 0.0f; }
    if (progress > m_totalHealth) { progress = m_totalHealth; }
    m_currentHealth = progress;
    float rectWidth = progress * m_scale;
    const CCPoint from = m_progressForeground->getTextureRect().origin;
    const CCRect rect = CCRectMake(from.x, from.y, rectWidth, m_progressForeground->getContentSize().height);
    setForegroundTextureRect(rect);
}

void HealthPoint::setForegroundTextureRect(const CCRect& rect)
{
    m_progressForeground->setTextureRect(rect);
}



float HealthPoint::getCurrentHealth() const
{
    return m_currentHealth;
}

float HealthPoint::getTotalHealth() const
{
    return m_totalHealth;
}
