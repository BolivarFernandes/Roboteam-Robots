#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>
#include<time.h>
char gamemap[20][40];//set map 20*40
int score=0;//current score
//mark snake
int x[800];
int y[800];
int len = 0;//length of the snake

//record information
 int fx=0;//x coordinate of food
 int fy=0;//y coordinate of food
 int fcount=0;//food #

 //main function
void createfood();//create food
void PrintgameMap(int x[],int y[]);//sketch map
void move(int x[],int y[]);//move the snake

int main()
{
    srand(time(NULL));
   //initialize the location of head and body, default length:2
    x[len] = 9;
    y[len] = 9;
    len++;
    x[len] = 9;
    y[len] = 8;
    len++;
    createfood();
    PrintgameMap(x,y);
    move(x,y);
    return 0;
}
void createfood()
{
    if(0==fcount)
    {
       int tfx=rand()%18+1;
        int tfy=rand()%38+1;
        int i,j;
        int have=0;//no food
        for(i=0;i<len;i++)
        {
            for(j=0;j<len;j++)
            {
                if(x[i]==fx&&y[j]==fy)
                {
                    have=1;
                    break;
                }
                else
                {
                    have=0;
                }
            }
            if(1==have)//if it is a part of the snake, continue
            {
                continue;
            }
            else//otherwise create food
            {
                fcount++;
                fx=tfx;
                fy=tfy;
                break;
            }
        }
    }
}
//game map
void PrintgameMap(int x[],int y[])
{
    int snake = 0,food=0;
    int i, j;
    //sketch map and initialize the location
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 40; j++)
        {
            if (i == 0 && j >= 1 && j <= 38)
            {
                gamemap[i][j] = '=';

            }
            else if (i == 19 && j >= 1 && j <= 38)
            {
                gamemap[i][j] = '=';
            }
            else if (j == 0 || j == 39)
            {
                gamemap[i][j] = '|';
            }
            else
            {
                gamemap[i][j] = ' ';
            }
            //judge the location
            int k;
            for ( k = 0; k < len; k++)
            {

                if (i == x[k]&&j == y[k])
                {
                    snake = 1;
                    break;
                }
                else
                {
                    snake = 0;
                }
            }
          {
              if(fcount&&fx==i&&fy==j)
              {
                  food=1;
              }
              else
              {
                  food=0;
              }
          }
            //if snake is not here
            if (1==snake )
            {
                printf("*");
            }
            else if(1==food)
            {
               printf("#");
            }
            //if snake is not here and there is no food
            else
            {
                printf("%c", gamemap[i][j]);
            }
        }
        printf("\n");
    }
    printf("score:%d\n",score);
    printf("Please use ASDF keys.");
}
//move
void move(int x[],int y[])
{
    char s;
    s=getch();
    int move=0,beat=0;
    while (1)
    {
        int cx[800];
        int cy[800];
        memcpy(cx, x, sizeof(int)*len);
        memcpy(cy, y, sizeof(int)*len);
        //head
        if (s=='w')
        {
                x[0]--;
                move=1;
                if(x[0]<=0)
                {
                   printf(" Game Over\nMade by Jarvis Wang  Jan. 20, 2017");
                   Sleep(2000);
                   break;
                }
        }
        else if (s=='s')
        {
            x[0]++;
            move=1;
            if(x[0]>=19)
            {
                printf(" Game Over\nMade by Jarvis Wang  Jan. 20, 2017");
                Sleep(2000);
                break;
            }
        }
        else if (s=='a')
        {
            y[0] --;
            move=1;
            if(y[0]<=0)
            {
                printf(" Game Over\nMade by Jarvis Wang  Jan. 20, 2017");
                Sleep(2000);
               break;
            }

        }
        else if (s=='d')
        {
             y[0]++;
            move=1;
             if(y[0]>=39)
            {
                 printf(" Game Over\nMade by Jarvis Wang  Jan. 20, 2017");
                 Sleep(2000);
                 break;
            }
        }
        //body
        int i;
        for ( i = 1; i < len; i++)
        {
            x[i] = cx[i - 1];
            y[i] = cy[i - 1];
        }
        for(i=1;i<len;i++)//if it bites itself
        {
            if(x[0]==x[i]&&y[0]==y[i])
            {
                beat=1;
            }
            else
            {
                beat=0;
            }
        }
        if(1==beat)
        {
            printf(" Game Over\nMade by Jarvis Wang  Jan. 20, 2017");
            Sleep(2000);
            break;
        }
        if(1==move)
        {
            if(fcount&&x[0]==fx&&y[0]==fy)//if it gets food
            {
                //copy current location of head to second point
                memcpy(x+1,cx,sizeof(int)*len);
                memcpy(y+1,cy,sizeof(int)*len);
                len++;
                fcount--;
                fx=0;
                fy=0;
                score= score + 10;
                createfood();
            }
            Sleep(100);
            system("cls");
            PrintgameMap( x, y);
        }
        else
        continue;
        if(kbhit())//judge push button
        {
            s=getch();
        }
     }
}
