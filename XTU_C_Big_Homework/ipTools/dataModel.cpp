/**
 * @file dataModel.cpp
 * @author DoraLY<770848871@qq.com>
 * @brief 数据模型类,提供了数据库的读取,查询等功能
 * @version 1.1
 * @date 2020-02-04
 *
 * @copyright Copyright (c) 2020
 *
 * Updata:2020-02-04
 * Fix: 通配符bug
 */
#pragma warning(disable : 4996)
#include "dataModel.h"

bool cmp_country(ipInfo a, ipInfo b) {
    return strcmp(a.country, b.country) < 0 ? true : false;
}

bool cmp_area(ipInfo a, ipInfo b) {
    return strcmp(a.area, b.area) < 0 ? true : false;
}

bool cmp_province(ipInfo a, ipInfo b) {
    return strcmp(a.province, b.province) < 0 ? true : false;
}

bool cmp_city(ipInfo a, ipInfo b) {
    return strcmp(a.city, b.city) < 0 ? true : false;
}

bool cmp_isp(ipInfo a, ipInfo b) {
    return strcmp(a.isp, b.isp) < 0 ? true : false;
}

dataModel::dataModel(bool enableLowMemoryMode) {
    lowMemoryMode = enableLowMemoryMode;
}

dataModel::~dataModel() { db.clear(); }

void dataModel::LoadIpData() {
    if (lowMemoryMode) {  //如果启动了低内存模式,就不加载数据库了
        return;
    }
    FILE* fp = nullptr;
    fp = fopen("ip.txt", "r+");  // C:\\Users\\DoraLY\\Desktop\\ipTools\\ip.txt
                                 // 可绝对目录可相对目录
    if (fp == nullptr) {
        printf("open fail errno = %d \n", errno);
        printf("Error: Cannot Find Database File 'ip.txt'!");
        exit(-1);
    }
    //循环读取每一行，直到文件尾
    while (!feof(fp)) {
        // 按照数据文件中
        // {起始地址}|{结束地址}|{国家}|{区域}|{省份}|{城市}|{ISP}\n
        // 的形式读入一行数据
        ipInfo tmp;
        /*
        char ipStart[20], ipEnd[20];
        fscanf(fp, "%[0-9.]|%[0-9.]|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]", ipStart,
        ipEnd, tmp.country, tmp.area, tmp.province, tmp.city, tmp.isp);
        tmp.ip_start.setIp(ipStart);
        tmp.ip_end.setIp(ipEnd);
        */
        int a1, a2, a3, a4, b1, b2, b3, b4;
        fscanf(fp, "%d.%d.%d.%d|%d.%d.%d.%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
               &a1, &a2, &a3, &a4, &b1, &b2, &b3, &b4, tmp.country, tmp.area,
               tmp.province, tmp.city, tmp.isp);
        tmp.ip_start.setIp(a1, a2, a3, a4);
        tmp.ip_end.setIp(b1, b2, b3, b4);
        fgetc(fp);
        db.push_back(tmp);
    }
    fclose(fp);  //关闭文件
}

int dataModel::BinarySearch(ip aip) {
    int low = 0;
    int high = db.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (isBelong(aip, db[mid].ip_start, db[mid].ip_end))
            return mid;
        else if (db[mid].ip_end > aip)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return 0;
}

Response dataModel::processStar(ip_set ips, Response response) {
    if (ips.isSpecial() == false) {
        return response;
    }
    Response new_response;
    for (int i = 0; i < response.info.size(); i++) {
        if (isBelong_star(ips.ip_start, ips.ip_end, response.info[i].ip_start,response.info[i].ip_end)) {
            ipInfo ipi = response.info[i];
            if (ips.ip_start.seg[3] == ips.ip_end.seg[3]){
                ipi.ip_start.seg[3] = ips.ip_start.seg[3];
                ipi.ip_end.seg[3] = ips.ip_end.seg[3];
            }
            if (ips.ip_start.seg[2] == ips.ip_end.seg[2]){
                ipi.ip_start.seg[2] = ips.ip_start.seg[2];
                ipi.ip_end.seg[2] = ips.ip_end.seg[2];
            }
            if (ips.ip_start.seg[1] == ips.ip_end.seg[1]){
                ipi.ip_start.seg[1] = ips.ip_start.seg[1];
                ipi.ip_end.seg[1] = ips.ip_end.seg[1];
            }
            if (ips.ip_start.seg[0] == ips.ip_end.seg[0]){
                ipi.ip_start.seg[0] = ips.ip_start.seg[0];
                ipi.ip_end.seg[0] = ips.ip_end.seg[0];
            }
            new_response.append(ips, ipi);
        }
    }
    return new_response;
}

