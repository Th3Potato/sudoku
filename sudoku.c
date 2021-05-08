#include "sudoku.h"

void copyBoard(coor source[9][9], coor dest[9][9]){
    for(int x = 0; x < 9; x++){
        for(int y = 0; y < 9; y++){
            dest[x][y].number = source[x][y].number;
            for(int choice = 0; choice < 9; choice++){
                dest[x][y].choices[choice] = source[x][y].choices[choice];
            }
        }
    }
}

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

//finner ut om to arrays har samme muligheter
int arrayEqual(int arr1[], int arr2[]){
    for(int i = 0; i < 9; i++){
        if(arr1[i] != arr2[i]){
            return 0;
        }
    }
    return 1;
}

int choiceAmmount(int arr[]){
    int size = 0;
    for(int i = 0; i < 9; i++){
        if(arr[i]){
            size++;
        }
    }
    return size;
}

values arrayValues(int arr[]){
    values tall;
    tall.value1 = -1; tall.value2 = -1;

    for(int i = 0; i < 9; i++){
        if(arr[i] && tall.value1 < 0){
            tall.value1 = i;
        }else if(arr[i] && tall.value1 >= 0){
            tall.value2 = i;
        }
    }
    return tall;
}

void resetArray(int arr[]){
    for(int num = 0; num < 9; num++){
        arr[num] = 0;
    }
}

coor2Ammount getPair(void){
    coor2Ammount answer;
    answer.locX = 0; answer.locY = 0; answer.locX2 = 0; answer.locY2 = 0; answer.ammount = 0;

    for(int x = 0; x < 8; x++){
        for(int y = 0; y < 8; y++){
            if(choiceAmmount(board[x][y].choices) == 2){
                for(int y2 = y+1; y2 < 9; y2++){
                    if(arrayEqual(board[x][y].choices,board[x][y2].choices)){
                        answer.ammount = 1;
                        answer.locX = x;
                        answer.locX2 = x;
                        answer.locY = y;
                        answer.locY2 = y2;
                        return answer;
                    }
                }
                for(int x2 = x+1; x2 < 9; x2++){
                    if(arrayEqual(board[x][y].choices,board[x2][y].choices)){
                        answer.ammount = 1;
                        answer.locX = x;
                        answer.locX2 = x2;
                        answer.locY = y;
                        answer.locY2 = y;
                        return answer;
                    }
                }
            }
        }
    }
    return answer;
}

int updatePair(void){
    coor2Ammount answer = getPair();
    values tall;
    int tall1; int tall2;
    int totalAnswers = 0;
    int difference = 0;

    if(answer.ammount){
            tall = arrayValues(board[answer.locX][answer.locY].choices);
            tall1 = tall.value1; tall2 = tall.value2;

        if(answer.locX == answer.locX2){
            int x = answer.locX;
            for(int y = 0; y < 9; y++){
                if(y != answer.locY && y != answer.locY2){
                    if(board[x][y].choices[tall1] || board[x][y].choices[tall2]){
                        //printf("fjerner tallene: %d og %d fra: %d,%d\n", tall1+1, tall2+1, y+1, x+1);
                        board[x][y].choices[tall1] = 0;
                        board[x][y].choices[tall2] = 0;
                        difference++;
                    }
                }
            }
            if(difference){
                printf("fant parene %d og %d i: %d,%d og %d,%d\n", tall1+1, tall2+1, 
                answer.locY+1, x, answer.locY2+1, x+1);
                totalAnswers++;
            }
            difference = 0;
        }
        

        if(answer.locY == answer.locY2){
            int y = answer.locY;
            for(int x = 0; x < 9; x++){
                if(x != answer.locX && x != answer.locX2){
                    if(board[x][y].choices[tall1] || board[x][y].choices[tall2]){
                        //printf("fjerner tallene: %d og %d fra: %d,%d\n", tall1+1, tall2+1, y+1, x+1);
                        board[x][y].choices[tall1] = 0;
                        board[x][y].choices[tall2] = 0;
                        difference++;
                    }
                }
            }
            if(difference){
                printf("fant parene %d og %d i: %d,%d og %d,%d\n", tall1+1, tall2+1, 
                y+1, answer.locX+1, y+1, answer.locX2+1);
                totalAnswers++;
            }
            difference = 0;
        }
    }

    return totalAnswers;
}

