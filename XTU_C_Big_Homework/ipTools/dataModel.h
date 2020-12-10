/**
 * @file dataModel.h
 * @author DoraLY<770848871@qq.com>
 * @brief 数据模型类的头文件
 * @version 1.1
 * @date 2020-02-04
 *
 * @copyright Copyright (c) 2020
 *
 * Updata:2020-2-4
 * Fix: 通配符bug
 */
#ifndef __MODEL_H__  //标准头文件结构
#define __MODEL_H__  //防止重复声明

#include "ipModel.h"
#include "main.h"

using namespace std;

/**
 * @brief 排序的比较函数,按国家排序
 *
 * @param a
 * @param b
 * @return true
 * @return false
 */
bool cmp_country(ipInfo a, ipInfo b);

/**
 * @brief 排序的比较函数,按区域排序
 *
 * @param a
 * @param b
 * @return true
 * @return false
 */
bool cmp_area(ipInfo a, ipInfo b);

/**
 * @brief 排序的比较函数,按省份排序
 *
 * @param a
 * @param b
 * @return true
 * @return false
 */
bool cmp_province(ipInfo a, ipInfo b);

/**
 * @brief 排序的比较函数,按城市排序
 *
 * @param a
 * @param b
 * @return true
 * @return false
 */
bool cmp_city(ipInfo a, ipInfo b);

/**
 * @brief 排序的比较函数,按isp排序
 *
 * @param a
 * @param b
 * @return true
 * @return false
 */
bool cmp_isp(ipInfo a, ipInfo b);

/**
 * @brief 查询请求类
 * 
 */
class Request {
   public:
    vector<ip_set> ipSet;
    /**
     * @brief 增加一条查询请求
     *
     * @param ipa 一个ip
     */
    void append(ip ipa) { ipSet.push_back(ipToIpSet(ipa)); }
    /**
     * @brief 增加一条查询请求
     *
     * @param ips 一个ip段
     */
    void append(ip_set ips) { ipSet.push_back(ips); }
};

/**
 * @brief 查询回复类
 * 
 */
class Response {
   public:
    vector<ipInfo> info;
    /**
     * @brief 增加结果
     *
     * @param ips 查询的ip
     * @param ipi 查询的结果
     */
    void append(ip_set ips, ipInfo ipi) {
        if (ips.ip_start > ipi.ip_start) {
            ipi.ip_start.setIp(ips.ip_start);
        }
        if (ips.ip_end < ipi.ip_end) {
            ipi.ip_end.setIp(ips.ip_end);
        }
        info.push_back(ipi);
    }

    /**
     * @brief 合并两个response
     *
     * @param response
     */
    void addResponse(Response response) {
        for (int i = 0; i < response.info.size(); i++) {
            info.push_back(response.info[i]);
        }
    }

    /**
     * @brief 排序
     *
     * @param method 排序方式
     */
    void SortBy(int method) {
        switch (method) {
            case sort_by_default + sort_by_seq:
                //"默认" , "顺序"
                break;
            case sort_by_default + sort_by_rev:
                //"默认" , "逆序"
                std::reverse(info.begin(), info.end());
                break;
            case sort_by_country + sort_by_seq:
                //"国家" , "顺序"
                std::sort(info.begin(), info.end(), cmp_country);
                break;
            case sort_by_country + sort_by_rev:
                //"国家" , "逆序"
                std::sort(info.begin(), info.end(), cmp_country);
                std::reverse(info.begin(), info.end());
                break;
            case sort_by_area + sort_by_seq:
                //"区域" , "顺序"
                std::sort(info.begin(), info.end(), cmp_area);
                break;
            case sort_by_area + sort_by_rev:
                //"区域" , "逆序"
                std::sort(info.begin(), info.end(), cmp_area);
                std::reverse(info.begin(), info.end());
                break;
            case sort_by_province + sort_by_seq:
                //"省份" , "顺序"
                std::sort(info.begin(), info.end(), cmp_province);
                break;
            case sort_by_province + sort_by_rev:
                //"省份" , "逆序"
                std::sort(info.begin(), info.end(), cmp_province);
                std::reverse(info.begin(), info.end());
                break;
            case sort_by_city + sort_by_seq:
                //"城市" , "顺序"
                std::sort(info.begin(), info.end(), cmp_city);
                break;
            case sort_by_city + sort_by_rev:
                //"城市" , "逆序"
                std::sort(info.begin(), info.end(), cmp_city);
                std::reverse(info.begin(), info.end());
                break;
            case sort_by_isp + sort_by_seq:
                //"isp" , "顺序"
                std::sort(info.begin(), info.end(), cmp_isp);
                break;
            case sort_by_isp + sort_by_rev:
                //"isp" , "逆序"
                std::sort(info.begin(), info.end(), cmp_isp);
                std::reverse(info.begin(), info.end());
                break;
            default:
                //"默认", "顺序"
                break;
        }
    }

