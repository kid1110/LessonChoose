#include<stdio.h>
#include "lesson.h"
#include <windows.h>
#include <string.h>
#include <stdlib.h>

Status createStudent(stu*L){		//����ѧ������ 
	*L = (stu)malloc(sizeof(student));
	(*L)->next = NULL;
	return TRUE;
}
Status createSystem(LinkInfo *L){		//�����γ�ϵͳϵͳ 
		*L = (LinkInfo)malloc(sizeof(LesInfo));
		(*L)->next = NULL;
		return TRUE;
	
}
Status insertLesson(LesInfo*L,LesInfo* q){	//�γ���Ϣ¼��
	if(!L){
		return SYNOTEXIST;
	}else{
			printf("�����룺\n");		//¼�ÿγ���Ϣ 
			printf("�γ̱��:\n");
			scanf("%d",&(q->lesson.lessonNum)); 
			printf("�γ�����:\n");
			scanf("%s",&(q->lesson.lessonName));
			printf("�Ͽ�ʱ��:\n");
			scanf("%d",&(q->lesson.lessonTime));
			printf("��ʦ����:\n");
			scanf("%s",&(q->lesson.teacherName));
			printf("����ʱ��:\n");
			scanf("%d",&(q->lesson.testTime));
			q->lesson.totalNum = 50;
			q->lesson.chooseNum = 0;
			LesInfo* t = L;
			while(t->next != NULL){
				t = t->next;
				if(t->lesson.lessonNum == q->lesson.lessonNum){
					free(q);
					return LEEXIST;
				}
			}
			q->next = NULL;
			t->next = q;
			FILE* fp;
			fp = fopen("lesson.txt","a");
			fprintf(fp,"\n");
			fprintf(fp,"%d",q->lesson.lessonNum);
			fprintf(fp,"%20s",q->lesson.lessonName);
			fprintf(fp,"%20d",q->lesson.lessonTime);
			fprintf(fp,"%20s",q->lesson.teacherName);
			fprintf(fp,"%20d",q->lesson.testTime);
			fprintf(fp,"%20d",q->lesson.chooseNum);
			fprintf(fp,"%20d",q->lesson.totalNum);
			fclose(fp);
			
			return TRUE;	
		
		
	}	
}
 