int removeRest(int x, int x2, int y, int y2, int tall1, int tall2){
    int difference = 0;

    for(int choice = 0; choice < 9; choice++){
        if(choice != tall1 && choice != tall2){
            if(board[x][y].choices[choice]){    
                //printf("fjernet tallet %d (!=: %d eller %d) fra %d,%d\n", choice+1, tall1+1, tall2+1, y+1, x+1);
                board[x][y].choices[choice] = 0;
                difference++;
            }
            if(board[x2][y2].choices[choice]){
                //printf("fjernet tallet %d (!=: %d eller %d) fra %d,%d\n", choice+1, tall1+1, tall2+1, y2+1, x2+1);
                board[x2][y2].choices[choice] = 0;
                difference++;
            }
        }
    }

    return difference;
}

int onlyTwo(void){
    int totalAnswers = 0; int difference;
    coor2Ammount arr[9]; //locX = første x koor, og locY er førte y koor. ammount er antall tall på en stripe

    //rader
    for(int x = 0; x < 9; x++){
        //tilbakestiller for hver rad
        difference = 0; 
        for(int i = 0; i < 9; i++){
            arr[i].locX = -1; arr[i].locY = -1;arr[i].locX2 = -1;arr[i].locY2 = -1; arr[i].ammount = 0;
        }

        //teller opp antall steder man kan finne hvert tall i en rad
        for(int num = 0; num < 9; num++){
            for(int y = 0; y < 9; y++){
                if(board[x][y].choices[num]){
                    if(arr[num].locY < 0){
                        arr[num].locY = y;
                    }else{
                        arr[num].locY2 = y;
                    }
                    arr[num].ammount++;
                }
            } 
        }

        //Sjekker antall
        for(int num = 0; num < 8; num++){
            if(arr[num].ammount == 2){
                for(int num2 = num+1; num2 < 9; num2++){
                    if(arr[num2].ammount == 2){
                        //Hvis disse tallene har samme y verdier(har alltid samme x): fjern andre alternativer
                        if(arr[num].locY == arr[num2].locY && arr[num].locY2 == arr[num2].locY2){
                            difference = removeRest(x,x,arr[num].locY,arr[num].locY2,num,num2);
                        }
                    }
                    if(difference){
                        printf("fant kun tallene %d og %d i %d,%d og %d,%d\n", 
                        num+1, num2+1, arr[num].locY+1, x+1, arr[num].locY2+1, x+1);
                        totalAnswers++;
                    }
                    difference = 0;
                }
            }
        }
    }
    //kolonner
    for(int y = 0; y < 9; y++){
        //tilbakestiller for hver rad
        difference = 0; 
        for(int i = 0; i < 9; i++){
            arr[i].locX = -1; arr[i].locY = -1;arr[i].locX2 = -1;arr[i].locY2 = -1; arr[i].ammount = 0;
        }

        //teller opp antall steder man kan finne hvert tall i en rad
        for(int num = 0; num < 9; num++){
            for(int x = 0; x < 9; x++){
                if(board[x][y].choices[num]){
                    if(arr[num].locX < 0){
                        arr[num].locX = x;
                    }else{
                        arr[num].locX2 = x;
                    }
                    arr[num].ammount++;
                }
            } 
        }

        for(int num = 0; num < 8; num++){
            if(arr[num].ammount == 2){
                for(int num2 = num+1; num2 < 9; num2++){
                    if(arr[num2].ammount == 2){
                        //Hvis disse tallene har samme x verdier(har alltid samme y): fjern andre alternativer
                        if(arr[num].locX == arr[num2].locX && arr[num].locX2 == arr[num2].locX2){
                            difference = removeRest(arr[num].locX,arr[num].locX2,y,y,num,num2);
                        }
                    }
                    if(difference){
                        printf("fant kun tallene %d og %d i %d,%d og %d,%d\n", 
                        num+1, num2+1, y+1, arr[num].locX+1, y+1, arr[num].locX2+1);
                        totalAnswers++;
                    }
                    difference = 0;
                }
            }
        }
    }

    //sjekker i kvadranter
    for(int x = 0; x < 3; x++){
        for(int y = 0; y < 3;y++){
            difference = 0; 
            for(int i = 0; i < 9; i++){
                arr[i].locX = -1; arr[i].locY = -1;arr[i].locX2 = -1;arr[i].locY2 = -1; arr[i].ammount = 0;
            }
            for(int num = 0; num < 9; num++){
                for(int x2 = 0; x2 < 3; x2++){
                    for(int y2 = 0; y2 < 3; y2++){
                        if(board[x*3+x2][y*3+y2].choices[num]){
                            if(arr[num].locX < 0){
                                arr[num].locX = x*3+x2;
                                arr[num].locY = y*3+y2;
                            }else{
                                arr[num].locX2 = x*3+x2;
                                arr[num].locY2 = y*3+y2;
                            }
                            arr[num].ammount++;
                        }
                    }
                }
            }

            for(int num = 0; num < 8; num++){
                if(arr[num].ammount == 2){
                    for(int num2 = num+1; num2 < 9; num2++){
                        if(arr[num2].ammount == 2){
                            if(arr[num].locX == arr[num2].locX && arr[num].locX2 == arr[num2].locX2
                            && arr[num].locY == arr[num2].locY && arr[num].locY2 == arr[num2].locY2){
                                difference = removeRest(arr[num].locX,arr[num].locX2,arr[num].locY,arr[num].locY2,num,num2);
                            }
                        }
                        if(difference){
                            printf("fant kun tallene %d og %d i %d,%d og %d,%d (kvadrant)\n", 
                            num+1, num2+1, arr[num].locY+1, arr[num].locX+1, arr[num].locY2+1, arr[num].locX2+1);
                            totalAnswers++;
                        }
                        difference = 0;
                    }
                }
            }
        }
    }

    return totalAnswers;
}

