#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include<time.h>
#include<ctype.h>
#include <time.h>
#include <windows.h>
#include <process.h>
 
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
 
int length;
int bend_no;
int len;
char key;
void record();
void load();
int life;
void Delay(long double);
void Move();
void Food();
int Score();
void Print();
void gotoxy(int x, int y);
void GotoXY(int x,int y);
void Bend();
void Boarder();
void Down();
void Left();
void Up();
void Right();
void ExitGame();
int Scoreonly();
 
struct coordinate
{
    int x;
    int y;
    int direction;
};
 
typedef struct coordinate coordinate;
 
coordinate head, bend[500],food,body[30];
int main(){
int abc;
printf("WHICH GAME DO YOU WANA PLAY?\nTITAK-1 SNAKE-2 GUESS THE NUMBER-3 STONE-PAPER-4 : ");
scanf("%d",&abc);
if(abc==1){
maintiktak();
}
else if(abc==2){
mainsnake();
}
else if(abc==3){
    mainguess();
}
else if(abc==4){
    spsmain();
}
 
else{
printf("WILL ADD MORE GAMES SOON");
}
 
return 0;
}
 
void mainsnake()
{
 
    char key;
 
    Print();
 
    system("cls");
 
    load();
 
    length=5;
 
    head.x=25;
 
    head.y=20;
 
    head.direction=RIGHT;
 
    Boarder();
 
    Food(); //to generate food coordinates initially
 
    life=3; //number of extra lives
 
    bend[0]=head;
 
    Move();   //initialing initial bend coordinate
 
 
 
}
 
void Move()
{
    int a,i;
 
    do
    {
 
        Food();
        fflush(stdin);
 
        len=0;
 
        for(i=0; i<30; i++)
 
        {
 
            body[i].x=0;
 
            body[i].y=0;
 
            if(i==length)
 
                break;
 
        }
 
        Delay(length);
 
        Boarder();
 
        if(head.direction==RIGHT)
 
            Right();
 
        else if(head.direction==LEFT)
 
            Left();
 
        else if(head.direction==DOWN)
 
            Down();
 
        else if(head.direction==UP)
 
            Up();
 
        ExitGame();
 
    }
    while(!kbhit());
 
    a=getch();
 
    if(a==27)
 
    {
 
        system("cls");
 
        exit(0);
 
    }
    key=getch();
 
    if((key==RIGHT&&head.direction!=LEFT&&head.direction!=RIGHT)||(key==LEFT&&head.direction!=RIGHT&&head.direction!=LEFT)||(key==UP&&head.direction!=DOWN&&head.direction!=UP)||(key==DOWN&&head.direction!=UP&&head.direction!=DOWN))
 
    {
 
        bend_no++;
 
        bend[bend_no]=head;
 
        head.direction=key;
 
        if(key==UP)
 
            head.y--;
 
        if(key==DOWN)
 
            head.y++;
 
        if(key==RIGHT)
 
            head.x++;
 
        if(key==LEFT)
 
            head.x--;
 
        Move();
 
    }
 
    else if(key==27)
 
    {
 
        system("cls");
 
        exit(0);
 
    }
 
    else
 
    {
 
        printf("\a");
 
        Move();
 
    }
}
 
