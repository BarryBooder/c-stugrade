#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>

#define N 20

/*
 * 函数列表
 * void Run(void);                         进入系统函数（装饰用）
 * void Color(short x);                    字体颜色函数（装饰用）
 * void MakeSure(void);                    操作确认函数
 * void PrintData(SG sg);                  数据流输出函数
 * void SortStuName(void);                 姓名排序函数
 * void SortTheAveScore(void);             平均分排序函数
 * void CalTheAveScore(void);              平均分计算函数
 * int MainMenu(void);                     主菜单模块
 * void AddStuGrade(void);                 录入学生成绩模块
 * void ShowStuGrade(void);                浏览学生成绩模块
 * void NoSortTheAveScore(void);           没有排序的平均分输出模块
 * void TheAveScore(void);                 有排序的平均分输出模块
 * void StuGradeRank(void);                带名次的平均分输出模块
*/

typedef struct StuGrade {
    char name[N];     //学生姓名
    char sub[3][N];      //科目
    int score[3];       //成绩
    double avg;            //平均分
} SG;
SG sg[N];

void Run(void);

void Color(short x);

void MakeSure(void);

void PrintData(SG sg);

void SortStuName(void);

void SortTheAveScore(void);

void CalTheAveScore(void);

int MainMenu(void);

void AddStuGrade(void);

void ShowStuGrade(void);

void NoSortTheAveScore(void);

void TheAveScore(void);

void StuGradeRank(void);

void Run(void){
    printf("学生成绩管理系统正在启动中……\n");
    char arr[102] = {'\0'};
    int n = 100, i = 0;
    while (i <= n){
        arr[i] = '=';
        printf("[%1s]\r%d%% ", arr, i);
        i++;
        Sleep(10);
    }
    printf("\n");
    MainMenu();
}

void Color(short x) //自定义函根据参数改变颜色
{
    if (x >= 0 && x <= 15)//参数在0-15的范围颜色
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);    //只有一个参数，改变字体颜色
    else//默认的颜色白色
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

//防止不小心点入学生成绩录入模块，加入一个确认模块
void MakeSure(void) {
    printf("确认开始录入学生成绩请按下【Y】，返回主菜单请按下【N】\n");
    int choiceIn;
    do
        choiceIn = getch();
    while ((choiceIn = toupper(choiceIn)) != 'Y' && choiceIn != 'N');
    choiceIn == 'Y' ? AddStuGrade() : MainMenu();
}

//这里的变量“sg”会覆盖全局变量“sg”，不影响程序运行，要分清调用
void PrintData(SG sg) {
    printf("学生姓名：%5s\n", sg.name);
    for (int j = 0; j < 3; ++j) {
        printf("科目：%8s 成绩：%6d\n", sg.sub[j], sg.score[j]);
    }
    printf("\n");
}

void SortStuName(void) {
    SG TempSG;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (strcmp(sg[j].name, sg[j + 1].name) > 0) {
                TempSG = sg[j];
                sg[j] = sg[j + 1];
                sg[j + 1] = TempSG;
            }
        }
    }
}

void SortTheAveScore(void){
    SG TempSg;

    for (int i = 0; i < N - 1; ++i) {
        for (int j = 0; j < N - i; ++j) {
            if (sg[j].avg < sg[j + 1].avg) {
                TempSg = sg[j];
                sg[j] = sg[j + 1];
                sg[j + 1] = TempSg;
            }
        }
    }
}

void CalTheAveScore(void) {
    int sum = 0;

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 3; ++j) {
            sum += sg[i].score[j];
            sg[i].avg = sum / 3.0;
        }
        sum = 0;
    }
}

int MainMenu(void) {
    while (1) {
        system("cls");
        int MainMenuButton;

        printf("---功能菜单---\n");
        printf("1.录入学生成绩\n");
        printf("2.浏览学生成绩\n");
        printf("3.查看学生成绩平均分\n");
        printf("4.排序学生成绩\n");
        printf("5.带排名排序学生成绩\n");
        printf("6.退出管理系统\n");
        printf("-------------\n");
        printf("请选择：\n");

        MainMenuButton = getch() - '0';
        system("cls");
        if (MainMenuButton == 0) break;
        else {
            switch (MainMenuButton) {
                case 1:
                    MakeSure();
                    break;
                case 2:
                    ShowStuGrade();
                    break;
                case 3:
                    NoSortTheAveScore();
                    break;
                case 4:
                    TheAveScore();
                    break;
                case 5:
                    StuGradeRank();
                    break;
                case 6:
                    exit(1);
                default:
                    printf("请输入0-5之间的数字！\n");
                    system("pause");
                    break;
            }
        }
    }
}

void AddStuGrade(void) {
    for (int i = 0; i < 10; ++i) {
        system("cls");
        printf("请输入学生姓名：\n");
        scanf("%s", sg[i].name);
        printf("\n");
        for (int j = 0; j < 3; j++) {
            printf("请输入科目 %d：\n", j + 1);
            scanf("%s", sg[i].sub[j]);
            printf("请输入科目 %d 的成绩：\n", j + 1);
            scanf("%d", &sg[i].score[j]);
            printf("\n");
            Color(1);
            printf("系统：第 %d 条信息已录入\n\n", j + 1);
            Color(15);
        }
        printf("输入【Y】以继续录入，输入【N】返回主菜单\n");
        int choiceIn;
        do
            choiceIn = getch();
        while ((choiceIn = toupper(choiceIn)) != 'Y' && choiceIn != 'N');
        choiceIn == 'Y' ? i = i : MainMenu();
    }
}

void ShowStuGrade(void) {
    system("cls");

    SortStuName();
    printf("查询到的结果为:\n");
    for (int i = 0; i < N; ++i) {
        if (0 < strlen(sg[i].name)) {
            PrintData(sg[i]);
        }
    }
    printf("\n");
    printf("请按下【任意按键】返回主菜单……");
    if (getch()) MainMenu();
}

void NoSortTheAveScore(void) {
    system("cls");

    CalTheAveScore();
    printf("查询到的结果为:\n");
    for (int i = 0; i < N; ++i) {
        if (0 < strlen(sg[i].name)) {
            printf("%5s 的平均成绩：%.2lf\n", sg[i].name, sg[i].avg);
        }
    }
    printf("\n");
    printf("请按下【任意按键】返回主菜单……");
    if (getch()) MainMenu();
}

void TheAveScore(void) {
    system("cls");

    CalTheAveScore();
    SortTheAveScore();

    printf("查询到的结果为:\n");
    for (int i = 0; i < N; ++i) {
        if (0 < strlen(sg[i].name)) {
            printf("%5s 的平均成绩：%.2lf\n", sg[i].name, sg[i].avg);
        }
    }
    printf("\n");
    printf("请按下【任意按键】返回主菜单……");
    if (getch()) MainMenu();
}

void StuGradeRank(void) {
    system("cls");
    SG TempSg;

    CalTheAveScore();
    SortTheAveScore();

    printf("查询到的结果为:\n");
    for (int i = 0; i < N; ++i) {
        if (0 < strlen(sg[i].name)) {
            printf("%5s 的平均成绩：%10.2lf 名次：%5d\n", sg[i].name, sg[i].avg, i + 1);
        }
    }
    printf("\n");
    printf("请按下【任意按键】返回主菜单……");
    if (getch()) MainMenu();
}

int main(void) {
    Run();
    return -1;
}
