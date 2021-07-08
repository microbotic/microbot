#include<stdio.h>
#include<string.h>
// #include<conio.h>
#include <stdlib.h>
#include<time.h>
//10x10 2D array Boards 
char boardA[10][10],boardB[10][10];
//board for opponent guessing
char boardAA[10][10],boardBB[10][10];
char orientation,x;
int y;
//Count the number of ships sunk
int player1_sunk_count=0;
int player2_sunk_count=0;

//Set win number for sinking ships
int win_number=4;
//Set ship types (max can 4)
int total_ships_categories=1;

//check for CPU opponent
int cpu=0;

//CPU level (default 1) Easy
cpu_level=1;

//if CPU hit the ship default is 0 means did not hit
cpu_hit=0;
last_x;
last_y;
//Function prototypes
int VerticalRow(char);
int VerticalChar(int);
void PrintBoardA();
void PrintBoardB();
void PrintBoardAA();
void PrintBoardBB();
void LoadBoardA();
void LoadBoardB();
void AddShip(char (*board)[],char ,char ,int ,int , int);
void Player1Ships();
void Player2Ships();
void Player1Turn();
void Player2Turn();
void StartGame();
int Column(int);
int RandomNumber();
char RandomOrientation();

//Convert character to integer
int VerticalRow(char x) {
    //+1 is used as I'm starting from 1
  return x - 97+1;
}
//Convert integer to character
int VerticalChar(int x) {
  return x + 97;
}

int Column(int x) {
  return x + 96;
}
//Random number generate between 1-10
int RandomNumber(){
    int lower=1,upper=10;
    srand(time(0));
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}
//Random move around the hit position for CPU
int RandomTryAround(){
    int lower=1,upper=4;
    srand(time(0));
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}
//Random orientation generate 'h' or 'v'
char RandomOrientation(){
    int lower=0,upper=1;
    srand(time(0));
    int num = (rand() % (upper - lower + 1)) + lower;
    if(num==0){
        return 'h';
    }
    else
        return 'v';
}

//Player 1 board printing on console
void PrintBoardA(){
    printf("\t<----Player 1 Board---->\n\n");
 for (int i = 0; i < 10; i++) {

    if (i == 0) {
      printf("    ");
      for (int j = 0; j < 10; j++)
        printf("%d   ", j+1);
      printf("\n\n");

    }
    printf("%c   ",VerticalChar(i));
    for (int j = 0; j < 10; j++){
      printf("%c   ", boardA[i][j]);

    }
    printf("\n\n");

  }
}

//Player 2 board printing on console
void PrintBoardB(){
    printf("\t<----Player 2 Board---->\n\n");
 for (int i = 0; i < 10; i++) {

    if (i == 0) {
      printf("    ");
      for (int j = 0; j < 10; j++)
        printf("%d   ", j+1);
      printf("\n\n");

    }
    printf("%c   ",VerticalChar(i));
    for (int j = 0; j < 10; j++){
      printf("%c   ", boardB[i][j]);

    }
    printf("\n\n");

  }
}
//Player 2's opponent board 
void PrintBoardAA(){
    printf("\n\t<----Opponent Player 1 Board---->\n\n");
 for (int i = 0; i < 10; i++) {

    if (i == 0) {
      printf("    ");
      for (int j = 0; j < 10; j++)
        printf("%d   ", j+1);
      printf("\n\n");

    }
    printf("%c   ",VerticalChar(i));
    for (int j = 0; j < 10; j++){
      printf("%c   ", boardAA[i][j]);

    }
    printf("\n\n");

  }
}
//Player 1's opponent board 
void PrintBoardBB(){
    if(cpu==1)
        printf("\n\t<----Opponent CPU Board---->\n\n");
    else
        printf("\n\t<----Opponent Player 2 Board---->\n\n");
 for (int i = 0; i < 10; i++) {

    if (i == 0) {
      printf("    ");
      for (int j = 0; j < 10; j++)
        printf("%d   ", j+1);
      printf("\n\n");

    }
    printf("%c   ",VerticalChar(i));
    for (int j = 0; j < 10; j++){
      printf("%c   ", boardBB[i][j]);

    }
    printf("\n\n");

  }
}

