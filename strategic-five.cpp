#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <conio.h>
using namespace std;


// ANSI color codes
#define RESET   "\033[0m"
#define RED     "\033[31m"      /* Red */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLD    "\033[1m"       /* Bold */



//Gameboard Class
class GameBoard 
{
public:
    char board[9][9];
    char boardx15[15][15];

public:
    GameBoard()   //Constructor
    {
        for (int i = 0; i < 9; ++i)  //Initializing the 9 x 9 board with spaces
        {
            for (int j = 0; j < 9; ++j)
            {
                board[i][j] = ' ';
            }
        }
        for (int i = 0; i < 15; ++i) //Initializing the 15 x 15 board with spaces
        {
            for (int j = 0; j < 15; ++j)
            {
                boardx15[i][j] = ' ';
            }
        }
    }
    //Function prototypes in class
    void drawBoardx9(char board[][9]);
    void drawBoardx15(char board[][15]);
    void placePieceforboardx9(int row, int col, char piece, int size);
    void placePieceforboardx15(int row, int col, char piece, int size);
    bool checkForWinx9(char board[][9], char piece);
    bool checkForWinx15(char board[][15], char piece);
    void botMovex9(char board[][9], int &row2, int &col2);
    void botMovex15(char boardx15[][15], int &row2, int &col2);
    bool checkDrawx9(char board[][9]);
    bool checkDrawx15(char board[][15]);

}game;

//Function prototypes for main function
void gamelogicfor9();
void gamelogicfo15();
void botforx15();
void botforx9();
int choice;
void MENU(int &mode);
void printWinnerScreen(char piece);
void boardType(int &preference);

int main()  //Main function
{
    int mode;
    MENU(mode);  //Display menu and get user's choice

    switch (mode)  //Checking case according to user input
    {
    case 1:
        system("cls");
        int preference;
        boardType(preference); 
        if (preference == 1) // Checking user's prefered board
        {
            gamelogicfor9(); //Game logic for 9 x 9 board against a fellow human
        }
        else if (preference == 2)
        {
            gamelogicfo15(); //Game logic for 15 x 15 board against a fellow human
        }
        break;
    case 2:
    {
        int preference;
        system ("cls");
        boardType(preference); // Checking user's prefered board
        if (preference == 1)
        {
            system("cls");
            botforx9();  //Game logic for 9 x 9 board against a bot
        }
        else if (preference == 2)
        {
            botforx15(); //Game logic for 15 x 15 board against a bot
        }
        break;
    }
    default:
        cout<<"Invalid choice\n";
        break;
    }
}

void GameBoard::drawBoardx9(char board[][9]) //Printing the 9 x 9 board
{
    cout << BOLD << WHITE << "      0   1   2   3   4   5   6   7   8" << RESET;
    cout << endl;

    for (int i = 0; i < 9; ++i)
    {
        cout << BOLD << i  << "   |" << RESET;
        for (int j = 0; j < 9; ++j)
        {
            if (board[i][j] == 'X')
            {
                cout << " " << BLUE << board[i][j] << RESET << BOLD<< " |" << RESET;
            }
            else if (board[i][j] == 'O')
            {
                cout << " " << RED <<board[i][j] << RESET << BOLD << " |" << RESET;
            }
            else
            {
                cout << " " << board[i][j]<< BOLD << " |" << RESET;
            }
        }
        cout << endl;
    }
}
void GameBoard::drawBoardx15(char board[][15])   //Printing 15 x 15 the board
{
    cout << BOLD  << WHITE << "      0   1   2   3   4   5   6   7   8   9  10  11  12  13  14" << RESET;
    cout << endl;

    for (int i = 0; i < 15; ++i)
    {
        cout << BOLD <<setw(3) << i << " |" << RESET;
        for (int j = 0; j < 15; ++j)
        {
            if (boardx15[i][j] == 'X')
            {
                cout << " " << BLUE << boardx15[i][j] << RESET << BOLD << " |" << RESET;
            }
            else if (boardx15[i][j] == 'O')
            {
                cout << " " << RED <<boardx15[i][j] << RESET << BOLD << " |" << RESET;
            }
            else
            {
                cout << " " << boardx15[i][j] << BOLD << " |" << RESET;
            }
            
        }
        cout << endl;
    }
}




