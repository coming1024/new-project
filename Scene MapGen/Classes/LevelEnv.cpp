#if true

/*
	Program LevelEnv 关卡场景
	File version alpha 0.4
	TC202006201042
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

#pragma warning(suppress:4996) //shut up
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
#pragma warning(suppress:4996) //shut up
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(Audio, true);

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
	MGM::Cmap PtMap(36, 50);
	if (!PtMap.GenerateMap(1, 3, 200, 100)); //false：未成功生成地图
	Vec2 manchor = Vec2(100, VisibleSize.height - 100); //地图左上角锚点
	double mscale = 0.25; //地图缩放
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

	//没看懂的物理引擎，但是可以用
	initWithPhysics();
	/*
	//完全没看懂的物理引擎
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	*/

	return true;
}

/*
	Program LevelEnv 关卡场景
	End
*/

#endif