Status StudentInform(student*L,student*q){	//������Ϣ¼�� 
	if(!L){
		return STNOTEXIST;
	}else{
		char confine[20];
		printf("�����룺\n");		//¼�ø�����Ϣ 
		printf("���ѧ��:\n");
		scanf("%d",&(q->studentNum));
		printf("�������:\n"); 
		scanf("%s",&(q->studentName));
		printf("����Ա�:\n");
		scanf("%s",&(q->studentSex));
		printf("����������:\n");
		scanf("%s",&(q->password));
		if(strlen(q->password) >20){
			free(q);
			return REGERROR;
		}else{
			printf("���ٴ�ȷ������\n");
			scanf("%s",&confine);
			if(strcmp(confine,q->password) == 0){
				q->LessonNum = 0;
				stu tp = L;
				while(tp->next != NULL){
					tp = tp->next;
					if(tp->studentNum == q->studentNum ){
						free(q);
						return STUEXIST;
						}
				}
				q->next = NULL;
				tp->next = q;
				q->lesnext = (LesInfo*)malloc(sizeof(LesInfo));
				q->lesnext->next = NULL; 
				return TRUE;
			}else{
				free(q);
				return FALSE;
			}	
			}
		
	}
	
}
Status PickLesson(student*L,LesInfo*s,LesInfo*q,int number){	//ͨ�����ѡ�� 
	if(!s){
		return SYNOTEXIST;  
	}else if(!L){ 
		return STNOTEXIST;
	}else{
		int chooseNum;
		printf("������γ̱��:\n");
		scanf("%d",&chooseNum);
		 
		student* t = L->next;
		LesInfo* tp = s;
		while((tp->lesson.lessonNum) != chooseNum){		//�γ̲������ж� 
			
			if(tp->next == NULL){
				return LENOTEXIST; 
			}
			tp = tp->next;
		}
		
		if(tp->lesson.chooseNum >= 50){		//�γ������ж� 
			return LEFULL;
		}
		while(t->studentNum != number){	//��֤�ͻ��ж� 
			t = t->next;
		}
		if(t->LessonNum == 2){		//�γ�ѡ����֤ 
			return CHOSENFULL;
		}
		
		LesInfo*ts = t->lesnext;
		q->lesson.lessonNum = tp->lesson.lessonNum;
		strcpy(q->lesson.lessonName,tp->lesson.lessonName);
		q->lesson.lessonTime = tp->lesson.lessonTime;		
		q->lesson.testTime = tp->lesson.testTime;
		strcpy(q->lesson.teacherName,tp->lesson.teacherName);
		
		while(ts->next != NULL){
			ts = ts->next;
			if(ts->lesson.lessonNum == chooseNum){
				free(q);
				return CHOSEN;
			}
		}
		ts->next = q;
		q->next = NULL;
		t->LessonNum += 1; 
		tp->lesson.chooseNum += 1;
		return TRUE; 
	}
}
Status DeleteChooseLesson(student*L,LesInfo*s,int number){		//ɾ��ѡ����Ϣ 
	if(!s){									//�ж�s�Ƿ���� 
		return SYNOTEXIST;
	}else if(!L){							//�ж�L�Ƿ���� 
		return STNOTEXIST;
	}else{	int updateNum,judge;
			judge = checkSelectLesson(L,s,number);
			if(judge == 0){
				return FALSE;
			}
			printf("������γ̱��\n");
			scanf("%d",&updateNum);
			student* t = L->next;		//��tѰ�ҿͻ� 
			LesInfo* tp = s;
			while(t->studentNum != number){
				t = t->next;
			}
		while((tp->lesson.lessonNum) != updateNum){
			if(tp->next == NULL){
				return LENOTEXIST; 
			}
			tp = tp->next;
		}
		LesInfo* p = t->lesnext;
		LesInfo* q;
		if(p->next == NULL){
			return FALSE;
		}
		if(p->next->next == NULL&&p->next != NULL){
			if(p->next->lesson.lessonNum == updateNum){
				free(p->next);
				p->next = NULL;
				tp->lesson.chooseNum -=1;
				t->LessonNum -= 1;
				return TRUE;
			}
		}else{
		while(p->next != NULL){
			if(p->next->lesson.lessonNum == updateNum){
				q = p->next->next;
				free(p->next);
				p->next = q;
				tp->lesson.chooseNum -= 1;
				t->LessonNum -= 1;
				return TRUE;
			}else{
				p = p->next;
			}
		}
	}
		return FALSE;
		}
}
Status checkTotalLesson(LesInfo*s){		//���Ŀ�ѡ��ѡ�ογ� 
	if(!s||s->next ==NULL){
		return SYNOTEXIST; 
	}else{
		LesInfo* tp = s->next;
		printf("�γ̱��  �γ�����  �Ͽ�ʱ��  ����ʱ��  ��ʦ����  ��ѡ��Ŀ  ��ѡ����\n");
		printf("---------------------------------------------------------------------\n");
		while(tp){
		
		printf("%7d%10s%10d%10d%10s%9d%9d",tp->lesson.lessonNum,tp->lesson.lessonName,tp->lesson.lessonTime,tp->lesson.testTime,tp->lesson.teacherName,tp->lesson.totalNum,tp->lesson.chooseNum);
		printf("\n");
		tp = tp->next;
		}
		printf("---------------------------------------------------------------------\n");
		return TRUE;
	}
}
Status checkSelectLesson(student*L,LesInfo*s,int number){			//�鿴�Ѿ�ѡ��γ�
	 if(!L){
	 	return STNOTEXIST;
	 }else if(!s){
	 	return SYNOTEXIST;
	 }else{
	 	int cnt = 0;
	 	student* tp = L->next;
	 	while(tp->studentNum != number){
	 		tp = tp->next;
		 }
		LesInfo* t = tp->lesnext;
		if(t->next == NULL){
			return FALSE;
		}else{
			printf("�γ̱��  �γ�����  �Ͽ�ʱ��  ����ʱ��  ��ʦ����\n");
		printf("-------------------------------------------------\n");
		while(t->next != NULL){
			cnt++;
			t = t->next; 
			printf("%7d%10s%10d%10d%10s",t->lesson.lessonNum,t->lesson.lessonName,t->lesson.lessonTime,t->lesson.testTime,t->lesson.teacherName);
			printf("\n");
			
		}
		printf("-------------------------------------------------\n");
		printf("��ѡ��%d��\n",cnt-1);
		return TRUE;
		}
	 }
}

 
Status DeleteLesson(LesInfo*s){							//ͨ�����ɾ���γ� 
	if(!s){
		return SYNOTEXIST; 
	}else{
		printf("��������Ҫɾ���Ŀγ̱��:\n");
		int LessonNum;
		scanf("%d",&LessonNum);
		LesInfo* tp = s;
			while(tp->next != NULL){
			if(tp->next->lesson.lessonNum == LessonNum){
				LesInfo* q = tp->next;
				tp->next = q->next;
				free(q);
				return TRUE;
			}else{
				tp = tp->next;
			}	
		}
		return LENOTEXIST;
		
		
	}		
}
Status StudentExist(student*L,int studentNum){
		student*t = L;
		while(t->next != NULL){
			t = t->next;
			if(t->studentNum == studentNum){
				return TRUE;
			}
		}
		return STUNOTEXIST;
	
}

