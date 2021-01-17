/***************************************************************************************
 *    File Name                :    lesson.h
 *    CopyRight                :
 *
 *    SYSTEM                    :   
 *    Create Data                :    2020.11.13
 *    Author/Corportation        :   wcq,oyl,lhl,mzh,lzm
 *
 *
 *--------------------------------Revision History--------------------------------------
 *    No    version        Data            Revised By            Item            Description
 *
 *
 ***************************************************************************************/
#ifndef _LESSON_H
#define _LESSON_H
/**************************************************************
 *    Multi-Include-Prevent Section										//Ԥ���� 
 **************************************************************/
/**************************************************************
 *    Macro Define Section												//�궨�� 
 **************************************************************/
 
 
 
 /**************************************************************
 *    Struct Define Section
 **************************************************************/
typedef struct Lesson{
	int lessonNum;			//�γ̱�� 
	int studentNum;			//ѧ��ѧ��
	char lessonName[20];	//�γ�����
	int lessonTime;			//�Ͽ�ʱ��
	char teacherName[15];	//��ʦ����
	int testTime;			//����ʱ��
	int chooseNum;			//ѡ������	
	int totalNum;			//��ѡ��Ŀ 	 
}Lesson;


typedef struct LesInfo{	//�α���Ϣ 
	Lesson lesson;
	struct LesInfo *next;
}LesInfo,*LinkInfo;




typedef struct Student{
	int studentNum;			//ѧ��ѧ��
	char studentName[15];	//ѧ������
	char password[20]; 		//ѧ������ 
	char studentSex[10];		//'��'Ϊ��������Ů��ΪŮ��
	int LessonNum;			//��ѡ�γ����� 
	struct Student *next;	//ѧ��ָ�� 
	LesInfo* lesnext;		//�γ�ָ�� 
}student, *stu;

typedef enum{
	TRUE = 1, FALSE = 0, STNOTEXIST = 2, SYNOTEXIST = 3, LEEXIST = 4, LENOTEXIST = 5,STUNOTEXIST = 6,LEFULL = 7,STUEXIST = 8,REGERROR = 9,PASSWORDERROR=10,CHOSEN = 11,CHOSENFULL = 12		//�ɹ���ʧ�ܣ��û������ڣ�ϵͳ�����ڣ��γ̴��ڣ��γ̲����� 
}Status; 

/**
 *  @name        : Status createSystem(LinkInfo *L);
 *    @description : ����ϵͳ 
 *    @param         L
 *  @notice      : None
 */
Status createSystem(LinkInfo *L);

/**
 *  @name        : Status insertLesson(LesInfo*L,LesInfo*q);
 *    @description : �γ���Ϣ¼�� 
 *    @param         L��q 
 *  @notice      : None
 */
Status insertLesson(LesInfo*L,LesInfo*q);

/**
 *  @name        : Status StudentInform(student*L,student*q);
 *    @description : ¼��ѧ����Ϣ 
 *    @param         L��q 
 *  @notice      : None
 */
Status StudentInform(student*L,student*q);
/**
 *  @name        : Status PickLesson(studnet*L,LesInfo*s,int chooseNum,LesInfo*q);
 *    @description : ͨ�����ѡ�� 
 *    @param         L,s,chooseNum,q
 *  @notice      : None
 */
Status PickLesson(student*L,LesInfo*s,LesInfo*q,int number);
/**
 *  @name        : Status DeleteChooseLesson(studnet*L,LesInfo*s,int upadateNum);
 *    @description : ɾ����ѡ�α� 
 *    @param         L,s,updateNum
 *  @notice      : None
 */
Status DeleteChooseLesson(student*L,LesInfo*s,int number);
/**
 *  @name        : Status checkTotalLesson(LesInfo*s);
 *    @description : �鿴���пγ� 
 *    @param         s
 *  @notice      : None
 */
Status checkTotalLesson(LesInfo*s);
/**
 *  @name        : Status checkSelectLesson(studnet*L);
 *    @description : �鿴��ѡ�γ� 
 *    @param         L
 *  @notice      : None
 */
Status checkSelectLesson(student*L,LesInfo*s,int number);
/**
 *  @name        : Status DeleteLesson(LesInfo*s, int LessonNum);
 *    @description : ͨ�����ɾ���γ� 
 *    @param         s,LessonNum 
 *  @notice      : None
 */
Status DeleteLesson(LesInfo*s);
/**
 *  @name        : Status StudentExist(student*L); 
 *    @description : ���ѧ���Ƿ���� 
 *    @param         L 
 *  @notice      : None
 */
Status StudentExist(student*L,int studentNum);
/**
 *  @name        : Status StudentExist(student*L,int studentNum); 
 *    @description : �ƶ���� 
 *    @param         x,y 
 *  @notice      : None
 */
void gotoxy(int x, int y);
/**
 *  @name        :  void menu(); 
 *    @description : �˵�ѡ�� 
 *    @param         None 
 *  @notice      : None
 */
 void menu();
 /**
 *  @name        :   Status createStudent(stu*L); 
 *    @description : ѧ��ͨ�� 
 *    @param         L
 *  @notice      : None
 */
 Status createStudent(stu*L);
  /**
 *  @name        :    void AdminMenu(); 
 *    @description : ����Ա���� 
 *    @param         None
 *  @notice      : None
 */
 void AdminMenu();
  /**
 *  @name        :    void UserMenu();
 *    @description : �û����� 
 *    @param         None
 *  @notice      : None
 */
 void UserMenu();
   /**
 *  @name        :     void CheckPassword(student*s,int number,char password[]); 
 *    @description : ����У�� 
 *    @param         None
 *  @notice      : None
 */
 Status CheckPassword(student*s,int number,char password[]);
    /**
 *  @name        :     void loginMenu();  
 *    @description : ��¼�˵� 
 *    @param         None
 *  @notice      : None
 */
 void loginMenu();
    /**
 *  @name        :      void manageMenu(); 
 *    @description : ����Ա��֤�˵� 
 *    @param         None
 *  @notice      : None
 */
 void manageMenu();
    /**
 *  @name        :       Status FindLesson(LesInfo*s);
 *    @description :   ͨ����Ų��ҿ� 
 *    @param         s
 *  @notice      : None
 */
 Status FindLesson(LesInfo*s);
     /**
 *  @name        :        Status showUser(student*s);
 *    @description :   չʾ�û� 
 *    @param         s
 *  @notice      : None
 */
 Status showUser(student*s);
      /**
 *  @name        :         void Init_file(FILE* t);
 *    @description :   �ļ���ʼ�� 
 *    @param         t
 *  @notice      : None
 */
 void Init_file(FILE* t);
       /**
 *  @name        :           Status insertLessonF(LesInfo*L,LesInfo* q,FILE* tp);
 *    @description :   �ļ�����γ� 
 *    @param         L��q,tp 
 *  @notice      : None
 */
 Status insertLessonF(LesInfo*L,LesInfo* q,FILE* tp);
       
#endif