//parameter tall er tallverdiene den sjekker for
int kvadrantSjekk(int x, int y, int tall, coor1 *answers){
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

int fixChoiceLine(int x, int y, int z, coor1 *answers){
    int difference = 0;
    if(answers->locX){
        for(int y2 = 0; y2 < 9; y2++){
            if(board[answers->locX+(x*3)-1][y2].choices[z] && y2 != (y*3) && y2 != (y*3)+1 && y2 != (y*3)+2){
                board[answers->locX+(x*3)-1][y2].choices[z] = 0;
                difference++;
            }
        }
        if(difference){
            printf("fant en stripe av tallet %d i y = %d\n", z+1, answers->locX+(x*3));
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
            printf("fant en stripe av tallet %d i x = %d\n", z+1, answers->locY+(y*3));
            return 1;
        }
    }
    return 0;
}

int shadowChoice(void){
    coor1 answers; //hvilket kolonne eller rad i kvadranten(0,1,2,3->0 = ingen)
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

int rowcolUpdate(int x, int y, int first, int sec, int third, int num){
    int difference = 0;  

    if(y == -1){
        int kvadrantX = x / 3;
        int kvadrantY = first / 3; 
        
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(kvadrantX*3+i != x && kvadrantY*3+j != (first || sec || (third >= 0))){
                    if(board[kvadrantX*3+i][kvadrantY*3+j].choices[num]){
                        //printf("fjernet fra koor: %d,%d\n", kvadrantY*3+j+1, kvadrantX*3+i+1);
                        board[kvadrantX*3+i][kvadrantY*3+j].choices[num] = 0;
                        difference++;
                    }
                }
            }
        }
    }else if(x == -1){
        int kvadrantX = first / 3;
        int kvadrantY = y / 3; 
        
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(kvadrantY*3+i != y && kvadrantX*3+j != (first || sec || (third >= 0)) ){
                    //printf("kvadY = %d, y = %d, kvadX = %d, x1 = %d, x2 = %d\n", kvadrantY*3+i+1, y+1, kvadrantX*3+j+1, first+1, sec+1);
                    if(board[kvadrantX*3+j][kvadrantY*3+i].choices[num]){
                        //printf("fjernet fra koor: %d,%d\n", kvadrantY*3+i+1, kvadrantX*3+j+1);
                        board[kvadrantX*3+j][kvadrantY*3+i].choices[num] = 0;
                        difference++;
                    }
                }
            }
        }
    }

    return difference;
}

