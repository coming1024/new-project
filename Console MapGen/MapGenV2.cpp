#if true

/*
    Program MapGen ��ͼ���ɲ���
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
//compare 2 elem UInt vector | �Ƚ�2Ԫ���޷�������vector
bool RH::CompVec2UInt(vector<unsigned int> fw, vector<unsigned int> bk)
//Used to sort coordinates
//������������
{
    if (fw.front() > bk.front()) return false;
    else if (fw.front() == bk.front())
    {
        if (fw.back() >= bk.back()) return false;
        else return true;
    }
    else return true;
}

//constructor | ���캯��
Gmap::Gmap(unsigned int svt, unsigned int shr)
//Specify the map vertical size 'svt' and horizontal size 'shr', generate empty map
//��ȷָ����ͼ��ֱ��С'svt'��ˮƽ��С'shr'�����ɿհ׵�ͼ
{
    Size_Vert = svt;
    Size_Hori = shr;
    Smap = new tile[(Size_Vert + 2) * (Size_Hori + 2)];
    GenInit();
}

//destructor | ��������
Gmap::~Gmap()
{
    delete[] Smap;
}

//get tile | ��ȡ����
Gmap::tile Gmap::GetTile(unsigned int cvt, unsigned int chr)
//Return tile at 'cvt,chr'(vertical,horizontal), return 'tile::error' if exceeds limit
//��������Ϊ'cvt,chr'(��ֱ,ˮƽ)�ķ��飬�����߽緵��'tile::error'
{
    if (cvt >= 0 && cvt <= Size_Vert + 1 && chr >= 0 && chr <= Size_Hori + 1) return Smap[cvt * (Size_Hori + 2) + chr];
    else return tile::error;
}

//set tile | ���÷���
Gmap::tile Gmap::SetTile(unsigned int cvt, unsigned int chr, Gmap::tile tl)
//Set tile at 'cvt,chr'(vertical,horizontal) into 'tl', return 'tile::error' if exceeds limit
//������Ϊ'cvt,chr'(��ֱ,ˮƽ)�ķ�������Ϊ'tl'�����أ������߽緵��'tile::error'
{
    if (cvt >= 0 && cvt <= Size_Vert + 1 && chr >= 0 && chr <= Size_Hori + 1)
    {
        Smap[cvt * (Size_Hori + 2) + chr] = tl;
        return Smap[cvt * (Size_Hori + 2) + chr];
    }
    else return tile::error;
}

//random coordinate | �������
vector<unsigned int> Gmap::RandCoord(unsigned int rvt, unsigned int rhr, int mode)
//Get random coordinate in vertical range 'rvt' and horizontal range 'rhr', normal distribution; 'mode' 0 = center, 1 = corner distribution
//�����ȡ��ֱ��Χ'rvt'��ˮƽ��Χ'rhr'�е�һ�����꣬��̬�ֲ���'mode' 0=����ɢ����1=����ɢ��
{
    if (rvt > Size_Vert) rvt = Size_Vert;
    if (rhr > Size_Hori) rhr = Size_Hori;
    vector<unsigned int> cord;
    double ovt, ohr;
    do ovt = GaussRand() * (double)rvt / 4;
    while (abs(ovt) > (double)rvt / 2); //�������߽�
    do ohr = GaussRand() * (double)rhr / 4;
    while (abs(ohr) > (double)rhr / 2); //�������߽�
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

//random coordinate | �������
vector<unsigned int> Gmap::RandCoord(void)
//Get random coordinate in the map
//�ڵ�ͼ�������ȡһ������
{
    vector<unsigned int> cord;
    cord.push_back((unsigned int)((double)Size_Vert * (double)rand() / (double)(RAND_MAX + 1) + 1));
    cord.push_back((unsigned int)((double)Size_Hori * (double)rand() / (double)(RAND_MAX + 1) + 1));
    return cord;
}

//generate map, initialize | ���ɵ�ͼ����ʼ��
void Gmap::GenInit(void)
//Clear map, place borders
//��յ�ͼ�����ñ߽�
{
    for (unsigned int vcot = 0; vcot <= Size_Vert + 1; vcot++)
        for (unsigned int hcot = 0; hcot <= Size_Hori + 1; hcot++)
            if (vcot == 0 || vcot == Size_Vert + 1 || hcot == 0 || hcot == Size_Hori + 1) SetTile(vcot, hcot, tile::border);
            else SetTile(vcot, hcot, tile::empty);
    Cord_Star.clear();
    Cord_Exit.clear();
    Cord_Obst.clear();
}

//generate map, entrance | ���ɵ�ͼ�����
void Gmap::GenStar(unsigned int num, double range, int maxatt = 100)
//Generate 'num' entrances in the range of 'range'(0~1), try 'maxatt' times at most, default 100 times
//��'range'(0~1)��Χ������'num'��������ڣ���ೢ��'maxatt'�Σ�Ĭ��100��
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

//generate map, exit | ���ɵ�ͼ������
void Gmap::GenExit(unsigned int num, double range, int maxatt = 100)
//Generate 'num' exits in the range of 'range'(0~1), try 'maxatt' times at most, default 100 times
//��'range'(0~1)��Χ������'num'�����ĳ��ڣ���ೢ��'maxatt'�Σ�Ĭ��100��
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

//generate map, obstacle | ���ɵ�ͼ���ϰ�
void Gmap::GenObst(unsigned int num, int maxatt = 10000)
//Generate 'num' obstacles, try 'maxatt' times at most, default 10000 times
//����'num'�������ϰ�����ೢ��'maxatt'�Σ�Ĭ��10000��
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

//print map | ��ӡ��ͼ
void Gmap::PrintMap(std::ostream& os = std::cout)
//Print map to 'os' stream, default to 'std::cout'
//��ӡ��ͼ��'os'����Ԥ��Ϊ'std::cout'
{
    for (unsigned int vcot = 0; vcot <= Size_Vert + 1; vcot++)
    {
        for (unsigned int hcot = 0; hcot <= Size_Hori + 1; hcot++)
            switch (GetTile(vcot, hcot))
            {
            case tile::border: os << "��"; break;
            case tile::empty: os << "��"; break;
            case tile::start: os << "��"; break;
            case tile::end: os << "��"; break;
            case tile::obstacle: os << "��"; break;
            default: os << "��"; break;
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
    //��ʼ�����������
    //����ÿ�����ɵĵ�ͼ������һ����

    Gmap a(25, 40);
    //���촹ֱ��25��ˮƽ��40��ĵ�ͼ����ʼ������ղ����ñ߽磩
    //��ͼʵ�ʴ�СΪ��ֱ25+2��ˮƽ40+2���߽�2�񲻼����ͼ��С
    { a.PrintMap(); system("pause>nul&cls"); }

    a.GenStar(10, 0.4);
    //�ڵ�ͼ����0.4��Χ���������1����ڣ�Խ�������뼸��Խ��
    //�˺���֧���ٴε��ã����ԭ�ȵ����������·���
    //���Ḳ���Ѿ����õ���ڣ����ڣ��ϰ�
    //���numֵ���õ�̫�߿��ܲ���ɹ������㹻�����������ԸĴ�maxatt
    { a.PrintMap(); system("pause>nul&cls"); }

    a.GenExit(3, 0.8);
    //�ڵ�ͼ�Ľ�0.8��Χ���������3����ڣ�Խ�����ĽǼ���Խ��
    //����������GenStar��ͬ
    { a.PrintMap(); system("pause>nul&cls"); }

    a.GenObst(100);
    //��������ͼ����������ϰ�������������ͬ
    //����������GenStar��ͬ
    { a.PrintMap(); system("pause>nul&cls"); }

    a.GenInit();
    //��յ�ͼ��
    { a.PrintMap(); system("pause>nul&cls"); }

    return 0;
}

/*
    Program MapGen ��ͼ���ɲ���
    End
*/

#endif