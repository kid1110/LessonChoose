#include <stdio.h>
#include <stdlib.h>
#include "lesson.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//void ad();
LinkInfo L = NULL;
student* s =NULL;
int main(int argc, char *argv[]) {
	int i;
	system("color 2");
	gotoxy(49,80);
	printf("欢迎来到选课系统");
	for(i=0;i<=15;i++){
		printf("\n");
	}
	restart:;
	menu();
	int choice;
	while(scanf("%d",&choice) != EOF){
		fflush(stdin);
		choice = (char)(choice+96);
		switch(choice){
			case 'a':{
				student* t = (student*)malloc(sizeof(student));
				int judge;
				system("cls");
				
				if(s == NULL){
					createStudent(&s);
					judge = StudentInform(s,t);
					if(judge == 1){
						printf("注册成功!\n");
						menu();
					}else if(judge == 0){
						printf("密码不一致\n");
						menu();
						
					}else if(judge == 9){
						printf("密码长度不能大于20\n");
						menu();
					}else if(judge == 8){
						printf("该用户已存在\n");
						menu();
					}
				}else{
					judge = StudentInform(s,t);
					if(judge == 1){
						printf("注册成功!\n");
						menu();
					}else if(judge == 0){
						printf("密码不一致\n");
						menu();
						
					}else if(judge == 9){
						printf("密码长度不能大于20\n");
						menu();
					}else if(judge == 8){
						printf("该用户已存在\n");
						menu();
					}
					
				}
				break;
			}
			case 'b': {
				loginrst:;
				int number,judge;
				char password[20];
				loginMenu();
				scanf("%d",&number);
				gotoxy(55,81); 
				scanf("%s",&password);
				judge = CheckPassword(s,number,password);
				if(judge ==6){
					printf("该用户不存在\n");
					goto restart;
				}else if(judge == 10){
					printf("密码错误\n");
					goto restart;
				}else if(judge == 2){
					printf("还没有用户进行注册\n");
					goto restart;
				}else{
					Userrst:;
					UserMenu();
					while(scanf("%d",&choice) != EOF){
						fflush(stdin);
						choice = (char)(choice+96);
						switch(choice){
							case 'a':{
									int judge;
									judge = checkTotalLesson(L);
									if(judge == 1){
										printf("查阅成功\n");
										system("pause");
										UserMenu();
									}else{
										printf("管理员还没有放置课程\n");
										UserMenu();
									}
									break;
							}
							case 'b':{
								int judge;
								LesInfo* t = (LesInfo*)malloc(sizeof(LesInfo));
								judge = PickLesson(s,L,t,number);
								if(judge == 3){
									printf("暂时未有课程可以选择\n");
								}else if(judge == 5){
									printf("该课程不存在");
								}else if(judge == 1){
									printf("选择成功");
								}else if(judge == 7){
									printf("该课程已经满人了\n");
								}else if(judge == 11){
									printf("不可以重复选择\n"); 
								}else if(judge == 12){
									printf("你已经不能选课了\n"); 
								}
								UserMenu();
								break;
							}
							case 'c': {
								int judge;
								judge = DeleteChooseLesson(s,L,number);
								if(judge == 3){
									printf("暂时未有课程可以选择\n");
								}else if(judge == 5){
									printf("该课程不存在\n");
								}else if(judge == 0){
									printf("你并没有选择该课程\n");
								}else if (judge == 1){
									printf("删除成功\n");
								}
								UserMenu();
								break;
							}
							case 'd':{
								int judge;
								judge = checkSelectLesson(s,L,number);
								if(judge == 3){
									printf("暂时未有课程发布\n");
								}else if(judge == 0){
									printf("你并没有选择课程\n");
								}else if(judge == 1){
									printf("查阅成功");
								}
								system("pause");
								UserMenu();
								break;
							}
							case 'e':{		//编号查找课程模块 
								int judge;
								judge =  FindLesson(L);
								if(judge == 3){
									printf("暂时未有课程发布\n");
								}else if(judge == 5){
									printf("该课程不存在\n");	
								}else if(judge == 1){
									printf("查找成功\n");
									system("pause");
								} 
								UserMenu();
								break;
							}
							case 'f':{
									gotoxy(57,82); 
									Sleep(1000); 
									goto restart;
									break;
							}
							default:{
								gotoxy(57,82); 
								printf("输入错误，请重新输入!");
								Sleep(1000); 
								goto Userrst;
								break;
							}
						}
					}
					
				}
				break;
			} 
			case 'c':{
				manageMenu();
				int Adminchoice;
				scanf("%d",&Adminchoice);
				if(Adminchoice == 123){
					Adminrst:;
					AdminMenu();
					while(scanf("%d",&choice) != EOF){
					fflush(stdin);
					choice = (char)(choice+96);
					switch(choice){
						case 'a':{
							LinkInfo q = (LinkInfo)malloc(sizeof(LesInfo));
							int judge;
							if(L == NULL){
								 createSystem(&L);
								judge = insertLesson(L,q);
								if(judge == 1){
									printf("插入成功");
									AdminMenu(); 
								}else if(judge == 0){
									printf("插入失败");
									AdminMenu();
								}else if(judge ==4){
									printf("该课程已存在");
									AdminMenu();
								}
							}else{
								judge = insertLesson(L,q);
								if(judge == 1){
									printf("插入成功"); 
									AdminMenu();
								}else if(judge == 0){
									printf("插入失败");
									AdminMenu();
								}else if(judge == 4){
									printf("该课程已存在");
									AdminMenu(); 
								}
							}
							break;
						}
						case 'b':{
							int judge;
							judge = DeleteLesson(L);
							if(judge == 3){
								printf("暂时未有课程\n");
								AdminMenu();
							}else if(judge == 5){
								printf("该课程不存在\n");
								AdminMenu();
							}else if(judge == 1){
								printf("删除成功\n");
								AdminMenu();
							}  
							break;
						}
						case 'c':{
							int judge;
							judge = checkTotalLesson(L);
							if(judge == 1){
								printf("成功\n");
								system("pause");
								AdminMenu();
							}else{
								printf("暂时未有课程\n");
								AdminMenu();
							}
							break;
						}
						case 'd':{
							int judge;
							judge = showUser(s);
							if(judge == 2){
								printf("暂时没有用户注册\n");
							}else if(judge == 1){
								printf("查阅成功\n");
								system("pause");
							}
							AdminMenu();
							break;
						}
						case 'e':{
							gotoxy(57,83); 
							goto restart;
							break;
						}
						case 'f':{
							int i,judge;
							if(L == NULL){
								LinkInfo q = (LinkInfo)malloc(sizeof(LesInfo));
								createSystem(&L);
								FILE* t = fopen("lessonInput.txt","r");
								for(i = 0;i<3;i++){
								LinkInfo q = (LinkInfo)malloc(sizeof(LesInfo));
								judge = insertLessonF(L, q,t);
								if(judge ==1){
									printf("插入成功！\n");
								}else if(judge ==4){
									printf("该课程已经存在\n");
								}
								}
								fclose(t);
								
							}else{
								FILE* t = fopen("lessonInput.txt","r");
								for(i = 0;i<3;i++){
								LinkInfo q = (LinkInfo)malloc(sizeof(LesInfo));
								judge = insertLessonF(L, q,t);
								if(judge ==1){
									printf("插入成功！\n");
								}else if(judge ==4){
									printf("该课程已经存在\n");
								}
								}
								fclose(t);
								
							} 
							
								printf("课程已经全部插入\n");
								AdminMenu();
							
							 
							break;
						} 			  
						default:{
							gotoxy(57,83); 
							printf("输入错误，请重新输入!");
							Sleep(1000); 
							goto Adminrst;
							break;
						} 
						}
					}
				}else{
					system("cls");
					gotoxy(49,82);
				printf("密码错误\n");
				for(i=0;i<=15;i++){
					printf("\n");
					}
					goto restart;
				}
				} 
				break;
			
			case 'd':{
					system("cls");
					 gotoxy(57,84);
					 printf("现在退出系统");
					 for(i=0;i<=15;i++){
						printf("\n");
						}
					FILE * fp;
					fp = fopen("lesson.txt","w");
					Init_file(fp);
					 Sleep(2000);
					 return 0;
				break;
			}
					
			default:gotoxy(57,84); 
					printf("输入错误，请重新输入!");
					Sleep(1000); 
					goto restart;	
					break;
		}	
	}
	 
	return 0;
}