Status CheckPassword(student*s,int number,char password[]){		//������ 
	if(!s){
		return STNOTEXIST;
	}else if(StudentExist(s,number) == 6){
		return STUNOTEXIST;
	}else{
		student*t = s;
		while(t->studentNum != number ){
			t = t->next;
		}
		if(strcmp(t->password,password) != 0){	
			return PASSWORDERROR;
		}else{
			return TRUE;
		}	
	}
}
Status FindLesson(LesInfo*s){		//�����γ� 
	if(!s){
		return SYNOTEXIST;	
	}else{
		int findNum;
		printf("������Ҫ���ҵĿγ̱��:\n");
		scanf("%d",&findNum);
		LesInfo*t = s->next;
		while(t->lesson.lessonNum != findNum){
			if(t->next == NULL){
				return LENOTEXIST;
			}else{
				t =t->next;
			}
		}
		printf("�γ̱��  �γ�����  �Ͽ�ʱ��  ����ʱ��  ��ʦ����  ��ѡ��Ŀ  ��ѡ����\n");
		printf("---------------------------------------------------------------------\n");
		printf("%7d%10s%10d%10d%10s%10d%10d",t->lesson.lessonNum,t->lesson.lessonName,t->lesson.lessonTime,t->lesson.testTime,t->lesson.teacherName,t->lesson.totalNum,t->lesson.chooseNum);
		printf("\n");
		printf("---------------------------------------------------------------------\n");
		return TRUE;
		
	}
	
}
Status showUser(student*s){
	if(!s){
		return STNOTEXIST;
	}else{
		student* tp = s;
		printf("    ѧ��      ����      �Ա�      ѡ������\n");
		printf("-----------------------------------------\n");
		while(tp->next != NULL){
			tp = tp->next;
			printf("%7d%9s%6s%11d",tp->studentNum,tp->studentName,tp->studentSex,tp->LessonNum);
			printf("\n");
					
		}
		printf("-----------------------------------------\n");
		return TRUE;
	}
}
Status insertLessonF(LesInfo*L,LesInfo* q,FILE* tp){		//�ļ�¼�뺯�� 
	if(!L){
		return SYNOTEXIST;	
	}else{	int i;
			
			fscanf(tp,"%d %s %d %s %d %d %d",&(q->lesson.lessonNum),&(q->lesson.lessonName),&(q->lesson.lessonTime),&(q->lesson.teacherName),&(q->lesson.testTime),&(q->lesson.chooseNum),&(q->lesson.totalNum)); 
			
			LesInfo* t = L;
			while(t->next != NULL){
				t = t->next;
				if(t->lesson.lessonNum == q->lesson.lessonNum){
					free(q);
					return LEEXIST;
				}
			}
			q->next = NULL;
			t->next = q;
			return TRUE;	
	}	
}
void gotoxy(int x, int y){   //����ƶ� 
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void menu(){
	int i;
	Sleep(1000);
	system("color 2");
	system("cls");	
	gotoxy(49,80);
	printf("1.ע��\n");
	gotoxy(49,81);
	printf("2.��¼\n");
	gotoxy(49,82);
	printf("3.����Աͨ��\n");
	gotoxy(49,83);
	printf("4.�˳�ϵͳ");
	gotoxy(49,84);
	printf("�����룺\n");  
	for(i=0;i<=15;i++){
		printf("\n");
	}
	gotoxy(57,84);
}
void AdminMenu(){
	int i;
	Sleep(1000);
	system("color 2");
	system("cls");
	gotoxy(49,80);
	printf("1.����α�\t");
	gotoxy(58,80);
	printf("  2.ɾ���α�\n");
	gotoxy(49,81);
	printf("3.��ѯ�α�\t");
	gotoxy(61,81);
	printf("4.�鿴��ע���û�");
	gotoxy(78,81);
	printf("5.����\n");
	gotoxy(49,82);
	printf("6.���ļ�¼��γ�");
	gotoxy(49,83);
	printf("�����룺\n");
	for(i=0;i<=15;i++){
		printf("\n");
	}
	gotoxy(57,83);	
}
void UserMenu(){
	int i;
	Sleep(1000);
	system("color 2");
	system("cls");
	gotoxy(49,80);
	printf("1.��ѯ��ѡ�α�\t");
	printf("2.ѡ��γ�  ");
	printf("3.��ѡ\n");
	gotoxy(49,81);
	printf("4.�鿴��ѡ�γ�\t");
	printf("5.�����γ�  ");
	printf("6.����\n");
	gotoxy(49,82);
	printf("�����룺\n");
	for(i=0;i<=15;i++){
		printf("\n");
	}
	gotoxy(57,82);
}

void loginMenu(){
	system("cls");
	int i;
	system("color 2");
	system("cls");
	gotoxy(49,80);
	printf("ѧ��:\n");
	gotoxy(49,81);
	printf("����:\n");
	for(i=0;i<=15;i++){
		printf("\n");
	}
	gotoxy(55,80);
}
void manageMenu(){
	int i;
	system("cls");
	gotoxy(49,82);
	printf("���������룺\n");
	for(i=0;i<=15;i++){
		printf("\n");
		}
	gotoxy(60,82);
}
void Init_file(FILE* t){
	char a[10] = "�γ̱��";
	char b[10] = "�γ�����";
	char c[10] = "�Ͽ�ʱ��";
	char d[10] = "��ʦ����";
	char e[10] = "����ʱ��";
	char f[10] = "ѡ������";
	char g[10] = "��ѡ��Ŀ";
	
	fprintf(t,"%s",a);
	fprintf(t,"%20s",b);
	fprintf(t,"%20s",c);
	fprintf(t,"%20s",d);
	fprintf(t,"%20s",e);
	fprintf(t,"%20s",f);
	fprintf(t,"%20s",g);  
}

  
