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
} test;

typedef struct forslag{
    int locX;
    int locY;
} forslag;

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

//parameter tall er tallverdiene den sjekker for
int kvadrantSjekk(int x, int y, int tall, forslag *answers){
    answers->locX = 0; answers->locY = 0;
    int endret = 0;

    for(int kvadX = 0; kvadX < 3; kvadX++){
        for(int kvadY = 0; kvadY < 3; kvadY++){
            if(board[x*3+kvadX][y*3+kvadY].choices[tall]){
                if(!endret){
                    answers->locX = kvadX+1;
                    answers->locY = kvadY+1;
                    endret = 1;
                }else{
                    if(answers->locX != kvadX+1){
                        answers->locX = 0;
                    }
                    if(answers->locY != kvadY+1){
                        answers->locY = 0;
                    }
                }
            }
        }
    }

    if(answers->locX || answers->locY){
        return 1;
    }else{
        return 0;
    }
}

int fixChoiceLine(int x, int y, int z, forslag *answers){
    int difference = 0;
    if(answers->locX){
        for(int y2 = 0; y2 < 9; y2++){
            if(board[answers->locX+(x*3)-1][y2].choices[z] && y2 != (y*3) && y2 != (y*3)+1 && y2 != (y*3)+2){
                board[answers->locX+(x*3)-1][y2].choices[z] = 0;
                difference++;
            }
        }
        if(difference){
            printf("Fant en stripe av tallet %d i y = %d\n", z+1, answers->locX+(x*3));
            return 1;
        }
    }else if(answers->locY){
        for(int x2 = 0; x2 < 9; x2++){
            if(board[x2][answers->locY+(y*3)-1].choices[z] && x2 != (x*3) && x2 != (x*3)+1 && x2 != (x*3)+2){
                board[x2][answers->locY+(y*3)-1].choices[z] = 0;
                difference++;
            }
        }
        if(difference){
            printf("Fant en stripe av tallet %d i x = %d\n", z+1, answers->locY+(y*3));
            return 1;
        }
    }
    return 0;
}

int shadowChoice(void){
    forslag answers; //hvilket kolonne eller rad i kvadranten(0,1,2,3->0 = ingen)
    int totalAnswers = 0; //Antall svar koden fant

    //x = x-koor, y = y-koor, z = spillertallene fra 1-9
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3; y++){
            for(int z = 0; z < 9; z++){
                if(kvadrantSjekk(x,y,z, &answers)){
                    totalAnswers += fixChoiceLine(x,y,z,&answers);
                }
            }

        }
    }
    return totalAnswers;
}

void numberUpdate(int x, int y, int z, test number[]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[(x*3)+i][(y*3)+j].choices[z]){
                number[z].ammount++;
                number[z].locX = 3*x+i;
                number[z].locY = 3*y+j;
            }
        }
    }
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
                numberUpdate(i,j,x,number);
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

    totalAnswers += onlyChoice();
    totalAnswers += shadowChoice();

    return totalAnswers;
}


int main(void){
    initBoard();
    printBoard();
    
    while(answer());

   printf("\nBrettet ser nå slik ut: \n");
   printBoard();

    while(1){
        printChoices();
        printf("\n");
    }
}