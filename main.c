/* 
 * File:   main.c
 * Author: avallonking
 *
 * Created on December 27, 2015, 2:03 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 A 2048 game
 */
void showMatrix(int (*matrix)[4]);
void initialize(int (*matrix)[4]);
void newElementGenerator(int (*matrix)[4]);
void move(int (*matrix)[4], char op);
int judge(int (*matrix)[4],int difficulty);
int setDifficulty();
int full(int (*matrix)[4]);
char getOperation();
void left(int (*matrix)[4]);
void right(int (*matrix)[4]);
void up(int (*matrix)[4]);
void down(int (*matrix)[4]);
int leftOk (int (*matrix)[4]);
int rightOk (int (*matrix)[4]);
int downOk (int (*matrix)[4]);
int upOk (int (*matrix)[4]);

int score = 0, step = 0;

int main(int argc, char** argv) 
{
    int matrix[4][4],diff;
    extern int score,step;
    //Initialize the Matrix
    initialize(matrix);
    //Set difficulty
    diff = setDifficulty();
    while(judge(matrix,diff) != 1) {
        //New element comes
        newElementGenerator(matrix);
        //Move according to operations
        move(matrix,getOperation());
        printf("\nScore: %d\tSteps: %d\n",score,step);
        printf("------------------------------------------------\n");
    }
    return 0;
}

void showMatrix(int (*matrix)[4]) 
{
    for (int i = 0;i < 4;i++) {
        for (int t = 0;t < 4;t++) {
            printf("%d\t",*(*(matrix+i)+t));
        }
        printf("\n");
    }
    printf("\n");
}

int judge(int (*matrix)[4], int difficulty) 
{
    int over = 0,same = 0;
    for (int i = 0;i < 4;i++) 
        for (int t = 0;t < 4;t++) {
            if (*(*(matrix+i)+t) >= difficulty) {
                over = 1;
                printf("You won!\n");
            }
            else {
                if (i - 1 >= 0 && *(*(matrix+i)+t) == *(*(matrix+i-1)+t))
                        same = 1;
                if (i + 1 < 4 && *(*(matrix+i)+t) == *(*(matrix+i+1)+t))
                        same = 1;
                if (t - 1 >= 0 && *(*(matrix+i)+t) == *(*(matrix+i)+t-1))
                        same = 1;
                if (t + 1 < 4 && *(*(matrix+i)+t) == *(*(matrix+i)+t+1))
                        same = 1;
            }
        }
    if (same == 0 && full(matrix)) {
        over = 1;
        printf("You lose!\n");
    }
    return over;
}

int setDifficulty() 
{
    int level, difficulty;
    printf("Please choose your difficulty: 1 for Easy, 2 for Intermediate, 3 for Hard\n");
    scanf("%d",&level);
    switch(level) {
        case 1 :
            difficulty = 16;
            break;
        case 2 :
            difficulty = 32;
            break;
        case 3 :
            difficulty = 2048;
            break;
        default :
            break;
    }
    return difficulty;
}

void initialize(int (*matrix)[4]) 
{
    for (int i = 0;i < 4;i++)
        for (int t = 0;t < 4;t++)
            *(*(matrix+i)+t) = 0;
}

int full(int (*matrix)[4])
{
    int flag = 1;
    for (int i = 0;i < 4;i++)
        for (int t = 0;t < 4;t++)
            if (*(*(matrix+i)+t) == 0)
                flag = 0;
    return flag;
}

void newElementGenerator(int (*matrix)[4]) 
{
    int row, col;
    if (!full(matrix)) {
        do {row = rand() % 4;
            col = rand() % 4;
         } while (*(*(matrix+row)+col));
        *(*(matrix+row)+col) = 2;
    }
    printf("New element comes!\n");
    showMatrix(matrix);
}

char getOperation() 
{
    char operation,rabbish;
    printf("What is your next step?\n");
    rabbish = getchar();    //Accept the "enter" from the scanf above
    operation = getchar();
    return operation;
}

void move(int (*matrix)[4], char op) 
{
    extern int step;
    ++step;
    switch(op) {
        case 'l': 
            left(matrix);
            break;
        case 'r':
            right(matrix);
            break;
        case 'u':
            up(matrix);
            break;
        case 'd':
            down(matrix);
            break;
        default:
            break;
    }
    showMatrix(matrix);
}

void left(int (*matrix)[4]) 
{
    extern int score;
    if (leftOk(matrix)) {
            //t row
            for (int t = 0;t < 4;t++) {
                //r col
                //Each step allows only 1 "add" operation
                int limit = 0; 
                for (int s = 0;s < 4;s++){
                    //Check if there are same elements or 0(from right to left). If yes, add them up.
                    for (int r = 0;r < 4;r++) {
                        if (r-1 >= 0) {
                            if (*(*(matrix+t)+r-1) != 0 && *(*(matrix+t)+r-1) == *(*(matrix+t)+r) && limit == 0) 
                            {score += *(*(matrix+t)+r-1) += *(*(matrix+t)+r);*(*(matrix+t)+r) = 0;limit = 1;}
                            else if (matrix[t][r-1] == 0)
                            {*(*(matrix+t)+r-1) += *(*(matrix+t)+r);*(*(matrix+t)+r) = 0;}
                        }
                    }
                }
            }
    }
    else {
        printf("Cannot move left!\n");
        move(matrix,getOperation());
    }
}

