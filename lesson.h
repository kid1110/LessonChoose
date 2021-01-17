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
 *    Multi-Include-Prevent Section										//预处理 
 **************************************************************/
/**************************************************************
 *    Macro Define Section												//宏定义 
 **************************************************************/
 
 
 
 /**************************************************************
 *    Struct Define Section
 **************************************************************/
typedef struct Lesson{
	int lessonNum;			//课程编号 
	int studentNum;			//学生学号
	char lessonName[20];	//课程名字
	int lessonTime;			//上课时间
	char teacherName[15];	//老师姓名
	int testTime;			//考试时间
	int chooseNum;			//选课人数	
	int totalNum;			//可选数目 	 
}Lesson;


typedef struct LesInfo{	//课表信息 
	Lesson lesson;
	struct LesInfo *next;
}LesInfo,*LinkInfo;




typedef struct Student{
	int studentNum;			//学生学号
	char studentName[15];	//学生姓名
	char password[20]; 		//学生密码 
	char studentSex[10];		//'男'为男生，‘女’为女生
	int LessonNum;			//已选课程数量 
	struct Student *next;	//学生指针 
	LesInfo* lesnext;		//课程指针 
}student, *stu;

typedef enum{
	TRUE = 1, FALSE = 0, STNOTEXIST = 2, SYNOTEXIST = 3, LEEXIST = 4, LENOTEXIST = 5,STUNOTEXIST = 6,LEFULL = 7,STUEXIST = 8,REGERROR = 9,PASSWORDERROR=10,CHOSEN = 11,CHOSENFULL = 12		//成功，失败，用户不存在，系统不存在，课程存在，课程不存在 
}Status; 

/**
 *  @name        : Status createSystem(LinkInfo *L);
 *    @description : 创建系统 
 *    @param         L
 *  @notice      : None
 */
Status createSystem(LinkInfo *L);

/**
 *  @name        : Status insertLesson(LesInfo*L,LesInfo*q);
 *    @description : 课程信息录入 
 *    @param         L，q 
 *  @notice      : None
 */
Status insertLesson(LesInfo*L,LesInfo*q);

/**
 *  @name        : Status StudentInform(student*L,student*q);
 *    @description : 录入学生信息 
 *    @param         L，q 
 *  @notice      : None
 */
Status StudentInform(student*L,student*q);
/**
 *  @name        : Status PickLesson(studnet*L,LesInfo*s,int chooseNum,LesInfo*q);
 *    @description : 通过编号选课 
 *    @param         L,s,chooseNum,q
 *  @notice      : None
 */
Status PickLesson(student*L,LesInfo*s,LesInfo*q,int number);
/**
 *  @name        : Status DeleteChooseLesson(studnet*L,LesInfo*s,int upadateNum);
 *    @description : 删除已选课表 
 *    @param         L,s,updateNum
 *  @notice      : None
 */
Status DeleteChooseLesson(student*L,LesInfo*s,int number);
/**
 *  @name        : Status checkTotalLesson(LesInfo*s);
 *    @description : 查看所有课程 
 *    @param         s
 *  @notice      : None
 */
Status checkTotalLesson(LesInfo*s);
/**
 *  @name        : Status checkSelectLesson(studnet*L);
 *    @description : 查看已选课程 
 *    @param         L
 *  @notice      : None
 */
Status checkSelectLesson(student*L,LesInfo*s,int number);
/**
 *  @name        : Status DeleteLesson(LesInfo*s, int LessonNum);
 *    @description : 通过编号删除课程 
 *    @param         s,LessonNum 
 *  @notice      : None
 */
Status DeleteLesson(LesInfo*s);
/**
 *  @name        : Status StudentExist(student*L); 
 *    @description : 监察学生是否存在 
 *    @param         L 
 *  @notice      : None
 */
Status StudentExist(student*L,int studentNum);
/**
 *  @name        : Status StudentExist(student*L,int studentNum); 
 *    @description : 移动光标 
 *    @param         x,y 
 *  @notice      : None
 */
void gotoxy(int x, int y);
/**
 *  @name        :  void menu(); 
 *    @description : 菜单选择 
 *    @param         None 
 *  @notice      : None
 */
 void menu();
 /**
 *  @name        :   Status createStudent(stu*L); 
 *    @description : 学生通道 
 *    @param         L
 *  @notice      : None
 */
 Status createStudent(stu*L);
  /**
 *  @name        :    void AdminMenu(); 
 *    @description : 管理员界面 
 *    @param         None
 *  @notice      : None
 */
 void AdminMenu();
  /**
 *  @name        :    void UserMenu();
 *    @description : 用户界面 
 *    @param         None
 *  @notice      : None
 */
 void UserMenu();
   /**
 *  @name        :     void CheckPassword(student*s,int number,char password[]); 
 *    @description : 密码校验 
 *    @param         None
 *  @notice      : None
 */
 Status CheckPassword(student*s,int number,char password[]);
    /**
 *  @name        :     void loginMenu();  
 *    @description : 登录菜单 
 *    @param         None
 *  @notice      : None
 */
 void loginMenu();
    /**
 *  @name        :      void manageMenu(); 
 *    @description : 管理员验证菜单 
 *    @param         None
 *  @notice      : None
 */
 void manageMenu();
    /**
 *  @name        :       Status FindLesson(LesInfo*s);
 *    @description :   通过编号查找课 
 *    @param         s
 *  @notice      : None
 */
 Status FindLesson(LesInfo*s);
     /**
 *  @name        :        Status showUser(student*s);
 *    @description :   展示用户 
 *    @param         s
 *  @notice      : None
 */
 Status showUser(student*s);
      /**
 *  @name        :         void Init_file(FILE* t);
 *    @description :   文件初始话 
 *    @param         t
 *  @notice      : None
 */
 void Init_file(FILE* t);
       /**
 *  @name        :           Status insertLessonF(LesInfo*L,LesInfo* q,FILE* tp);
 *    @description :   文件输入课程 
 *    @param         L，q,tp 
 *  @notice      : None
 */
 Status insertLessonF(LesInfo*L,LesInfo* q,FILE* tp);
       
#endif
