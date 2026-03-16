// 编译环境：Visual studio 2022，MSVC 1940，EasyX_26.1.1
#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <io.h>

using namespace std;

void drawMenu()
{
    setbkcolor(WHITE);
    cleardevice();

    settextstyle(30, 0, _T("Consolas"));
    settextcolor(BLACK);

    outtextxy(250, 50, _T("气象数据管理系统"));

    rectangle(200, 150, 400, 200);
    outtextxy(260, 160, _T("文件分类"));

    rectangle(200, 220, 400, 270);
    outtextxy(260, 230, _T("文件查询"));

    rectangle(200, 290, 400, 340);
    outtextxy(260, 300, _T("数据分析"));

    rectangle(200, 360, 400, 410);
    outtextxy(280, 370, _T("退出"));
}

int fileSort()
{
    system("mkdir dx24\\H58265");
    system("mkdir dx24\\Z58265");
    system("mkdir dx24\\P58265");
    system("mkdir dx24\\T58265");
    system("mkdir dx24\\U58265");
    system("mkdir dx24\\W58265");
    system("mkdir dx24\\R58265");

    system("copy 自动气象站data\\A* dx24\\A58265");
    system("copy 自动气象站data\\H* dx24\\H58265");
    system("copy 自动气象站data\\Z* dx24\\Z58265");
    system("copy 自动气象站data\\P* dx24\\P58265");
    system("copy 自动气象站data\\T* dx24\\T58265");
    system("copy 自动气象站data\\U* dx24\\U58265");
    system("copy 自动气象站data\\W* dx24\\W58265");
    system("copy 自动气象站data\\R* dx24\\R58265");

    system("tree dx24 /F > tree.txt");

    return 1;
}

int fileSearch()
{
    int year, month;
    string station;
    char type;
    char filepath[120];

    cout << "输入年份:";
    cin >> year;

    cout << "输入月份:";
    cin >> month;

    if (month < 1 || month > 12)
    {
        cout << "月份输入错误 (1-12)" << endl;
        return 0;
    }

    cout << "输入区站号:";
    cin >> station;

    cout << "输入类型(A H Z P T U W R):";
    cin >> type;

    type = toupper(type);

    switch (type)
    {
    case 'A':
        // A文件：A58265-202403
        snprintf(filepath, sizeof(filepath),
            "dx24\\%c%s\\%c%s-%d%02d",
            type,
            station.c_str(),
            type,
            station.c_str(),
            year,
            month);
        break;

    case 'H':
    case 'Z':
    case 'P':
    case 'T':
    case 'U':
    case 'W':
    case 'R':
        // 普通文件：T5826503.026
        snprintf(filepath, sizeof(filepath),
            "dx24\\%c%s\\%c%s%02d.%03d",
            type,
            station.c_str(),
            type,
            station.c_str(),
            month,
            year % 1000);
        break;

    default:
        cout << "文件类型输入错误" << endl;
        return 0;
    }

    cout << "查询路径: " << filepath << endl;

    if (_access(filepath, 0) == 0)
    {
        cout << "文件存在" << endl;
        return 1;
    }
    else
    {
        cout << "文件不存在" << endl;
        return 0;
    }
}

int dataAnalyse()
{
    MessageBox(GetHWnd(),
        _T("数据分析模块（待实现气温曲线绘图）"),
        _T("提示"),
        MB_OK);

    return 1;
}

int main()
{
    initgraph(600, 500);

    drawMenu();

    while (true)
    {
        MOUSEMSG msg = GetMouseMsg();

        if (msg.uMsg == WM_LBUTTONDOWN)
        {
            int x = msg.x;
            int y = msg.y;

            if (x > 200 && x < 400 && y>150 && y < 200)
            {
                if (fileSort())
                    MessageBox(GetHWnd(), _T("文件分类完成"), _T("提示"), MB_OK);
                else
                    MessageBox(GetHWnd(), _T("文件分类失败"), _T("错误"), MB_ICONERROR);
            }

            else if (x > 200 && x < 400 && y>220 && y < 270)
            {
                if (fileSearch())
                    MessageBox(GetHWnd(), _T("查询完成"), _T("提示"), MB_OK);
                else
                    MessageBox(GetHWnd(), _T("未找到文件"), _T("提示"), MB_OK);
            }

            else if (x > 200 && x < 400 && y>290 && y < 340)
            {
                dataAnalyse();
            }

            else if (x > 200 && x < 400 && y>360 && y < 410)
            {
                break;
            }
        }
    }

    closegraph();
    return 0;
}
