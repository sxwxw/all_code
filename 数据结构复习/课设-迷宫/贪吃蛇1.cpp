
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
 
#define UP     1
#define DOWN   -1
#define LEFT   2
#define RIGHT  -2
 
struct Snake    //define the snake
{
 int hang;
 int lie;
 struct Snake *next;
};
 
struct Snake food; //define the food
struct Snake *head= NULL;
struct Snake *tail = NULL;
int key;
int dir;
int set = 49;
int nub = 4;
 
void initFood()  //init food
{
 int x = rand()%20;
 int y = (rand()%19)+1;
 food.hang = x;
 food.lie = y;
}
 
void initNcurse() //init ncurse
{
 initscr();
 keypad(stdscr,1); 
 noecho();
}
 
int hasFood(int i,int j) //judge whether shoule show the food
{
 if(food.hang == i && food.lie == j)
 {
  return 1;
 }
 return 0;
}
 
int hasSnakeNode(int i, int j) //judge whether shoule show the snake
{
 struct Snake *p;
 p = head;
 while(p != NULL) 
 {
  if(p->hang == i && p->lie == j)
     { 
                return 1;
  }
         p = p->next;
 }
 return 0;
}
 
void gamePic()   //show the whole picture
{
 int hang;
 int lie;
 move(0,0);
 for(hang=0;hang<20;hang++)     //20*20 size map
 {
  if(hang == 0)
  {
   for(lie=0;lie<20;lie++)
   {
    printw("--");
   }
   printw("\n"); 
  }
  if(hang >= 0 && hang <= 19)
  {
                        for(lie=0;lie<=20;lie++)
                        {
                                if(lie == 0 || lie == 20)
                                        printw("|");
                         else if(hasSnakeNode(hang,lie))
    {
     printw("[]");
    }
    else if(hasFood(hang,lie))
    {
     printw("##");
    }
    else
                        printw("  ");
   }
   printw("\n");
  }
  if(hang == 19)
                {
                        for(lie=0;lie<20;lie++)
                        {
                                printw("--");
                        }
   printw("\n");
  }
 }
 printw("by HaoQing, Happy Game!\n");
 switch(dir)
        {
                case UP:
                        printw("Snake UP!   \n");
                        break;
                case DOWN:
   printw("Snake DOWN! \n");
                        break;
                case LEFT:
   printw("Snake LEFT! \n");
                        break;
                case RIGHT:
   printw("Snake RIGHT!\n");
                        break;
        }
 if(nub >= 380)
 {
  printw("------------------------------------\n");
  printw("==============YOU WIN!==============\n");
         printw("------------------------------------\n");
 }
}
 
void addNode()   //add the node of snake
{
 struct Snake *new = (struct Snake *)malloc(sizeof(struct Snake));
  
 new->next = NULL;
 
 switch(dir)
 {
  case UP:
   new->hang = tail->hang-1;
                        new->lie = tail->lie;
                        break;
  case DOWN:
                        new->hang = tail->hang+1;
                        new->lie = tail->lie;
                        break;
  case LEFT:
                        new->hang = tail->hang;
                        new->lie = tail->lie-1;
                        break;
  case RIGHT:
                        new->hang = tail->hang;
                        new->lie = tail->lie+1;
                        break;
 }
 tail->next = new;
 tail = new;
}
 
void initSnake()                //init snake
{
        struct Snake *p;
 
        dir = RIGHT;
 
        while(head != NULL)
        {
                p = head;
                head = head->next;
                free(p);
        }
        initFood();
        head = (struct Snake *)malloc(sizeof(struct Snake));
        head->hang = 1;
        head->lie = 1;
        head->next = NULL;
 
        tail = head;
        addNode();
        addNode();
        addNode();
}
 
void deleNode()   //delete the node of snake   
{
 struct Snake *p;
 p = head;
 head = head->next;
 free(p);
}
 
int ifSnakeDie()  //judge whether the snake is die
{
 struct Snake *p;
 p = head;
 if(tail->hang < 0 || tail->lie == 0 || tail->hang == 20 || tail->lie == 20)
        {
         return 1;     
        }
 while(p->next != NULL)
 {
  if(p->hang == tail->hang && p->lie == tail->lie)
   return 1;
  p=p->next;
 }
 return 0;
}
 
void moveSnake()  //move the snake
{
 addNode();
 if(hasFood(tail->hang,tail->lie))
 { initFood();
  nub++;  //judge whether win
 }
 else
  deleNode();
 if(set != 49 && set != 50 && set != 53)
 {
  if(ifSnakeDie())
   initSnake();
 }
}
 
void refreshJieMian()  //refresh the picture
{
 while(1)
 {
  moveSnake();
  gamePic();
  refresh();
  switch(set)
  {
   case 49:
    usleep(200000);
    break;
   case 50:
                                usleep(100000);
                                break;
   case 51:
                                usleep(100000);
                                break;
   case 52:
                                usleep(80000);
                                break;
   case 53:
    usleep(70000);
    break;
   default:
    usleep(150000); 
  }
 }
}
 
void turn(int direction) //prevent reverse
{
 if(set != 49 && set != 50 && set != 53)
 { if(abs(dir) != abs(direction))
  {
   dir = direction;
  }
 }
 else
  dir = direction;
}
 
void changeDir()  //change direction
{
 while(1)
 {
  if(set != 53)
  {
   key = getch();
   switch(key)
   {
    case KEY_DOWN:
     turn(DOWN);   //-1
     break;
    case KEY_UP:
     turn(UP);     //1
     break;
    case KEY_LEFT:
     turn(LEFT);   //2
     break;
    case KEY_RIGHT:
     turn(RIGHT);  //-2
     break;
   } 
  }
  else
  {
   if(tail->hang > food.hang)
    turn(UP);
   else if(tail->hang < food.hang)
    turn(DOWN);
   if(tail->lie > food.lie)
    turn(LEFT);
   else if(tail->lie < food.lie)
    turn(RIGHT); 
  }
 }
}
 
int main()
{
 initNcurse();
 
 printw("======Welcome To Snake Eating!======\n");
 printw("------------------------------------\n"); 
 printw("Please select difficulty level:\n");
 printw("\n");
 printw("   Fool,please enter    \"1\"\n");
 printw("   Simple,please enter  \"2\"\n");
 printw("   Hard,please enter    \"3\"\n");
 printw("   Hell,please enter    \"4\"\n");
 printw("   Auto,please enter    \"5\"\n");
 printw("------------------------------------\n");
 printw("You want:");
 
 set = getch();
 
 pthread_t t1;
 pthread_t t2;
 
 initSnake();
 
 gamePic();
 
 pthread_create(&t1,NULL,(void *)refreshJieMian,NULL);
 pthread_create(&t2,NULL,(void *)changeDir,NULL);
 
 while(1);
 
 endwin();
 return 0;
}
