#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct coor{
    int number;
    int choices[9];
} coor;

typedef struct test{
    int ammount;
    int locX;
    int locY;
    int locX2;
    int locY2;
} test;

coor board[9][9];

int onlyChoice(void);

void initChoices(void){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            for(int x = 0; x < 9; x++){
                board[i][j].choices[x] = 1;
            }
        }
    }
}

void updateChoices(int x, int y){
    int number = board[x][y].number;

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            //samme rad eller kolonne
            if(i == x || j == y){
                board[i][j].choices[number-1] = 0;
            }
            //samme boks
            if((i/3) == (x/3) && (j/3) == (y/3)){
                board[i][j].choices[number-1] = 0;
            } 
            if(board[i][j].number != 0){
                for(int x = 0; x < 9; x++){
                    board[i][j].choices[x] = 0;
                }
            }
        }
    }
}

int shadowChoice(void){
    test number[9];
    int totalAnswers = 0;

    for(int i = 0; i < 9; i++){
        number[i].ammount = 0;
    }

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            for(int x = 0; x < 9; x++){
                if(board[i*3][j*3].choices[x] == 1){
                    if(number[x].ammount == 0){
                        number[x].locX = 3*i;
                        number[x].locY = 3*j;
                    }else{
                        number[x].locX2 = 3*i;
                        number[x].locY2 = 3*j;
                    }
                    number[x].ammount++;
                }
                if(board[(i*3)+1][(j*3)].choices[x] == 1){
                    if(number[x].ammount == 0){
                        number[x].locX = 3*i+1;
                        number[x].locY = 3*j;
                    }else{
                        number[x].locX2 = 3*i;
                        number[x].locY2 = 3*j;
                    }
                    number[x].ammount++;
                }
                if(board[(i*3)][(j*3)+1].choices[x] == 1){
                    if(number[x].ammount == 0){
                        number[x].locX = 3*i;
                        number[x].locY = 3*j+1;
                    }else{
                        number[x].locX2 = 3*i;
                        number[x].locY2 = 3*j;
                    }
                    number[x].ammount++;
                }
                if(board[(i*3)+1][(j*3)+1].choices[x] == 1){
                    if(number[x].ammount == 0){
                        number[x].locX = 3*i+1;
                        number[x].locY = 3*j+1;
                    }else{
                        number[x].locX2 = 3*i;
                        number[x].locY2 = 3*j;
                    }
                    number[x].ammount++;
                }
                if(board[(i*3)+2][(j*3)].choices[x] == 1){
                    if(number[x].ammount == 0){
                        number[x].locX = 3*i+2;
                        number[x].locY = 3*j;
                    }else{
                        number[x].locX2 = 3*i;
                        number[x].locY2 = 3*j;
                    }
                    number[x].ammount++;
                }
                if(board[(i*3)][(j*3)+2].choices[x] == 1){
                    if(number[x].ammount == 0){
                        number[x].locX = 3*i;
                        number[x].locY = 3*j+2;
                    }else{
                        number[x].locX2 = 3*i;
                        number[x].locY2 = 3*j;
                    }
                    number[x].ammount++;
                }
                if(board[(i*3)+2][(j*3)+1].choices[x] == 1){
                    if(number[x].ammount == 0){
                        number[x].locX = 3*i+2;
                        number[x].locY = 3*j+1;
                    }else{
                        number[x].locX2 = 3*i;
                        number[x].locY2 = 3*j;
                    }
                    number[x].ammount++;
                }
                if(board[(i*3)+1][(j*3)+2].choices[x] == 1){
                    if(number[x].ammount == 0){
                        number[x].locX = 3*i+1;
                        number[x].locY = 3*j+2;
                    }else{
                        number[x].locX2 = 3*i;
                        number[x].locY2 = 3*j;
                    }
                    number[x].ammount++;
                }
                if(board[(i*3)+2][(j*3)+2].choices[x] == 1){
                    if(number[x].ammount == 0){
                        number[x].locX = 3*i+2;
                        number[x].locY = 3*j+2;
                    }else{
                        number[x].locX2 = 3*i;
                        number[x].locY2 = 3*j;
                    }
                    number[x].ammount++;
                }
            }
            for(int n = 0; n < 9; n++){
                if(number[n].ammount == 2 && number[n].locX == number[n].locX2){
                    for(int x = 0; x < 9; x++){
                        for(int y = 0; y < 9; y++){
                            if(x == number[n].locX){
                                board[x][y].choices[n] = 0;
                            }
                        }
                    }
                    printf("fant en skyggestripe av tallet: %d i y = %d \n", n+1, number[n].locX+1);
                    totalAnswers++;
                }
                if(number[n].ammount == 2 && number[n].locY == number[n].locY2){
                    for(int x = 0; x < 9; x++){
                        for(int y = 0; y < 9; y++){
                            if(y == number[n].locY){
                                board[x][y].choices[n] = 0;
                            }
                        }
                    }
                    printf("fant en skyggestripe av tallet: %d i x = %d %d, %d %d \n", n+1, number[n].locY+1, number[n].locX+1, number[n].locY2+1, number[n].locX2+1);
                    totalAnswers++;
                }
            }
            for(int i = 0; i < 9; i++){
                number[i].ammount = 0;
                number[i].locX = 0;
                number[i].locY = 0;
                number[i].locX2 = 0;
                number[i].locY2 = 0;
            }
        }
    }
    return totalAnswers;
}

