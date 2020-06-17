#if true

/*
    Program MapGen 地图生成测试
    File version alpha 0.2
    TC202006171031
    ERR=ETH (P.Q.)
*/

/*
    Include
*/
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <algorithm>
#include "GaussRand.h"

/*
    Declaration
*/
using std::vector;
namespace RH
{
    bool CompVec2UInt(vector<unsigned int> fw, vector<unsigned int> bk);
    class Gmap
    {
    private:
        unsigned int Size_Vert;
        unsigned int Size_Hori;
        enum class tile
        {
            error = -2,
            border = -1,
            empty = 0,
            start = 1,
            end = 2,
            obstacle = 3
        };
        tile* Smap;
        vector<vector<unsigned int>> Cord_Star;
        vector<vector<unsigned int>> Cord_Exit;
        vector<vector<unsigned int>> Cord_Obst;
        vector<unsigned int> RandCoord(unsigned int rvt, unsigned int rhr, int mode);
        vector<unsigned int> RandCoord(void);
    public:
        Gmap(unsigned int svt, unsigned int shr);
        ~Gmap();
        tile GetTile(unsigned int cvt, unsigned int chr);
        tile SetTile(unsigned int cvt, unsigned int chr, tile tl);
        void GenInit(void);
        void GenStar(unsigned int num, double range, int maxatt);
        void GenExit(unsigned int num, double range, int maxatt);
        void GenObst(unsigned int num, int maxatt);
        void PrintMap(std::ostream& os);
    };
}
using namespace RH;

/*
    Definition
*/
//compare 2 elem UInt vector | 比较2元素无符号整型vector
bool RH::CompVec2UInt(vector<unsigned int> fw, vector<unsigned int> bk)
//Used to sort coordinates
//用于排序坐标
{
    if (fw.front() > bk.front()) return false;
    else if (fw.front() == bk.front())
    {
        if (fw.back() >= bk.back()) return false;
        else return true;
    }
    else return true;
}

//constructor | 构造函数
Gmap::Gmap(unsigned int svt, unsigned int shr)
//Specify the map vertical size 'svt' and horizontal size 'shr', generate empty map
//明确指定地图垂直大小'svt'与水平大小'shr'，生成空白地图
{
    Size_Vert = svt;
    Size_Hori = shr;
    Smap = new tile[(Size_Vert + 2) * (Size_Hori + 2)];
    GenInit();
}

//destructor | 析构函数
Gmap::~Gmap()
{
    delete[] Smap;
}

//get tile | 读取方块
Gmap::tile Gmap::GetTile(unsigned int cvt, unsigned int chr)
//Return tile at 'cvt,chr'(vertical,horizontal), return 'tile::error' if exceeds limit
//返回坐标为'cvt,chr'(垂直,水平)的方块，超出边界返回'tile::error'
{
    if (cvt >= 0 && cvt <= Size_Vert + 1 && chr >= 0 && chr <= Size_Hori + 1) return Smap[cvt * (Size_Hori + 2) + chr];
    else return tile::error;
}

//set tile | 设置方块
Gmap::tile Gmap::SetTile(unsigned int cvt, unsigned int chr, Gmap::tile tl)
//Set tile at 'cvt,chr'(vertical,horizontal) into 'tl', return 'tile::error' if exceeds limit
//将坐标为'cvt,chr'(垂直,水平)的方块设置为'tl'并返回，超出边界返回'tile::error'
{
    if (cvt >= 0 && cvt <= Size_Vert + 1 && chr >= 0 && chr <= Size_Hori + 1)
    {
        Smap[cvt * (Size_Hori + 2) + chr] = tl;
        return Smap[cvt * (Size_Hori + 2) + chr];
    }
    else return tile::error;
}

