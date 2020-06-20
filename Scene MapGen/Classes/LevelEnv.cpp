#if true

/*
	Program LevelEnv �ؿ�����
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
	Audio = "RH_SRYAudio/Astrodophin.mp3"; //sry�Ļ���
	AudioSwitch = "RH_SRYAudio/EMBER_GeometryDash_(WPerShi Remix).mp3"; //sry������
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

	srand((unsigned int)time(NULL)); //��ʼ�����������

	auto title = Label::createWithTTF("Level Environment Preview", "fonts/Marker Felt.ttf", 24); //���⣬������
	if (title != nullptr)
	{
		title->setPosition(Vec2(Origin.x + VisibleSize.width / 2, Origin.y + VisibleSize.height - title->getContentSize().height));
		this->addChild(title, 1);
	}

	//				��ֱ��С
	//				|	ˮƽ��С
	//				|	|	��ڸ���
	//				|	|	|	���ڸ���
	//				|	|	|	|	�ϰ�����
	//				|	|	|	|	|	���Ӹ���
	//				|	|	|	|	|	|
	MGM::Cmap PtMap(36, 50);
	if (!PtMap.GenerateMap(1, 3, 200, 100)); //false��δ�ɹ����ɵ�ͼ
	Node* RlMap = MapInstantiate(PtMap); //����������ͼ
	RlMap->setScale(0.25);

#pragma warning(suppress:4996) //shut up
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(AudioSwitch, true);

	//û�������������棬���ǿ�����
	initWithPhysics();
	/*
	//��ȫû��������������
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	*/

	return true;
}

Node* LevelEnv::MapInstantiate(MGM::Cmap &map)
{//��ԭ�͵�ͼʵ����
	auto EnvNode = Node::create();
	EnvNode->setScale(0.25); //��ͼ���ţ�Ŀǰ�����ã���ʽʹ�ÿ�����Ŵ�
	EnvNode->setPosition(Vec2(100, VisibleSize.height - 100)); //��ʼλ��
	for (unsigned int vcot = 0; vcot <= map.GetSize().front() + 1; vcot++)
		for (unsigned int rev_hcot = 0; rev_hcot <= map.GetSize().back() + 1; rev_hcot++)
		{
			Sprite* bprite = map.BackInstantiate(vcot, map.GetSize().back() + 1 - rev_hcot);
			if (bprite != nullptr)
				EnvNode->addChild(bprite, -1);
			Sprite* aprite = map.TileInstantiate(vcot, map.GetSize().back() + 1 - rev_hcot);
			if (aprite != nullptr)
				EnvNode->addChild(aprite, 0);
			Sprite* fprite = map.ForeInstantiate(vcot, map.GetSize().back() + 1 - rev_hcot);
			if (fprite != nullptr)
				EnvNode->addChild(fprite, 2);
		}
	addChild(EnvNode);
	return EnvNode;
}

/*
	Program LevelEnv �ؿ�����
	End
*/

#endif