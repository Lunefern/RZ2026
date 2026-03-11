// 编译环境：Visual studio 2022，EasyX_26.1.1
#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <io.h>

using namespace std;

int main() {

    int year, month;
    string station;
    char type;

    system("mkdir dx24\\A58265");
    system("mkdir dx24\\H58265");
    system("mkdir dx24\\Z58265");
    system("mkdir dx24\\P58265");
    system("mkdir dx24\\T58265");
    system("mkdir dx24\\U58265");
    system("mkdir dx24\\W58265");
    system("mkdir dx24\\R58265");

    system("tree dx24 /F > tree.txt");

    system("copy 自动气象站data\\A* dx24\\A58265");
    system("copy 自动气象站data\\H* dx24\\H58265");
    system("copy 自动气象站data\\Z* dx24\\Z58265");
    system("copy 自动气象站data\\P* dx24\\P58265");
    system("copy 自动气象站data\\T* dx24\\T58265");
    system("copy 自动气象站data\\U* dx24\\U58265");
    system("copy 自动气象站data\\W* dx24\\W58265");
    system("copy 自动气象站data\\R* dx24\\R58265");

    cout << "输入年份:";
    cin >> year;

    cout << "输入月份:";
    cin >> month;

    cout << "输入区站号:";
    cin >> station;

    cout << "输入类型(A，H，Z，P，T，U，W，R):";
    cin >> type;

    char filename[50];

    switch (type){
    case 'A':
        break;
    case 'H':
        break;
    case 'Z':
        break;
    case 'P':
        break;
    case 'T':
        sprintf(filename, "%c%s%02d.%03d", type, station.c_str(), month, year % 1000);
        break;
    case 'U':
        break;
    case 'W':
        break;
    case 'R':
        break;
    }

    cout << "查询文件: " << filename << endl;

    if (_access(filename, 0) == 0)
        cout << "文件存在" << endl;
    else
        cout << "文件不存在" << endl;

    return 0;
}