void GameBoard::placePieceforboardx9(int row, int col, char piece, int size)  //Replacing the space with the piece at the user entered index for 9 x 9 board
{
    if (row >= 0 && row < size && col >= 0 && col < size && board[row][col] == ' ') //Checking is the indices entered by user is valid
    {
        board[row][col] = piece;  //placing the piece
    }
    else
    {
        cout << "Invalid move! Try again." << endl;
    }
}

void GameBoard::placePieceforboardx15(int row, int col, char piece, int size) //Replacing the space with the piece at the user entered index for 15 x 15 board
{
    if (row >= 0 && row < size && col >= 0 && col < size && boardx15[row][col] == ' ')  //Checking is the indices entered by user is valid
    {
        boardx15[row][col] = piece;  //placing the piece
    }
    else
    {
        cout << "Invalid move! Try again." << endl;
    }
}

void gamelogicfor9()  //Game logic for 9 x 9 board against human
{
    while (true)
    {
        system("cls");
        int row1, row2, column1, column2;
        game.drawBoardx9(game.board);
        cout<<"Move for X\n";
        cout << "Enter row and column: ";   //Asking for indices from X
        cin >> row1 >> column1;
        game.placePieceforboardx9(row1, column1, 'X', 9); //Replacing space with X
        system("cls");
        game.drawBoardx9(game.board);
        bool status = game.checkForWinx9(game.board, 'X');
        if (status == true)
        {
            break;
        }
        bool draw = game.checkDrawx9(game.board); //checking if game is draw
        if (draw)
        {
            system("cls");
            cout<<"THE GAME IS A DRAW\n";
            break;
        }
        cout<<"Move for O\n";
        cout << "Enter row and column: "; //Asking for indices from O
        cin >> row2 >> column2;
        game.placePieceforboardx9(row2, column2, 'O', 9);  //Replacing space with O
        status = game.checkForWinx9(game.board, 'O'); //Cheking win condition
        if (status == true)
        {
            break;
        }
        draw = game.checkDrawx9(game.board); //checking again if the game is draw
        if (draw)
        {
            system("cls");
            cout<<"THE GAME IS A DRAW\n";
            break;
        }
        system("cls");
        game.drawBoardx9(game.board);
    }
}

void gamelogicfo15()  //Game logic for 15 x 15 board against human
{
    while (true)
    {
        system("cls");
        int row1, row2, column1, column2;
        game.drawBoardx15(game.boardx15);
        cout<<"MOVE FOR X\n";
        cout << "Enter row and column: ";   //Asking for indices from X
        cin >> row1 >> column1;
        game.placePieceforboardx15(row1, column1, 'X', 15);  //Replacing space with X
        system("cls");
        game.drawBoardx15(game.boardx15);  
        bool statusof15 = game.checkForWinx15(game.boardx15, 'X'); //Cheking win condition
        if (statusof15)
        {
            system("cls");
            cout<<"THE GAME IS A DRAW\n";
            break;
        }
        bool draw = game.checkDrawx15(game.boardx15); //checking if game is draw
        if (draw)
        {
            system("cls");
            cout<<"THE GAME IS A DRAW\n";
            break;
        }
        cout<<"MOVE FOR O\n";
        cout << "Enter row and column: "; //asking user O for indices
        cin >> row2 >> column2;
        game.placePieceforboardx15(row2, column2, 'O', 15);  //Replacing space with O
        statusof15 = game.checkForWinx15(game.boardx15, 'O'); //Checking win conditions
        if (statusof15)
        {
            break;
        }
        draw = game.checkDrawx15(game.boardx15);  //Checking again if the game is draw
        if (draw)
        {
            break;
        }
        game.drawBoardx15(game.boardx15);
    }
}
bool GameBoard :: checkForWinx9(char board[][9], char piece)  //Checking win conditons for 9 x 9 board
{
    /*
        checking if five consecutive X or O appears on the board horizontally, vertically, on main and secondary diagonal
    */
    for (int i = 0; i < 9; i++)  //Checking horizontally for 9 x 9
    {
        int rowOcc = 0;
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == piece)
            {
                rowOcc++;
                if (rowOcc == 5)
                {
                    printWinnerScreen(piece);
                    return true;
                } 
            }
            else
            {
                rowOcc = 0;
            }
        }  
    }

    for (int i = 0; i < 9; i++)  //checking vertically for 9 x 9
    {
        int colOccu = 0;
        for (int j = 0; j < 9; j++)
        {
            if (board[j][i] == piece)
            {
                colOccu++;
                if (colOccu == 5)
                {
                    printWinnerScreen(piece);
                    return true;
                }
            }
            else
            {
                colOccu = 0;
            }
        }
    }

    int Mdia = 0, SDia = 0;
    for (int i = 0; i < 9; i++)  //checking main diagonal for 9 x 9
    {
        for (int j = 0; j < 9; j++)
        {
            if (i == j)
            {
                if (board[i][j] == piece)
                {
                    Mdia++;
                    if (Mdia == 5)
                    {
                        printWinnerScreen(piece);
                        return true;
                    }
                }
                else
                {
                    Mdia = 0;
                }
            }
        }
    }

    for (int i = 0; i < 9; i++)  //Checking secondary diagonal for 9 x 9 
    {
        for (int j = 0; j < 9; j++)
        {
            if (i + j == 8)
            {
                if (board[i][j] == piece)
                {
                    SDia++;
                    if (SDia == 5)
                    {
                        printWinnerScreen(piece);
                        return true;
                    }
                }
                else
                {
                    SDia = 0;
                }
            }
        }
    }
    return false;
}


