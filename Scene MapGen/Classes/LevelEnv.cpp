#if true

/*
	Program LevelEnv 关卡场景
	File version alpha 0.3
	TC202006192221
	ERR=ETH (P.Q.)
*/

#include "LevelEnv.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

LevelEnv::LevelEnv()
{
	VisibleSize = Director::getInstance()->getVisibleSize();
	Origin = Director::getInstance()->getVisibleOrigin();
	Audio = "RH_SRYAudio/Astrodophin.mp3"; //sry的滑稽
	AudioSwitch = "RH_SRYAudio/EMBER_GeometryDash_(WPerShi Remix).mp3"; //sry的力量
}

LevelEnv::~LevelEnv()
{
	//doing nothing
}

Scene* LevelEnv::createScene()
{
	return LevelEnv::create();
}

bool LevelEnv::init()
{
	if (!Scene::init()) return false;
	this->initDate();

#pragma warning(suppress:4996) //shut up
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
#pragma warning(suppress:4996) //shut up
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(Audio, true);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	srand((unsigned int)time(NULL)); //初始化随机数种子

	auto title = Label::createWithTTF("Level Environment Preview", "fonts/Marker Felt.ttf", 24); //标题，测试用
	if (title != nullptr)
	{
		title->setPosition(Vec2(Origin.x + VisibleSize.width / 2, Origin.y + VisibleSize.height - title->getContentSize().height));
		this->addChild(title, 1);
	}

	//				垂直大小
	//				|	水平大小
	//				|	|	入口个数
	//				|	|	|	出口个数
	//				|	|	|	|	障碍个数
	//				|	|	|	|	|	盒子个数
	//				|	|	|	|	|	|
	MGM::Cmap PtMap(20, 27);
	if (!PtMap.GenerateMap(1, 3, 20, 10)); //false：未成功生成地图
	Vec2 manchor = Vec2(-20, VisibleSize.height - 100);  //地图左上角锚点
	double mscale = 1.1; //地图缩放
	Node* BackGround = PtMap.MapInstantiate(-1); //地图背景
	BackGround->setPosition(manchor);
	BackGround->setScale(mscale);
	addChild(BackGround, -1);
	Node* Physic = PtMap.MapInstantiate(0); //地图物理
	Physic->setPosition(manchor);
	Physic->setScale(mscale);
	addChild(Physic, 0);
	Node* Foreground = PtMap.MapInstantiate(1); //地图前景
	Foreground->setPosition(manchor);
	Foreground->setScale(mscale);
	addChild(Foreground, 2);


	//人物的zorder设置成1

#pragma warning(suppress:4996) //shut up
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(AudioSwitch, true);

	initWithPhysics();
	this->getPhysicsWorld()->setGravity(Vec2(0, 0));

	//初始化英雄
	hero_qishi = qishi::create(heroCache, "one_r0.png");
	hero_qishi->setPosition(Vec2(200, visibleSize.height / 2));
	hero_qishi->setZOrder(1);
	auto playerPos = hero_qishi->getPosition();
	this->addChild(hero_qishi, 1);
	//设置装备位置
	hero_qishi->equipmentOne->setPosition(Vec2(hero_qishi->getContentSize().width / 1.25, hero_qishi->getContentSize().height / 2));
	hero_qishi->equipmentTwo->setPosition(Vec2(hero_qishi->getContentSize().width / 1.25, hero_qishi->getContentSize().height / 2));
	hero_qishi->_pt_bullets = CCArray::create();
	CC_SAFE_RETAIN(hero_qishi->_pt_bullets);
	auto qishiBody = PhysicsBody::createBox(hero_qishi->getContentSize());
	qishiBody->setRotationEnable(false);
	hero_qishi->setPhysicsBody(qishiBody);
	///////////////////////
	//将宝箱放入
	auto bulletFrame = bulletCache->getSpriteFrameByName("ptzd.png");
	auto bullet = Bullet::create(3, bulletFrame);
	auto equipmentCFQ = equipment::create(2, 3, 1, 1, equipmentCache, "cfqz.png", bullet);
	SpriteFrame* frameClose;
	SpriteFrame* frameOpen;
	Vector<SpriteFrame*> vector_frame_open;
	frameClose = chestCache->getSpriteFrameByName("chestClose.png");
	vector_frame_open.pushBack(frameClose);
	frameOpen = chestCache->getSpriteFrameByName("chestOpen.png");
	vector_frame_open.pushBack(frameOpen);
	auto chestOne = Chest::creat(chestCache, "chestClose.png", vector_frame_open, equipmentCFQ);
	auto chestBody = PhysicsBody::createBox(chestOne->getContentSize());
	chestBody->setDynamic(false);
	chestOne->setPhysicsBody(chestBody);
	chestArray->addObject(chestOne);
	chestOne->setPosition(visibleSize.width-150 , visibleSize.height / 2);
	this->addChild(chestOne, 2);




	//两种监听器
	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = CC_CALLBACK_2(LevelEnv::onKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(LevelEnv::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);
	auto touchlistener = EventListenerTouchOneByOne::create();
	touchlistener->onTouchBegan = CC_CALLBACK_2(LevelEnv::onTouchBegan, this);
	touchlistener->onTouchMoved = CC_CALLBACK_2(LevelEnv::onTouchMoved, this);
	touchlistener->onTouchEnded = CC_CALLBACK_2(LevelEnv::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, this);

	this->schedule(schedule_selector(LevelEnv::upDataHeroNature), 0.05f);
	this->schedule(schedule_selector(LevelEnv::upDataAddEnergy), 1.5);

	return true;
}
void LevelEnv::initDate()
{
	weaponArray = CCArray::create();
	CC_SAFE_RETAIN(weaponArray);
	propArray = CCArray::create();
	CC_SAFE_RETAIN(propArray);
	chestArray = CCArray::create();
	CC_SAFE_RETAIN(chestArray);

	bulletCache = SpriteFrameCache::sharedSpriteFrameCache();
	bulletCache->addSpriteFramesWithFile("bullet.plist");
	propCache = SpriteFrameCache::sharedSpriteFrameCache();
	propCache->addSpriteFramesWithFile("prop.plist");
	equipmentCache = SpriteFrameCache::sharedSpriteFrameCache();
	equipmentCache->addSpriteFramesWithFile("weapon.plist");
	chestCache = SpriteFrameCache::sharedSpriteFrameCache();
	chestCache->addSpriteFramesWithFile("chest.plist");
	heroCache = SpriteFrameCache::sharedSpriteFrameCache();
	heroCache->addSpriteFramesWithFile("oneHero.plist");
}

void LevelEnv::upDataHeroNature(float t)
{
	auto progress1 = (ProgressTimer*)hero_qishi->getBloodProgress();
	progress1->setPercentage((((float)hero_qishi->getCurrentLifeNum()) / (float)hero_qishi->getTotalLifeNum()) * 100);

	auto progress2 = (ProgressTimer*)hero_qishi->getEnergyProgress();
	progress2->setPercentage((((float)hero_qishi->getCurrentEnergy()) / (float)hero_qishi->getTotalEnergy()) * 100);

	auto progress3 = (ProgressTimer*)hero_qishi->getDefenceProgress();
	progress3->setPercentage((((float)hero_qishi->getCurrentDefence()) / (float)hero_qishi->getTotalDefence()) * 100);
}
void LevelEnv::upDataAddEnergy(float t)
{
	hero_qishi->addCurrentEnergy(1);
}

void LevelEnv::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event)
{
	if (hero_qishi->getDeath() == false)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_J)
		{
			hero_qishi->swithWeapon(keycode, event);
		}
		if (keycode == EventKeyboard::KeyCode::KEY_A || keycode == EventKeyboard::KeyCode::KEY_S
			|| keycode == EventKeyboard::KeyCode::KEY_D || keycode == EventKeyboard::KeyCode::KEY_W
			|| keycode == EventKeyboard::KeyCode::KEY_UP_ARROW || keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW
			|| keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW || keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			hero_qishi->heroMove(keycode, event);
		}
		if (keycode == EventKeyboard::KeyCode::KEY_K)
		{
			this->playerAndWeaponCollision(weaponArray);
			this->playerAndPropCollison(propArray);
			this->playerAndChestCollison(chestArray);
		}
	}
}

