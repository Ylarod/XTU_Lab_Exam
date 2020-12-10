/**
 * @file Controller.h
 * @author DoraLY<770848871@qq.com>
 * @brief 控制器类头文件
 * @version 1.0
 * @date 2020-01-29
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef __CONTROLLER_H__  //标准头文件结构
#define __CONTROLLER_H__  //防止重复声明

#include "View.h"
#include "dataModel.h"
#include "main.h"

/**
 * @brief 控制器类
 *
 */
class Controller {
   private:
    dataModel db;
    View view;
    Request request;
    Response response;
    int status;
    int pageMax;
    int page;
    char* input;
    int ix;
    int iy;
    int query_click;
    float time;
    clock_t start, end;

   public:
    /**
     * @brief 构造函数
     *
     * @param model 数据模型类
     * @param view 视图类
     */
    Controller(dataModel model, View view);

    /**
     * @brief 键盘事件处理
     *
     * @param keyAnsi 按键对应的ansi值
     * @param keyCode 键代码
     */
    void keyboardEvent(char keyAnsi, int keyCode);

    /**
     * @brief 处理鼠标点击事件
     *
     * @param x 鼠标点击的x坐标
     * @param y 鼠标点击的y坐标
     */
    void mouseClickEvent(int x, int y);

    /**
     * @brief 鼠标滚轮处理
     *
     * @param num 滚动值,接近0的时候为向上滑,接近65536时为向下滑
     */
    void mouseWheeledEvent(int num);

    /**
     * @brief 加载欢迎界面
     *
     */
    void Hello();
};

#endif  // __CONTROLLER_H__