bool GameBoard :: checkForWinx15(char board[][15], char piece) //Checking win conditions for 15 x 15 board
{  
    /*
        checking if five consecutive X or O appears on the board horizontally, vertically, on main and secondary diagonal
    */
    for (int i = 0; i < 15; i++)  //checking horizontally
    {
        int rowOcc = 0;
        for (int j = 0; j < 15; j++)
        {
            if (boardx15[i][j] == piece)
            {
                rowOcc++;
                if (rowOcc == 5)
                {
                    printWinnerScreen(piece);
                    return true;
                } 
            }
            else
            {
                rowOcc = 0;
            }
        }  
    }

    for (int i = 0; i < 15; i++)  //checking vertically
    {
        int colOccu = 0;
        for (int j = 0; j < 15; j++)
        {
            if (boardx15[j][i] == piece)
            {
                colOccu++;
                if (colOccu == 5)
                {
                    printWinnerScreen(piece);
                    return true;
                }
            }
            else
            {
                colOccu = 0;
            }
        }
    }

    int Mdia = 0, SDia = 0;
    for (int i = 0; i < 15; i++)  //checking main diagonal
    {
        for (int j = 0; j < 15; j++)
        {
            if (i == j)
            {
                if (boardx15[i][j] == piece)
                {
                    Mdia++;
                    if (Mdia == 5)
                    {
                        printWinnerScreen(piece);
                        return true;
                    }
                }
                else
                {
                    Mdia = 0;
                }
            }
        }
    }

    for (int i = 0; i < 15; i++)  //checking secondary diagonal
    {
        for (int j = 0; j < 15; j++)
        {
            if (i + j == 14)
            {
                if (boardx15[i][j] == piece)
                {
                    SDia++;
                    if (SDia == 5)
                    {
                        printWinnerScreen(piece);
                        return true;
                    }
                }
                else
                {
                    SDia = 0;
                }
            }
        }
    }
    return false;
}
void botforx9()  //Game logic for match against a bot for 9 x 9 board
{
    srand(time(0));
    while (true)
    {
        system("cls");
        int row1 = 0, row2 = 0, column1 = 0, column2 = 0;
        game.drawBoardx9(game.board);
        cout << "Enter row and column: ";  //Asking user for inputing row and coloumn
        cin >> row1 >> column1;
        game.placePieceforboardx9(row1, column1, 'X', 9); //Placing the piece instead of space
        system("cls");
        game.drawBoardx9(game.board);      
        bool status = game.checkForWinx9(game.board, 'X');
        if (status)
        {
            break;
        }
        bool draw = game.checkDrawx9(game.board);  //Checking if the game is draw
        if (draw)
        {
            system("cls");
            cout<<"THE GAME IS A DRAW\n";
            break;
        }
        game.drawBoardx9(game.board);
        game.botMovex9 (game.board, row2, column2); //Bot's turn
        game.placePieceforboardx9(row2, column2, 'O', 9); //replacing space with O
        status = game.checkForWinx9(game.board, 'O');
        if (status)
        {
            break;
        }
        draw = game.checkDrawx9(game.board);  //checking again if the game is draw
        if (draw)
        {
            system("cls");
            cout<<"THE GAME IS A DRAW\n";
            break;
        }
        game.drawBoardx9(game.board);
    }
}
void botforx15()  //Game logic for match against bot in 15 x 15
{
    srand(time(0));
    while (true)
    {
        system("cls");
        int row1, row2, column1, column2;
        game.drawBoardx15(game.boardx15);
        cout << "Enter row and column: ";  //Asking user for inputing row and coloumn
        cin >> row1 >> column1;
        system("cls");
        game.drawBoardx15(game.boardx15);
        game.placePieceforboardx15(row1, column1, 'X', 15);  //Placing X
        bool statusof15 = game.checkForWinx15(game.boardx15, 'X');  //Checking if X wins
        if (statusof15) 
        {
            break;
        }
        bool draw = game.checkDrawx15(game.boardx15);  //checking if the game is draw
        if (draw)
        {
            system("cls");
            cout<<"THE GAME IS A DRAW\n";
            break;
        }
        game.drawBoardx15(game.boardx15);
        game.botMovex15 (game.boardx15, row2, column2);  //Bot's turn
        game.placePieceforboardx15(row2, column2, 'O', 15);  //Placing O
        statusof15 = game.checkForWinx15(game.boardx15, 'O'); //Checking if X wins
        if (statusof15)
        {
            break;
        }
        draw = game.checkDrawx15(game.boardx15);  //Checking again if the game is draw
        if (draw)
        {
            system("cls");
            cout<<"THE GAME IS A DRAW\n";
            break;
        }
        game.drawBoardx15(game.boardx15);
    }
}
void GameBoard:: botMovex9 (char board[][9], int &row2, int &col2)  //Bot move for 9 x 9 board
{   
   do
    {
        //Randomly choosing an index between 0 and 8
        row2 = rand() % 8;  
        col2 = rand() % 8; 
    }
    while (board[row2][col2] != ' ');  //Making sure the index is a valid move
}
void GameBoard:: botMovex15 (char board[][15], int &row2, int &col2)  //Bot move for 15 x 15 board
{   
    
    do
    {
        //randomly choosing an index between 0 15 
        row2 = rand() % 15;  
        col2 = rand() % 15;  
    }
    while (boardx15[row2][col2] != ' '); //Making sure the index is valid
}
void MENU(int &mode)  //Proving users with a dynamic and appealing UI
{
    cout << "\033[?25l";  //Hiding the cursor
    mode = 0;
    system("cls");
    cout << BLUE <<"\t\t\t\t>=>        >=>            >=>     \n"
        << "\t\t\t\t>=>        >=>            >=>      \n"
        << "\t\t\t\t>=>   >>   >=>   >==>     >=>    >==>    >=>     >===>>=>>==>    >==>\n"
        << "\t\t\t\t>=>  >=>   >=> >>   >=>   >=>  >=>     >=>  >=>   >=>  >>  >=> >>   >=>\n" << RESET
        << CYAN <<"\t\t\t\t>=> >> >=> >=> >>===>>=>  >=> >=>     >=>    >=>  >=>  >>  >=> >>===>>=>\n"
        << "\t\t\t\t>> >>    >===> >>         >=>  >=>     >=>  >=>   >=>  >>  >=> >>\n"
        << "\t\t\t\t>=>        >=>  >====>   >==>    >==>    >=>     >==>  >>  >=>  >====>  \n" << RESET;
    cout << "\n";
    cout << "\n";
    cout << "\t\t\t\t\t\tHUMAN VS HUMAN\n";
    cout << "\t\t\t\t\t\tHuman VS AI\n";
    while (true)
    {
        char input = getch();  //Reads input from keyboard without printing it on screen
        Beep(400, 400);
        switch (input)
        {
        case 'w':
        {
            system("cls");
            cout << BLUE <<"\t\t\t\t>=>        >=>            >=>     \n"
                 << "\t\t\t\t>=>        >=>            >=>      \n"
                 << "\t\t\t\t>=>   >>   >=>   >==>     >=>    >==>    >=>     >===>>=>>==>    >==>\n"
                 << "\t\t\t\t>=>  >=>   >=> >>   >=>   >=>  >=>     >=>  >=>   >=>  >>  >=> >>   >=>\n" << RESET
                 << CYAN <<"\t\t\t\t>=> >> >=> >=> >>===>>=>  >=> >=>     >=>    >=>  >=>  >>  >=> >>===>>=>\n"
                 << "\t\t\t\t>> >>    >===> >>         >=>  >=>     >=>  >=>   >=>  >>  >=> >>\n"
                 << "\t\t\t\t>=>        >=>  >====>   >==>    >==>    >=>     >==>  >>  >=>  >====>  \n" << RESET;
            cout << "\n";
            cout << "\n";
            cout << BOLD << BLUE <<"\t\t\t\t\t\t[HUMAN VS HUMAN]\n"<< RESET;
            cout << "\t\t\t\t\t\tHuman VS AI\n";
            mode = 1;
            break;
        }
        case 's':
        {
            system("cls");
            cout << BLUE <<"\t\t\t\t>=>        >=>            >=>     \n"
                 << "\t\t\t\t>=>        >=>            >=>      \n"
                 << "\t\t\t\t>=>   >>   >=>   >==>     >=>    >==>    >=>     >===>>=>>==>    >==>\n"
                 << "\t\t\t\t>=>  >=>   >=> >>   >=>   >=>  >=>     >=>  >=>   >=>  >>  >=> >>   >=>\n"<< RESET 
                 << CYAN <<"\t\t\t\t>=> >> >=> >=> >>===>>=>  >=> >=>     >=>    >=>  >=>  >>  >=> >>===>>=>\n"
                 << "\t\t\t\t>> >>    >===> >>         >=>  >=>     >=>  >=>   >=>  >>  >=> >>\n"
                 << "\t\t\t\t>=>        >=>  >====>   >==>    >==>    >=>     >==>  >>  >=>  >====>  \n" << RESET;
            cout << "\n";
            cout << "\n";
            cout << "\t\t\t\t\t\tHuman VS Human\n";
            cout << BOLD << BLUE <<"\t\t\t\t\t\t[HUMAN VS AI]\n" << RESET;

            mode = 2;
            break;
        }
        default:
        {
            cout << RED << "\nInvalid choice \n"<< RESET;
        }
    }

    if (input == 13 || input == 'q')
    {
        cout << "\033[?25h"; //Making the cursor visible again
        break;
    }
}
}
void printWinnerScreen(char piece)  //Proving users with a dynamic and appealing UI
{
    system("cls");
    cout << "\n\n";
    cout << "\t\t\t\t\t" << BLUE << "+-------------------------------------+" << RESET << "\n";
    cout << "\t\t\t\t\t" << CYAN << "Congratulations, " << YELLOW << piece << RESET << CYAN << " you are the winner!" << RESET << "\n";
    cout << "\t\t\t\t\t" << BLUE << "+-------------------------------------+" << RESET << "\n\n";
}
void boardType(int&preference)
{
    system("cls");
    cout << "\033[?25l"; //Hiding the cursor
    preference = 0;
    cout<< RED << BOLD <<"Choose board type:\n"<< RESET;
    cout<<"9 x 9 board\n";
    cout<<"15 x 15 board";
    while (true)
    {
        char input = getch(); //Reads input from keyboard without printing it on screen
        Beep(400, 400);
        switch(input)
        {
            case 'w':
            {   
                system("cls");
                cout<< RED << BOLD <<"Choose board type:\n"<< RESET;
                cout<< BLUE <<">"<< RESET << BOLD << CYAN <<" 9 x 9 board\n" << RESET;
                cout<<"15 x 15 board\n";
                preference = 1;
                break;
            }
            case 's':
            {
                system("cls");
                cout<< RED << BOLD <<"Choose board type:\n"<< RESET;
                cout<<"9 x 9 board\n";
                cout<< BLUE <<">"<< RESET << BOLD << CYAN <<" 15 x 15 board\n" << RESET;
                preference = 2;
                break;
            }

        }


        if (input == 13)
        {
             cout << "\033[?25h"; //Making the cursor visible again
            break;
        }

    }
}
bool GameBoard :: checkDrawx9(char board[][9])  //Checking if the game is draw for 9 x 9
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] != ' ')  //Checking if there is a piece
            {
                return false;  //Returning false suggesting game is not a draw
            }
        }
    }

    return true;  //returns true there are no empty spaces
} 
bool GameBoard :: checkDrawx15(char boardx15[][15]) //Checking if the game is draw for 15 x 15
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (boardx15[i][j] != ' ') //Checking if there is a piece
            {
                return false; //Returning false suggesting game is not a draw
            }
        }
    }
    return true; //returns true there are no empty spaces
}