void LevelEnv::onKeyReleased(EventKeyboard::KeyCode keycode, Event* event)
{
	if (hero_qishi->getDeath() == false)
	{
		if (hero_qishi->_isMoveing == true)
		{
			hero_qishi->heroStopMove(keycode, event);
		}
	}
}

bool LevelEnv::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	if (hero_qishi->getDeath() == false)
	{
		hero_qishi->commonAttack(pTouch, pEvent);
		return true;
	}
	return false;
}
void LevelEnv::onTouchMoved(Touch* pTouch, Event* pEvent)
{
	/*if (hero_qishi->getDeath() == false)
	{
		if (hero_qishi->nowEquipment->_isContinue)
		{
			hero_qishi->commonAttack(pTouch, pEvent);
		}
	}*/
}
void LevelEnv::onTouchEnded(Touch* pTouch, Event* pEvent)
{
	if (hero_qishi->getDeath() == false)
	{
		hero_qishi->stopcommonAttack(pTouch, pEvent);
	}
}
bool LevelEnv::isCollision(CCRect rect1, CCRect rect2)
{
	float x1 = rect1.origin.x;
	float y1 = rect1.origin.y;
	float w1 = rect1.size.width;
	float h1 = rect1.size.height;
	float x2 = rect2.origin.x;
	float y2 = rect2.origin.y;
	float w2 = rect2.size.width;
	float h2 = rect2.size.height;
	if (x1 + w1 * 0.5 < x2 - w2 * 0.5)
	{
		return false;
	}
	else if (x1 - w1 * 0.5 > x2 + w2 * 0.5)
	{
		return false;
	}
	else if (y1 + h1 * 0.5 < y2 - h2 * 0.5)
	{
		return false;
	}
	else if (y1 - h1 * 0.5 > y2 + h2 * 0.5)
	{
		return false;
	}
	return true;
}
//人和武器
void LevelEnv::playerAndWeaponCollision(CCArray* weaponArray1)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto heroRect = CCRectMake(hero_qishi->getPosition().x, hero_qishi->getPosition().y, hero_qishi->getContentSize().width +30, hero_qishi->getContentSize().height - 3);
	for (int i = 0; i < weaponArray1->count(); i++)
	{
		equipment* weapon = (equipment*)weaponArray1->objectAtIndex(i);
		auto weaponRect = CCRectMake(weapon->getPosition().x, weapon->getPosition().y, hero_qishi->getContentSize().width, hero_qishi->getContentSize().height);
		if (this->isCollision(heroRect, weaponRect))
		{
			if (hero_qishi->nowEquipment == hero_qishi->equipmentOne)
			{
				//将被选的武器从资源除去
				weaponArray1->removeObjectAtIndex(i);
				weapon->removeFromParent();
				//将落下武器加入武器库
				hero_qishi->equipmentOne->removeFromParent();
				equipment* equipTemp = hero_qishi->equipmentOne;
				weaponArray->addObject(equipTemp);
				equipTemp->setPosition(hero_qishi->getPosition().x, hero_qishi->getPosition().y);
				this->addChild(equipTemp, 2);
				//被选武器加入英雄
				hero_qishi->equipmentOne = weapon;
				hero_qishi->nowEquipment = hero_qishi->equipmentOne;
				hero_qishi->addChild(hero_qishi->equipmentOne, 2);
				if (hero_qishi->getLeftOrRight() == true)
				{
					hero_qishi->equipmentOne->setPosition(Vec2(hero_qishi->getContentSize().width / 6, hero_qishi->getContentSize().height / 2));
				}
				if (hero_qishi->getLeftOrRight() == false)
				{
					hero_qishi->equipmentOne->setPosition(Vec2(hero_qishi->getContentSize().width / 1.25, hero_qishi->getContentSize().height / 2));
				}
			}
			else if (hero_qishi->nowEquipment == hero_qishi->equipmentTwo)
			{
				weaponArray1->removeObjectAtIndex(i);
				weapon->removeFromParent();

				hero_qishi->equipmentTwo->removeFromParent();
				equipment* equipTemp = hero_qishi->equipmentTwo;
				weaponArray->addObject(equipTemp);
				equipTemp->setPosition(hero_qishi->getPosition().x, hero_qishi->getPosition().y);
				this->addChild(equipTemp, 2);

				hero_qishi->equipmentTwo = weapon;
				hero_qishi->nowEquipment = hero_qishi->equipmentTwo;
				hero_qishi->addChild(hero_qishi->equipmentTwo, 2);
				if (hero_qishi->getLeftOrRight() == 1)
				{
					hero_qishi->equipmentTwo->setPosition(Vec2(hero_qishi->getContentSize().width / 6, hero_qishi->getContentSize().height / 2));
				}
				if (hero_qishi->getLeftOrRight() == 0)
				{
					hero_qishi->equipmentTwo->setPosition(Vec2(hero_qishi->getContentSize().width / 1.25, hero_qishi->getContentSize().height / 2));
				}
			}
		}
	}
}
//人和道具
void LevelEnv::playerAndPropCollison(CCArray* propArray1)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto heroRect = CCRectMake(hero_qishi->getPosition().x, hero_qishi->getPosition().y, hero_qishi->getContentSize().width - 7, hero_qishi->getContentSize().height);
	for (int i = 0; i < propArray1->count(); i++)
	{
		Prop* prop = (Prop*)propArray1->objectAtIndex(i);
		auto propRect = CCRectMake(prop->getPosition().x, prop->getPosition().y, prop->getContentSize().width + 5, prop->getContentSize().height + 3);
		if (this->isCollision(heroRect, propRect))
		{
			//类型为1就是加血的
			if (prop->getType() == 1)
			{
				hero_qishi->addCurrentLifeNum(prop->getAddNum());
			}
			//类型为2就是加防御的
			if (prop->getType() == 2)
			{
				hero_qishi->addCurrentDefence(prop->getAddNum());
			}
			propArray1->removeObjectAtIndex(i);
			prop->removeFromParent();
		}
	}
}
//人和宝箱
void LevelEnv::playerAndChestCollison(CCArray* chestArray1)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto heroRect = CCRectMake(hero_qishi->getPosition().x, hero_qishi->getPosition().y, hero_qishi->getContentSize().width - 7, hero_qishi->getContentSize().height);
	for (int i = 0; i < chestArray->count(); i++)
	{
		Chest* chest = (Chest*)chestArray1->objectAtIndex(i);
		auto chestRect = CCRectMake(chest->getPosition().x, chest->getPosition().y, chest->getContentSize().width+50, chest->getContentSize().height);
		if (this->isCollision(heroRect, chestRect))
		{
			auto animationOpen = Animation::createWithSpriteFrames(chest->vector_frame);
			animationOpen->setDelayPerUnit(0.2f);
			animationOpen->setLoops(1);
			auto animateOpen = Animate::create(animationOpen);
			chest->runAction(animateOpen);
			equipment* equip = chest->getEquipment();
			weaponArray->addObject(equip);
			equip->setPosition(chest->getPosition().x, chest->getPosition().y);
			this->addChild(equip, 3);
			chestArray1->removeObjectAtIndex(i);
		}
	}
}
/*
	Program LevelEnv 关卡场景
	End
*/

#endif