void gotoxy(int x, int y)
{
 
    COORD coord;
 
    coord.X = x;
 
    coord.Y = y;
 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
 
}
void GotoXY(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
}
void load()
{
    int row,col,r,c,q;
    gotoxy(36,14);
    printf("loading...");
    gotoxy(30,15);
    for(r=1; r<=20; r++)
    {
        for(q=0; q<=100000000; q++); //to display the character slowly
        printf("%c",177);
    }
    getch();
}
void Down()
{
    int i;
    for(i=0; i<=(head.y-bend[bend_no].y)&&len<length; i++)
    {
        GotoXY(head.x,head.y-i);
        {
            if(len==0)
                printf("v");
            else
                printf("*");
        }
        body[len].x=head.x;
        body[len].y=head.y-i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y++;
}
void Delay(long double k)
{
    Score();
    long double i;
    for(i=0; i<=(10000000); i++);
}
void ExitGame()
{
    int i,check=0;
    for(i=4; i<length; i++) //starts with 4 because it needs minimum 4 element to touch its own body
    {
        if(body[0].x==body[i].x&&body[0].y==body[i].y)
        {
            check++;    //check's value increases as the coordinates of head is equal to any other body coordinate
        }
        if(i==length||check!=0)
            break;
    }
    if(head.x<=10||head.x>=70||head.y<=10||head.y>=30||check!=0)
    {
        life--;
        if(life>=0)
        {
            head.x=25;
            head.y=20;
            bend_no=0;
            head.direction=RIGHT;
            Move();
        }
        else
        {
            system("cls");
            printf("All lives completed\nBetter Luck Next Time!!!\nPress any key to quit the game\n");
            record();
            exit(0);
        }
    }
}
void Food()
{
    if(head.x==food.x&&head.y==food.y)
    {
        length++;
        time_t a;
        a=time(0);
        srand(a);
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
 
            food.y+=11;
    }
    else if(food.x==0)/*to create food for the first time coz global variable are initialized with 0*/
    {
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
            food.y+=11;
    }
}
void Left()
{
    int i;
    for(i=0; i<=(bend[bend_no].x-head.x)&&len<length; i++)
    {
        GotoXY((head.x+i),head.y);
        {
            if(len==0)
                printf("<");
            else
                printf("*");
        }
        body[len].x=head.x+i;
        body[len].y=head.y;
        len++;
    }
    Bend();
    if(!kbhit())
        head.x--;
 
}
void Right()
{
    int i;
    for(i=0; i<=(head.x-bend[bend_no].x)&&len<length; i++)
    {
        //GotoXY((head.x-i),head.y);
        body[len].x=head.x-i;
        body[len].y=head.y;
        GotoXY(body[len].x,body[len].y);
        {
            if(len==0)
                printf(">");
            else
                printf("*");
        }
        /*body[len].x=head.x-i;
        body[len].y=head.y;*/
        len++;
    }
    Bend();
    if(!kbhit())
        head.x++;
}
void Bend()
{
    int i,j,diff;
    for(i=bend_no; i>=0&&len<length; i--)
    {
        if(bend[i].x==bend[i-1].x)
        {
            diff=bend[i].y-bend[i-1].y;
            if(diff<0)
                for(j=1; j<=(-diff); j++)
                {
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y+j;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff; j++)
                {
                    /*GotoXY(bend[i].x,(bend[i].y-j));
                    printf("*");*/
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y-j;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
        }
        else if(bend[i].y==bend[i-1].y)
        {
            diff=bend[i].x-bend[i-1].x;
            if(diff<0)
                for(j=1; j<=(-diff)&&len<length; j++)
                {
                    /*GotoXY((bend[i].x+j),bend[i].y);
                    printf("*");*/
                    body[len].x=bend[i].x+j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
            else if(diff>0)
                for(j=1; j<=diff&&len<length; j++)
                {
                    /*GotoXY((bend[i].x-j),bend[i].y);
                    printf("*");*/
                    body[len].x=bend[i].x-j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)
                        break;
                }
        }
    }
}
void Boarder()
{
    system("cls");
    int i;
    GotoXY(food.x,food.y);   /*displaying food*/
    printf("F");
    for(i=10; i<71; i++)
    {
        GotoXY(i,10);
        printf("!");
        GotoXY(i,30);
        printf("!");
    }
    for(i=10; i<31; i++)
    {
        GotoXY(10,i);
        printf("!");
        GotoXY(70,i);
        printf("!");
    }
}
void Print()
{
    //GotoXY(10,12);
    printf("\tWelcome to the mini Snake game.(press any key to continue)\n");
    getch();
    system("cls");
    printf("\tGame instructions:\n");
    printf("\n-> Use arrow keys to move the snake.\n\n-> You will be provided foods at the several coordinates of the screen which you have to eat. Everytime you eat a food the length of the snake will be increased by 1 element and thus the score.\n\n-> Here you are provided with three lives. Your life will decrease as you hit the wall or snake's body.\n\n-> YOu can pause the game in its middle by pressing any key. To continue the paused game press any other key once again\n\n-> If you want to exit press esc. \n");
    printf("\n\nPress any key to play game...");
    if(getch()==27)
        exit(0);
}
void record()
{
    char plname[20],nplname[20],cha,c;
    int i,j,px;
    FILE *info;
    info=fopen("record.txt","a+");
    getch();
    system("cls");
    printf("Enter your name\n");
    scanf("%[^\n]",plname);
    //************************
    for(j=0; plname[j]!='\0'; j++) //to convert the first letter after space to capital
    {
        nplname[0]=toupper(plname[0]);
        if(plname[j-1]==' ')
        {
            nplname[j]=toupper(plname[j]);
            nplname[j-1]=plname[j-1];
        }
        else nplname[j]=plname[j];
    }
    nplname[j]='\0';
    //*****************************
    //sdfprintf(info,"\t\t\tPlayers List\n");
    fprintf(info,"Player Name :%s\n",nplname);
    //for date and time
 
    time_t mytime;
    mytime = time(NULL);
    fprintf(info,"Played Date:%s",ctime(&mytime));
    //**************************
    fprintf(info,"Score:%d\n",px=Scoreonly());//call score to display score
    //fprintf(info,"\nLevel:%d\n",10);//call level to display level
    for(i=0; i<=50; i++)
        fprintf(info,"%c",'_');
    fprintf(info,"\n");
    fclose(info);
    printf("Wanna see past records press 'y'\n");
    cha=getch();
    system("cls");
    if(cha=='y')
    {
        info=fopen("record.txt","r");
        do
        {
            putchar(c=getc(info));
        }
        while(c!=EOF);
    }
    fclose(info);
}
int Score()
{
    int score;
    GotoXY(20,8);
    score=length-5;
    printf("SCORE : %d",(length-5));
    score=length-5;
    GotoXY(50,8);
    printf("Life : %d",life);
    return score;
}
int Scoreonly()
{
    int score=Score();
    system("cls");
    return score;
}
void Up()
{
    int i;
    for(i=0; i<=(bend[bend_no].y-head.y)&&len<length; i++)
    {
        GotoXY(head.x,head.y+i);
        {
            if(len==0)
                printf("^");
            else
                printf("*");
        }
        body[len].x=head.x;
        body[len].y=head.y+i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y--;
}
char square[10] = { 'o', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
 
int checkwin();
void board();
 
void maintiktak()
{
 
    int player = 1, i, choice;
 
    char mark;
 
  do
    {
        board();
        player = (player % 2) ? 1 : 2 ;
        if(player%2==0){
        system("color 01");
    }
    else{
        system("color 04");
    }
 
        printf("   Player %d, enter a number:  ", player);
        scanf("%d", &choice);
 
        mark = (player == 1) ? 'X'  : 'O';
 
        if (choice == 1 && square[1] == '1')
            square[1] = mark;
 
        else if (choice == 2 && square[2] == '2')
            square[2] = mark;
 
        else if (choice == 3 && square[3] == '3')
            square[3] = mark;
 
        else if (choice == 4 && square[4] == '4')
            square[4] = mark;
 
        else if (choice == 5 && square[5] == '5')
            square[5] = mark;
 
        else if (choice == 6 && square[6] == '6')
            square[6] = mark;
 
        else if (choice == 7 && square[7] == '7')
            square[7] = mark;
 
        else if (choice == 8 && square[8] == '8')
            square[8] = mark;
 
        else if (choice == 9 && square[9] == '9')
            square[9] = mark;
 
        else
        {
            printf("   Invalid move ");
 
            player--;
            getch();
        }
        i = checkwin();
 
        player++;
    }while (i ==  - 1);
 
    board();
 
    if (i == 1)
        printf("==>\aPlayer %d win ", --player);
    else
        printf("==>\aGame draw");
 
    getch();
 
 
}
 
/*********************************************
FUNCTION TO RETURN GAME STATUS
1 FOR GAME IS OVER WITH RESULT
-1 FOR GAME IS IN PROGRESS
O GAME IS OVER AND NO RESULT
 **********************************************/
 
int checkwin()
{
    if (square[1] == square[2] && square[2] == square[3])
        return 1;
 
    else if (square[4] == square[5] && square[5] == square[6])
        return 1;
 
    else if (square[7] == square[8] && square[8] == square[9])
        return 1;
 
    else if (square[1] == square[4] && square[4] == square[7])
        return 1;
 
    else if (square[2] == square[5] && square[5] == square[8])
        return 1;
 
    else if (square[3] == square[6] && square[6] == square[9])
        return 1;
 
    else if (square[1] == square[5] && square[5] == square[9])
        return 1;
 
    else if (square[3] == square[5] && square[5] == square[7])
        return 1;
 
    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' &&
        square[4] != '4' && square[5] != '5' && square[6] != '6' && square[7]
        != '7' && square[8] != '8' && square[9] != '9')
 
        return 0;
    else
        return  - 1;
}
 
 
/*******************************************************************
FUNCTION TO DRAW BOARD OF TIC TAC TOE WITH PLAYERS MARK
 ********************************************************************/
 
 
void board()
{
system("color 01");
    printf("\n\n\tTic Tac Toe\n\n");
 
    printf("Player 1 (X)  -  Player 2 (O)\n\n\n");
 
 
    printf("     |     |     \n");
    printf("  %c  |  %c  |  %c \n", square[1], square[2], square[3]);
 
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
 
    printf("  %c  |  %c  |  %c \n", square[4], square[5], square[6]);
 
    printf("_____|_____|_____\n");
    printf("     |     |     \n");
 
    printf("  %c  |  %c  |  %c \n", square[7], square[8], square[9]);
 
    printf("     |     |     \n\n");
}
void mainguess()
{
    int random_genNo=0,count=0,num;
    int stime;
    long ltime;
    int abcd=0;
int difficulty;
    //initialise srand with current time, to get random number on every run
    ltime = time(NULL);
    stime = (unsigned) ltime/2;
    srand(stime);
 
    //generate random number
    random_genNo=rand()%1000;
    printf("CHOOSE YOUR LEVEL EASY-1 MEDIUM-2 HARD-3 ");
scanf("%d",&difficulty);
if(difficulty==1){
    abcd==15;
}
else if(difficulty==2){
    abcd==10;
}
else{
    abcd==7;
}
    //run infinite loop
    while(1)
    {
        //increase counter
count+=1;
 
        //read number from user
        printf("\n\nGuess a number from (0 to 1000): ");
 
scanf("%d",&num);
        //compare entered number with generated number
 
        if(random_genNo==num){
            printf("Congratulations, you have guessed a correct number.");
            break;
        }
        else if(random_genNo<num){
            printf("Generated number is less than entered number, try your luck again...");
        }
        else if(random_genNo>num){
            printf("Generated number is greater than entered number, try your luck again...");
        }
 
        if(count==15){
            printf("\n\n### Maximum limit of atttempt finished, BAD LUCK !!!\n");
           break;
        }
    }
 
 
}
int spsmain(){printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\tHi test your luck in stone paper scissors by playing against computer\n\n\t\t\t\t\t\t");
    system("color 01");
Sleep(300);
system("color 02");
Sleep(300);
system("color 03");
Sleep(300);
system("color 04");
Sleep(300);
system("color 05");
Sleep(300);
system("color 01");
srand(time(NULL));
int r = rand();
int choose,sum=0,i;
system("pause");
system("cls");
for(i=0;i<5;i++){
printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\tCHOOSE 1-STONE 2-PAPER 3-SCISSORS-- ");
scanf("%d",&choose);
printf("\t\t\t\t\t\t");
if(choose==1&& r%3==0){
    printf("        tie\n");sum++;
}
else if(choose==1&& r%3==1){
    printf("lost opponent choose paper\n");sum--;
}
else if(choose==1&& r%3==2){
    printf("WON OPPONENT CHOOSED SCISSORS\n");sum+=2;
}
else if(choose==2&& r%3==0){
    printf("WON OPPONENT CHOOSED STONE\n");sum+=2;
}
else if(choose==2&& r%3==1){
    printf("       tie\n");sum++;
}
else if(choose==2&& r%3==2){
    printf("lost opponent choose scissors\n");sum--;
}
else if(choose==3&& r%3==0){
    printf("lost opponent choose scissors\n");sum--;
}
else if(choose==3&& r%3==1){
    printf("WON OPPONENT CHOOSED paper\n");sum+=2;
}
else if(choose==3&& r%3==2){
    printf("       tie\n");sum++;
}
else{
    printf("ENTER CORRECT NUMBER\n");sum-=2;
}
    system("color 01");
Sleep(300);
system("color 02");
Sleep(300);
system("color 03");
Sleep(300);
system("color 04");
Sleep(300);
system("color 05");
Sleep(300);
system("color 01");
system("pause");
system("cls");}
printf("\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t");
printf("your score is %d\n",sum);
printf("\n\t\t\t\t\t");
if(sum>6){
    printf("you have very good luck");
}
else if(sum>2){
    printf("better luck next time");
}
else{
    printf("bad luck");
}
system("color 01");
Sleep(300);
system("color 02");
Sleep(300);
system("color 03");
Sleep(300);
system("color 04");
Sleep(300);
system("color 05");
Sleep(300);
return 0;
}