/**
 * @file Controller.cpp
 * @author DoraLY<770848871@qq.com>
 * @brief 控制器类
 * @version 1.0
 * @date 2020-01-29
 *
 * @copyright Copyright (c) 2020
 *
 */
#pragma warning(disable : 4996)
#include "Controller.h"

/*
Status
case 0: 欢迎界面
case 1: 查询界面
case 2: 设置界面
case 3: 关于界面
case 4: 结果界面
*/

Controller::Controller(dataModel model, View view) {
    this->db = model;
    this->view = view;

    //初始化char数组 input
    input = new char[MAX_INPUT_X];
    memset(input, 0, MAX_INPUT_X);
    ix = 0;
    iy = 0;
    status = -1;
    query_click = 0;
}

void Controller::Hello() {
    view.showHello();
    status = 0;
}

void Controller::keyboardEvent(char keyAnsi, int keyCode) {
    HANDLE hd;
    COORD pos;
    hd = GetStdHandle(STD_OUTPUT_HANDLE);  //获取标准输出的句柄
    switch (status) {
        case 0:  //欢迎界面
            switch (keyAnsi) {
                case '1':  //加载查询界面
                    view.showQuery();
                    status = 1;
                    pos.X = ix;
                    pos.Y = iy + 6;
                    SetConsoleCursorPosition(hd, pos);
                    break;
                case '2':  //加载设置界面
                    view.showSetting();
                    status = 2;
                    break;
                case '3':  //加载关于界面
                    view.showAbout();
                    status = 3;
                    break;
                case '0':
                    exit(0);
                    break;
            }
            break;
        case 1:  // 查询界面
            switch (query_click) {
                case 1:  //查询内容模式
                    if (('0' <= keyAnsi && keyAnsi <= '9') || keyAnsi == '.' ||
                        keyAnsi == '*' || keyAnsi == '-') {
                        if (ix < MAX_INPUT_X) {
                            pos.X = ix;
                            pos.Y = iy + 6;
                            SetConsoleCursorPosition(hd, pos);
                            putchar(keyAnsi);
                            input[ix] = keyAnsi;
                            ix++;
                        }
                    } else if (keyCode == 13) {  //换行符
                        switch (judgeStr(input)) {
                            case Type_Unknown:
                                // printf("\nError: Cannot recognize '%s' in
                                // input!\n",input);
                                SetConsoleTitle(TEXT(
                                    "添加失败,格式错误,"
                                    "请输入正确的ip地址或ip地址段("
                                    "通配符仅可使用于ip地址中),如192.168.1.1 , "
                                    "1.1.1.1-2.2.2.2 , 1.1.*.*"));
                                return;
                            case Type_ip:
                                request.append(strToIpSet(input));
                                break;
                            case Type_ip_set:
                                request.append(strToIpSet(input));
                                break;
                        }
                        ix = 0;
                        iy++;
                        char str[64];
                        sprintf(
                            str,
                            "欢迎使用 ipTools by DoraLY    当前需查询个数:%d个",
                            iy);
                        SetConsoleTitle(TEXT(str));
                        memset(input, 0, MAX_INPUT_X);
                    } else if (keyAnsi == 'a' || keyAnsi == 'A') {
                        start = clock();
                        SetConsoleTitle(TEXT("正在查询中....."));
                        response = db.query(request);
                        end = clock();
                        time = (float)(end - start) * 1000 / CLOCKS_PER_SEC;
                        pageMax = view.setResponse(response);
                        SetConsoleTitle(TEXT("欢迎使用 ipTools by DoraLY"));
                        view.showResponse(1, time);
                        page = 1;
                        status = 4;
                    }
                    break;
                case 2:  //查询文件模式
                    if (('A' <= keyAnsi && keyAnsi <= 'Z') ||
                        ('a' <= keyAnsi && keyAnsi <= 'z') ||
                        ('0' <= keyAnsi && keyAnsi <= '9') || keyAnsi == '.' ||
                        keyAnsi == '-') {
                        if (ix < MAX_INPUT_X) {
                            pos.X = ix;
                            pos.Y = iy + 6;
                            SetConsoleCursorPosition(hd, pos);
                            putchar(keyAnsi);
                            input[ix] = keyAnsi;
                            ix++;
                        }
                    } else if (keyCode == 13) {  //换行符
                        Request request = db.LoadRequestFromFile(input);
                        start = clock();
                        SetConsoleTitle(TEXT("正在查询中....."));
                        response = db.query(request);
                        end = clock();
                        time = (float)(end - start) * 1000 / CLOCKS_PER_SEC;
                        pageMax = view.setResponse(response);
                        SetConsoleTitle(TEXT("欢迎使用 ipTools by DoraLY"));
                        view.showResponse(1, time);
                        page = 1;
                        status = 4;
                    }
                    break;
                default:  //未点击
                    if (keyAnsi == 'a' || keyAnsi == 'A') {
                        SetConsoleTitle(
                            TEXT("欢迎使用 ipTools by DoraLY 查询内容模式"));
                        query_click = 1;
                    } else if (keyAnsi == 'b' || keyAnsi == 'B') {
                        SetConsoleTitle(
                            TEXT("欢迎使用 ipTools by DoraLY 查询文件模式"));
                        query_click = 2;
                    }
                    break;
            }
            if (keyCode == 8) {  //退格
                if (ix > 0) {
                    ix--;
                    pos.X = ix;
                    pos.Y = iy + 6;
                    SetConsoleCursorPosition(hd, pos);
                    putchar(' ');
                }
            } else if (keyCode == 37) {  //方向键左
                if (0 < ix) {
                    ix--;
                }
            } else if (keyCode == 39) {  //方向键右
                if (ix < MAX_INPUT_X) {
                    ix++;
                }
            }
            pos.X = ix;
            pos.Y = iy + 6;
            SetConsoleCursorPosition(hd, pos);
            break;
        case 2: {  // 设置界面
            if (keyAnsi == '0') {
                view.showHello();
                status = 0;
                return;
            }
            Config config;
            if (keyAnsi == '7') {
                int now;
                now = config.get(method_Sort);
                config.set(method_Sort, now == 10 ? 0 : now + 1);
            } else {
                config.set(keyAnsi - '0',
                           config.get(keyAnsi - '0') == 0 ? 1 : 0);
            }
        }
            if ('0' <= keyAnsi && keyAnsi <= '7') {
                view.showSetting();
            }
            break;
        case 3:  //关于界面
            this->Hello();
            break;
        case 4:
            if (keyCode == 38 || keyCode == 37) {
                //方向键上/左
                if (1 < page) {
                    view.showResponse(--page, time);
                }
            } else if (keyCode == 40 || keyCode == 39) {
                //方向键下/右
                if (page < pageMax) {
                    view.showResponse(++page, time);
                }
            } else if (keyAnsi == 's' || keyAnsi == 'S') {
                char tmp_filename[] = "result.csv";
                response.saveToFile(tmp_filename);
                SetConsoleTitle(TEXT("已保存到result.csv"));
            }
    }
}

