#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct coor{
    int number;
    int choices[9];
} coor;

coor board[9][9];

void onlyChoice(void);

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

void onlyChoice(void){
    int numbersY[9];
    int numbersX[9];
    int numbersBox[9];
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
            for(int k = 0; k < 3; k++){
                for(int x = 0; x < 9; x++){
                    if(board[(i*3)+k][(j*3)].choices[x] == 1){
                        numbersBox[x]++;
                    }
                    if(board[(i*3)][(j*3)+k].choices[x] == 1){
                        numbersBox[x]++;
                    }
                    if(board[(i*3)+k][(j*3)+k].choices[x] == 1){
                        numbersBox[x]++;
                    }
                }
            }

            for(int n = 0; n < 9; n++){
                if(numbersBox[n] == 1){
                    for(int k = 0; k < 3; k++){
                        if(board[(i*3)+k][(j*3)+k].choices[n] == 1){
                            printf("fant tallet: %d i posisjonen (%d,%d) i en boks\n", n+1, (i*3)+k+1, (j*3)+k+1);
                            board[(i*3)+k][(j*3)+k].number = n+1;
                            updateChoices((i*3)+k, (j*3)+k);
                        }
                        
                    }
                }
            }
            memset(numbersBox, 0, 9);
        }
    }

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
    return totalAnswers;
}


int main(void){
    int modified = 1;

    initBoard();
    printBoard();
    
    
    while(answer()){
        onlyChoice();
    }
   printf("\nBrettet ser nå slik ut: \n");
   printBoard();

    while(1){
        printChoices();
        printf("\n");
    }
}