#include <iostream>

//for the kbht function 
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;

char getch();
int kbhit();

bool gameover;
const int width =20;
const int height =20;
int tailX[100],tailY[100];
int ntail;
int x,y,fruitY,fruitX,score;
enum eDirection { STOP =0,LEFT,RIGHT,UP,DOWN};
eDirection dir;
void Setup()
{
    gameover=false;
    dir = STOP;
    x=width /2;
    y=height /2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score=0;
}
void Draw()
{
    system("clear"); // system("cls") for windows
    for(int i=0;i<width+2;i++)
        cout<<"#";
    cout<<endl;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(j==0)
                cout<<"#";
            if(i== y && j== x)
                cout<<"0";
            else if(i== fruitY && j==fruitX)
                cout<<"F";
            else
               {
                bool print=false;
                for(int k=0;k<ntail;k++)
                {
                    if(tailX[k]==j && tailY[k]==i)
                    {
                        cout<<"o";
                        print=true;
                    }
                }
                if(!print)
                cout<<" ";
               }
            if(j==width-1)
                cout<<"#";

        }
        cout<<endl;
    }
    for(int i=0;i<width+2;i++)
        cout<<"#";
    cout<<endl;
    cout<<"Score="<<score;
}
void Input()
{
    if(kbhit())
    {
        switch(getch())
        {
            case 'a':
            dir=LEFT;
            break;
            case 'd':
            dir=RIGHT;
            break;
            case 'w':
            dir=UP;
            break;
            case 's':
            dir=DOWN;
            break;
            case 'x':
            gameover=true;
            break;
        }
    }
}
void Logic()
{
    int prevX=tailX[0];
    int prevY =tailY[0];
    int prev2X,prev2y;
    tailX[0]=x;
    tailY[0]=y;
    for(int i=1;i<ntail;i++)
    {
        prev2X=tailX[i];
        prev2y=tailY[i];
        tailX[i]=prevX;
        tailY[i]=prevY;
        prevX=prev2X;
        prevY=prev2y;
    }
    switch(dir)
    {
        case LEFT:
        x--;
        break;
        case RIGHT:
        x++;
        break;
        case UP:
        y--;
        break;
        case DOWN:
        y++;
        break;
        default:
        break;
    }
    // if(x>width || x<0 || y>height ||y<0)
    //     gameover=true;
    if(x>=width)
        x=0;
    else if(x<0)
        x=width-1;
    if(y>=height)
        y=0;
    else if(y<0)
        y=height-1;
    for(int i=0;i<ntail;i++)
        if(tailX[i]==x&&tailY[i]==y)
            gameover=true;
    if(x==fruitX && y==fruitY)
    {
        score+=10;
        fruitX = rand() % width;
        fruitY = rand() %height;
        ntail++;
    }
}
int main()
{
    Setup();
    while(!gameover)
    {
        Draw();
        Input();
        Logic();
        //Sleep(;10),sleep(10)
    }
}


// Kbht() for linux
//this function checks wheather any key is preessed on the keyboard
// if not presseed then 0 else 1;
//This function doesnot need to be defined on widows it is anailabl
//in conio.h header file

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}


char getch(){
    /*#include <unistd.h>   //_getch*/
    /*#include <termios.h>  //_getch*/
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    printf("%c\n",buf);
    return buf;
 }
