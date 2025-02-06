#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>

int i, waiting =140, present_x=5, present_y=5, previous_x=5, previous_y=5;
int food_x, food_y, score=0, danger_x[50]={0}, danger_y[50]={0};

char direction='D';
void printScore(){
    printf("\nScore = %d", score);
    printf("\nThank You !!!");
}

void putFood(){
    srand(time(NULL));
    here:
    food_x =  5 + 25* ( rand() % 18);
    food_y =  5 + 25* ( rand() % 18);
    // to prevent the overlapping position of food and danger
    for(i=0; i<score; i++){
		if(danger_x[i] == food_x && danger_y[i] == food_y){
		   goto here;
		}
    }
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(food_x, food_y, WHITE);
}

void putDanger(){
    for(i=0; i<score; i++){
		setfillstyle(SOLID_FILL, BLACK);
		floodfill(danger_x[i], danger_y[i], WHITE);
		danger_x[i] = 5 + 25* ( rand() % 18);
		danger_y[i] = 5 + 25* ( rand() % 18);
		setfillstyle(XHATCH_FILL, MAGENTA);
		floodfill(danger_x[i], danger_y[i], WHITE);
    }
}

int haveEaten(){
    if(present_x == food_x && present_y == food_y){
		return 1;
    }else{
		return 0;
    }
}

int touchDanger(){
    for(i=0; i<score; i++){
		if(danger_x[i] == present_x && danger_y[i] == present_y){
		   return 1;
		}
    }
    return 0;
}

void plotSnake(){
    setfillstyle(SOLID_FILL, BLACK);
    floodfill(previous_x, previous_y, WHITE);
    setfillstyle(SOLID_FILL, GREEN);
    floodfill(present_x, present_y, WHITE);

    if(haveEaten()){
		putDanger();
        score += 1;
		putFood();
    }
   
    if(touchDanger()){
		printScore();
		getch();
		exit(1);
    }
}

void movement(){
    FILE *file;
    plotSnake();

    file = fopen("ARROW.txt", "rt");
    if (file) {
        direction = fgetc(file);
        fclose(file);
    } else {
        printf("Error reading direction file\n");
    }
    switch(direction){

    case 'W':   // toward UP
        present_y = previous_y - 25;
        if(present_y < 5){
            present_y = 430;
        }
        plotSnake();
        previous_y = present_y;
        delay(waiting);
        break;

    case 'A':   // toward LEFT
        present_x = previous_x - 25;
        if(present_x < 5){
            present_x = 430;
        }
        plotSnake();
        previous_x = present_x;
        delay(waiting);
        break;

    case 'S':     // toward DOWN
        present_y = previous_y + 25;
        if(present_y > 430){
            present_y = 5;
        }
        plotSnake();
        previous_y = present_y;
        delay(waiting);
        break;

    case 'D':   // toward RIGHT
        present_x = previous_x + 25;
        if(present_x > 430){
            present_x = 5;
        }
        plotSnake();
        previous_x = present_x;
        delay(waiting);
        break;

    case 'Q':
        printScore();
        getch();
        exit(1);

    }
}

void makeBoard(){
    rectangle(0, 0, 450, 450);
    for(i=0; i<18; i++){
        line(25*i , 0, 25*i, 450);
        line(0, 25*i, 450, 25*i);
    }
}

int main(){
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "C:\\TURBOC3\\BGI");
	
       makeBoard();
       putFood();
       while(1){
		   movement();
      }

closegraph();
return 0;
}