//random coordinate | 随机坐标
vector<unsigned int> Gmap::RandCoord(unsigned int rvt, unsigned int rhr, int mode)
//Get random coordinate in vertical range 'rvt' and horizontal range 'rhr', normal distribution; 'mode' 0 = center, 1 = corner distribution
//随机获取垂直范围'rvt'与水平范围'rhr'中的一个坐标，正态分布；'mode' 0=中心散布，1=角落散布
{
    if (rvt > Size_Vert) rvt = Size_Vert;
    if (rhr > Size_Hori) rhr = Size_Hori;
    vector<unsigned int> cord;
    double ovt, ohr;
    do ovt = GaussRand() * (double)rvt / 4;
    while (abs(ovt) > (double)rvt / 2); //防超出边界
    do ohr = GaussRand() * (double)rhr / 4;
    while (abs(ohr) > (double)rhr / 2); //防超出边界
    switch (mode)
    {
    case 0:
        if (ovt >= 0) cord.push_back((unsigned int)floor(((double)Size_Vert + 1) / 2 + ovt));
        else cord.push_back((unsigned int)ceil(((double)Size_Vert + 1) / 2 + ovt));
        if (ohr >= 0) cord.push_back((unsigned int)floor(((double)Size_Hori + 1) / 2 + ohr));
        else cord.push_back((unsigned int)ceil(((double)Size_Hori + 1) / 2 + ohr));
        break;
    case 1:
        if (ovt >= 0) cord.push_back((unsigned int)floor(1.0 + ovt));
        else cord.push_back((unsigned int)ceil((double)Size_Vert + ovt));
        if (ohr >= 0) cord.push_back((unsigned int)floor(1.0 + ohr));
        else cord.push_back((unsigned int)ceil((double)Size_Hori + ohr));
        break;
    default:
        cord.push_back(0);
        cord.push_back(0);
        break;
    }
    return cord;
}

//random coordinate | 随机坐标
vector<unsigned int> Gmap::RandCoord(void)
//Get random coordinate in the map
//在地图中随机获取一个坐标
{
    vector<unsigned int> cord;
    cord.push_back((unsigned int)((double)Size_Vert * (double)rand() / (double)(RAND_MAX + 1) + 1));
    cord.push_back((unsigned int)((double)Size_Hori * (double)rand() / (double)(RAND_MAX + 1) + 1));
    return cord;
}

//generate map, initialize | 生成地图，初始化
void Gmap::GenInit(void)
//Clear map, place borders
//清空地图，放置边界
{
    for (unsigned int vcot = 0; vcot <= Size_Vert + 1; vcot++)
        for (unsigned int hcot = 0; hcot <= Size_Hori + 1; hcot++)
            if (vcot == 0 || vcot == Size_Vert + 1 || hcot == 0 || hcot == Size_Hori + 1) SetTile(vcot, hcot, tile::border);
            else SetTile(vcot, hcot, tile::empty);
    Cord_Star.clear();
    Cord_Exit.clear();
    Cord_Obst.clear();
}

//generate map, entrance | 生成地图，入口
void Gmap::GenStar(unsigned int num, double range, int maxatt = 100)
//Generate 'num' entrances in the range of 'range'(0~1), try 'maxatt' times at most, default 100 times
//在'range'(0~1)范围内生成'num'个数的入口，最多尝试'maxatt'次，默认100次
{
    for (unsigned int ccot = 0; ccot < Cord_Star.size(); ccot++) SetTile(Cord_Star[ccot][0], Cord_Star[ccot][1], tile::empty);
    Cord_Star.clear();
    while (maxatt-- && Cord_Star.size() < num)
    {
        vector<unsigned int> cord = RandCoord((unsigned int)(range * Size_Vert), (unsigned int)(range * Size_Hori), 0);
        bool valid = true;
        for (unsigned int ccot = 0; ccot < Cord_Star.size() && valid; ccot++)
            if (cord == Cord_Star[ccot]) valid = false;
        for (unsigned int ccot = 0; ccot < Cord_Exit.size() && valid; ccot++)
            if (cord == Cord_Exit[ccot]) valid = false;
        for (unsigned int ccot = 0; ccot < Cord_Obst.size() && valid; ccot++)
            if (cord == Cord_Obst[ccot]) valid = false;
        if (valid)
        {
            Cord_Star.push_back(cord);
            SetTile(cord[0], cord[1], tile::start);
        }
    }
    sort(Cord_Star.begin(), Cord_Star.end(), CompVec2UInt);
}

