// Author : Asad Iqbal
// Programming language : C
// Date Coded: 1/6/2018
// Simple Harmony game for command line

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BROW 5
#define BCOL 4

typedef struct blocks{
    int number;
    char letter;
} block ;

void printBoard(block **board, int turns){
    int i,j;

    system("cls");

    printf(" -------- -------- -------- --------\n");

    for(i=0;i<BROW;i++){
        for(j=0;j<BCOL;j++){
            printf("|       |");
        }
        printf("\n");
        for(j=0;j<BCOL;j++){
            printf("|   %c   |",board[i][j].letter);
        }
        printf("\n");
        for(j=0;j<BCOL;j++){
            if(board[i][j].number<10){
                printf("|   %i   |",board[i][j].number);
            }else{
                printf("|   %i  |",board[i][j].number);
            }
        }
        printf("\n");
        printf(" -------- -------- -------- --------\n");
    }

    printf("Turns taken: %i\n",turns);

}

void swap(block **board, int one, int two){
    int i,j, x1,x2,y1,y2;
    block hold;

    if((one >0 && one <13) && (two > 0 && two <13)){

        for(i=0;i<BROW;i++){
            for(j=0;j<BCOL;j++){
                if(board[i][j].number==one){
                    x1=i;
                    y1=j;
                }

                if(board[i][j].number==two){
                    x2=i;
                    y2=j;
                }
            }// for i ends
        }// for j ends

        // printf("one=%i, x1=%i, y1=%i\n",one,x1,y1);

        hold.number=board[x1][y1].number;
        hold.letter=board[x1][y1].letter;

        board[x1][y1].number=board[x2][y2].number;
        board[x1][y1].letter=board[x2][y2].letter;

        board[x2][y2].number=hold.number;
        board[x2][y2].letter=hold.letter;

    }// if limits

}


void init(block **board){
    int i,j,one=0,two=0;

    for(i=0;i<BROW;i++){
        for(j=0;j<BCOL;j++){
            if(i==0){
                board[i][j].number=0;
                board[i][j].letter='A';
            }else if(i==4){
                board[i][j].number=13;
                board[i][j].letter='E';
            }else{
                if(i==1){
                    board[i][j].letter='B';
                }else if(i==2){
                    board[i][j].letter='C';
                }else{
                    board[i][j].letter='D';
                }
                board[i][j].number=((i-1)*4)+(j+1);
            }
        }// for j ends
    }//for i ends

    for(i=0; i<20;i++){ // shuffle 20 times
        one=0; two=0;
        while(one==two){
            while(!(one>0 && one<13)){
                one=(rand()%11)+1;
            }

            while(!(two>0 && two<13)){
                two=(rand()%11)+1;
            }
        }

        //printf("one=%i, two=%i\n",one,two);

        swap(board,one,two);
    }// for i ends

}

int checkGameComplete(block **board){
    int i,j,check=1,complete=1;

    for(i=1;i<(BROW-1);i++){
        for(j=0;j<BCOL;j++){
            if(check==board[i][j].number){
                check=check+1;
            }else{
                complete=0;
            }
        }// for j ends
    }//for i ends

    if(complete==1){
        return 1;
    }

    return 0;
}

void printfile(void){
    FILE *scorehof;
    char name[10] = "";
    int moves = 0;

    /* Open file in read mode */
    scorehof = fopen("score.txt", "r");


    if (scorehof == NULL) {		/* Print error if files is missing */
        printf("\nSCORE FILE NOT FOUND!");
    } else {

        printf("Name	Moves\n");
        printf("==============");

        while ((fscanf(scorehof, "%s %i", &name, &moves)) > 0) {	/* Read through file till end and print all entries */
            printf("\n%s	%i", name, moves);
        }
    }

    /* Close file */
    fclose(scorehof);
}

void writefile(char name[],int moves){
    FILE *scorehof;

    /* Open file in append mode */
    scorehof = fopen("score.txt", "a");


    if (scorehof == NULL) {		/* Print error if file is missing */
        printf("\nSCORE FILE NOT FOUND!");
    } else {
        fprintf(scorehof, "\n%s %i", name, moves);	/* Append name of player and steps to file */
    }

    /* Close file */
    fclose(scorehof);
}


int main() {
    int i, turns=0, input1=-999,input2=-999, error=0;
    block **board;
    char name[50];
    time_t t;
    srand((unsigned) time(&t));

    board = (block **)malloc(sizeof(block *) * BROW);
    for (i = 0; i < BROW; i++) {
        board[i] = (block *)malloc(sizeof(block) * BCOL);
    }

    init(board);

    printf("***********************WELCOME*******************\n");
    printf("*********************ASAD IQBAL******************\n");
    printf("***********************HARMONY*******************\n");
    printf("\n-------------PREVIOUS HIGHSCORES---------------\n");
    printfile();

    printf("\nPlease enter you name to start the game:");
    scanf("%s",&name);

    do{
        error=0;
        printBoard(board, turns);

        fflush(stdin);

        printf("Select first box, or press 0 to exit: ");
        scanf("%i",&input1);

        if(input1==0){
            break;
        }

        if(input1<1 || input1>12){
            printf("\n First box does not exist! please select values between 1 and 12");
            error=1;
        }

        if(error==0){
            printf("\nSelect second box: ");
            scanf("%i",&input2);

            if(input2<1 || input2>12){
                printf("\n Second box does not exist! please select values between 1 and 12");
                error=1;
            }
        }

        if(error==0){
            swap(board, input1, input2);
            turns=turns+1;
        }
    }while(input1!=0 && (checkGameComplete(board)==0));

    if(checkGameComplete(board)==1){
        printBoard(board, turns);
        printf("\n\nCONGRATS!! You won! it took you only %i turns to solve the puzzle",turns);
        writefile(name,turns);
    }


    return 0;
}
