#if false

/*
    Program MapGen ��ͼ���ɲ���
    File version alpha 0.1
    TC202006102028
    ERR=ETH (P.Q.)
*/

/*Include*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <Windows.h>

/*Basic*/
#define Vt 0
#define Hr 1
using namespace std;

/*Settings*/
const unsigned int Size_Vert = 26;     //map size on vertical ��ͼ��ֱ��С (don't set less than 16 ��ҪС��16)
const unsigned int Size_Hori = 45;     //map size on horizon ��ͼˮƽ��С (don't set less than 16 ��ҪС��16)
const unsigned int Exit_Numb = 3;      //exit generation time �������ɴ��� (may be less but 1 at least �������ɵ��������õ�������1��)

/*Global variables*/
char Gmap[Size_Vert][Size_Hori];    //gloabal map ȫ�ֵ�ͼ
int Cord[1 + Exit_Numb][2];         //coordinate index ��������
unsigned int Seed = 0;              //random seed �������

/*Functions*/
void PrintMap(bool clrs);   //print map ��ӡ��ͼ

//Main ������
int main(void)
{
    if (!Seed) Seed = (unsigned int)time(NULL);
    srand(Seed);
    //����1����ʼ�����߽�
    {
        for (int xcot = 0; xcot < Size_Vert; xcot++) for (int ycot = 0; ycot < Size_Hori; ycot++)
            if (xcot == 0 || xcot == Size_Vert - 1 || ycot == 0 || ycot == Size_Hori - 1) Gmap[xcot][ycot] = -1;
            else  Gmap[xcot][ycot] = 0;
        PrintMap(1);
        cout << "Step 1: Boarder\n";
        system("pause>nul");
    }
    //����2���������յ�
    {
        //�ڵ�ͼ�м�����������
        Cord[0][Vt] = ((rand() % 0x8001 + rand() % 0x8001) % 0x10000 - 0x8000) * (int)Size_Vert / 6 / 0x8000 + Size_Vert / 2;
        Cord[0][Hr] = ((rand() % 0x8001 + rand() % 0x8001) % 0x10000 - 0x8000) * (int)Size_Hori / 6 / 0x8000 + Size_Hori / 2;
        Gmap[Cord[0][Vt]][Cord[0][Hr]] = 1;
        //�ڵ�ͼ��Ȧ�����յ�
        for (int prts = 1; prts <= Exit_Numb; prts++)
        {
            bool VtHr = rand() >= 0x4000, PlMn = rand() >= 0x4000;
            Cord[prts][VtHr ? Vt : Hr] = ((rand() % 0x8001 + rand() % 0x8001) % 0x10000 - 0x8000) * (int)(VtHr ? Size_Vert : Size_Hori) / 8 / 0x8000 * (PlMn ? 1 : -1) + (PlMn ? (VtHr ? Size_Vert : Size_Hori) / 6 : (VtHr ? Size_Vert : Size_Hori) * 5 / 6);
            Cord[prts][VtHr ? Hr : Vt] = ((rand() % 0x8001 + rand() % 0x8001) % 0x10000 - 0x8000) * (int)(VtHr ? Size_Hori : Size_Vert) / 3 / 0x8000 + (VtHr ? Size_Hori : Size_Vert) / 2;
            Gmap[Cord[prts][Vt]][Cord[prts][Hr]] = 2;
        }
        PrintMap(1);
        cout << "Step 2: Start and End\n";
        system("pause>nul");
    }
    //����3������ϰ���δ��ɣ�
    {
        for (int prts = 1; prts <= 50; prts++)
        {
            int cord2[1][2] = {};
            re:
            cord2[0][Vt] = rand() * (Size_Vert - 2) / 0x7fff + 1;
            cord2[0][Hr] = rand() * (Size_Hori - 2) / 0x7fff + 1;
            for (int temp = 0; temp < 1 + Exit_Numb; temp++)
                if (cord2[0][Vt] == Cord[temp][Vt] && cord2[0][Hr] == Cord[temp][Hr]) goto re;
            Gmap[cord2[0][Vt]][cord2[0][Hr]] = 3;
        }


        PrintMap(1);
        cout << "Step 3: Obstacle\n";
        system("pause>nul");
    }



    return 0;
}

//print map ��ӡ��ͼ
void PrintMap(bool clrs = 0)
{
    if (clrs) system("cls");
    for (int xcot = 0; xcot < Size_Vert; xcot++)
    {
        for (int ycot = 0; ycot < Size_Hori; ycot++)
            switch (Gmap[xcot][ycot])
            {
            case -1: printf("��"); break;
            case 0: printf("��"); break;
            case 1: printf("��"); break;
            case 2: printf("��"); break;
            case 3: printf("��"); break;
            }
        printf("\n");
    }
}

/*
    Program MapGen ��ͼ���ɲ���
    End
*/

#endif