/**
 * @file View.h
 * @author DoraLY<770848871@qq.com>
 * @brief 视图类
 * @version 1.0
 * @date 2020-01-29
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef __VIEW_H__  //标准头文件结构
#define __VIEW_H__  //防止重复声明

#include "dataModel.h"
#include "ipModel.h"
#include "main.h"

/**
 * @brief 视图类
 * 
 */
class View {
   private:
    Response response;
    int pageMax;

   public:
    /**
     * @brief 显示欢迎界面
     *
     */
    void showHello();
    /**
     * @brief 显示设置界面
     *
     */
    void showSetting();
    /**
     * @brief 显示查询界面
     *
     */
    void showQuery();

    /**
     * @brief 设置查询结果
     *
     * @param response 查询结果
     * @return int 一共有多少页
     */
    int setResponse(Response response);

    /**
     * @brief 显示查询结果
     *
     * @param page 第几页,1开始
     * @param time 查询耗时
     */
    void showResponse(int page, float time);

    /**
     * @brief 展示关于界面
     *
     */
    void showAbout();
};

#endif  // __VIEW_H__