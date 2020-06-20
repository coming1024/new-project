#if true

/*
	Program LevelEnv 关卡场景
	File version alpha 0.5
	TC202006201600
	ERR=ETH (P.Q.)
*/

#include "LevelEnv.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

static int level = 0;

LevelEnv::LevelEnv()
{
	VisibleSize = Director::getInstance()->getVisibleSize();
	Origin = Director::getInstance()->getVisibleOrigin();
	Audio = "RH_SRYAudio/Astrodophin.mp3"; //sry的滑稽
	AudioSwitch = "RH_SRYAudio/EMBER_GeometryDash_(WPerShi Remix).mp3"; //sry的力量
	GlobalMap = nullptr;
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

	srand((unsigned int)time(NULL)); //初始化随机数种子

	auto title = Label::createWithTTF("Level Environment Preview", "fonts/Marker Felt.ttf", 24); //标题，测试用
	title->setPosition(Vec2(Origin.x + VisibleSize.width / 2, Origin.y + VisibleSize.height - title->getContentSize().height));
	title->enableGlow(Color4B::BLUE);
	this->addChild(title);
	
	auto closeItem = MenuItemImage::create( //按钮
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(LevelEnv::Trigger, this));
	float x = Origin.x + VisibleSize.width - closeItem->getContentSize().width / 2;
	float y = Origin.y + closeItem->getContentSize().height / 2;
	closeItem->setPosition(Vec2(x, y));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	//没看懂的物理引擎，但是可以用
	initWithPhysics();
	/*
	//完全没看懂的物理引擎
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	*/

#pragma warning(suppress:4996) //shut up
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
#pragma warning(suppress:4996) //shut up
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(Audio, true);




	Node* PtMap;
	PtMap = GenerateEnv(level); //第0关
	addChild(PtMap, 0);
	//PtMap->setVisible(false);


#pragma warning(suppress:4996) //shut up
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(AudioSwitch, true);

	return true;
}

Node* LevelEnv::GenerateEnv(int level)
{
	unsigned int vtsize; //地图垂直大小
	unsigned int hrsize; //地图水平大小
	unsigned int stcont; //地图入口个数
	unsigned int edcont; //地图出口个数
	unsigned int obcont; //地图障碍个数
	unsigned int bxcont; //地图箱子个数
	double strang = 0.4; //地图入口范围
	double edrang = 0.8; //地图出口范围
	switch (level)
	{
	case 0:
		vtsize = 20;
		hrsize = 27;
		stcont = 1;
		edcont = 5;
		obcont = 20;
		bxcont = 10;
		break;
	case 1:
		vtsize = 22;
		hrsize = 29;
		stcont = 1;
		edcont = 5;
		obcont = 36;
		bxcont = 16;
		break;
	case 2:
		vtsize = 24;
		hrsize = 32;
		stcont = 1;
		edcont = 4;
		obcont = 44;
		bxcont = 25;
		break;
	case 3:
		vtsize = 26;
		hrsize = 35;
		stcont = 1;
		edcont = 3;
		obcont = 55;
		bxcont = 30;
		break;
	case 4:
		vtsize = 28;
		hrsize = 37;
		stcont = 1;
		edcont = 2;
		obcont = 60;
		bxcont = 40;
		break;

	default:
		vtsize = 20;
		hrsize = 27;
		stcont = 0;
		edcont = 0;
		obcont = 0;
		bxcont = 0;
		break;
	}
	if (GlobalMap != nullptr) delete GlobalMap;
	GlobalMap = new MGM::Cmap(vtsize, hrsize);
	if (!GlobalMap->GenerateMap(stcont, edcont, obcont,bxcont,strang, edrang))
		throw "Failed map generation";
	Node* map = GlobalMap->MapInstantiate();
	//动态调整地图缩放
	double vtscale = VisibleSize.height / ((double)vtsize * 64); //!64使用
	double hrscale = VisibleSize.width / ((double)hrsize * 64); //!64使用
	double scale;
	if (vtscale < hrscale) scale = vtscale * 0.8;
	else scale = hrscale * 0.8;
	map->setScale(scale);
	//动态调整地图偏移
	double vtoffset = VisibleSize.height / 2 + ((double)vtsize * 64 / 2 * scale); //!64使用
	double hroffset = VisibleSize.width / 2 - ((double)hrsize * 64 / 2 * scale); //!64使用
	map->setPositionY(vtoffset-16);
	map->setPositionX(hroffset-32);
	return map;
}

void LevelEnv::Trigger(Ref* pSender)
{
	//Director::getInstance()->end();
	level++;
	Director::getInstance()->replaceScene(CCTransitionFade::create(0.5, createScene(), Color3B(0, 127, 127)));
	
}

/*
	Program LevelEnv 关卡场景
	End
*/

#endif