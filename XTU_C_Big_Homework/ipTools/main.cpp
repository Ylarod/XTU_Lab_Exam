/**
 * @file main.cpp
 * @author DoraLY<770848871@qq.com>
 * @brief 程序入口点
 * @version 1.1
 * @date 2020-02-04
 *
 * @copyright Copyright (c) 2020
 *
 * Updata:2020-02-04
 * Fix: 通配符bug,修改编码为UTF-8
 */
#pragma warning(disable : 4996)
#pragma warning(disable : 6031)
#include <bits/stdc++.h>

#include "Controller.h"
#include "View.h"
#include "dataModel.h"
#include "main.h"

bool isLoading = true;
void setConsoleListener(Controller controller);
DWORD WINAPI Loading(LPVOID lpParamter);

/**
 * @brief 显示进度条的子线程
 *
 * @param lpParamter
 * @return DWORD Loading
 */
DWORD WINAPI Loading(LPVOID lpParamter) {
    int T = 100;
    while (T--) {
        if (isLoading == false) {
            break;
        }
        printf("#");
        Sleep(40);
    }
    return 0L;
}

/**
 * @brief 程序入口点
 *
 * @param argc 参数个数
 * @param argv 具体参数
 * @return int
 */
int main(int argc, char* argv[]) {
    system("chcp 65001");
    //处理参数
    if (argc > 1) {
        //低内存模式打开GUI
        if(argc == 2 && strcmp(argv[1],"-lm") == 0){ 
            dataModel model(true);
            View view;
            Controller controller(model, view);
            SetConsoleTitle(TEXT("欢迎使用 ipTools by DoraLY    低内存模式"));
            model.~dataModel();
            controller.Hello();
            setConsoleListener(controller);
        }
        // Command Line Interface
        int isSave = -1;
        dataModel model;
        Request request;
        Response tmp;
        model.LoadIpData();
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-o") == 0) {
                i++;
                isSave = i;
            } else if (strcmp(argv[i], "-i") == 0) {
                i++;
                tmp.addResponse(
                    model.query(model.LoadRequestFromFile(argv[i])));
            } else {
                tmp.addResponse(model.queryOne(strToIpSet(argv[i])));
            }
        }
        if (isSave > 0) {
            tmp.saveToFile(argv[isSave]);
            printf("已保存到%s", argv[isSave]);
            return 0;
        }
        for (int i = 0; i < tmp.info.size(); i++) {
            printf("%d|  ", i);
            printf("%s", tmp.info[i].ip_start.getIpStr());
            if (tmp.info[i].ip_start.getIpInt() !=
                tmp.info[i].ip_end.getIpInt()) {
                printf("-%s  |\t", tmp.info[i].ip_end.getIpStr());
            } else {
                printf("  |\t");
            }
            printf("%s  |\t", tmp.info[i].country);
            printf("%s  |\t", tmp.info[i].area);
            printf("%s  |\t", tmp.info[i].province);
            printf("%s  |\t", tmp.info[i].city);
            printf("%s  |\t", tmp.info[i].isp);
            printf("\n");
        }
        //printf("Welcome to use!");
    } else {
        // Console Interface 正常模式
        dataModel model;
        SetConsoleTitle(TEXT("加载数据库中......"));
        HANDLE hThread = CreateThread(NULL, 0, Loading, NULL, 0, NULL);
        CloseHandle(hThread);
        clock_t a, b;
        a = clock();
        model.LoadIpData();
        b = clock();
        float lt = (float)(b - a) * 1000 / CLOCKS_PER_SEC;
        isLoading = false;
        char str[64];
        sprintf(str, "欢迎使用 ipTools by DoraLY    数据库加载耗时:%gms", lt);
        SetConsoleTitle(TEXT(str));
        View view;
        Controller controller(model, view);
        model.~dataModel();
        controller.Hello();
        setConsoleListener(controller);
    }
}

/**
 * @brief 创建控制台事件监听器
 *
 * @param controller 实例化后的Controller类
 */
void setConsoleListener(Controller controller) {  //设置控制台事件监听器
    HANDLE h = GetStdHandle(STD_INPUT_HANDLE); //获取控制台句柄
    if (h == NULL) {
        exit(1);  // 未找到控制台句柄退出
    }
    //设置控制台模式, 启用窗口,鼠标输入
    DWORD cNumRead, fdwMode, i;
    fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if (!SetConsoleMode(h, fdwMode)) fprintf(stderr, "%s\n", "SetConsoleMode");
    //获取输入
    DWORD cc;
    INPUT_RECORD irec;
    KEY_EVENT_RECORD key;
    MOUSE_EVENT_RECORD mouse;
    for (;;) {
        ReadConsoleInput(h, &irec, 1, &cc);
        //鼠标事件
        if (irec.EventType == MOUSE_EVENT) {
            mouse = (MOUSE_EVENT_RECORD&)irec.Event;
            if (mouse.dwButtonState ==
                FROM_LEFT_1ST_BUTTON_PRESSED) {  //左键单击
                controller.mouseClickEvent((int)mouse.dwMousePosition.X,
                                           (int)mouse.dwMousePosition.Y);
            }
            if (mouse.dwEventFlags == MOUSE_WHEELED) {  // 滑轮滚动
                controller.mouseWheeledEvent(
                    (int)(HIWORD(mouse.dwButtonState)));
            }
        } else if (irec.EventType == KEY_EVENT) {  //键盘事件
            key = (KEY_EVENT_RECORD&)irec.Event;
            if (key.bKeyDown) {
                controller.keyboardEvent(key.uChar.AsciiChar,
                                         (int)key.wVirtualKeyCode);
            }
        }
        // 重新设置控制台模式,防止监听失效
        h = GetStdHandle(STD_INPUT_HANDLE);
        SetConsoleMode(h, fdwMode);
    }
}