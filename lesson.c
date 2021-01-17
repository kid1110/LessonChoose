#include<stdio.h>
#include "lesson.h"
#include <windows.h>
#include <string.h>
#include <stdlib.h>

Status createStudent(stu*L){		//创建学生链表 
	*L = (stu)malloc(sizeof(student));
	(*L)->next = NULL;
	return TRUE;
}
Status createSystem(LinkInfo *L){		//创建课程系统系统 
		*L = (LinkInfo)malloc(sizeof(LesInfo));
		(*L)->next = NULL;
		return TRUE;
	
}
Status insertLesson(LesInfo*L,LesInfo* q){	//课程信息录入
	if(!L){
		return SYNOTEXIST;
	}else{
			printf("请输入：\n");		//录用课程信息 
			printf("课程编号:\n");
			scanf("%d",&(q->lesson.lessonNum)); 
			printf("课程名字:\n");
			scanf("%s",&(q->lesson.lessonName));
			printf("上课时间:\n");
			scanf("%d",&(q->lesson.lessonTime));
			printf("老师姓名:\n");
			scanf("%s",&(q->lesson.teacherName));
			printf("考试时间:\n");
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
 
Status StudentInform(student*L,student*q){	//个人信息录入 
	if(!L){
		return STNOTEXIST;
	}else{
		char confine[20];
		printf("请输入：\n");		//录用个人信息 
		printf("你的学号:\n");
		scanf("%d",&(q->studentNum));
		printf("你的名字:\n"); 
		scanf("%s",&(q->studentName));
		printf("你的性别:\n");
		scanf("%s",&(q->studentSex));
		printf("请输入密码:\n");
		scanf("%s",&(q->password));
		if(strlen(q->password) >20){
			free(q);
			return REGERROR;
		}else{
			printf("请再次确认密码\n");
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
Status PickLesson(student*L,LesInfo*s,LesInfo*q,int number){	//通过编号选课 
	if(!s){
		return SYNOTEXIST;  
	}else if(!L){ 
		return STNOTEXIST;
	}else{
		int chooseNum;
		printf("请输入课程编号:\n");
		scanf("%d",&chooseNum);
		 
		student* t = L->next;
		LesInfo* tp = s;
		while((tp->lesson.lessonNum) != chooseNum){		//课程不存在判断 
			
			if(tp->next == NULL){
				return LENOTEXIST; 
			}
			tp = tp->next;
		}
		
		if(tp->lesson.chooseNum >= 50){		//课程满人判断 
			return LEFULL;
		}
		while(t->studentNum != number){	//验证客户判断 
			t = t->next;
		}
		if(t->LessonNum == 2){		//课程选满验证 
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
Status DeleteChooseLesson(student*L,LesInfo*s,int number){		//删除选课信息 
	if(!s){									//判断s是否存在 
		return SYNOTEXIST;
	}else if(!L){							//判断L是否存在 
		return STNOTEXIST;
	}else{	int updateNum,judge;
			judge = checkSelectLesson(L,s,number);
			if(judge == 0){
				return FALSE;
			}
			printf("请输入课程编号\n");
			scanf("%d",&updateNum);
			student* t = L->next;		//用t寻找客户 
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
Status checkTotalLesson(LesInfo*s){		//查阅可选的选课课程 
	if(!s||s->next ==NULL){
		return SYNOTEXIST; 
	}else{
		LesInfo* tp = s->next;
		printf("课程编号  课程名字  上课时间  考试时间  老师姓名  可选数目  已选人数\n");
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
Status checkSelectLesson(student*L,LesInfo*s,int number){			//查看已经选择课程
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
			printf("课程编号  课程名字  上课时间  考试时间  老师姓名\n");
		printf("-------------------------------------------------\n");
		while(t->next != NULL){
			cnt++;
			t = t->next; 
			printf("%7d%10s%10d%10d%10s",t->lesson.lessonNum,t->lesson.lessonName,t->lesson.lessonTime,t->lesson.testTime,t->lesson.teacherName);
			printf("\n");
			
		}
		printf("-------------------------------------------------\n");
		printf("共选课%d门\n",cnt-1);
		return TRUE;
		}
	 }
}

 
Status DeleteLesson(LesInfo*s){							//通过编号删除课程 
	if(!s){
		return SYNOTEXIST; 
	}else{
		printf("请输入想要删除的课程编号:\n");
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

Status CheckPassword(student*s,int number,char password[]){		//密码检测 
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
Status FindLesson(LesInfo*s){		//搜索课程 
	if(!s){
		return SYNOTEXIST;	
	}else{
		int findNum;
		printf("请输入要查找的课程编号:\n");
		scanf("%d",&findNum);
		LesInfo*t = s->next;
		while(t->lesson.lessonNum != findNum){
			if(t->next == NULL){
				return LENOTEXIST;
			}else{
				t =t->next;
			}
		}
		printf("课程编号  课程名字  上课时间  考试时间  老师姓名  可选数目  已选人数\n");
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
		printf("    学号      名字      性别      选课数量\n");
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
Status insertLessonF(LesInfo*L,LesInfo* q,FILE* tp){		//文件录入函数 
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
void gotoxy(int x, int y){   //光标移动 
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
	printf("1.注册\n");
	gotoxy(49,81);
	printf("2.登录\n");
	gotoxy(49,82);
	printf("3.管理员通道\n");
	gotoxy(49,83);
	printf("4.退出系统");
	gotoxy(49,84);
	printf("请输入：\n");  
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
	printf("1.插入课表\t");
	gotoxy(58,80);
	printf("  2.删除课表\n");
	gotoxy(49,81);
	printf("3.查询课表\t");
	gotoxy(61,81);
	printf("4.查看已注册用户");
	gotoxy(78,81);
	printf("5.返回\n");
	gotoxy(49,82);
	printf("6.从文件录入课程");
	gotoxy(49,83);
	printf("请输入：\n");
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
	printf("1.查询可选课表\t");
	printf("2.选择课程  ");
	printf("3.退选\n");
	gotoxy(49,81);
	printf("4.查看已选课程\t");
	printf("5.搜索课程  ");
	printf("6.返回\n");
	gotoxy(49,82);
	printf("请输入：\n");
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
	printf("学号:\n");
	gotoxy(49,81);
	printf("密码:\n");
	for(i=0;i<=15;i++){
		printf("\n");
	}
	gotoxy(55,80);
}
void manageMenu(){
	int i;
	system("cls");
	gotoxy(49,82);
	printf("请输入密码：\n");
	for(i=0;i<=15;i++){
		printf("\n");
		}
	gotoxy(60,82);
}
void Init_file(FILE* t){
	char a[10] = "课程编号";
	char b[10] = "课程名字";
	char c[10] = "上课时间";
	char d[10] = "老师名字";
	char e[10] = "考试时间";
	char f[10] = "选课人数";
	char g[10] = "可选数目";
	
	fprintf(t,"%s",a);
	fprintf(t,"%20s",b);
	fprintf(t,"%20s",c);
	fprintf(t,"%20s",d);
	fprintf(t,"%20s",e);
	fprintf(t,"%20s",f);
	fprintf(t,"%20s",g);  
}

  