//generate map, exit | 生成地图，出口
void Gmap::GenExit(unsigned int num, double range, int maxatt = 100)
//Generate 'num' exits in the range of 'range'(0~1), try 'maxatt' times at most, default 100 times
//在'range'(0~1)范围内生成'num'个数的出口，最多尝试'maxatt'次，默认100次
{
    for (unsigned int ccot = 0; ccot < Cord_Exit.size(); ccot++) SetTile(Cord_Exit[ccot][0], Cord_Exit[ccot][1], tile::empty);
    Cord_Exit.clear();
    while (maxatt-- && Cord_Exit.size() < num)
    {
        vector<unsigned int> cord = RandCoord((unsigned int)(range * Size_Vert), (unsigned int)(range * Size_Hori), 1);
        bool valid = true;
        for (unsigned int ccot = 0; ccot < Cord_Star.size() && valid; ccot++)
            if (cord == Cord_Star[ccot]) valid = false;
        for (unsigned int ccot = 0; ccot < Cord_Exit.size() && valid; ccot++)
            if (cord == Cord_Exit[ccot]) valid = false;
        for (unsigned int ccot = 0; ccot < Cord_Obst.size() && valid; ccot++)
            if (cord == Cord_Obst[ccot]) valid = false;
        if (valid)
        {
            Cord_Exit.push_back(cord);
            SetTile(cord[0], cord[1], tile::end);
        }
    }
    sort(Cord_Exit.begin(), Cord_Exit.end(), CompVec2UInt);
}

//generate map, obstacle | 生成地图，障碍
void Gmap::GenObst(unsigned int num, int maxatt = 10000)
//Generate 'num' obstacles, try 'maxatt' times at most, default 10000 times
//生成'num'个数的障碍，最多尝试'maxatt'次，默认10000次
{
    for (unsigned int ccot = 0; ccot < Cord_Obst.size(); ccot++) SetTile(Cord_Obst[ccot][0], Cord_Obst[ccot][1], tile::empty);
    Cord_Obst.clear();
    while (maxatt-- && Cord_Obst.size() < num)
    {
        vector<unsigned int> cord = RandCoord();
        bool valid = true;
        for (unsigned int ccot = 0; ccot < Cord_Star.size() && valid; ccot++)
            if (cord == Cord_Star[ccot]) valid = false;
        for (unsigned int ccot = 0; ccot < Cord_Exit.size() && valid; ccot++)
            if (cord == Cord_Exit[ccot]) valid = false;
        for (unsigned int ccot = 0; ccot < Cord_Obst.size() && valid; ccot++)
            if (cord == Cord_Obst[ccot]) valid = false;
        if (valid)
        {
            Cord_Obst.push_back(cord);
            SetTile(cord[0], cord[1], tile::obstacle);
        }
    }
    sort(Cord_Obst.begin(), Cord_Obst.end(), CompVec2UInt);
}

//print map | 打印地图
void Gmap::PrintMap(std::ostream& os = std::cout)
//Print map to 'os' stream, default to 'std::cout'
//打印地图到'os'流，预设为'std::cout'
{
    for (unsigned int vcot = 0; vcot <= Size_Vert + 1; vcot++)
    {
        for (unsigned int hcot = 0; hcot <= Size_Hori + 1; hcot++)
            switch (GetTile(vcot, hcot))
            {
            case tile::border: os << "＃"; break;
            case tile::empty: os << "　"; break;
            case tile::start: os << "Ｓ"; break;
            case tile::end: os << "Ｅ"; break;
            case tile::obstacle: os << "ｏ"; break;
            default: os << "＄"; break;
            }
        os << std::endl;
    }
}

/*
    main function
*/
int main(void)
{
    srand((unsigned int)time(NULL));
    //初始化随机数种子
    //否则每次生成的地图都会是一样的

    Gmap a(25, 40);
    //构造垂直高25格，水平宽40格的地图，初始化（清空并放置边界）
    //地图实际大小为垂直25+2，水平40+2，边界2格不计入地图大小
    { a.PrintMap(); system("pause>nul&cls"); }

    a.GenStar(10, 0.4);
    //在地图中央0.4范围内随机放置1个入口，越靠近中央几率越大
    //此函数支持再次调用，会把原先的入口清除重新放置
    //不会覆盖已经放置的入口，出口，障碍
    //如果num值设置的太高可能不会成功放置足够的数量，可以改大maxatt
    { a.PrintMap(); system("pause>nul&cls"); }

    a.GenExit(3, 0.8);
    //在地图四角0.8范围内随机放置3个入口，越靠近四角几率越大
    //其他特性与GenStar相同
    { a.PrintMap(); system("pause>nul&cls"); }

    a.GenObst(100);
    //在整个地图上随机放置障碍，各处几率相同
    //其他特性与GenStar相同
    { a.PrintMap(); system("pause>nul&cls"); }

    a.GenInit();
    //清空地图用
    { a.PrintMap(); system("pause>nul&cls"); }

    return 0;
}

/*
    Program MapGen 地图生成测试
    End
*/

#endif