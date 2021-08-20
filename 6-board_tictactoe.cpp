#include<graphics.h> /* header file */
#include<stdio.h>
#include<stdlib.h>
#include "string.h"
#include "time.h"
#define d 70                //d=distance
#define s 60                //s=size
#define f 150               //f=display coordinate factor
char b[3][3];
void display(int,int);
int checkWin(int,int,int);
int checkDraw(int,int);

int checkWin(int sx,int sy,int player)
{
    char str[25];
    int i,j;
    for(i=0;i<3;i++)
    {
        if((b[i][0]==b[i][1]&&b[i][0]==b[i][2]&&b[i][0]!=' ')||(b[0][i]==b[1][i]&&b[0][i]==b[2][i]&&b[0][i]!=' '))
        {
            display(sx,sy);
            sprintf(str,"Player %d (%c) Won!!!",player+1,player?'O':'X');
            outtextxy(150,400,str);
            setcolor(RED);
            return(1);
        }
        if((b[0][0]==b[1][1]&&b[1][1]==b[2][2]&&b[2][2]!=' ')||(b[0][2]==b[1][1]&&b[1][1]==b[2][0]&&b[2][0]!=' '))
        {
            display(sx,sy);
            sprintf(str,"Player %d (%c) Won!!!",player+1,player?'O':'X');
            outtextxy(150,400,str);
            setcolor(RED);
            return(1);
        }
    }
    return(0);
}

int checkDraw(int sx,int sy)
{
    int i,j,k=0;
    char str[25];
    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            if(b[i][j]!=' ')
                k++;
    if(k==9)        //All cells are marked but yet no winner i.e. Draw
    {
        display(sx,sy);
        sprintf(str,"The game is draw!!!");
        outtextxy(150,400,str);
        setcolor(RED);
        return(1);
    }
    return(0);
}

void display(int sx, int sy)
{
    int i,j;
    char str[2];
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            if(j==sx&&i==sy)
                setcolor(RED);
            else
                setcolor(BLACK);
            rectangle(j*d+f,i*d+f,j*d+s+f,i*d+s+f);
            sprintf(str,"%c",b[i][j]);               //To print Player's symbol in cell
            outtextxy(j*d+20+f, i*d+20+f, str);
        }
    }
}

int getkey()
{
    int ch;
    ch=getch();
    if(ch==0)
    {
        ch=getch();
        return(ch);
    }
    return(ch);
}

int main()
{
    int gd,gm,sx=0,sy=0,i,j,k,count=2,player;
    char str[25];
    int ch;
    int move;
    int c;
    printf("Board positions are numbered so:\n1 2 3\n4 5 6\n7 8 9\n");
	printf("You have O, Computer has X.\n\n");
	int moves[9];
	for(int i=0;i<9;i++)
        moves[i]=i+1;

    detectgraph(&gd,&gm);
    initgraph(&gd,&gm,NULL);
    setbkcolor(WHITE);
    cleardevice();

    for(i=0;i<3;i++)
        for(j=0;j<3;j++)
            b[i][j]=' ';

    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);

    while(1)
    {
        cleardevice();
        setcolor(BLACK);
        char aa[]="COMPUTER: X";
        outtextxy(150,40,aa);
        char ab[]="USER: O";
        outtextxy(150,60,ab);
        // current Player number
        player=count%2;
        sprintf(str,"Player : %d (%c)",player+1,player?'O':'X');
        setcolor(GREEN);
        outtextxy(150,100,str);
        printf("\n%s --- Move: ",str);
        display(sx,sy);
        srand(time(NULL));
        if(player==0)
        {
            c = rand() % 8;
            while(moves[c]==-1)
            {
                c++;
                if(c==9)
                {
                    c=0;
                }
            }
            switch(c+1)
            {
                case 1:
                    sx=0;
                    sy=0;
                    moves[0]=-1; //Position is taken
                    break;
                case 2:
                    sx=1;
                    sy=0;
                    moves[1]=-1;
                    break;
                case 3:
                    sx=2;
                    sy=0;
                    moves[2]=-1;
                    break;
                case 4:
                    sx=0;
                    sy=1;
                    moves[3]=-1;
                    break;
                case 5:
                    sx=1;
                    sy=1;
                    moves[4]=-1;
                    break;
                case 6:
                    sx=2;
                    sy=1;
                    moves[5]=-1;
                    break;
                case 7:
                    sx=0;
                    sy=2;
                    moves[6]=-1;
                    break;
                case 8:
                    sx=1;
                    sy=2;
                    moves[7]=-1;
                    break;
                case 9:
                    sx=2;
                    sy=2;
                    moves[8]=-1;
                    break;
            }
        }
        else
        {
            scanf("%d",&ch);
            switch(ch)
            {
                case 1:
                    sx=0;
                    sy=0;
                    moves[0]=-1; //Position is taken
                    break;
                case 2:
                    sx=1;
                    sy=0;
                    moves[1]=-1;
                    break;
                case 3:
                    sx=2;
                    sy=0;
                    moves[2]=-1;
                    break;
                case 4:
                    sx=0;
                    sy=1;
                    moves[3]=-1;
                    break;
                case 5:
                    sx=1;
                    sy=1;
                    moves[4]=-1;
                    break;
                case 6:
                    sx=2;
                    sy=1;
                    moves[5]=-1;
                    break;
                case 7:
                    sx=0;
                    sy=2;
                    moves[6]=-1;
                    break;
                case 8:
                    sx=1;
                    sy=2;
                    moves[7]=-1;
                    break;
                case 9:
                    sx=2;
                    sy=2;
                    moves[8]=-1;
                    break;
                default :
                    break;
            }
        }
        if(b[sy][sx]==' ')       //Mark the cell only if it is empty
        {
            if(player==0)
                b[sy][sx]='X';
            else
                b[sy][sx]='O';
            count++;
        }
        if(checkWin(sx,sy,player)==1||checkDraw(sx,sy)==1)
            break;

    }
    getch();
    closegraph();

    return 0;
}