//Storing . in Player 1 boards
void LoadBoardA(){
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
        boardA[i][j] = '.';

         }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
        boardAA[i][j] = '*';

         }
    }
}
//Storing . in Player 2 boards
void LoadBoardB(){
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
        boardB[i][j] = '.';

         }
    }
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
        boardBB[i][j] = '*';

         }
    }
}
//Function for adding specific type of ship in specific position of given board
void AddShip(char board[10][10],char orientation,char ship_type,int x,int y, int player){
    int flag=0; //flag check for again adding ship in case something went wrong
    if(orientation=='v'){ // for vertical orientation
        if(ship_type=='A' || ship_type=='a'){ //for A type ship
            for (int i = x; i < 10; i++) {
                if(x+5>10 || board[i-1][y-1]!='.'){ //ship size should not exceed from table
                    flag=1;
                    break;
                }
                if(i<x+5)//only allow 5 boxes
                board[i-1][y-1] = ship_type;
                    
            }
        }
        else if(ship_type=='B' || ship_type=='b'){//for B type ship
            for (int i = x; i <= 10; i++) {

                if(x+3>10 || board[i-1][y-1]!='.'){//ship size should not exceed from table
                    printf("%d",x);
                    flag=1;
                    break;
                }
                if(i<=x+3)//only allow 4 boxes
                board[i-1][y-1] = ship_type;
                    
            }
        }
        else if(ship_type=='C' || ship_type=='c'){//for C type ship
            for (int i = x; i <= 10; i++) {
                if(x+2>10 || board[i-1][y-1]!='.'){//ship size should not exceed from table
                    flag=1;
                    break;
                }
                if(i<=x+2)//only allow 3 boxes
                board[i-1][y-1] = ship_type;
                    
            }
        }
        else if(ship_type=='D' || ship_type=='d'){//for D type ship
            for (int i = x; i <= 10; i++) {
                if(x+1>10 || board[i-1][y-1]!='.'){//ship size should not exceed from table
                    flag=1;
                    break;
                }
                if(i<=x+1)//only allow 2 boxes
                board[i-1][y-1] = ship_type;
                    
            }
        }
        else{
            flag=1;
        }


    }
    else if(orientation=='h'){// for horizontal orientation
        if(ship_type=='A' || ship_type=='a'){
            for (int i = y; i <= 10; i++) {
                if(y+4>10 || board[x-1][i-1]!='.'){
                    flag=1;
                    break;
                }
                if(i<=y+4)
                board[x-1][i-1] = ship_type;
                    
            }
        }
        else if(ship_type=='B' || ship_type=='b'){
            for (int i = y; i <= 10; i++) {
                if(y+3>10 || board[x-1][i-1]!='.'){
                    flag=1;
                    break;
                }
                if(i<=y+3)
                board[x-1][i-1] = ship_type;
                    
            }
        }
        else if(ship_type=='C' || ship_type=='c'){
            for (int i = y; i <= 10; i++) {
                if(y+2>10 || board[x-1][i-1]!='.'){
                    flag=1;
                    break;
                }
                if(i<=y+2)
                board[x-1][i-1] = ship_type;
                    
            }
        }
        else if(ship_type=='D' || ship_type=='d'){
            for (int i = y; i <= 10; i++) {
                if(y+1>10 || board[x-1][i-1]!='.'){
                    flag=1;
                    break;
                }
                if(i<=y+1)
                board[x-1][i-1] = ship_type;
                    
            }
        }
        else{
            flag=1;
        }

    }
    else{
        flag=1;
    }
    if(flag==1){

        if(player==1){//try again for player 1
        LoadBoardA();
        Player1Ships();
        }
        else{// try again for player 2
        LoadBoardB();
        Player2Ships(); 
        }
    }
    
}
//Function for adding specific type of ship in specific position of given board by CPU
int AddShipCPU(char board[10][10],char orientation,char ship_type,int x,int y, int player){
    int flag=0; //flag check for again adding ship in case something went wrong
    if(orientation=='v'){ // for vertical orientation
        if(ship_type=='A' || ship_type=='a'){ //for A type ship
            for (int i = x; i < 10; i++) {
                if(x+5>10 || board[i-1][y-1]!='.'){ //ship size should not exceed from table
                    flag=1;
                    break;
                }
                if(i<x+5)//only allow 5 boxes
                board[i-1][y-1] = ship_type;
                    
            }
        }
        else if(ship_type=='B' || ship_type=='b'){//for B type ship
            for (int i = x; i <= 10; i++) {

                if(x+3>10 || board[i-1][y-1]!='.'){//ship size should not exceed from table
                    printf("%d",x);
                    flag=1;
                    break;
                }
                if(i<=x+3)//only allow 4 boxes
                board[i-1][y-1] = ship_type;
                    
            }
        }
        else if(ship_type=='C' || ship_type=='c'){//for C type ship
            for (int i = x; i <= 10; i++) {
                if(x+2>10 || board[i-1][y-1]!='.'){//ship size should not exceed from table
                    flag=1;
                    break;
                }
                if(i<=x+2)//only allow 3 boxes
                board[i-1][y-1] = ship_type;
                    
            }
        }
        else if(ship_type=='D' || ship_type=='d'){//for D type ship
            for (int i = x; i <= 10; i++) {
                if(x+1>10 || board[i-1][y-1]!='.'){//ship size should not exceed from table
                    flag=1;
                    break;
                }
                if(i<=x+1)//only allow 2 boxes
                board[i-1][y-1] = ship_type;
                    
            }
        }
        else{
            flag=1;
        }


    }
    else if(orientation=='h'){// for horizontal orientation
        if(ship_type=='A' || ship_type=='a'){
            for (int i = y; i <= 10; i++) {
                if(y+4>10 || board[x-1][i-1]!='.'){
                    flag=1;
                    break;
                }
                if(i<=y+4)
                board[x-1][i-1] = ship_type;
                    
            }
        }
        else if(ship_type=='B' || ship_type=='b'){
            for (int i = y; i <= 10; i++) {
                if(y+3>10 || board[x-1][i-1]!='.'){
                    flag=1;
                    break;
                }
                if(i<=y+3)
                board[x-1][i-1] = ship_type;
                    
            }
        }
        else if(ship_type=='C' || ship_type=='c'){
            for (int i = y; i <= 10; i++) {
                if(y+2>10 || board[x-1][i-1]!='.'){
                    flag=1;
                    break;
                }
                if(i<=y+2)
                board[x-1][i-1] = ship_type;
                    
            }
        }
        else if(ship_type=='D' || ship_type=='d'){
            for (int i = y; i <= 10; i++) {
                if(y+1>10 || board[x-1][i-1]!='.'){
                    flag=1;
                    break;
                }
                if(i<=y+1)
                board[x-1][i-1] = ship_type;
                    
            }
        }
        else{
            flag=1;
        }

    }
    else{
        flag=1;
    }
    if(flag==0){
        //system("pause");

         printf("\n");
    }
    else{// try again for player 2
    //system("pause");
        system("cls");
        orientation=RandomOrientation();
                x= Column(RandomNumber());
                y=RandomNumber();
        AddShipCPU(board,orientation,ship_type,VerticalRow(x),y, player);
        }
    
}
// Populate Player 1 ships
void Player1Ships(){
    char ship_category='A';
    for(int i=1;i<=total_ships_categories;i++){ // Ship A one time, Ship B two times, Ship C three times, Ship D four times
        for(int j=1;j<=i;j++){
            //system("cls");
            PrintBoardA();
            printf("\nShip %c with %d blocks:",ship_category,6-i);
            printf("\nOrientation Vertical or Horizontal e.g(v or h): ");
            scanf(" %c", & orientation);
            printf("\nx and y coordinates e.g(A 1): ");
            scanf(" %c %d", &x, &y);
            AddShip(boardA,orientation,ship_category,VerticalRow(x),y,1);  
            
        }
        ship_category++;
        //system("cls");
        PrintBoardA();
        //system("pause");
  
    }
  
    

}
// Populate Player 2 ships
void Player2Ships(){
    
     char ship_category='A';
    for(int i=1;i<=total_ships_categories;i++){// Ship A one time, Ship B two times, Ship C three times, Ship D four times
        for(int j=1;j<=i;j++){
            //system("cls");
            PrintBoardB();
            printf("\nShip %c with %d blocks:",ship_category,6-i);
            if(cpu==1){
                orientation=RandomOrientation();
                x= Column(RandomNumber());
                y=RandomNumber();
                AddShipCPU(boardB,orientation,ship_category,VerticalRow(x),y,2);


            }
            else{
            printf("\nOrientation Vertical or Horizontal: e.g(v or h):");
            scanf(" %c", & orientation);
            printf("\nx and y coordinates e.g(A 1): ");
            scanf(" %c %d", &x, &y);
            AddShip(boardB,orientation,ship_category,VerticalRow(x),y,2);
            }
              
            
        }
        ship_category++;
        //system("cls");
        PrintBoardB();
        //system("pause");
  
    }
    

}
// Player 1 move for Atacking opponent's board
void Player1Turn(){
    //system("cls");
    PrintBoardBB();
    printf("\n\t<----Player 1 Turn---> ");
    printf("\nx and y coordinates to attack e.g(A 1): ");
    scanf(" %c %d", &x, &y);
    int i=VerticalRow(x);
    if(i<=10 && y<=10){
        if(boardB[i-1][y-1]!='.' && boardBB[i-1][y-1]=='*'){// opponent's board should not contain . and opponent's board for guessing should not be *
            boardBB[i-1][y-1]='S';
            player2_sunk_count++;// count the sunk ships of Player 2
            printf("\nShip %c of Player 2 is sunk !",boardB[i-1][y-1]);
            if(player2_sunk_count==win_number){// check sunk ships are equal to specific win number
                //system("cls");
                PrintBoardBB();
                printf("\nPlayer 1 Wins !!!!");
                //system("\npause");
                exit(0);

            }
            printf("\nYou have got an extra turn !");
            //system("\npause");

            Player1Turn();
        }
        else if(boardBB[i-1][y-1]=='S'){ // check for already suck ships
            printf("\nAlready sunk Ship !");
            
        }
        else{// missed fires
            boardBB[i-1][y-1]='M';
            printf("\nMiss fired !");
            
        }
        //system("cls");
        printf("\nTotal %d ship(s) sunk of Player 2 !",player2_sunk_count);
        PrintBoardBB();  
        if(cpu==1)
            printf("\nPress ENTER for CPU turn !!!!");
        else
            printf("\nPress ENTER for Player 2 Turn !!!!");
        //system("\npause");
        Player2Turn();

    }
    else{
        printf("\nInvalid location !!!!");//system("\npause");
        Player1Turn();
    }


}
// Player 1 move for Atacking opponent's board
void Player2Turn(){
    //system("cls");
    PrintBoardAA();
    if(cpu==1){
        printf("\n\t<----CPU Turn---> ");
        if(cpu_hit==1){
            printf("\n\t<----CPU Hit Probability---> ");
            int option= RandomTryAround();// Select any option between 1 and 4
            if(option==1)
                x=last_x+1; //Move right side 
            else if(option==2)
                x=last_x-1;  //Move left side 
            else if(option==2)
                y=last_y+1;  //Move top side 
            else 
                y=last_y-1;  //Move down side 
        }
        else{
            x= Column(RandomNumber());
            // sleep(1); 
            y=RandomNumber();

        }

    }
        
    else{
        printf("\n\t<----Player 2 Turn---> ");
        printf("\nx and y coordinates to attack e.g(A 1): ");
        scanf(" %c %d", &x, &y);

    }

    
    int i=VerticalRow(x);
    if(i<=10 && y<=10){
        if(boardA[i-1][y-1]!='.' && boardAA[i-1][y-1]=='*'){// opponent's board should not contain . and opponent's board for guessing should not be *
            boardAA[i-1][y-1]='S';
            cpu_hit=1;
            last_x=i-1;
            last_y=y-1;
            player1_sunk_count++;// count the sunk ships of Player 1
            printf("\nShip %c of Player 1 is sunk !",boardA[i-1][y-1]);
            if(player1_sunk_count==win_number){// check sunk ships are equal to specific win number
            // system("cls");
            PrintBoardAA();
            printf("\nPlayer 2 Wins !!!!");
            // system("\npause");
            exit(0);

        }
            printf("\nYou have got an extra turn !");
            // system("\npause");
            Player2Turn();

            
        }
        else if(boardAA[i-1][y-1]=='S'){// check for already suck ships
            printf("\nAlready sunk Ship !");  
            cpu_hit=0;
        }
        else{// missed fires
            boardAA[i-1][y-1]='M';
            printf("\nMiss fired !");
            cpu_hit=0;
            
        }
        // system("cls");
        printf("\nTotal %d ship(s) sunk of Player 1 !",player1_sunk_count);
        PrintBoardAA();  
        
        printf("\nPress ENTER for Player 1 Turn !!!!");
        // system("\npause");
        Player1Turn();

    }
    else{
        printf("\nInvalid location !!!!");system("\npause");
        Player2Turn();
    }


}
//funtion to initially call the player 1 first
void StartGame(){
    // system("cls");
    printf("Press ENTER to start Game !\n");
 
    Player1Turn();


}
void main(){
   
    char selection,selection1,selection2;
    // system("cls");
    printf("1- Play Battleship!\n");
    printf("2- Rules\n");
    printf("Select an option: ");
    scanf(" %c",&selection);

    if (selection == '1'){ // 1 for playing game
        //system("cls");
         printf("1- Player vs CPU!\n");
         printf("2- Player vs Player\n");
         printf("Select an option: ");
         scanf(" %c",&selection1);
         if(selection1=='1'){
            cpu=1;
            //system("cls");
            printf("1- Easy\n");
            printf("2- Hard\n");
            printf("Select CPU level: ");
            scanf(" %c",&selection2);
            if(selection2=="2"){
                cpu_level=2;
            }
         }
            LoadBoardA();
            LoadBoardB();
            Player1Ships();
            Player2Ships();
            StartGame();
        
    }
    if (selection == '2') {// 2 for instructions
      //system("cls");
      printf("1. You have to destroy your opponent's war ships before he destroys yours.\n");
      printf("2. The battlefield is of 10x10 grid size in which you place your 10 ships\n");
      printf("3. You can place your ships by entering its orientation, i.e horizontal or vertical. For horizontal orientation, type 'h' in the orientation option and type 'v' for vertical\n");
      printf("4. and its x y coordinates(both separated by a space) where x is the row (a-j) and y is the column (1-10) number\n");
      printf("5. You have a fleet of 10 battle ships: \n");
      printf("   * 1 Ship  A: 5 boxes long \n");
      printf("   * 2 Ships B: 4 boxes long \n"); 
      printf("   * 3 Ships C: 3 boxes long \n");
      printf("   * 4 Ships D: 2 boxes long \n");
      printf("6. After placing your ships, you can attack the enemy area. To attack a area, enter its x y coordinate (separated by a space)\n");
      printf("7. Attack hit to the enemy ship is denoted by a 'S' and you get an extra turn\n");
      printf("8. Attack miss is denoted by a 'M' and your turn ends\n");
      printf("Press ENTER to continue!");
      
      //system("pause");
      main();
    
    }
    
}