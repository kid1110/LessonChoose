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
	printf("��ӭ����ѡ��ϵͳ");
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
						printf("ע��ɹ�!\n");
						menu();
					}else if(judge == 0){
						printf("���벻һ��\n");
						menu();
						
					}else if(judge == 9){
						printf("���볤�Ȳ��ܴ���20\n");
						menu();
					}else if(judge == 8){
						printf("���û��Ѵ���\n");
						menu();
					}
				}else{
					judge = StudentInform(s,t);
					if(judge == 1){
						printf("ע��ɹ�!\n");
						menu();
					}else if(judge == 0){
						printf("���벻һ��\n");
						menu();
						
					}else if(judge == 9){
						printf("���볤�Ȳ��ܴ���20\n");
						menu();
					}else if(judge == 8){
						printf("���û��Ѵ���\n");
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
					printf("���û�������\n");
					goto restart;
				}else if(judge == 10){
					printf("�������\n");
					goto restart;
				}else if(judge == 2){
					printf("��û���û�����ע��\n");
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
										printf("���ĳɹ�\n");
										system("pause");
										UserMenu();
									}else{
										printf("����Ա��û�з��ÿγ�\n");
										UserMenu();
									}
									break;
							}
							case 'b':{
								int judge;
								LesInfo* t = (LesInfo*)malloc(sizeof(LesInfo));
								judge = PickLesson(s,L,t,number);
								if(judge == 3){
									printf("��ʱδ�пγ̿���ѡ��\n");
								}else if(judge == 5){
									printf("�ÿγ̲�����");
								}else if(judge == 1){
									printf("ѡ��ɹ�");
								}else if(judge == 7){
									printf("�ÿγ��Ѿ�������\n");
								}else if(judge == 11){
									printf("�������ظ�ѡ��\n"); 
								}else if(judge == 12){
									printf("���Ѿ�����ѡ����\n"); 
								}
								UserMenu();
								break;
							}
							case 'c': {
								int judge;
								judge = DeleteChooseLesson(s,L,number);
								if(judge == 3){
									printf("��ʱδ�пγ̿���ѡ��\n");
								}else if(judge == 5){
									printf("�ÿγ̲�����\n");
								}else if(judge == 0){
									printf("�㲢û��ѡ��ÿγ�\n");
								}else if (judge == 1){
									printf("ɾ���ɹ�\n");
								}
								UserMenu();
								break;
							}
							case 'd':{
								int judge;
								judge = checkSelectLesson(s,L,number);
								if(judge == 3){
									printf("��ʱδ�пγ̷���\n");
								}else if(judge == 0){
									printf("�㲢û��ѡ��γ�\n");
								}else if(judge == 1){
									printf("���ĳɹ�");
								}
								system("pause");
								UserMenu();
								break;
							}
							case 'e':{		//��Ų��ҿγ�ģ�� 
								int judge;
								judge =  FindLesson(L);
								if(judge == 3){
									printf("��ʱδ�пγ̷���\n");
								}else if(judge == 5){
									printf("�ÿγ̲�����\n");	
								}else if(judge == 1){
									printf("���ҳɹ�\n");
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
								printf("�����������������!");
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
									printf("����ɹ�");
									AdminMenu(); 
								}else if(judge == 0){
									printf("����ʧ��");
									AdminMenu();
								}else if(judge ==4){
									printf("�ÿγ��Ѵ���");
									AdminMenu();
								}
							}else{
								judge = insertLesson(L,q);
								if(judge == 1){
									printf("����ɹ�"); 
									AdminMenu();
								}else if(judge == 0){
									printf("����ʧ��");
									AdminMenu();
								}else if(judge == 4){
									printf("�ÿγ��Ѵ���");
									AdminMenu(); 
								}
							}
							break;
						}
						case 'b':{
							int judge;
							judge = DeleteLesson(L);
							if(judge == 3){
								printf("��ʱδ�пγ�\n");
								AdminMenu();
							}else if(judge == 5){
								printf("�ÿγ̲�����\n");
								AdminMenu();
							}else if(judge == 1){
								printf("ɾ���ɹ�\n");
								AdminMenu();
							}  
							break;
						}
						case 'c':{
							int judge;
							judge = checkTotalLesson(L);
							if(judge == 1){
								printf("�ɹ�\n");
								system("pause");
								AdminMenu();
							}else{
								printf("��ʱδ�пγ�\n");
								AdminMenu();
							}
							break;
						}
						case 'd':{
							int judge;
							judge = showUser(s);
							if(judge == 2){
								printf("��ʱû���û�ע��\n");
							}else if(judge == 1){
								printf("���ĳɹ�\n");
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
									printf("����ɹ���\n");
								}else if(judge ==4){
									printf("�ÿγ��Ѿ�����\n");
								}
								}
								fclose(t);
								
							}else{
								FILE* t = fopen("lessonInput.txt","r");
								for(i = 0;i<3;i++){
								LinkInfo q = (LinkInfo)malloc(sizeof(LesInfo));
								judge = insertLessonF(L, q,t);
								if(judge ==1){
									printf("����ɹ���\n");
								}else if(judge ==4){
									printf("�ÿγ��Ѿ�����\n");
								}
								}
								fclose(t);
								
							} 
							
								printf("�γ��Ѿ�ȫ������\n");
								AdminMenu();
							
							 
							break;
						} 			  
						default:{
							gotoxy(57,83); 
							printf("�����������������!");
							Sleep(1000); 
							goto Adminrst;
							break;
						} 
						}
					}
				}else{
					system("cls");
					gotoxy(49,82);
				printf("�������\n");
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
					 printf("�����˳�ϵͳ");
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
					printf("�����������������!");
					Sleep(1000); 
					goto restart;	
					break;
		}	
	}
	 
	return 0;
}