void right(int (*matrix)[4]) 
{
    extern int score;
    if (rightOk(matrix)) {
            //t row
            for (int t = 0;t < 4;t++) {
                //r col
                //Each step allows only 1 "add" operation
                int limit = 0; 
                for (int s = 0;s < 4;s++){
                    //Check if there are same elements or 0(from right to left). If yes, add them up.
                    for (int r = 3;r >= 0;r--) {
                        if (r+1 < 4) {
                            if (*(*(matrix+t)+r+1) != 0 && *(*(matrix+t)+r+1) == *(*(matrix+t)+r) && limit == 0) 
                            {score += *(*(matrix+t)+r+1) += *(*(matrix+t)+r);*(*(matrix+t)+r) = 0;limit = 1;}
                            else if (*(*(matrix+t)+r+1) == 0)
                            {*(*(matrix+t)+r+1) += *(*(matrix+t)+r);*(*(matrix+t)+r) = 0;}
                        }
                    }
                }
            }
    }
    else {
        printf("Cannot move right!\n");
        move(matrix,getOperation());
    }
}

void up(int (*matrix)[4]) 
{
    extern int score;
    if (upOk(matrix)) {
            //t col
            for (int t = 0;t < 4;t++) {
                //r row
                //Each step allows only 1 "add" operation
                int limit = 0; 
                for (int s = 0;s < 4;s++){
                    //Check if there are same elements or 0(from right to left). If yes, add them up.
                    for (int r = 0;r < 4;r++) {
                        if (r-1 >= 0) {
                            if (*(*(matrix+r-1)+t) != 0 && *(*(matrix+r-1)+t) == *(*(matrix+r)+t) && limit == 0) 
                            {score += *(*(matrix+r-1)+t) += *(*(matrix+r)+t);*(*(matrix+r)+t) = 0;limit = 1;}
                            else if (*(*(matrix+r-1)+t) == 0)
                            {*(*(matrix+r-1)+t) += *(*(matrix+r)+t);*(*(matrix+r)+t) = 0;}
                        }
                    }
                }
            }
    }
    else {
        printf("Cannot move upward!\n");
        move(matrix,getOperation());
    }
}

void down(int (*matrix)[4]) 
{
    extern int score;
    if (downOk(matrix)) {
            //t col
            for (int t = 0;t < 4;t++) {
                //r row
                //Each step allows only 1 "add" operation
                int limit = 0; 
                for (int s = 0;s < 4;s++){
                    //Check if there are same elements or 0(from right to left). If yes, add them up.
                    for (int r = 3;r >= 0;r--) {
                        if (r+1 < 4) {
                            if (*(*(matrix+r+1)+t) != 0 && *(*(matrix+r+1)+t) == *(*(matrix+r)+t) && limit == 0) 
                            {score += *(*(matrix+r+1)+t) += *(*(matrix+r)+t);*(*(matrix+r)+t) = 0;limit = 1;}
                            else if (*(*(matrix+r+1)+t) == 0)
                            {*(*(matrix+r+1)+t) += *(*(matrix+r)+t);*(*(matrix+r)+t) = 0;}
                        }
                    }
                }
            }
    }
    else {
        printf("Cannot move downward!\n");
        move(matrix,getOperation());
    }
}

int leftOk (int (*matrix)[4])
{
    int ok = 0;
    for (int i = 0;i < 4;i++)
        for (int t = 1;t < 4;t++) {
            if (*(*(matrix+i)+t) != 0 && *(*(matrix+i)+t) == *(*(matrix+i)+t-1))
                ok = 1;
            else if (*(*(matrix+i)+t-1) == 0)
                ok = 1;
        }
    return ok;
}

int rightOk (int (*matrix)[4])
{
    int ok = 0;
    for (int i = 0;i < 4;i++)
        for (int t = 2;t >= 0;t--) {
            //Same element exists
            if (*(*(matrix+i)+t) != 0 && *(*(matrix+i)+t) == *(*(matrix+i)+t+1))
                ok = 1;
            // Space exists
            else if (*(*(matrix+i)+t+1) == 0)
                ok = 1;
        }
    return ok;
}

int downOk (int (*matrix)[4])
{
    int ok = 0;
    for (int i = 0;i < 4;i++) 
        for (int t = 1;t < 4;t++) {
            if (*(*(matrix+t)+i) != 0 && *(*(matrix+t)+i) == *(*(matrix+t-1)+i))
                ok = 1;
            else if (*(*(matrix+t-1)+i) == 0)
                ok = 1;
        }
    return ok;
}

int upOk (int (*matrix)[4])
{
    int ok = 0;
    for (int i = 0;i < 4;i++)
        for (int t = 2;t >= 0;t--) {
            if (*(*(matrix+t)+i) != 0 && *(*(matrix+t)+i) == *(*(matrix+t+1)+i))
                ok = 1;
            else if (*(*(matrix+t+1)+i) == 0)
                ok = 1;
        }
    return ok;
}