int updateRowCol(int x, int y, int first, int sec, int third, int z, int ammount){
    int difference;
    int totalAnswers = 0;
    
    if(ammount == 2){
        if(first / 3 == sec / 3){
            difference = rowcolUpdate(x,y,first,sec,third,z);
            if(difference){
                if(x == -1){
                    printf("fant tallet: %d i %d,%d og %d,%d\n", z+1, y+1, first+1, y+1, sec+1);
                }else if(y == -1){
                    printf("fant tallet: %d i %d,%d og %d,%d\n", z+1, first+1, x+1, sec+1, x+1);
                }
                totalAnswers++;
            }
        }
    }else if(ammount == 3){
        if(first / 3 == sec / 3 && first / 3 == third / 3){
            difference = rowcolUpdate(x,y,first,sec,third,z);
            if(difference){
                if(x == -1){
                    printf("fant tallet: %d i %d,%d og %d,%d og %d,%d\n", z+1, y+1, first+1, y+1, sec+1, y+1, third+1);
                }else if(y == -1){
                    printf("fant tallet: %d i %d,%d og %d,%d og %d,%d\n", z+1, first+1, x+1, sec+1, x+1, third+1, x+1);
                }
                totalAnswers++;
            }
        }
    }
    return totalAnswers;
}

int rowcolFix(void){
    int ammount;
    int first; int sec; int third;
    int totalAnswers = 0;
    int difference = 0;

    for(int z = 0; z < 9; z++){
        for(int x = 0; x < 9; x++){
            ammount = 0;
            first = -1; sec = -1; third = -1;
            for(int y = 0; y < 9; y++){
                if(!board[x][y].number){
                    if(board[x][y].choices[z]){
                        if(ammount == 0){
                            first = y;
                        }else if(ammount == 1){
                            sec = y;
                        }else if(ammount == 2){
                            third = y;
                        }
                        ammount++;
                    }
                }
            }
            int y = -1;
            totalAnswers += updateRowCol(x,y,first,sec,third,z,ammount);
        }
    }

    for(int z = 0; z < 9; z++){
        for(int y = 0; y < 9; y++){
            ammount = 0;
            first = -1; sec = -1; third = -1;
            for(int x = 0; x < 9; x++){
                if(!board[x][y].number){
                    if(board[x][y].choices[z]){
                        if(ammount == 0){
                            first = x;
                        }else if(ammount == 1){
                            sec = x;
                        }else if(ammount == 2){
                            third = x;
                        }
                        ammount++;
                    }
                }
            }
            int x = -1;
            totalAnswers += updateRowCol(x,y,first,sec,third,z,ammount);
        }
    }
    return totalAnswers;
}

