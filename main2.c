#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Spot[] = {1,2,3,4,5,6,7,8,9};
int turn = 1; 
int difficulty; // Difficulty --> 1: Easy, 2: Medium, 3: Impossible
int Player1[] = {0,0,0,0,0,0,0,0,0};
int Player2[] = {0,0,0,0,0,0,0,0,0};
int winning[8][3] = {
    {1,2,3}, {4,5,6}, {7,8,9},
    {1,4,7}, {2,5,8}, {3,6,9},
    {1,5,9}, {3,5,7}
};

char SelectionChar(int PlayerNumber) { // Player character selection
    switch(PlayerNumber) {
        case 1:
            return 'X'; // Player 
        case 0:
            return ' ';
        case 2:
            return 'O'; // Computer
    }
}

void draw(int Grid[9], int Player1[9], int Player2[9]){ // draw the board out. 

//after creating interface GUI. need to change. as not everytime the page will refresh and draw out the board again.

    int board[9];

    for (int i=0; i<9; i++){

        if (Grid[i] != 0){ // means not taken by anyone. 
            board[i] = SelectionChar(0); //not owned by anyone
            continue;
        } else { // taken by someone.

            for (int j=0; j<9; j++){ // == 0 means taken by someone
                if (i+1 == Player1[j]){ // loop within player1 own list. see whether is taken by him anot
                    board[i] = SelectionChar(1); // if yes. draw on the board
                    break;
                }
                if (i+1 == Player2[j]){ // loop within player2 own list. see whether is taken by him anot
                    board[i] = SelectionChar(2); // if yes. draw on the board
                    break;
                }
            }

        }
    }

    printf("\nX: Player, O: Computer\n");
    printf(" %c | %c | %c\n",board[0],board[1],board[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",board[3],board[4],board[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c\n",board[6],board[7],board[8]);
}

void printarray(int A[], char str[], int n){ // Array to print, Message within the printing starting "Array of ", size of the array 

    printf("\n Array of %s\n", str);

    for (int i=0; i<n; i++){

        printf("%d ", A[i]);

    }

    printf("\n");

}

bool ArrayCompare(int A[], int B[], int n, int m) //A is given array, B is the winning condition array e.g. {3,5,7}, size of A, size of B array
{
    int checker = 0; // if reach 3 means, there is 3 similar element A and B
 
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 3; j++){
            if (A[i] == B[j]){
                checker++;
                if (checker == 3){
                    return true;
                }
            }
        }
    }
    return false;
}

int wincondition(int Player[]){ // Given Array (Player1/2/Computer), Check with all the winning possibilities

    int n = sizeof(Player1) / sizeof(int); //size of the array
    int CPlayer[n]; 

    for (int i = 0; i<n; i++){ // Replicate Player board given
        CPlayer[i] = Player[i]; 
    }

    //printarray(CPlayer, "choices of Player", n);

    int specificwinning[3]; //define an array to replicate one of the winning possibility
    int numberofrow = sizeof(winning)/sizeof(winning[0]); //Winning rows possibilities. Hence, 8.

    for (int j = 0; j < numberofrow; j++){ 
        for (int i = 0; i < 3; i++){ // Replicate one winning possibility
            specificwinning[i] = winning[j][i]; //winning is the variable defined ontop. 
            // printf("%d ", specificwinning[i]);
        }

        for (int k = 0; k < numberofrow; k++){ // checking with Player array 
            if (ArrayCompare(CPlayer, specificwinning, n, 3)) return 1; // return true if MATCHED! Means someone won.
        }
    }
    return 0;

}

int playermove(){ // Player move turn. 
        int playermove;

        printf("Enter your move: ");
        scanf("%d", &playermove); 

        if (Spot[playermove-1] == 0){ //spot taken
            printf("Please keyed in a spot that is not taken\n");
            return 0; //0 --> call again
        } else if (playermove > 9 || playermove < 0){ //invalid spot
            printf("Please keyed in a correct input\n");
            return 0; //0 --> call again
        } else { //valid spot
            Spot[playermove-1] = 0;
            Player1[turn-1] = playermove;
        }

    return 1;
}

