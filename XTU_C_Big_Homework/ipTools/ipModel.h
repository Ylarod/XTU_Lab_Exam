/**
 * @file ipModel.h
 * @author DoraLY<770848871@qq.com>
 * @brief ip模型类
 * @version 1.1
 * @date 2020-02-04
 *
 * @copyright Copyright (c) 2020
 *
 * Updata:2020-02-04
 * Fix: 通配符bug
 */
#ifndef __IP_MODEL_H__  //标准头文件结构
#define __IP_MODEL_H__  //防止重复声明

//起始地址|结束地址|国家|区域|省份|城市|ISP
#define MAX_COUNTRY 16
//限定国家名最长为16位(保证中文英文都可以完全输入)
#define MAX_AREA 8
//限定国家名最长为8位(保证中文英文都可以完全输入)
#define MAX_PROVINCE 32
//限定省份名最长为32位(保证中文英文都可以完全输入)
#define MAX_CITY 32
//限定城市名最长为32位(保证中文英文都可以完全输入)
#define MAX_ISP 40
//限定ISP名最长为40位(保证中文英文都可以完全输入)

// judgeStr函数返回值定义
#define Type_Unknown 0  //未知类型
#define Type_ip 1       // ip类型
#define Type_ip_set 2   // ip_set类型

#include <cstdio>
#include <cstdlib>
#include <cstring>

// 定义 ip 类
class ip {
   public:
    union {
        unsigned char seg[4];  // IP地址共4字节，或者看成无符号字符数组所指4部分
        unsigned int address;  //或者看成一个整体
    };

   public:
    /**
     * @brief 构造函数,从4个整数
     * 
     * @param s0 第一个
     * @param s1 第二个
     * @param s2 第三个
     * @param s3 第四个
     */
    ip(int s0 = 0, int s1 = 0, int s2 = 0, int s3 = 0);

    /**
     * @brief 构造函数,从字符串
     * 
     * @param str ip字符串
     */
    ip(char str[]);

    /**
     * @brief 拷贝构造函数
     * 
     * @param obj 
     */
    ip(const ip& obj);                       //拷贝构造函数

    /**
     * @brief 取ip字符串
     * 
     * @return char* ip字符串
     */
    char* getIpStr();

    /**
     * @brief 取ip地址对应整数
     * 
     * @return int ip整数
     */
    int getIpInt();                              //取ip地址(数字形式)

    /**
     * @brief 置ip,类似构造函数
     * 
     * @param s0 
     * @param s1 
     * @param s2 
     * @param s3 
     */
    void setIp(int s0, int s1, int s2, int s3);

    /**
     * @brief 置ip,类似构造函数
     * 
     * @param str 
     */
    void setIp(char str[]);

    /**
     * @brief 置ip,类似构造函数
     * 
     * @param ipa 
     */
    void setIp(ip ipa);

    /**
     * @brief 重载 == 操作符
     * 
     * @param next 
     * @return true 
     * @return false 
     */
    bool operator==(const ip& next) {
        if (address == next.address) {
            return true;
        }
        return false;
    }

    /**
     * @brief 重载 > 操作符
     * 
     * @param next 
     * @return true 
     * @return false 
     */
    bool operator>(const ip& next) {
        if (address > next.address) {
            return true;
        }
        return false;
    }

    /**
     * @brief 重载 < 操作符
     * 
     * @param next 
     * @return true 
     * @return false 
     */
    bool operator<(const ip& next) {
        if (address < next.address) {
            return true;
        }
        return false;
    }

    /**
     * @brief 重载 ++ 操作符
     * 
     * @return ip 
     */
    ip operator++() {
        address++;
        return *this;
    }

    /**
     * @brief 重载 -- 操作符
     * 
     * @return ip 
     */
    ip operator--() {
        address++;
        return *this;
    }
};


/**
 * @brief 定义 结构体 ip_set 表示ip段
 * 
 */
class ip_set{
    public:
    ip ip_start;  //起始地址
    ip ip_end;    //结束地址

    /**
     * @brief 判断该出是否为*
     * 
     * @param pos 位置
     * @return true 
     * @return false 
     */
    bool isStar(int pos);

    /**
     * @brief 取*个数
     * 
     * @return int 
     */
    int starCount();

    /**
     * @brief 判断是否为特殊类型
     * 
     * @return int 
     */
    int isSpecial();
};


/**
 * @brief 定义 类 ipInfo 存储从数据文件导入的数据
 * 
 */
class ipInfo {
   public:
    ip ip_start;                  //起始地址
    ip ip_end;                    //结束地址
    char country[MAX_COUNTRY];    //国家
    char area[MAX_AREA];          //区域
    char province[MAX_PROVINCE];  //省份
    char city[MAX_CITY];          //城市
    char isp[MAX_ISP];            // ISP
};

//声明ip相关函数
/**
 * @brief 判断ip是否在某ip段内
 * 
 * @param a_ip 待判断的ip
 * @param ip_start 左端点
 * @param ip_end 右端点
 * @return true 
 * @return false 
 */
bool isBelong(ip a_ip, ip ip_start, ip ip_end);

/**
 * @brief 判断ip段是否在某ip段内(通配符处理)
 * 
 * @param a_ip_start 起始ip地址(Request内的)
 * @param a_ip_end 结束ip地址(Request内的)
 * @param b_ip_start 起始ip地址(Response内的)
 * @param b_ip_end 结束ip地址(Response内的)
 * @return true 
 * @return false 
 */
bool isBelong_star(ip a_ip_start,ip a_ip_end, ip b_ip_start, ip b_ip_end);

/**
 * @brief 处理通配符,将含通配符的ip字符串转成IP段
 * 
 * @param str 
 * @return ip_set 
 */
ip_set star2ip_set(char str[]);

/**
 * @brief 将一个ip转成自身到自身的ip段
 * 
 * @param a_ip 
 * @return ip_set 
 */
ip_set ipToIpSet(ip a_ip);

/**
 * @brief 将字符串转换成ip段
 * 
 * @param str ip字符串
 * @return ip_set 
 */
ip_set strToIpSet(char str[]);

/**
 * @brief 判断字符串类型
 * 
 * @param str 一段字符串
 * @return int 常量值(Type_Unknown,Type_ip,Type_ip_set)
 */
int judgeStr(char str[]);

#endif  //__IP_MODEL_H__