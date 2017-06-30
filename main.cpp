
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<dos.h>
#include<graphics.h>
#include<stdlib.h>
#include<iostream>
#include<cstring>
using namespace std;

const int limit = 100;
int platformCircles;
int headPath[limit];


inline void ShiftAIndex(int pathSize) {
    int i =pathSize;
    int j=limit-1;
    while(1) {
        if(pathSize>=limit) {
            headPath[j]= headPath[j-1];
            j--;
            if(j==0) break;

        } else if(i==0)
            break;
        else {
            headPath[i]=headPath[i-1];
            i--;
            if(i==0) break;
        }
    }

}


inline void displayScore( int sc) {



    //following codes works only in clanguage not in codeblocks c++
    int color = COLOR(352,7326,1264);
    int x =10;
    setcolor(color);
    int y1 =   (getmaxy()/5),y2=(getmaxy()/4);
//	int y1 = 500,y2=450;
    rectangle(x-30,y1-20,x+50,y2+15);
    setfillstyle(SOLID_FILL,color);
    floodfill(x,(y2+y1)/2,color);

    setcolor(color);
    settextstyle(8,HORIZ_DIR,3);
    outtextxy(x,y1,"SCORE:");
    //char [5] ;

    //convert int into string
    //itoa(sc,score,10);

    stringstream stream;
    stream<<sc;
    string convSt   = stream.str();
    int k = 0;
    char ch ='r';
    char content[6];
    k=0;
    while(ch!='\0') {
        ch = convSt[k];
        content[k]=ch;
        k++;
    }




    //cout<<"\n Score in char form is"<<content;
    //setcolor();
    setcolor(COLOR(2542,643623,84573));
    settextstyle(6,HORIZ_DIR,5);
    outtextxy(x,y2-5,content);

}
int radius;


struct Circle {
    int x;
    int y;

    int isFilled;
    // -1 = not filled
};
Circle ccircle[1100];

struct Snake {
    Circle head;
    Circle body[limit];
    Circle tail;
    //tail will have same color as background color:
};

inline void makeCircle(Circle c, int  color) {
    int x  = c.x;
    int y = c.y;
    setcolor(color);
    circle(x,y,radius);
    setfillstyle(SOLID_FILL,color);
    floodfill(x,y,color);

}

void gameOver(Snake snake,int bodyLength) {
    int i;
    for(i=0; i<=10; i++) {
        int color=BLACK;
        if(i%2==0) color=YELLOW;

        delay(200-6*i);

        makeCircle(snake.head,color);
        //body
        int m =0;
        for(m; m<=bodyLength; m++) {
            makeCircle(snake.body[m],color);
        }

        settextstyle(3,HORIZ_DIR,4);
        setcolor(COLOR(626,7252,613));
        outtextxy(50,400,"Hungry?? Grab Snickers!! but not your own FLESH");
    }
    delay(3000);
    exit(78);




}

void eatenSound(){

}

inline int makeRandomFood() {
//    //cout<<"\n generating the food pos";
    srand( time(NULL) ); // hackish but gets the job done.
    int x;
    x = rand(); // everytime it is different because the seed is different.
    int foodPos = x%(platformCircles+1);
    //cout<<"\n Returning "<<foodPos<<" from the makeRandom()";

    return foodPos;
}

//inline shiftArray