void Controller::mouseClickEvent(int x, int y) {
    HANDLE hd;
    COORD pos;
    hd = GetStdHandle(STD_OUTPUT_HANDLE); /*获取标准输出的句柄*/
    switch (status) {
        case 0:             //欢迎界面
            if (y == 14) {  //查询界面
                if (46 <= x && x <= 62) {
                    // printf("click at %d,%d do 1\n", x, y);
                    view.showQuery();
                    pos.X = ix;
                    pos.Y = iy + 6;
                    SetConsoleCursorPosition(hd, pos);
                    status = 1;
                }
            } else if (y == 15) {  //设置界面
                if (46 <= x && x <= 62) {
                    // printf("click at %d,%d do 2\n", x, y);
                    view.showSetting();
                    status = 2;
                }
            } else if (y == 16) {  //关于界面
                if (46 <= x && x <= 62) {
                    // printf("click at %d,%d do 3\n", x, y);
                    view.showAbout();
                    status = 3;
                }
            } else if (y == 17) {  //退出系统
                if (46 <= x && x <= 62) {
                    // printf("click at %d,%d do 0\n", x, y);
                    exit(0);
                }
            }
            break;
        case 1:
            if (y == 2) {
                if (4 <= x && x <= 62) {  // 查询输入内容
                    if (query_click != 1) {
                        query_click = 1;
                        SetConsoleTitle(
                            TEXT("欢迎使用 ipTools by DoraLY 查询内容模式"));
                    } else {
                        start = clock();
                        SetConsoleTitle(TEXT("正在查询中....."));
                        response = db.query(request);
                        end = clock();
                        time = (float)(end - start) * 1000 / CLOCKS_PER_SEC;
                        pageMax = view.setResponse(response);
                        SetConsoleTitle(TEXT("欢迎使用 ipTools by DoraLY"));
                        view.showResponse(1, time);
                        page = 1;
                        status = 4;
                    }
                }
            }
            if (y == 3) {
                if (4 <= x && x <= 62) {  //查询输入文件
                    if (query_click != 2) {
                        query_click = 2;
                        SetConsoleTitle(
                            TEXT("欢迎使用 ipTools by DoraLY 查询文件模式"));
                    } else {
                        Request request = db.LoadRequestFromFile(input);
                        start = clock();
                        SetConsoleTitle(TEXT("正在查询中....."));
                        response = db.query(request);
                        end = clock();
                        time = (float)(end - start) * 1000 / CLOCKS_PER_SEC;
                        pageMax = view.setResponse(response);
                        SetConsoleTitle(TEXT("欢迎使用 ipTools by DoraLY"));
                        view.showResponse(1, time);
                        page = 1;
                        status = 4;
                    }
                }
            }
            break;
        case 2: {
            bool isChanged = false;
            {
                Config config;
                switch (y) {
                    case 6:
                        if (46 <= x && x <= 69) {  //无数据时是否输出
                            config.set(
                                is_PrintWithoutData,
                                config.get(is_PrintWithoutData) == 0 ? 1 : 0);
                            isChanged = true;
                        }
                        break;
                    case 7:
                        if (46 <= x && x <= 61) {  //输出国家
                            config.set(
                                is_PrintCountry,
                                config.get(is_PrintCountry) == 0 ? 1 : 0);
                            isChanged = true;
                        }
                        break;
                    case 8:
                        if (46 <= x && x <= 61) {  //输出区域
                            config.set(is_PrintArea,
                                       config.get(is_PrintArea) == 0 ? 1 : 0);
                            isChanged = true;
                        }
                        break;
                    case 9:
                        if (46 <= x && x <= 61) {  //输出省份
                            config.set(
                                is_PrintProvince,
                                config.get(is_PrintProvince) == 0 ? 1 : 0);
                            isChanged = true;
                        }
                        break;
                    case 10:
                        if (46 <= x && x <= 61) {  //输出城市
                            config.set(is_PrintCity,
                                       config.get(is_PrintCity) == 0 ? 1 : 0);
                            isChanged = true;
                        }
                        break;
                    case 11:
                        if (46 <= x && x <= 61) {  //输出ISP
                            config.set(is_PrintISP,
                                       config.get(is_PrintISP) == 0 ? 1 : 0);
                            isChanged = true;
                        }
                        break;
                    case 12:
                        if (46 <= x && x <= 68) {  //输出方式
                            int now;
                            now = config.get(method_Sort);
                            config.set(method_Sort, now == 10 ? 0 : now + 1);
                            isChanged = true;
                        }
                        break;
                    case 13:
                        if (46 <= x && x <= 57) {  //返回主界面
                            view.showHello();
                            status = 0;
                        }
                        break;
                }
            }
            if (isChanged) {
                view.showSetting();
            }
        } break;
        case 3:
            this->Hello();
            break;
    }
}

void Controller::mouseWheeledEvent(int num) {  //处理滚轮滑动事件
    if (status == 4) {                         //结果界面
        if (num < 32768) {
            //向上滑
            if (1 < page) {
                view.showResponse(--page, time);
            }
        } else {
            //向下滑
            if (page < pageMax) {
                view.showResponse(++page, time);
            }
        }
    }
}
