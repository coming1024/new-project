#if true

/*
	Program LevelEnv �ؿ�����
	File version alpha 0.2
	TC202006191617
	ERR=ETH (P.Q.)
*/

#include "LevelEnv.h"
#include "SimpleAudioEngine.h"
#include "MapGenMerge.h"

USING_NS_CC;

LevelEnv::LevelEnv()
{
	VisibleSize = Director::getInstance()->getVisibleSize();
	Origin = Director::getInstance()->getVisibleOrigin();
	Audio = "RH_SRYAudio/Astrodophin.mp3"; //sry�Ļ���
	AudioSwitch = "RH_SRYAudio/EMBER_GeometryDash_(WPerShi Remix).mp3";
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

	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(Audio, true);

	srand((unsigned int)time(NULL)); //��ʼ�����������

	auto title = Label::createWithTTF("Level Environment Preview", "fonts/Marker Felt.ttf", 24); //���⣬������
	if (title != nullptr)
	{
		title->setPosition(Vec2(Origin.x + VisibleSize.width / 2, Origin.y + VisibleSize.height - title->getContentSize().height));
		this->addChild(title, 1);
	}

#if true //�ɵĵ�ͼ����
	unsigned int Size_Vert = 36;
	unsigned int Size_Hori = 50;
	MGM::Gmap PtMap(Size_Vert, Size_Hori);
	for (unsigned int num = 1, maxatt = 100; num && maxatt; maxatt--)
		if (PtMap.GenerateTile(MGM::Gmap::tile::start, 1, 0.4)) num--; //����������ڣ��ɹ������-1��maxattΪ���ѭ������
	for (unsigned int num = 3, maxatt = 100; num && maxatt; maxatt--)
		if (PtMap.GenerateTile(MGM::Gmap::tile::end, 2, 0.8)) num--; //�������ɳ��ڣ��ɹ������-1��maxattΪ���ѭ������
	for (unsigned int num = 200, maxatt = 1000; num && maxatt; maxatt--)
		if (PtMap.GenerateTile(MGM::Gmap::tile::obstacle, 0)) num--; //���������ϰ����ɹ������-1��maxattΪ���ѭ������
	for (unsigned int num = 100, maxatt = 1000; num && maxatt; maxatt--)
		if (PtMap.GenerateTile(MGM::Gmap::tile::box, 0)) num--; //�������ɺ��ӣ��ɹ������-1��maxattΪ���ѭ������
#else //�µĵ�ͼ���ɣ���Ҫ����дGmap�ĸ��ƹ��캯��������
	const unsigned int Size_Vert = 36; //��ֱ��С
	const unsigned int Size_Hori = 50; //ˮƽ��С
	const unsigned int Cont_Star = 1;  //��ڸ���
	const unsigned int Cont_Exit = 3;  //���ڸ���
	const unsigned int Cont_Obst = 200;//�ϰ�����
	const unsigned int Cont_Boxx = 100;//���Ӹ���
	MGM::Gmap PtMap = GenerateMap(Size_Vert, Size_Hori, Cont_Star, Cont_Exit, Cont_Obst, Cont_Boxx);
#endif

	auto EnvNode = Node::create();
	EnvNode->setPosition(Vec2(100, VisibleSize.height - 100));

	for (unsigned int vcot = 0; vcot <= Size_Vert + 1; vcot++)
		for (unsigned int rev_hcot = 0; rev_hcot <= Size_Hori + 1; rev_hcot++)
			TileInstantiate(PtMap, EnvNode, vcot, Size_Hori + 1 - rev_hcot);

	addChild(EnvNode);

	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(AudioSwitch, true);

	return true;
}

void LevelEnv::TileInstantiate(MGM::Gmap &map, Node* mnode, unsigned int cvt, unsigned int chr)
{//��ԭ�͵�ͼ�ϵķ���ʵ��������Ϊmnode���ڵ�Ķ��ӣ�������child
	Sprite* tile = Sprite::create();//���Ǽ���physicsBody
	tile->setAnchorPoint(Vec2(0, 0));
	tile->setPosition(Vec2(chr * 16, -(int)cvt * 16));
	char texture[256] = { 0 };
	switch (map.GetTile(cvt, chr))
	{
	case MGM::Gmap::tile::border:
		sprintf(texture, "RH_Environment/Blue/border_%d.png", rand() % 3);
		tile->setTexture(texture);
		break;
	case MGM::Gmap::tile::empty:
		sprintf(texture, "RH_Environment/Blue/empty_%d.png", rand() % 9);
		tile->setTexture(texture);
		break;
	case MGM::Gmap::tile::start:
		sprintf(texture, "RH_Environment/Blue/start.png");
		tile->setTexture(texture);
		break;
	case MGM::Gmap::tile::end:
		sprintf(texture, "RH_Environment/Blue/end.png");
		tile->setTexture(texture);
		break;
	case MGM::Gmap::tile::obstacle:
		sprintf(texture, "RH_Environment/Blue/obstacle_%d.png", rand() % 2);
		tile->setTexture(texture);
		break;
	case MGM::Gmap::tile::box:
		sprintf(texture, "RH_Environment/Blue/box_%d.png", rand() % 1);
		tile->setTexture(texture);
		break;
	default:
		break;
	}
	mnode->addChild(tile);
}

MGM::Gmap LevelEnv::GenerateMap(unsigned int svt, unsigned int shr, unsigned int cst, unsigned int ced, unsigned int cob, unsigned int cbx)
{//��װ�ĵ�ͼ���ɺ�����svt*shr��С�����cst��������ced�����ϰ�cob��������cbx��
	const unsigned int Star_Attp = 100;
	const unsigned int Exit_Attp = 100;
	const unsigned int Obst_Attp = 1000;
	const unsigned int Boxx_Attp = 1000;
	const double Star_Rang = 0.4;
	const double Exit_Rang = 0.8;
	MGM::Gmap tmap(svt, shr);
	for (unsigned int num = cst, maxatt = Star_Attp; num && maxatt; maxatt--)
		if (tmap.GenerateTile(MGM::Gmap::tile::start, 1, Star_Rang)) num--;
	for (unsigned int num = ced, maxatt = Exit_Attp; num && maxatt; maxatt--)
		if (tmap.GenerateTile(MGM::Gmap::tile::end, 2, Exit_Rang)) num--;
	for (unsigned int num = cob, maxatt = Obst_Attp; num && maxatt; maxatt--)
		if (tmap.GenerateTile(MGM::Gmap::tile::obstacle, 0)) num--;
	for (unsigned int num = cbx, maxatt = Boxx_Attp; num && maxatt; maxatt--)
		if (tmap.GenerateTile(MGM::Gmap::tile::box, 0)) num--;
	return tmap;
}

/*
	Program LevelEnv �ؿ�����
	End
*/

#endif