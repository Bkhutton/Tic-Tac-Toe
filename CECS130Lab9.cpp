/*---------------------------------------------------------------------*/
/* Brandon Hutton */
/* CECS 130 Lab 9 */
/* 3/20/18 */
/* Description: TIC-TAC-TOE*/
/*---------------------------------------------------------------------*/

#include <iostream>
#include<stdlib.h>
#include<ctime>
#include<string>
using namespace std;

//Player class
class Player{
	public:
	char character;
	
	Player()
	{
		character = 'X';
	}
	
	Player(char c)
	{
		character = c;
	}
	
	char getCharacter()
	{
		return character;
	}
};

//Function prototypes
bool getFirstTurn();
bool checkBoard(char board[3][3]);
void printBoard(char board[3][3], Player p1, Player p2);
void movePlayer2(char board[3][3], Player p2);
void movePlayer1(char board[3][3], Player p1);

//Returns which player will go first
bool getFirstTurn()
{
	int r = rand()%10;
	return r < 5;
}

//Checks to see if someone has won
bool checkBoard(char board[3][3])
{
	//Checks rows
	for(int x=0;x<3;x++)
	{
		if(board[x][0] == board[x][1] && board[x][2] == board[x][1] && board[x][0]!=0)
		{
			return true;
		}
		if(board[0][x] == board[1][x]  && board[2][x] == board[1][x] && board[0][x]!=0)
		{
			return true;
		}
	}
	
	//Check diagonals
	if(board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0]!=' ')
	{
		return true;
	}
	if(board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2]!='-')
	{
		return true;
	}
	return false;
}
//Player1 move
void movePlayer1(char board[3][3], Player p1)
{
	int row;
	int col;
	int flag = -1;
	while(flag < 0)
	{
		//User inputs what row and column they want to make their move in
		cout << "Enter row" << endl;
		cin >> row;
		cout << "Enter column" << endl;
		cin >> col;
		//Checks to see if the space isn't taken
		if(board[row][col]!='X' && board[row][col]!='O')
		{
			board[row][col]=p1.getCharacter();
			flag = 1;									//Flag made positive to cut out the loop
		}
		else
		{
			cout << "That spot is already in use! Pick again..." << endl;
		}
	}	
	cout << "You Moved!" << endl;
}

//Player2 (Computer) move
void movePlayer2(char board[3][3], Player p2)
{
	int flag = -1;
	while(flag < 0)
	{
		//Randon integer between 0 and 3
		int r1 = rand()%3;
		int r2 = rand()%3;
		//Checks to make sure the spot isn't taken
		if(board[r1][r2]!='X' && board[r1][r2]!='O')
		{
			board[r1][r2] = p2.getCharacter();
			flag = 1;								//Flag made positive to cut out of the loop
		}
	}
	cout << "Player 2 Moved" << endl;
}

//Prints updated board
void printBoard(char board[3][3], Player p1, Player p2)
{
	//Loops through rows
	for(int i=0;i<3;i++)
	{
		//Loops through columns
		for(int j=0;j<3;j++)
		{
			//If board space is empty replaces it with a "-"
			if(board[i][j]!='X' && board[i][j]!='O')
			{
				cout << "-";
			}
			//Otherwise places an "X" or "O"
			else
			{
				cout << board[i][j];
			}
		}
		cout<<endl;
	}
}

int main()
{
	bool player1Turn;					//Player turn variable
	int moves =0;						//Counts moves
	bool gameOver = false;				//Tells if someone has won
	char board[3][3];					//2D Board array
	
	Player player1,player2;				//Player variables
	
	srand(time(NULL));					//Initializes random
	player1Turn = getFirstTurn();		//Sets which player goes first, player1 if true, player 2 if false
	
	//Constructs each player class according to who goes first
	if(player1Turn)
	{
		player1 = Player('X');
		player2 = Player('O');
		cout << "Coin toss decided you move first!" << endl;
	}
	else
	{
		player1 = Player('O');
		player2 = Player('X');
		cout << "Coin toss decided your opponent moves first." << endl;
	}
	//Loops until game is over
	while(!gameOver)
	{
		moves++;								//Adds one to counter
		//Checks to see whos turn it is
		if(player1Turn)
		{
			movePlayer1(board,player1);			//Moves for player 1
			player1Turn = false;				//Changes turn
		}
		else
		{
			movePlayer2(board,player2);			//Moves for computer
			player1Turn = true;					//Changes turn
		}
		printBoard(board,player1,player2);		//Prints the board for user to see
		gameOver = checkBoard(board);			//Sees if there is a winner
		
		//Checks for tie
		if (moves >=9 && !gameOver)
		{
			moves++;
			gameOver = true;
		}
	}
	
	//Prints winner
	if(moves>9)
	{
		cout << "TIE!" << endl;
	}
	else if(player1Turn)
	{
		cout << "PLAYER 2 WINS!" << endl;
	}
	else
	{
		cout << "YOU WIN!" << endl;
	}
}
