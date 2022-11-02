#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define MAX_X 50
#define MAX_Y 24
#define DIR_LEFT 75
#define DIR_RIGHT 77
#define STAR_NUM 30

typedef struct _star{
    int x,y;
    int speed;
}star;

void gotoxy(int x, int y){
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void ReSizeConsole(int w, int h){
    char chTemp[30];
    sprintf(chTemp,"mode con cols=%d lines=%d",w,h);
    system(chTemp);
}

void ClearCursor(){
    CONSOLE_CURSOR_INFO c = {0};
    c.dwSize = 1;
    c.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&c);
}

void DisplayStart(){
    while(1){
        if(_kbhit()){
            _getch();
            break;
        }

        gotoxy(MAX_X/5, MAX_Y/2);
        printf("�����Ϸ��� �ƹ�Ű�� ��������!");
        Sleep(500);
        gotoxy(MAX_X/5, MAX_Y/2);
        printf("                                  ");
        Sleep(500);
    }

}

void DisplayGameScreen(){
    for(int y = 2; y < MAX_Y; y++){
        for(int x = 0; x < MAX_X; x += 2){
            if( x == 0 || y == 2 || x ==MAX_X-2 || y == MAX_Y -1){
                gotoxy(x, y);
                printf("��");
            }

            else{
                gotoxy(x,y);
                printf("  ");
            }
        }
    }
}
void setPlayerPosition(int x, int dir){
    if(dir == DIR_LEFT){
        gotoxy(x+1,MAX_Y-2);
        printf("  ");
    }

    else if(dir == DIR_RIGHT){
        gotoxy(x-1, MAX_Y-2);
        printf("  ");
    }
    gotoxy(x,MAX_Y-2);
    printf("��");
}

void DisplayScore(int sc){
    gotoxy(MAX_X/2, 1);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x60);
    printf("Score : %2d",sc);
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0x0F);
}

void initStar(star *s){
    for(int i = 0; i <STAR_NUM; i++){
        s[i].y = 3;
        s[i].x = rand()%46 + 2; // 2 ~ 47
        s[i].speed = rand()%20 + 10; // 10 ~ 29
    }
}

void DisplayStar(star * s, int cnt){
    for(int i = 0; i<STAR_NUM; i++){
        if(s[i].y > 3 && cnt%s[i].speed == 0){
            gotoxy(s[i].x, s[i]. y-1);
            printf(" ");
        }
        if(s[i].y > MAX_Y-2 && cnt%s[i].speed == 0){
            s[i].y = 3;
            s[i].x = rand()%46 + 2; // 2 ~ 47
            s[i].speed = rand()%20 + 10; // 10 ~ 29
        }
       else if(cnt%s[i].speed == 0){
            gotoxy(s[i].x,s[i].y);
            printf("*");
            s[i].y++;
        }
    }
}

int CheckCursh(star *s, int x)
{
    for(int i = 0; i < STAR_NUM; i++){
        if(s[i].y == MAX_Y-2 && (s[i].x == x || s[i].x == x+1))
            return 1;
    }
    return 0;
}

int main(){
    int Player_xPosition = MAX_X/2-1;
    int score = 0;
    int count = 0;

    star s[STAR_NUM];

    srand(time(NULL));
    initStar(s);

    ClearCursor();
    ReSizeConsole(MAX_X,MAX_Y);
    DisplayStart();
    system("cls");

    DisplayGameScreen();
    DisplayScore(score);
    setPlayerPosition(Player_xPosition,0);


    while(1){
        DisplayStar(s,count);
        if(count % 100 == 0){
            DisplayScore(score++);
        }

        if(_kbhit()){
            char key = _getch();
            if(key == DIR_LEFT && Player_xPosition > 2){
                setPlayerPosition(--Player_xPosition,DIR_LEFT);
            }
            else if(key == DIR_RIGHT){
                if(Player_xPosition < MAX_X - 4)
                    setPlayerPosition(++Player_xPosition,DIR_RIGHT);
            }

        }
        if(CheckCursh(s,Player_xPosition)){
            system("cls");
            gotoxy(MAX_X/2-4,MAX_Y/2-1);
            printf("���� ���� !");
            gotoxy(MAX_X/2-4, MAX_Y/2);
            printf("�������� :%2d", score);
            break;
        }
        Sleep(10);
        count++;
    }
    getchar();
}
