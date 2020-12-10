/**
 * @file View.cpp
 * @author DoraLY<770848871@qq.com>
 * @brief 视图类
 * @version 0.1
 * @date 2020-01-29
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#pragma warning(disable:4996)
#include "View.h"

void View::showHello()//开始界面 
{
    system("cls");//清屏
	system("color 0A");//使用黑底亮绿色字体 
	printf("\n");
	printf("\n");
	printf("\n");
 	printf("\t\t\t              *******                  *******                 \n");
 	printf("\t\t\t            **           *          *           **             \n");
	printf("\t\t\t          **               *     *                **           \n");
	printf("\t\t\t        **                   * *                    **         \n");
	printf("\t\t\t       **                                            **        \n");                
	printf("\t\t\t      **                                              **       \n");                 
	printf("\t\t\t      **                   欢迎使用                    **      \n");              
	printf("\t\t\t      **                                               **      \n");
	printf("\t\t\t      **                                               **      \n");
	printf("\t\t\t      **                IP地址查询系统                 **      \n");
	printf("\t\t\t      **             请选择所要进入的页面：            **      \n");
	printf("\t\t\t       **             1. ------进入系统               **      \n");
	printf("\t\t\t        **            2. ------打开设置              **       \n");
	printf("\t\t\t         **           3. ------关于界面             **         \n");
	printf("\t\t\t           **         0. ------退出程序            **           \n");
	printf("\t\t\t             **                                 **             \n");
	printf("\t\t\t               **                             **               \n");
	printf("\t\t\t                 **                         **                 \n");
	printf("\t\t\t                    **                    **                   \n");
	printf("\t\t\t                      **                **                     \n");
	printf("\t\t\t                         **          **                        \n");
	printf("\t\t\t                           **      **                          \n");
	printf("\t\t\t                               **                              \n");
} 


void View::showSetting(){
	Config config;
    system("cls");       //清屏
    system("color 0A");  //使用黑底亮绿色字体
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t\t\t\t****************************************************\n");
    printf("\t\t\t\t**************************设置**********************\n");
    printf("\t\t\t\t* ------------------------------------------------ *\n");
    printf("\t\t\t\t*|            1.【%s】无数据时是否输出            |*\n",config.get(is_PrintWithoutData) == 1 ? "是" : "否");
    printf("\t\t\t\t*|            2.【%s】输出国家                    |*\n",config.get(is_PrintCountry) == 1 ? "是" : "否");
    printf("\t\t\t\t*|            3.【%s】输出区域                    |*\n",config.get(is_PrintArea) == 1 ? "是" : "否");
    printf("\t\t\t\t*|            4.【%s】输出省份                    |*\n",config.get(is_PrintProvince) == 1 ? "是" : "否");
    printf("\t\t\t\t*|            5.【%s】输出城市                    |*\n",config.get(is_PrintCity) == 1 ? "是" : "否");
    printf("\t\t\t\t*|            6.【%s】输出ISP                     |*\n",config.get(is_PrintISP) == 1 ? "是" : "否");

	switch(config.get(method_Sort)){
		case sort_by_default + sort_by_seq:
			printf("\t\t\t\t*|            7.【按照%s,%s输出】             |*\n", "默认" , "顺序" );
		break;
		case sort_by_default + sort_by_rev:
			printf("\t\t\t\t*|            7.【按照%s,%s输出】             |*\n", "默认" , "逆序" );
		break;
		case sort_by_country + sort_by_seq:
			printf("\t\t\t\t*|            7.【按照%s,%s输出】             |*\n", "国家" , "顺序" );
		break;
		case sort_by_country + sort_by_rev:
			printf("\t\t\t\t*|            7.【按照%s,%s输出】             |*\n", "国家" , "逆序" );
		break;
		case sort_by_area + sort_by_seq:
			printf("\t\t\t\t*|            7.【按照%s,%s输出】             |*\n", "区域" , "顺序" );
		break;
		case sort_by_area + sort_by_rev:
			printf("\t\t\t\t*|            7.【按照%s,%s输出】             |*\n", "区域" , "逆序" );
		break;
		case sort_by_province + sort_by_seq:
			printf("\t\t\t\t*|            7.【按照%s,%s输出】             |*\n", "省份" , "顺序" );
		break;
		case sort_by_province + sort_by_rev:
			printf("\t\t\t\t*|            7.【按照%s,%s输出】             |*\n", "省份" , "逆序" );
		break;
		case sort_by_city + sort_by_seq:
			printf("\t\t\t\t*|            7.【按照%s,%s输出】             |*\n", "城市" , "顺序" );
		break;
		case sort_by_city + sort_by_rev:
			printf("\t\t\t\t*|            7.【按照%s,%s输出】             |*\n", "城市" , "逆序" );
		break;
		case sort_by_isp + sort_by_seq:
			printf("\t\t\t\t*|            7.【按照%s,%s输出】             |*\n", "isp" , "顺序" );
		break;
		case sort_by_isp + sort_by_rev:
			printf("\t\t\t\t*|            7.【按照%s,%s输出】             |*\n", "isp" , "逆序" );
		break;
		default:
			printf("\t\t\t\t*|            7.【按照%s,%s输出】             |*\n", "默认", "顺序");
		break;
	}

    printf("\t\t\t\t*|            0.返回主菜单                        |*\n");
    printf("\t\t\t\t* ------------------------------------------------ *\n");
    printf("\t\t\t\t****************************************************\n");
}

void View::showAbout(){
    system("cls");//清屏
	system("color 0A");//使用黑底亮绿色字体 
    printf("\n\n\n");
    printf("\t\t* -------------------------------------------------------------------------------->\n");
	printf("\t\t*|                              ipTools [版本 1.1.0]\n");
    printf("\t\t*|\n");
    printf("\t\t*|                   Copyright (c) 2020 DoraLY<770848871@qq.com>\n");
    printf("\t\t*|\n");
    printf("\t\t*|  Permission is hereby granted, free of charge, to any person obtaining a copy\n");
    printf("\t\t*|  of this software and associated documentation files (the \"Software\"), to deal\n");
    printf("\t\t*|  in the Software without restriction, including without limitation the rights\n");
    printf("\t\t*|  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell\n");
    printf("\t\t*|  copies of the Software, and to permit persons to whom the Software is\n");
    printf("\t\t*|  furnished to do so, subject to the following conditions:\n");
    printf("\t\t*|\n");
    printf("\t\t*|  The above copyright notice and this permission notice shall be included in all\n");
    printf("\t\t*|  copies or substantial portions of the Software.\n");
    printf("\t\t*|\n");
    printf("\t\t*|  THE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\n");
    printf("\t\t*|  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\n");
    printf("\t\t*|  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\n");
    printf("\t\t*|  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\n");
    printf("\t\t*|  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\n");
    printf("\t\t*|  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\n");
    printf("\t\t*|  SOFTWARE.\n");
	printf("\t\t* -------------------------------------------------------------------------------->\n");
}

int View::setResponse(Response response_) {
	response = response_;
	pageMax = response.info.size() / 20 + 1;
	return pageMax;
}

void View::showResponse(int page,float time){
    system("cls");//清屏
	system("color 0A");//使用黑底亮绿色字体 
    printf("\n");
    printf("\t* -------------------------------------------------------------------------------->\n");
	printf("\t*|                             查询结果(第%d页/共%d页)\n",page,pageMax);
	printf("\t*|                          耗时:%gms 记录数:%d条 保存(s键)\n",time,response.info.size());
	printf("\t* -------------------------------------------------------------------------------->\n");
    printf("\t*|\n");
	Config config;
	if (page > pageMax) {
		page = pageMax;
	}
	int record_start = (page-1) * 20;
	int record_end = page * 20;
	if (page == pageMax) {
		record_end = response.info.size();
	}
	response.SortBy(config.get(method_Sort));
	for(int i=record_start;i<record_end;i++){
		printf("\t*|  ");
		printf("%s", response.info[i].ip_start.getIpStr());
		if(response.info[i].ip_start.getIpInt() != response.info[i].ip_end.getIpInt()){
			printf("-%s  |\t", response.info[i].ip_end.getIpStr());
		}
		else {
			printf("  |\t");
		}
		int judge=config.get(is_PrintWithoutData);
		if(config.get(is_PrintCountry) == 1){
			int judge2 = strcmp(response.info[i].country,"0");
			if(judge2 != 0 || (judge2 == 0 && judge == 1)){
				printf("%s  |\t",response.info[i].country);
			}
		}
		if(config.get(is_PrintArea) == 1){
			int judge2 = strcmp(response.info[i].area,"0");
			if(judge2 != 0 || (judge2 == 0 && judge == 1)){
				printf("%s  |\t",response.info[i].area);
			}
		}
		if(config.get(is_PrintProvince) == 1){
			int judge2 = strcmp(response.info[i].province,"0");
			if(judge2 != 0 || (judge2 == 0 && judge == 1)){
				printf("%s  |\t",response.info[i].province);
			}
		}
		if(config.get(is_PrintCity) == 1){
			int judge2 = strcmp(response.info[i].city,"0");
			if(judge2 != 0 || (judge2 == 0 && judge == 1)){
				printf("%s  |\t",response.info[i].city);
			}
		}
		if(config.get(is_PrintISP) == 1){
			int judge2 = strcmp(response.info[i].isp,"0");
			if(judge2 != 0 || (judge2 == 0 && judge == 1)){
				printf("%s  |\t",response.info[i].isp);
			}
		}
		printf("\n");
	}
    printf("\t*|\n");  
	printf("\t* -------------------------------------------------------------------------------->\n");
}


void View::showQuery(){
	system("cls");//清屏
	system("color 0A");//使用黑底亮绿色字体 
	printf("    IP地址查询系统    \n");
	printf("* ----------------- *\n");
	printf("*|  a.查询输入内容  |*\n");
	printf("*|  b.查询输入文件  |*\n");
	printf("* ----------------- *\n");
}