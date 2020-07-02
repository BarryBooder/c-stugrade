#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>

#define N 20

/*
 * �����б�
 * void Run(void);                         ����ϵͳ������װ���ã�
 * void Color(short x);                    ������ɫ������װ���ã�
 * void MakeSure(void);                    ����ȷ�Ϻ���
 * void PrintData(SG sg);                  �������������
 * void SortStuName(void);                 ����������
 * void SortTheAveScore(void);             ƽ����������
 * void CalTheAveScore(void);              ƽ���ּ��㺯��
 * int MainMenu(void);                     ���˵�ģ��
 * void AddStuGrade(void);                 ¼��ѧ���ɼ�ģ��
 * void ShowStuGrade(void);                ���ѧ���ɼ�ģ��
 * void NoSortTheAveScore(void);           û�������ƽ�������ģ��
 * void TheAveScore(void);                 �������ƽ�������ģ��
 * void StuGradeRank(void);                �����ε�ƽ�������ģ��
*/

typedef struct StuGrade {
    char name[N];     //ѧ������
    char sub[3][N];      //��Ŀ
    int score[3];       //�ɼ�
    double avg;            //ƽ����
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
    printf("ѧ���ɼ�����ϵͳ���������С���\n");
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

void Color(short x) //�Զ��庯���ݲ����ı���ɫ
{
    if (x >= 0 && x <= 15)//������0-15�ķ�Χ��ɫ
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);    //ֻ��һ���������ı�������ɫ
    else//Ĭ�ϵ���ɫ��ɫ
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

//��ֹ��С�ĵ���ѧ���ɼ�¼��ģ�飬����һ��ȷ��ģ��
void MakeSure(void) {
    printf("ȷ�Ͽ�ʼ¼��ѧ���ɼ��밴�¡�Y�����������˵��밴�¡�N��\n");
    int choiceIn;
    do
        choiceIn = getch();
    while ((choiceIn = toupper(choiceIn)) != 'Y' && choiceIn != 'N');
    choiceIn == 'Y' ? AddStuGrade() : MainMenu();
}

//����ı�����sg���Ḳ��ȫ�ֱ�����sg������Ӱ��������У�Ҫ�������
void PrintData(SG sg) {
    printf("ѧ��������%5s\n", sg.name);
    for (int j = 0; j < 3; ++j) {
        printf("��Ŀ��%8s �ɼ���%6d\n", sg.sub[j], sg.score[j]);
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

        printf("---���ܲ˵�---\n");
        printf("1.¼��ѧ���ɼ�\n");
        printf("2.���ѧ���ɼ�\n");
        printf("3.�鿴ѧ���ɼ�ƽ����\n");
        printf("4.����ѧ���ɼ�\n");
        printf("5.����������ѧ���ɼ�\n");
        printf("6.�˳�����ϵͳ\n");
        printf("-------------\n");
        printf("��ѡ��\n");

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
                    printf("������0-5֮������֣�\n");
                    system("pause");
                    break;
            }
        }
    }
}

void AddStuGrade(void) {
    for (int i = 0; i < 10; ++i) {
        system("cls");
        printf("������ѧ��������\n");
        scanf("%s", sg[i].name);
        printf("\n");
        for (int j = 0; j < 3; j++) {
            printf("�������Ŀ %d��\n", j + 1);
            scanf("%s", sg[i].sub[j]);
            printf("�������Ŀ %d �ĳɼ���\n", j + 1);
            scanf("%d", &sg[i].score[j]);
            printf("\n");
            Color(1);
            printf("ϵͳ���� %d ����Ϣ��¼��\n\n", j + 1);
            Color(15);
        }
        printf("���롾Y���Լ���¼�룬���롾N���������˵�\n");
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
    printf("��ѯ���Ľ��Ϊ:\n");
    for (int i = 0; i < N; ++i) {
        if (0 < strlen(sg[i].name)) {
            PrintData(sg[i]);
        }
    }
    printf("\n");
    printf("�밴�¡����ⰴ�����������˵�����");
    if (getch()) MainMenu();
}

void NoSortTheAveScore(void) {
    system("cls");

    CalTheAveScore();
    printf("��ѯ���Ľ��Ϊ:\n");
    for (int i = 0; i < N; ++i) {
        if (0 < strlen(sg[i].name)) {
            printf("%5s ��ƽ���ɼ���%.2lf\n", sg[i].name, sg[i].avg);
        }
    }
    printf("\n");
    printf("�밴�¡����ⰴ�����������˵�����");
    if (getch()) MainMenu();
}

void TheAveScore(void) {
    system("cls");

    CalTheAveScore();
    SortTheAveScore();

    printf("��ѯ���Ľ��Ϊ:\n");
    for (int i = 0; i < N; ++i) {
        if (0 < strlen(sg[i].name)) {
            printf("%5s ��ƽ���ɼ���%.2lf\n", sg[i].name, sg[i].avg);
        }
    }
    printf("\n");
    printf("�밴�¡����ⰴ�����������˵�����");
    if (getch()) MainMenu();
}

void StuGradeRank(void) {
    system("cls");
    SG TempSg;

    CalTheAveScore();
    SortTheAveScore();

    printf("��ѯ���Ľ��Ϊ:\n");
    for (int i = 0; i < N; ++i) {
        if (0 < strlen(sg[i].name)) {
            printf("%5s ��ƽ���ɼ���%10.2lf ���Σ�%5d\n", sg[i].name, sg[i].avg, i + 1);
        }
    }
    printf("\n");
    printf("�밴�¡����ⰴ�����������˵�����");
    if (getch()) MainMenu();
}

int main(void) {
    Run();
    return -1;
}