int minimax(int CopySpot[9], int Playerturn, int turncopy, bool imperfect){ //  Playerturn = -1 or 1 . Player 1 (-1)  and Computer player2 (1)

    ++turncopy;
    if (imperfect){ //if medium mode. thn only go one layer of searches.
        int winner = wincondition(Player2); // return 1 if win. 0 if lose // test to see if computer won before moving to next step
        if(winner != 0) {
            --turncopy; 
            return 1; // give positive points if computer win.
        }

        int move = -1;
        int score = 2;//Losing moves are preferred to no move
        int i;
        for(i = 1; i < 10; ++i) {//For all moves,
            if(CopySpot[i-1] != 0) {//If legal,
                CopySpot[i-1] = 0;
                Player1[turncopy-1] = i;

                int insidewinner = wincondition(Player1); //return 1 if player wins. and 0 if lose
                int thisScore = (insidewinner != 0)?-1:0;

                if(thisScore < score) {
                    score = thisScore;
                    move = i;
                }//Pick the one that's worst for the opponent
                CopySpot[i-1] = i;
                Player1[turncopy-1] = 0;
            }
        }
        --turncopy;
        if(move == -1) {return 0;};
        return score;
    } else {
        if (Playerturn == (-1)){ // PLayerturn = -1, PLayer 1 turn
            int winner = wincondition(Player2); // return 1 if win. 0 if lose // test to see if computer won before moving to next step
            if(winner != 0) {
                --turncopy; 
                return 1; // give positive points if computer win.
            }

            int move = -1;
            int score = 2;//Losing moves are preferred to no move
            int i;
            for(i = 1; i < 10; ++i) {//For all moves,
                if(CopySpot[i-1] != 0) {//If legal,
                    CopySpot[i-1] = 0;
                    Player1[turncopy-1] = i;
                    int thisScore = minimax(CopySpot, Playerturn*-1, turncopy, false);
                    if(thisScore < score) {
                        score = thisScore;
                        move = i;
                    }//Pick the one that's worst for the opponent
                    CopySpot[i-1] = i;
                    Player1[turncopy-1] = 0;
                }
            }
            --turncopy;
            if(move == -1) {return 0;};
            return score;

        } else { // Playerturn = 1. Computer turn
            int winner = wincondition(Player1); // return 1 if win. 0 if lose
            if(winner != 0) {
                --turncopy; 
                return -1; // give negative points if player 1 wins the game. disadvatange for computer
            }

            int move = -1;
            int score = -2;//Losing moves are preferred to no move
            int i;
            for(i = 1; i < 10; ++i) {//For all moves,
                if(CopySpot[i-1] != 0) {//If legal,
                    CopySpot[i-1] = 0;
                    Player2[turncopy-1] = i;
                    int thisScore = minimax(CopySpot, Playerturn*-1, turncopy, false);
                    if(thisScore > score) {
                        score = thisScore;
                        move = i;
                    }//Pick the one that's worst for the opponent
                    Player2[turncopy-1] = 0;
                    CopySpot[i-1] = i;
                }
            }
            --turncopy;
            if(move == -1) {return 0;};
            return score;
    }
    }
}

int worstmove(bool worst, int foundScore, int Storedscore, int move, int i){
    if (worst){
        if(foundScore < Storedscore) { // replace the score if the found score in [i] is lower than the stored 
            return 1;
        }
    } else {
        if(foundScore > Storedscore) { // replace the score if the found score in [i] is higher than the stored 
            return 1;
        } 
    }

    // allow more flexible move. rather than same move throughout all program runs.
    if (foundScore == Storedscore){
        int random = rand()%2; //1 or 0
        if (random == 0){ // if 1 then there is a chance that the computer changes and select another move which is the same score as storedscore. 
            return 1;
        }
    }
    return 0;
}