int onlyChoice(void){
    int numbersY[9];
    int numbersX[9];
    test number[9];
    
    memset(numbersY, 0, 9);
    memset(numbersX, 0, 9);
    for(int i = 0; i < 9; i++){
        number[i].ammount = 0;
    }

    int totalAnswers = 0;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            for(int x = 0; x < 9; x++){
                if(board[i][j].choices[x] == 1){
                    numbersY[x]++;
                }
                if(board[j][i].choices[x] == 1){
                    numbersX[x]++;
                }
            }
        }
        for(int n = 0; n < 9; n++){
            if(numbersY[n] == 1){
                for(int j = 0; j < 9; j++){
                    if(board[i][j].choices[n] == 1){
                        printf("fant tallet: %d i posisjonen (%d,%d) i en kollonne\n", n+1, j+1, i+1);
                        totalAnswers++;
                        board[i][j].number = n+1;
                        updateChoices(i, j);
                    }
                    
                }
            }
        }
        memset(numbersY, 0, 9);

        for(int n = 0; n < 9; n++){
            if(numbersX[n] == 1){
                for(int j = 0; j < 9; j++){
                    if(board[j][i].choices[n] == 1){
                        printf("fant tallet: %d i posisjonen (%d,%d) i en rad\n", n+1, i+1, j+1);
                        totalAnswers++;
                        board[j][i].number = n+1;
                        updateChoices(j, i);
                    }
                    
                }
            }
        }
        memset(numbersX, 0, 9);
    }

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            for(int x = 0; x < 9; x++){
                if(board[i*3][j*3].choices[x] == 1){
                    number[x].ammount++;
                    number[x].locX = 3*i;
                    number[x].locY = 3*j;
                }
                if(board[(i*3)+1][(j*3)].choices[x] == 1){
                    number[x].ammount++;
                    number[x].locX = 3*i+1;
                    number[x].locY = 3*j;
                }
                if(board[(i*3)][(j*3)+1].choices[x] == 1){
                    number[x].ammount++;
                    number[x].locX = 3*i;
                    number[x].locY = 3*j+1;
                }
                if(board[(i*3)+1][(j*3)+1].choices[x] == 1){
                    number[x].ammount++;
                    number[x].locX = 3*i+1;
                    number[x].locY = 3*j+1;
                }
                if(board[(i*3)+2][(j*3)].choices[x] == 1){
                    number[x].ammount++;
                    number[x].locX = 3*i+2;
                    number[x].locY = 3*j;
                }
                if(board[(i*3)][(j*3)+2].choices[x] == 1){
                    number[x].ammount++;
                    number[x].locX = 3*i;
                    number[x].locY = 3*j+2;
                }
                if(board[(i*3)+2][(j*3)+1].choices[x] == 1){
                    number[x].ammount++;
                    number[x].locX = 3*i+2;
                    number[x].locY = 3*j+1;
                }
                if(board[(i*3)+1][(j*3)+2].choices[x] == 1){
                    number[x].ammount++;
                    number[x].locX = 3*i+1;
                    number[x].locY = 3*j+2;
                }
                if(board[(i*3)+2][(j*3)+2].choices[x] == 1){
                    number[x].ammount++;
                    number[x].locX = 3*i+2;
                    number[x].locY = 3*j+2;
                }
            }
            for(int n = 0; n < 9; n++){
                if(number[n].ammount == 1){
                    if(board[number[n].locX][number[n].locY].choices[n] == 1){
                        printf("fant tallet: %d i posisjonen (%d,%d) i en boks\n", n+1, number[n].locY+1, number[n].locX+1);
                        totalAnswers++;
                        board[number[n].locX][number[n].locY].number = n+1;
                        updateChoices(number[n].locX, number[n].locY);
                    }
                }
            }
            for(int i = 0; i < 9; i++){
                number[i].ammount = 0;
                number[i].locX = 0;
                number[i].locY = 0;
            }
        }
    }
    return totalAnswers;
}

void initBoard(void){
    char boardString[81];
    int stringNum;
    initChoices();

    printf("Skriv inn brettet ditt: \n");
    scanf("%s", &boardString);
    printf("\n");
    
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            stringNum = boardString[i*9+j] - '0';
            board[i][j].number = stringNum;
            if(stringNum != 0){
                updateChoices(i, j);
            }
        }
    }
}

void printBoard(void){
    for(int i = 0; i < 9; i++){
        if(i == 3 || i == 6){
            printf("—————————————————————\n");
        }
        for(int j = 0; j < 9; j++){
            if(j == 3 || j == 6){
                printf("| ");
            }
            printf("%d ", board[i][j].number);
        }
        printf("\n");
    }
    printf("\n");
}

void printChoices(void){
    int x, y;

    printf("Skriv inn koordinatene: \n");
    scanf("%d", &x);
    scanf("%d", &y);

    printf("Tallet: %d\n", board[y-1][x-1].number);
    for(int i = 0; i < 9; i++){
        printf("%d", board[y-1][x-1].choices[i]);
    }
}

int answer(void){
    int choices = 0;
    int answerPos;
    int totalAnswers = 0;
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            for(int x = 0; x < 9; x++){
                if(board[i][j].choices[x] == 1){
                    choices++;
                    answerPos = x;
                }
            }
            if(choices == 1){
                printf("fant tallet: %d i posisjonen (%d,%d)\n", answerPos+1, j+1, i+1);
                board[i][j].number = answerPos+1;
                totalAnswers++;
                updateChoices(i, j);
            }
            choices = 0;
        }
    }

    int extra = onlyChoice();
    //int extra2 = shadowChoice();

    totalAnswers += extra;
    //totalAnswers += extra2;

    return totalAnswers;
}


int main(void){
    int modified = 1;

    initBoard();
    printBoard();
    
    
    while(answer()){
    }
   printf("\nBrettet ser nå slik ut: \n");
   printBoard();

    while(1){
        printChoices();
        printf("\n");
    }
}