Response dataModel::queryOne_LowMemory(ip_set ips) {
    Response response;
    bool isRecord = false;
    FILE* fp = nullptr;
    fp = fopen("ip.txt", "r+");
    if (fp == nullptr) {
        printf("open fail errno = %d \n", errno);
        printf("Error: Cannot Find Database File 'ip.txt'!");
        exit(-1);
    }
    while (!feof(fp)) {
        ipInfo tmp;
        int a1, a2, a3, a4, b1, b2, b3, b4;
        fscanf(fp, "%d.%d.%d.%d|%d.%d.%d.%d|%[^|]|%[^|]|%[^|]|%[^|]|%[^\n]",
               &a1, &a2, &a3, &a4, &b1, &b2, &b3, &b4, tmp.country, tmp.area,
               tmp.province, tmp.city, tmp.isp);
        tmp.ip_start.setIp(a1, a2, a3, a4);
        tmp.ip_end.setIp(b1, b2, b3, b4);
        fgetc(fp);

        if (isBelong(ips.ip_start, tmp.ip_start, tmp.ip_end)) {
            isRecord = true;
        }
        if (isRecord) {
            response.append(ips, tmp);
        }
        if (isBelong(ips.ip_end, tmp.ip_start, tmp.ip_end)) {
            break;
        }
    }
    fclose(fp);  //关闭文件
    return processStar(ips, response);
}

Response dataModel::queryOne(ip_set ips) {
    if (lowMemoryMode) {  //如果启动了低内存模式,使用低内存模式查询
        return queryOne_LowMemory(ips);
    }
    Response response;
    int starNum = ips.starCount();
    bool isStar[4] = {ips.isStar(0), ips.isStar(1), ips.isStar(2),
                      ips.isStar(3)};
    if (ips.isSpecial() == true) {
        if (starNum == 1) {
            for (int i = 0; i <= 255; i++) {
                ip tmp_ip;
                if (isStar[0] == true) {
                    tmp_ip.setIp(i, ips.ip_start.seg[2], ips.ip_start.seg[1],
                                 ips.ip_start.seg[0]);
                } else if (isStar[1] == true) {
                    tmp_ip.setIp(ips.ip_start.seg[3], i, ips.ip_start.seg[1],
                                 ips.ip_start.seg[0]);
                } else if (isStar[2] == true) {
                    tmp_ip.setIp(ips.ip_start.seg[3], ips.ip_start.seg[2], i,
                                 ips.ip_start.seg[0]);
                }
                Response tmp_response = queryOne(ipToIpSet(tmp_ip));
                response.addResponse(tmp_response);
            }
            return response;
        }
    }
    int start = 0, end = 0;
    start = BinarySearch(ips.ip_start);
    end = BinarySearch(ips.ip_end);
    for (int i = start; i <= end; i++) {
        response.append(ips, db[i]);
    }
    return processStar(ips, response);
}

Response dataModel::query(Request request) {
    Response response;
    for (int j = 0; j < request.ipSet.size(); j++) {
        response.addResponse(queryOne(request.ipSet[j]));
    }
    return response;
}

Request dataModel::LoadRequestFromFile(char* filename) {
    Request request;
    char tmp[MAX_INPUT_X];
    FILE* fp = fopen(filename, "r+");
    if (fp == nullptr) {
        printf("Error: Cannot Open Target Request File!");
        exit(-1);
    }
    while (!feof(fp)) {
        fscanf(fp, "%[0-9.*-]", tmp);
        switch (judgeStr(tmp)) {
            case Type_Unknown:
                printf("Error: Cannot recognize '%s' in input file!", tmp);
                exit(-1);
                break;
            case Type_ip:
                request.append(strToIpSet(tmp));
                break;
            case Type_ip_set:
                request.append(strToIpSet(tmp));
                break;
        }
        fgetc(fp);
    }
    fclose(fp);  //关闭文件
    return request;
}