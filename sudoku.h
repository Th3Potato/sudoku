#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct coor{
    int number;
    int choices[9];
} coor;

typedef struct coor1{
    int locX;
    int locY;
} coor1;

typedef struct coor2{
    int locX;
    int locY;
    int locX2;
    int locY2;
} coor2;

typedef struct coorAmmount{
    int ammount;
    int locX;
    int locY;
} coorAmmount;

typedef struct coor2Ammount{
    int ammount;
    int locX;
    int locY;
    int locX2;
    int locY2;
} coor2Ammount;

typedef struct values{
    int value1;
    int value2;
} values;

//om kommentarer skal være på eller av
int comments = 1;

//Brettet alle algoritmene jobber med/på(global variabel)
coor board[9][9];


//kopierer brettet fra source til til dest
void copyBoard(coor source[9][9], coor dest[9][9]); 

//sjekker om brettet er helt fullt
int finished(void); 

//Setter alle mulighetene til 1(på starten av programmet)
void initChoices(void); 

//Oppdaterer mulighetene til de i samme rad/kollonne/kvadrant til gitt koordinat
void updateChoices(int x, int y); 

//finner ut om to arrays har samme muligheter
int arrayEqual(int arr1[], int arr2[]); 

//finner antall muligeheter i en array
int choiceAmmount(int arr[]); 

//finner de to mulighetene til en array(funker bare hvis det er 2 totalt)
values arrayValues(int arr[]); 

//nullsetter arrayen
void resetArray(int arr[]); 

//Lar spilleren skrive inn brettet. Fyller inn tallene og oppdaterer mulighetene til brettet
void initBoard(void);

//printer brettet slik det ser ut
void printBoard(void);

//Lar deg velge en koordinat du kan sjekke mulighetene til
void printChoices(void);

//lager en string av brettet
char *boardToString(void);

//sjekker om brettet er unikt
int isUnique(char *board, char **boardArr);


//------------Hjelpealgoritmer------------:

//(Brukes i onlyOnePlace()) sjekker hvor mange av muligheten z som finnes i en gitt kvadrant
void numberUpdate(int x, int y, int z, coorAmmount number[]);

//(Brukes i updatePair())finner 2 plasser i en hel kolonne/rad som kun inneholder de 2 samme tallene
coor2Ammount getPair(void); 

//(ETTER å ha kjørt onlyTwo()): fjerner de andre mulighetene i de to stedene onlyTwo fant
int removeRest(int x, int x2, int y, int y2, int tall1, int tall2);

//(Brukes i shadowchoice()) finner hvilken radnummer/kolonnenummer der de to eneste mulighetene i kvadranten er
int kvadrantSjekk(int x, int y, int tall, coor1 *answers);

//(Brukes i shadowChoice()) fjerner de to mulighetene fra resten av raden/kolonnen(alt annen enn kvadranten)
int fixChoiceLine(int x, int y, int z, coor1 *answers);

//(Brukes i updateRowCol()) fjerner muligheten fra resten av kvadranten
int rowcolUpdate(int x, int y, int first, int sec, int third, int num);

//(Brukes i rowcolFix()) sjekker om det er 2 eller 3 tall som er funnet
int updateRowCol(int x, int y, int first, int sec, int third, int z, int ammount);


//------------Løsealgoritmer------------:

//finner om det er en koordinat som kun kan ha ett tall
int onlyChoice(void);

//finner det eneste stedet i en rad/kolonne/kvadrant som kan ha ett tall
int onlyOnePlace(void);

//Finner TO tall som kun kan være i de samme TO stedene i en rad/kolonne/kvadrant
int onlyTwo(void);

//bruker getPair og fjerner resten av kolonnens/radens muligheter av de 2 samme tallene
int updatePair(void); 

//leter i en kvadrant til den finner to muligheter som kun er i samme rad/kolonne
int shadowChoice(void);

//finner 2 eller 3 steder i en kolonne/rad der ett tall er
int rowcolFix(void);


//kjører alle algoritmene i funksjonen
int runAlgorithms(void);

//Prøve og feile til den klarer å fullføre brettet
char **tester(void); 