    /**
     * @brief 将结果保存到文件
     *
     * @param filename 文件名
     */
    void saveToFile(char filename[]) {
        Config config;
        FILE* fp = fopen(filename, "w");
        int judge = config.get(is_PrintWithoutData);
        for (int i = 0; i < info.size(); i++) {
            fprintf(fp, "%d,", i);
            fprintf(fp, "%s", info[i].ip_start.getIpStr());
            if (info[i].ip_start.getIpInt() != info[i].ip_end.getIpInt()) {
                fprintf(fp, "-%s\t,", info[i].ip_end.getIpStr());
            } else {
                fprintf(fp, "\t,");
            }
            if (config.get(is_PrintCountry) == 1) {
                int judge2 = strcmp(info[i].country, "0");
                if (judge2 != 0 || (judge2 == 0 && judge == 1)) {
                    fprintf(fp, "%s\t,", info[i].country);
                }
            }
            if (config.get(is_PrintArea) == 1) {
                int judge2 = strcmp(info[i].area, "0");
                if (judge2 != 0 || (judge2 == 0 && judge == 1)) {
                    fprintf(fp, "%s\t,", info[i].area);
                }
            }
            if (config.get(is_PrintProvince) == 1) {
                int judge2 = strcmp(info[i].province, "0");
                if (judge2 != 0 || (judge2 == 0 && judge == 1)) {
                    fprintf(fp, "%s\t,", info[i].province);
                }
            }
            if (config.get(is_PrintCity) == 1) {
                int judge2 = strcmp(info[i].city, "0");
                if (judge2 != 0 || (judge2 == 0 && judge == 1)) {
                    fprintf(fp, "%s\t,", info[i].city);
                }
            }
            if (config.get(is_PrintISP) == 1) {
                int judge2 = strcmp(info[i].isp, "0");
                if (judge2 != 0 || (judge2 == 0 && judge == 1)) {
                    fprintf(fp, "%s\t,", info[i].isp);
                }
            }
            fprintf(fp, "\n");
        }
        fclose(fp);
    }
};

/**
 * @brief 数据模型类
 * 
 */
class dataModel {
   private:
    vector<ipInfo> db;
    bool lowMemoryMode;

    /**
     * @brief 从数据库中二分查找某ip的位置
     * 
     * @param aip 待查找的ip
     * @return int 下标
     */
    int BinarySearch(ip aip);

    /**
     * @brief 查询单个ip段,低内存模式
     * 
     * @param ips ip段
     * @return Response 结果
     */
    Response queryOne_LowMemory(ip_set ips);
    
    /**
     * @brief 去除特殊情况下重复查询出的部分
     * 
     * @param ips ip段
     * @param response 结果
     * @return Response 处理后的结果
     */
    Response processStar(ip_set ips,Response response);
    
   public:
    /**
     * @brief 构造函数
     * 
     * @param lowMemoryMode 启动低内存模式
     */
    dataModel(bool lowMemoryMode = false);
    /**
     * @brief 析构函数,释放所占用的内存
     *
     */
    ~dataModel();

    /**
     * @brief 加载ip数据库文件(在低内存模式中不起作用)
     *
     */
    void LoadIpData();

    /**
     * @brief 查询单个ip段
     *
     * @param ips ip段
     * @return Response 结果
     */
    Response queryOne(ip_set ips);

    /**
     * @brief 执行批量查询操作
     *
     * @param request 请求
     * @return Response 结果
     */
    Response query(Request request);

    /**
     * @brief 从文件读入请求
     *
     * @param filename 文件名
     * @return Request 请求
     */
    Request LoadRequestFromFile(char* filename);
};

#endif