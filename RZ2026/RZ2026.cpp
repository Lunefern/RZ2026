// 编译环境：Visual studio 2022，MSVC 1940，EasyX_26.1.1
#define _CRT_SECURE_NO_WARNINGS
#include <graphics.h>
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <io.h>

using namespace std;

//读取某一分钟温度
float getTemperature(const char* filepath, int day, int hour, int minute)
{
    // ===== 参数基本检查 =====
    if (day < 1 || day > 31 || hour < 0 || hour > 23 || minute < 1 || minute > 60)
        return -999;

    FILE* fp = fopen(filepath, "rb");
    if (!fp)
        return -999;

    // ===== 计算记录号 =====
    int N = day * 24 + hour - 19;

    // 防止月初负记录号
    if (N <= 0)
    {
        fclose(fp);
        return -999;
    }

    // ===== 每条记录长度（含回车换行）=====
    const int recordSize = 248; // 246 + \r\n

    // ===== 跳过第1条头记录 =====
    long offset = recordSize + (N - 1) * recordSize;

    // 定位
    if (fseek(fp, offset, SEEK_SET) != 0)
    {
        fclose(fp);
        return -999;
    }

    // ===== 读取一条记录 =====
    char buffer[300] = { 0 };
    size_t readSize = fread(buffer, 1, 246, fp);

    if (readSize != 246)
    {
        fclose(fp);
        return -999;
    }

    // ===== 计算分钟位置 =====
    int pos = 4 + (minute - 1) * 4;

    if (pos + 4 > 246)
    {
        fclose(fp);
        return -999;
    }

    char tempStr[5] = { 0 };
    strncpy(tempStr, buffer + pos, 4);

    fclose(fp);

    // ===== 处理缺测和初始化数据 =====
    if (tempStr[0] == '/' || tempStr[0] == '-')
        return -999;

    // ===== 转换温度 =====
    float temp = (float)atof(tempStr) / 10.0;

    return temp;
}

//计算某一天平均温度
float getDayAvg(const char* filepath, int day)
{
    float sum = 0;
    int count = 0;

    for (int h = 0; h < 24; h++)
    {
        for (int m = 1; m <= 60; m++)
        {
            float t = getTemperature(filepath, day, h, m);
            if (t > -100)
            {
                sum += t;
                count++;
            }
        }
    }

    if (count == 0) return 0;
    return sum / count;
}

//画曲线
void drawCurve(float data[], int n)
{
    cleardevice();

    // ===== 坐标参数 =====
    int left = 60;     // 左边距
    int bottom = 420;  // 底部
    int right = 560;
    int top = 60;

    // ===== 画坐标轴 =====
    setlinecolor(BLACK);
    line(left, bottom, right, bottom); // X轴
    line(left, bottom, left, top);     // Y轴

    // ===== 标题 =====
    settextstyle(20, 0, _T("Consolas"));
    outtextxy(200, 20, _T("全年日平均气温变化曲线"));

    // ===== Y轴刻度（温度）=====
    for (int t = -10; t <= 40; t += 10)
    {
        int y = bottom - (t + 10) * 5;  // 映射

        line(left - 5, y, left, y);

        TCHAR str[10];
        _stprintf(str, _T("%d"), t);
        outtextxy(20, y - 10, str);
    }

    // ===== X轴刻度（天数）=====
    for (int i = 0; i <= n; i += 30)
    {
        int x = left + i * 1.3;

        line(x, bottom, x, bottom + 5);

        TCHAR str[10];
        _stprintf(str, _T("%d"), i);
        outtextxy(x - 10, bottom + 10, str);
    }

    // ===== 曲线 =====
    setlinecolor(RED);
    setlinestyle(PS_SOLID, 2); // 线型（满足题目要求）

    for (int i = 0; i < n - 1; i++)
    {
        float t1 = data[i];
        float t2 = data[i + 1];

        // 限制范围（防止飞图）
        if (t1 > 40) t1 = 40;
        if (t1 < -10) t1 = -10;
        if (t2 > 40) t2 = 40;
        if (t2 < -10) t2 = -10;

        int x1 = left + i * 1.3;
        int y1 = bottom - (t1 + 10) * 5;

        int x2 = left + (i + 1) * 1.3;
        int y2 = bottom - (t2 + 10) * 5;

        line(x1, y1, x2, y2);
    }

    // ===== 图例 =====
    settextstyle(16, 0, _T("Consolas"));
    settextcolor(RED);
    outtextxy(400, 60, _T("红线：日平均气温"));
}

//菜单绘制
void drawMenu() {
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

//文件分类
int fileSort() {
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


//文件查询
int fileSearch() {
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
            "dx24\\%c%s\\%c%s-%d%02d.txt",
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


//数据分析
int dataAnalyse()
{
    int year, month, day, hour, minute;
    string station = "58265";
    string flag;

    cout << "输入年份:";
    cin >> year;

    cout << "输入月份:";
    cin >> month;

    cout << "输入日期:";
    cin >> day;

    cout << "输入小时:";
    cin >> hour;

    cout << "输入分钟(1-60):";
    cin >> minute;

    char filepath[120];

    // 拼当前月T文件路径
    sprintf(filepath,
        "dx24\\T%s\\T%s%02d.%03d",
        station.c_str(),
        station.c_str(),
        month,
        year % 1000
    );

    // 查询某一时刻温度
    float temp = getTemperature(filepath, day, hour, minute);

    cout << "该时刻气温: " << temp << " ℃" << endl;

    cout << "是否需要绘制气温曲线图('y' for yes, 'n' for no)";
    cin >> flag;

        if (flag == "y" || flag == "Y")
        {
            // ===== 计算全年（简化：每月按30天）=====
            float yearTemp[366];
            int index = 0;

            for (int m = 1; m <= 12; m++)
            {
                sprintf(filepath,
                    "dx24\\T%s\\T%s%02d.%03d",
                    station.c_str(),
                    station.c_str(),
                    m,
                    year % 1000
                );

                if (_access(filepath, 0) != 0)
                    continue;

                for (int d = 1; d <= 30; d++)  // 简化
                {
                    yearTemp[index++] = getDayAvg(filepath, d);
                }
            }
            // ===== 画图 =====
            drawCurve(yearTemp, index);

            MessageBox(GetHWnd(),
                _T("气温曲线绘制完成"),
                _T("提示"),
                MB_OK);

            // ===== 等待鼠标点击 =====
            outtextxy(200, 450, _T("点击返回"));

            while (true)
            {
                MOUSEMSG msg = GetMouseMsg();
                if (msg.uMsg == WM_LBUTTONDOWN)
                    break;
            }
            return 1;
        }
        else
        {
            return 1;
        }

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
                drawMenu();  // 在这里恢复菜单
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