int main() {


    int gd=DETECT, gm;

    initgraph(&gd,&gm,"C:\\TC\\BGI");
    initwindow(1000,700,"SnakeGame");


    int bkcolor = COLOR(6325,765313,87248);
    setcolor(bkcolor);
    setfillstyle(SOLID_FILL,bkcolor);
    rectangle(0,0,getmaxx(),getmaxy());
    floodfill(134,466,bkcolor);

//	setbgcolor(GREEN);
    int cnX = getmaxx()/2;
    int cnY = getmaxy()/2;

    int sqSize = 675/2;
    int sqX1 =cnX-sqSize;
    int sqX2 =cnX+sqSize;
    int sqY1 =cnY-sqSize;
    int sqY2 = cnY+sqSize;

    int bkCol = BLACK;
    setcolor(bkCol);

    setfillstyle(SOLID_FILL,bkCol);
    rectangle(sqX1,sqY1,sqX2,sqY2);
    floodfill(cnX,cnY,bkCol);

    //delay(3000);ccircle

    //Global Value radius::
    radius =15;

    int xAx,yAx,cirOnAxis =0;
    int padding=10;
    int cirNo=0;
    int r = radius;

    xAx = sqX1+r+padding;
    yAx = sqY1+r+padding;
    int inLoop =0;

    while(1) {
        ccircle[cirNo].x=xAx;
        ccircle[cirNo].y=yAx;
        ccircle[cirNo].isFilled = -1;//-1 = not occupied by snake
        Circle cTemp = ccircle[cirNo];
        int col = BLACK;
        cirNo++;
        platformCircles++;
        xAx= xAx+2*radius;
        if(inLoop==0)
            cirOnAxis++;

        if(xAx>(sqX2-radius)) {

            //make xAx =0;
            xAx=sqX1+radius+padding;
            //Shift yAx a step down
            yAx=yAx+2*radius;

            inLoop++;
            if(inLoop>cirOnAxis)
                break;

            //Terminate the loop
            if(yAx >(sqY2-radius)) {
                break;
            }
        }
    }

    Circle platFormCircle[cirOnAxis*cirOnAxis];
    int lp =0;
    for(; lp<(cirOnAxis*cirOnAxis); lp++) {
        platFormCircle[lp] =ccircle[lp];
        makeCircle(platFormCircle[lp],BLACK);
    }
    //**************************************************************************

    //FOOD MANAGEMENent
    //foods are stored at!
    int l = lp;
    int Food[] = {lp%15,235,345,457,123,658,561,2,76,234,6,345,123,4,79,222,326,99,999,43,753,172,848,767,37,243,984,72,893,234,678,243,710,10,2,62,0,2,395,42,4,8,343,658,561,2,76,234,6,345,123,78,243,710,10,2,62,0,2,395,42,4,8,343,35,345,457,123,658,561,534,62,0,2,395,42,4,8,343,658,561,2};
//    lp=0;
//    //cout<<"\n Inserting the FOod list";
//    for(;lp<2*limit;lp++){
//        Food[lp]= makeRandomFood();
//        makeCircle(platFormCircle[Food[lp]],WHITE);
//        //delay(50);
//    }
//    delay(5000);
    int foodIndex = 0;

    //Create a food at new space;
    int flag =1;
    //Loop runs until food finds a new space
    while(flag) {
        int foodCir = Food[foodIndex];
        if(platFormCircle[foodCir].isFilled<0) {
            makeCircle(platFormCircle[foodCir],WHITE);
            flag=0;
        } else {
            foodIndex++;
        }
    }


//***********************************************************************************

    //GAME STARTS
    int headPos = cirNo/2;
    //headPos =
    headPath[0]=headPos;
    //headPath[1] = headPos-1;
    int snakeLength=0;

    Snake snake;
    snake.head = platFormCircle[headPos];
    int pathSize =0;
    char ch ='l';
    int speed = 100;
    snakeLength =0;
    const int  AxiCirCount = cirOnAxis;
    cirOnAxis;
    while(1) {


        if(ch=='I'||ch=='i') {

            //infinity loop provides animation
            while(1) {
                delay(speed);
                if(headPos>=cirOnAxis) {
                    headPos-=cirOnAxis;
                } else if(false) {
                    ////cout<<"";
                } else if(headPos<cirOnAxis) {
                    int onCol= cirOnAxis-headPos;
                    headPos = cirNo-onCol;
                }
                //snake head
                snake.head = platFormCircle[headPos];
                ShiftAIndex(pathSize);
                headPath[0]=headPos;
                makeCircle(snake.head,BLUE);
                //check if game is over
                if(snake.head.isFilled>0) {
                    gameOver(snake,snakeLength);
                    //printf("position filled is:%d",headPos);
                }
                //snake body
                int m = 0;
                for(m; m<snakeLength; m++) {
                    platFormCircle[headPath[m+1]].isFilled=2;
                    snake.body[m]=platFormCircle[headPath[m+1]];
                    makeCircle(snake.body[m],GREEN);
                    platFormCircle[headPath[m+1]].isFilled=2;

                }
                //snake tail
                platFormCircle[headPath[snakeLength+1]].isFilled = -1;
                snake.tail = platFormCircle[headPath[snakeLength+1]];
                makeCircle(snake.tail,BLACK);


                pathSize++;

                //Check if snake has eaten the food
                if(Food[foodIndex]==headPos) {

                    foodIndex++;

                    int flag =1;
                    //Loop runs until food finds a new space
                    while(flag) {
                        if(platFormCircle[Food[foodIndex]].isFilled<0) {
                            makeCircle(platFormCircle[Food[foodIndex]],WHITE);
                            flag=0;
                        } else
                            foodIndex++;
                    }

                    snakeLength++;
                    displayScore(snakeLength);
                }

                if(kbhit()) {
                    ch = getch();
                    break;
                }


            }//while
        }//if

        //move horizontal
        else	if(ch=='j'||ch=='J') {



            while(1) {
                delay(speed);
                if(((headPos+1)%cirOnAxis)==1)
                    headPos+=cirOnAxis-1;
                else
                    headPos-=1;


                //snake head
                snake.head = platFormCircle[headPos];
                ShiftAIndex(pathSize);
                headPath[0]=headPos;
                makeCircle(snake.head,BLUE);
                //check if game over
                if(snake.head.isFilled>0)
                    gameOver(snake,snakeLength);
                //snake body
                int m = 0;
                for(m; m<snakeLength; m++) {
                    platFormCircle[headPath[m+1]].isFilled=2;
                    snake.body[m]=platFormCircle[headPath[m+1]];

                    makeCircle(snake.body[m],GREEN);

                }
                //snake tail
                snake.tail = platFormCircle[headPath[snakeLength+1]];
                makeCircle(snake.tail,BLACK);
                platFormCircle[headPath[snakeLength+1]].isFilled=-1;
                pathSize++;

                //Check if snake has eaten the food
                if(Food[foodIndex]==headPos) {

                    foodIndex++;

                    int flag =1;
                    //Loop runs until food finds a new space
                    while(flag) {
                        if(platFormCircle[Food[foodIndex]].isFilled<0) {
                            makeCircle(platFormCircle[Food[foodIndex]],WHITE);
                            flag=0;
                        } else
                            foodIndex++;
                    }

                    snakeLength++;
                    displayScore(snakeLength);
                }
                if(kbhit()) {
                    ch=getch();
                    break;
                }

            }


        } else if(ch=='l'||ch=='L') {
            while(1) {
                delay(speed);

//                makeCircle(platFormCircle[testCir],GREEN);
//            delay(3000);


                if(((headPos+1)%cirOnAxis)==0)
                    headPos-=cirOnAxis-1;
                else
                    headPos+=1;

                //snake head
                snake.head = platFormCircle[headPos];
                ShiftAIndex(pathSize);
                headPath[0]=headPos;

                makeCircle(snake.head,BLUE);
                if(snake.head.isFilled>0)
                    gameOver(snake,snakeLength);
                //snake body
                int m = 0;
                for(m; m<snakeLength; m++) {
                    snake.body[m]=platFormCircle[headPath[m+1]];
                    makeCircle(snake.body[m],GREEN);
                    platFormCircle[headPath[m+1]].isFilled=2;

                }
                //snake tail
                platFormCircle[headPath[snakeLength+1]].isFilled=-1;
                snake.tail = platFormCircle[headPath[snakeLength+1]];

                //cout<<"\n Snake Tail Position is: \n\t x="<< snake.tail.x<<"\t y = "<<snake.tail.y;
                //delay(1100);
                makeCircle(snake.tail,BLACK);

                pathSize++;

                //Check if snake has eaten the food
                if(Food[foodIndex]==headPos) {

                    foodIndex++;

                    int flag =1;
                    //Loop runs until food finds a new space
                    while(flag) {
                        if(platFormCircle[Food[foodIndex]].isFilled<0) {
                            makeCircle(platFormCircle[Food[foodIndex]],WHITE);
                            platFormCircle[headPath[m+1]].isFilled=2;
                            flag=0;
                        } else
                            foodIndex++;
                    }

                    snakeLength++;
                    displayScore(snakeLength);
                }
                if(kbhit()) {
                    ch=getch();
                    break;
                }

            }

        } else if(ch=='k'||ch=='K') {
            while(1) {
                delay(speed);
                if(headPos> (cirNo-cirOnAxis)) {
                    headPos%=cirOnAxis;

                } else {
                    headPos += cirOnAxis     ;
                }


                //snake head
                snake.head = platFormCircle[headPos];
                ShiftAIndex(pathSize);
                headPath[0]=headPos;
                makeCircle(snake.head,BLUE);
                if(snake.head.isFilled>0)
                    gameOver(snake,snakeLength);
                //snake body
                int m = 0;
                for(m; m<snakeLength; m++) {
                    snake.body[m]=platFormCircle[headPath[m+1]];
                    platFormCircle[headPath[m+1]].isFilled=2;
                    makeCircle(snake.body[m],GREEN);

                }
                //snake tail
                snake.tail = platFormCircle[headPath[snakeLength+1]];
                makeCircle(snake.tail,BLACK);
                platFormCircle[headPath[snakeLength+1]].isFilled=-1;

                pathSize++;

                //Check if snake has eaten the food
                if(Food[foodIndex]==headPos) {

                    foodIndex++;

                    int flag =1;
                    //Loop runs until food finds a new space
                    while(flag) {
                        if(platFormCircle[Food[foodIndex]].isFilled<0) {
                            makeCircle(platFormCircle[Food[foodIndex]],WHITE);

                            flag=0;
                        } else
                            foodIndex++;
                    }

                    snakeLength++;
                    displayScore(snakeLength);
                }


                if(kbhit()) {
                    ch = getch();
                    break;
                }


            }
        } else if(ch==13) {
            //cout<<"\nGame Paused";
            //ch=getch();
            cout<<"\n Terminating the program";
            break;

        }vc
    }
    getch();
    closegraph();

}