int computermove(int turncopy){ // Computer move turn.
        int computermove, Storedscore = -2, move, foundScore; // defined storedscore as -2 so it will be replaced by whatever move comes in.

        printarray(Spot, "Array of Available Spot", 9);
        int random = rand()%9; // produce number from 0 to 9. 
        int mistake = (random <= 4)?1:0; // if 0 to 4 thn make a mistake. 5, 6, 7, 8 and 9 thn use optimal moves. 50% chance of making mistakes. 50% rate

        for (int i=1; i<10; i++){ // loop through all possible moves.
            if(Spot[i-1] != 0){ //the move can be made
                Spot[i-1] = 0;
                Player2[turncopy-1] = i;

                if (difficulty == 1 || difficulty == 3){
                    foundScore = minimax(Spot, (-1), turncopy, false); // the current [i] move score.
                } else { // else 2. medium mode. imperfect minimax
                    foundScore = minimax(Spot, (-1), turncopy, true); // turncopy replace by 0. Since it is going to read only next move. it does not need to keep track of turn
                }

                printf("foundScore %d: %d\n", i, foundScore);
                Player2[turncopy-1] = 0; //place back the board
                Spot[i-1] = i;

                // difficult = 1 (easy) --> uses percentage to show the chances of making mistakes
                if (difficulty == 1){
                    printf("mistake: %i\n", mistake);
                    if (mistake){ // mistake occurs. do a stupid move
                        Storedscore = 2; 
                        if(worstmove(true, foundScore, Storedscore, move, i)){
                            Storedscore = foundScore; 
                            move = i;
                        }
                    } else {
                        if(worstmove(false, foundScore, Storedscore, move, i)){
                            Storedscore = foundScore; 
                            move = i;
                        }
                    }

                } else {
                    // difficult = 3 (impossible). --> minimax | difficult = 2 (medium) --> imperfect minimax
                    if(worstmove(false, foundScore, Storedscore, move, i)){
                        Storedscore = foundScore; 
                        move = i;
                    }
                }


            }
        }

        printf("computermove: %d\n", move); // use the best possible move 
            Spot[move-1] = 0;
            Player2[turncopy-1] = move;
        //}

    return 1;
}

int flipcoin(){ // flip a coin to see who start first
    int n = 5, random, coin = 0;
    time_t t;
        
    /* Intializes random number generator */
    srand((unsigned) time(&t)); //create a seed that uses time to randomise.

    /* Print 5 random numbers from 0 to 1 */
    for(int i = 0 ; i < 5 ; i++ ) { // flip the coin each side if the random number is 1. Make it more random
        random = rand()%2;
        if (random == 1 && coin == 0){
            coin = 1;
        } else if (random == 1 && coin == 1){
            coin = 0;
        }
    }

    printf("Flipping Coin... ...\n"); //if 0 then computer turn first. if 1 then player turn first.
    printf("0: Computer turn, 1: Player turn\n"); 
    printf("coin: %d\n", coin); 

    return coin;
}

int main(){
    
    int coin;

    coin = flipcoin();

    printf("Select Difficulty --> 1: Easy, 2: Medium, 3: Impossible\n");
    scanf("%d", &difficulty);
    if (difficulty < 1 || difficulty > 3){
        printf("Please select a correct difficulty level.");
        return 0;
    }

    for (int i=0; turn<10; turn++){ // becuz turn started at 1. it needs to stop at 10. for a completion of 9 turns
            printf("\nTurn: %d\n", turn);
        if (coin){
            if (playermove() == 0){turn--; continue;} //if 0, means keyed in wrong input. call again
            // printarray(Spot, "Available Spot", n);
            // printarray(Player1, "Player 1 Set", n);
            coin = 0; //pass to computer turn
            if (wincondition(Player1)) {
                printf("\nPlayer 1 won\n"); 
                draw(Spot, Player1, Player2); 
                break; //if 1, then break loop. end game
            }

        } else {
            if (computermove(turn) == 0){turn--; continue;} //if 0, means keyed in wrong input. call again
            // printarray(Spot, "Available Spot", n);
            // printarray(Player2, "Computer Set", n);
            coin = 1; //pass to player turn
            if (wincondition(Player2)) {
                printf("\nPlayer 2 won\n"); 
                draw(Spot, Player1, Player2); 
                break; //if 1, then break loop. end game
            }
        }
            printf("\n");
            draw(Spot, Player1, Player2); // after every turn. draw out the board. 

    }
    
    if (wincondition(Player1) == 0 && wincondition(Player2) == 0){
        printf("It is a draw!\n"); 
    }

    return 0;
}