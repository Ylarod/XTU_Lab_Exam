/**
 * @file Config.h
 * @author DoraLY<770848871@qq.com>
 * @brief 配置类,声明一些配置,并提供了将配置保存到文件的功能
 * @version 1.0
 * @date 2020-01-29
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef __CONFIG_H__  //标准头文件结构
#define __CONFIG_H__  //防止重复声明

//设置选项
#define is_PrintWithoutData 1  //没有数据时是否输出
#define is_PrintCountry 2      //是否输出国家
#define is_PrintArea 3         //是否输出地区
#define is_PrintProvince 4     //是否输出省份
#define is_PrintCity 5         //是否输出城市
#define is_PrintISP 6          //是否输出ISP
#define method_Sort 7          //输出排序方式

//设置值
#define sort_by_default 0   // 按默认排序输出
#define sort_by_country 2   // 按国家排序输出
#define sort_by_area 4      //按区域排序输出
#define sort_by_province 6  //按省份排序输出
#define sort_by_city 8      //按城市排序输出
#define sort_by_isp 10      //按ISP排序输出
#define sort_by_seq 0       //顺序
#define sort_by_rev 1       //逆序

/**
 * @brief 配置类,读写程序配置
 */
class Config {
   private:
    int isPrintWithoutData;
    int isPrintCountry;
    int isPrintArea;
    int isPrintProvince;
    int isPrintCity;
    int isPrintISP;
    int methodSort;

   public:
    /**
    * @brief 构造函数,读入文件内配置
    * 
    */
    Config() {
        FILE* fp = nullptr;
        fp = fopen("config.txt", "r");
        if (fp == NULL) {
            //创建默认设置
            fp = fopen("config.txt", "w");
            fprintf(fp, "%d,%d,%d,%d,%d,%d,%d", 0, 1, 1, 1, 1, 1, 0);
            InitDefaultConfig();
        }
        fscanf(fp, "%d,%d,%d,%d,%d,%d,%d", &isPrintWithoutData, &isPrintCountry,
               &isPrintArea, &isPrintProvince, &isPrintCity, &isPrintISP,
               &methodSort);
        fclose(fp);
    }

    /**
     * @brief 析构函数,保存配置到文件
     * 
     */
    ~Config() {
        FILE* fp = nullptr;
        fp = fopen("config.txt", "w");
        fprintf(fp, "%d,%d,%d,%d,%d,%d,%d", isPrintWithoutData, isPrintCountry,
                isPrintArea, isPrintProvince, isPrintCity, isPrintISP,
                methodSort);
        fclose(fp);
    }

    /**
     * @brief 初始化默认配置
     */
    void InitDefaultConfig() {
        isPrintWithoutData = 0;
        isPrintCountry = 1;
        isPrintArea = 1;
        isPrintProvince = 1;
        isPrintISP = 1;
        methodSort = sort_by_default;
    }

    /**
     * @brief 设置配置
     * 
     * @param key 键
     * @param value 键值
     */
    void set(int key, int value) {
        switch (key) {
            case is_PrintWithoutData:
                isPrintWithoutData = value;
                break;
            case is_PrintCountry:
                isPrintCountry = value;
                break;
            case is_PrintArea:
                isPrintArea = value;
                break;
            case is_PrintProvince:
                isPrintProvince = value;
                break;
            case is_PrintCity:
                isPrintCity = value;
                break;
            case is_PrintISP:
                isPrintISP = value;
                break;
            case method_Sort:
                methodSort = value;
                break;
        }
    }

    /**
     * @brief 取配置
     * 
     * @param key 键
     * @return int 配置值
     */
    int get(int key) {
        switch (key) {
            case is_PrintWithoutData:
                return isPrintWithoutData;
                break;
            case is_PrintCountry:
                return isPrintCountry;
                break;
            case is_PrintArea:
                return isPrintArea;
                break;
            case is_PrintProvince:
                return isPrintProvince;
                break;
            case is_PrintCity:
                return isPrintCity;
                break;
            case is_PrintISP:
                return isPrintISP;
                break;
            case method_Sort:
                return methodSort;
                break;
        }
        return -1;
    }
};

#endif  // __CONFIG_H__