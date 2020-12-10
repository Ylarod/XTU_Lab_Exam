/**
 * @file ipModel.cpp
 * @author DoraLY<770848871@qq.com>
 * @brief ip模型类的实现
 * @version 1.1
 * @date 2020-02-04
 *
 * @copyright Copyright (c) 2020
 *
 * Updata:2020-02-04
 * Fix: 通配符bug
 */
#pragma warning(disable : 4996)
#include "ipModel.h"

using namespace std;

ip::ip(int s0, int s1, int s2, int s3) {
    //下面赋值的顺序，涉及整型数据存储结构，参考
    //《整型数据在内存中如何存储？》(http://blog.csdn.net/sxhelijian/article/details/51015706)
    seg[0] = s3;
    seg[1] = s2;
    seg[2] = s1;
    seg[3] = s0;
}

ip::ip(char str[]) {
    int s0, s1, s2, s3;
    sscanf(str, "%d.%d.%d.%d", &s0, &s1, &s2, &s3);
    seg[0] = s3;
    seg[1] = s2;
    seg[2] = s1;
    seg[3] = s0;
}

ip::ip(const ip &obj) {
    seg[0] = obj.seg[0];
    seg[1] = obj.seg[1];
    seg[2] = obj.seg[2];
    seg[3] = obj.seg[3];
}

char *ip::getIpStr() {
    char *str;
    str = new char[16];
    sprintf(str, "%d.%d.%d.%d", int(seg[3]), int(seg[2]), int(seg[1]),
            int(seg[0]));
    return str;
}

int ip::getIpInt() { return address; }

void ip::setIp(int s0, int s1, int s2, int s3) {
    seg[0] = s3;
    seg[1] = s2;
    seg[2] = s1;
    seg[3] = s0;
}

void ip::setIp(char str[]) {
    int s0, s1, s2, s3;
    sscanf(str, "%d.%d.%d.%d", &s0, &s1, &s2, &s3);
    seg[0] = s3;
    seg[1] = s2;
    seg[2] = s1;
    seg[3] = s0;
}

void ip::setIp(ip ipa) { address = ipa.getIpInt(); }

bool isBelong(ip a_ip, ip ip_start, ip ip_end) {
    if (ip_start.getIpInt() <= a_ip.getIpInt() &&
        a_ip.getIpInt() <= ip_end.getIpInt()) {
        return true;
    }
    return false;
}

bool isBelong_star(ip a_ip_start, ip a_ip_end, ip b_ip_start, ip b_ip_end) {
    int ip_int[4];
    ip_int[0] = a_ip_start.seg[3] == a_ip_end.seg[3] ? a_ip_start.seg[3] : 256;
    ip_int[1] = a_ip_start.seg[2] == a_ip_end.seg[2] ? a_ip_start.seg[2] : 256;
    ip_int[2] = a_ip_start.seg[1] == a_ip_end.seg[1] ? a_ip_start.seg[1] : 256;
    ip_int[3] = a_ip_start.seg[0] == a_ip_end.seg[0] ? a_ip_start.seg[0] : 256;
    if (b_ip_start.seg[3] <= ip_int[0] && ip_int[0] <= b_ip_end.seg[3] ||
        ip_int[0] == 256) {
        if (b_ip_start.seg[2] <= ip_int[1] && ip_int[1] <= b_ip_end.seg[2] ||
            ip_int[1] == 256) {
            if (b_ip_start.seg[1] <= ip_int[2] &&
                    ip_int[2] <= b_ip_end.seg[1] ||
                ip_int[2] == 256) {
                if (b_ip_start.seg[0] <= ip_int[3] &&
                        ip_int[3] <= b_ip_end.seg[0] ||
                    ip_int[3] == 256) {
                    return true;
                }
            }
        }
    }
    return false;
}
ip_set star2ip_set(char str[]) {
    ip_set res;
    char s[4][4];
    bool a[4];
    sscanf(str, "%[0-9*].%[0-9*].%[0-9*].%[0-9*]", s[0], s[1], s[2], s[3]);
    for (int i = 0; i < 4; i++) {
        a[i] = (strcmp(s[i], "*") == 0);  // 是否为通配符
    }
    res.ip_start.setIp(a[0] ? 0 : atoi(s[0]), a[1] ? 0 : atoi(s[1]),
                       a[2] ? 0 : atoi(s[2]), a[3] ? 0 : atoi(s[3]));
    res.ip_end.setIp(a[0] ? 255 : atoi(s[0]), a[1] ? 255 : atoi(s[1]),
                     a[2] ? 255 : atoi(s[2]), a[3] ? 255 : atoi(s[3]));
    return res;
}

ip_set ipToIpSet(ip a_ip) {
    ip_set tmp;
    tmp.ip_start = a_ip;
    tmp.ip_end = a_ip;
    return tmp;
}

ip_set strToIpSet(char str[]) {
    ip_set set;
    if (judgeStr(str) == Type_ip) {
        set = star2ip_set(str);
    } else {
        char *ip1, *ip2;
        ip1 = strtok(str, "-");
        ip2 = strtok(NULL, "-");
        set.ip_start.setIp(ip1);
        set.ip_end.setIp(ip2);
    }
    return set;
}

int strchrt(const char *p, const char chr) {  //取某字符在字符串中出现的次数
    int count = 0, i = 0;
    while (*(p + i)) {
        if (p[i] == chr) ++count;
        ++i;
    }
    return count;
}

int judgeStr(char str[]) {
    int i = strchrt(str, '.');
    if (strchr(str, '-') != NULL) {
        if (i == 6) {
            return Type_ip_set;
        }
    } else {
        if (i == 3) {
            return Type_ip;
        }
    }
    return Type_Unknown;
}

bool ip_set::isStar(int pos) {
    if (ip_start.seg[3 - pos] == 0 && ip_end.seg[3 - pos] == 255) {
        return true;
    }
    return false;
}

int ip_set::starCount() {
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (isStar(i)) {
            count++;
        }
    }
    return count;
}

int ip_set::isSpecial() {
    /*
    0: *_*_*_* 普通
    0: 0_*_*_* 普通
    0: 0_0_*_* 普通
    0: 0_0_0_* 普通
    1: *_0_*_* 以下均为特殊类型
    2: *_*_0_*
    3: *_*_*_0
    4: 0_*_0_*
    5: *_0_0_*
    6: 0_*_*_0
    7: *_0_*_0
    8: *_*_0_0
    9: 0_0_*_0
    10: 0_*_0_0
    11: *_0_0_0
    */
    int count = starCount();
    if (count == 4 || count == 0) {
        return false;
    }
    if (count == 3 && isStar(0) == false) {
        return false;
    }
    if (count == 2 && isStar(0) == false && isStar(1) == false) {
        return false;
    }
    if (count == 1 && isStar(3) == true) {
        return false;
    }
    return true;
}