void numberUpdate(int x, int y, int z, coorAmmount number[]){
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

int onlyOnePlace(void){
    int numbersY[9];
    int numbersX[9];
    coorAmmount number[9];
    
    memset(numbersY, 0, 9*sizeof(int));
    memset(numbersX, 0, 9*sizeof(int));
    for(int i = 0; i < 9; i++){
        number[i].ammount = 0;
    }

    int totalAnswers = 0;
    for(int i = 0; i < 9; i++){ //y-koor så x
        for(int j = 0; j < 9; j++){ //x-koor så y
            for(int x = 0; x < 9; x++){ //tall
                if(board[i][j].choices[x] == 1){ //i = 0, j = 8 , x = 8
                    numbersY[x]++;
                }
                if(board[j][i].choices[x] == 1){
                    numbersX[x]++;
                }
            }
        }
        for(int n = 0; n < 9; n++){ //tall
            if(numbersY[n] == 1){
                for(int j = 0; j < 9; j++){
                    if(board[i][j].choices[n] == 1){
                        printf("fant tallet: %d i posisjonen (%d,%d), eneste i raden\n", n+1, j+1, i+1);
                        totalAnswers++;
                        board[i][j].number = n+1;
                        updateChoices(i, j);
                    }
                    
                }
            }
        }
        memset(numbersY, 0, 9*sizeof(int));

        for(int n = 0; n < 9; n++){ //tall
            if(numbersX[n] == 1){
                for(int j = 0; j < 9; j++){
                    if(board[j][i].choices[n] == 1){
                        printf("fant tallet: %d i posisjonen (%d,%d), eneste i kolonnen\n", n+1, i+1, j+1);
                        totalAnswers++;
                        board[j][i].number = n+1;
                        updateChoices(j, i);
                    }
                    
                }
            }
        }
        memset(numbersX, 0, 9*sizeof(int));
    }

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            for(int x = 0; x < 9; x++){
                numberUpdate(i,j,x,number);
            }
            for(int n = 0; n < 9; n++){
                if(number[n].ammount == 1){
                    if(board[number[n].locX][number[n].locY].choices[n] == 1){
                        printf("fant tallet: %d i posisjonen (%d,%d), eneste i en kvadranten\n", n+1, number[n].locY+1, number[n].locX+1);
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

int onlyChoice(void){
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
                printf("fant tallet: %d i posisjonen (%d,%d), eneste i koor\n", answerPos+1, j+1, i+1);
                board[i][j].number = answerPos+1;
                totalAnswers++;
                updateChoices(i, j);
            }
            choices = 0;
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
    int num;
    char input[5];

    printf("Skriv inn koordinatene: \n");
    scanf("%s", &input);
    if(!strcmp(input, "cheat")){
        printf("tries: %d\n", tester());
        return;
    }else{
        x = atoi(input);
    }
    scanf("%d", &y);

    printf("Tallet: %d\n", board[y-1][x-1].number);
    for(int i = 0; i < 9; i++){
        printf("%d", board[y-1][x-1].choices[i]);
    }

    printf("\nErstatt med: (0-9)\n");
    scanf("%d", &num);
    if(num > 0 && num <= 9){
        board[y-1][x-1].number = num;
        updateChoices(y-1,x-1);
        while(runAlgorithms());
        printf("\nBrettet ser nå slik ut: \n");
        printBoard();
    }

}

//cheats
int tester(void){
    int tries = 0;
    coor copy[9][9];
    copyBoard(board,copy);

    for(int x = 0; x < 9; x++){
        for(int y = 0; y < 9; y++){
            if(!board[x][y].number){
                for(int num = 0; num < 9; num++){
                    if(board[x][y].choices[num]){
                        printf("prøver tallet: %d i (%d,%d)\n", num+1, y+1, x+1);
                        board[x][y].number = num+1;
                        updateChoices(y,x);
                        while(runAlgorithms());
                        if(finished()){
                            printf("\nBrettet ser nå slik ut: \n");
                            printBoard();
                            return tries;
                        }  
                    }
                    tries++;
                    copyBoard(copy,board);
                }
            }
        }
    }

    return tries;
}

int finished(void){
    for(int x = 0; x < 9; x++){
        for(int y = 0; y < 9; y++){
            if(!board[x][y].number){
                return 0;
            }
        }
    }
    return 1;
}

int runAlgorithms(void){
    int totalAnswers = 0;

    totalAnswers += onlyChoice();
    totalAnswers += onlyOnePlace();
    totalAnswers += shadowChoice();
    totalAnswers += updatePair();
    totalAnswers += rowcolFix();
    totalAnswers += onlyTwo();

    return totalAnswers;
}

int main(void){
    initBoard();
    printBoard();

    while(runAlgorithms());

    printf("\nBrettet ser nå slik ut: \n");
    printBoard();

    while(!finished()){
        printChoices();
        printf("\n");
    }
    printf("Sudokuen er løst!\n");
}