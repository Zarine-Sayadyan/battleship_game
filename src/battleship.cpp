#include <iostream>
#include <sstream>
#include <cstdlib>
#include "battleship.hpp"

//instruction to the game
void help() {
    std::cout << "\nInstruction to the Game: " << std::endl;
    std::cout << "- The program generate board and ships, the user hits it. " << std::endl;    
    std::cout << "- To become the winner of Battleship you must be able to sink all ships. " << std::endl;
    std::cout << "- There are 1 four-dimensional ship, 2 three-dimensional ship, 3 two-dimensional ship and 4 one-dimensional ship. " << std::endl;
    std::cout << "- Enter your hit in this form - number.number (e.g. 1.2). Your input number have to be between 0 to 9. " << std::endl;
    std::cout << "- First number is row, second number is column. " << std::endl; 
    std::cout << "- The ship is marked with the symbol 'X'. " << std::endl;
    std::cout << "- The miss hit is marked with the symbol '*'. " << std::endl;
    std::cout << "- The injured ship is marked with the symbol 'X'. " << std::endl;
    std::cout << "- The sank ship is marked with the symbol 'x'. " << std::endl;
    std::cout << "- If you want to stop the game input 'e'. " << std::endl;
    std::cout << "- If you want to read instruction again input 'h'. " << std::endl;
    std::cout << "- If you want to show generation board input 's'. " << std::endl;
    std::cout << "Let's play. " << std::endl << std::endl;
}
//preface teks befor game
void game_preface() {
    std::cout << "\n-------------------------------------------------------" << std::endl;
    std::cout << "|                  Battleship Game                    |" << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << "                 Welcome to the game.                  " << std::endl;
    help();
}
//print board
void is_print_board(char a[10][10]) {

    for (int i = 0; i < 10; ++i) {
        if (0 == i) std::cout << "  ";
        std::cout << i << " ";
    }
    std::cout << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << i << " ";
        for (int j = 0; j < 10; ++j) {
            std::cout << a[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
//function checks array is empty or not
bool check_empty_array(char gen_board[10][10], int row, int row_up, int col, int row_down,const int& ship,const int& is_row_col) {
    bool b = true;
    for (int i = row - row_up; i <= row + row_down; ++i) { 
        for (int j = col - 1; j < col + ship + 1; ++j) {
            if (2 == is_row_col && gen_board[j][i] != '-') {
                b = false;
                break;
            } else if (1 == is_row_col && gen_board[i][j] != '-') {
                b = false;
                break;
            }
        }
    }
    return b;
}   
//calls empty array function in the appropriate direction 
bool is_call_empty_array(char gen_board[10][10], int row, int col, const int& ship, const int& is_row_col) {
    bool b = true;
    if (2 == is_row_col) {
        int t = col;
        col = row;
        row = t;
    }
    if (0 == row) {
       b = check_empty_array (gen_board, row, 0, col, 1, ship, is_row_col); 
    } else if (9 == row) {
       b = check_empty_array (gen_board, row, 1, col, 0, ship, is_row_col);
    } else {
       b = check_empty_array (gen_board, row, 1, col, 1, ship, is_row_col);
    }
    return b;
}
//generates ships random
void is_gen_ship(char gen_board[10][10]) {
    srand(time(NULL));
    int ship_length = 4;
    int ship_count = 1;
    for (int i = 0; i < 4; ++i) {
        for(int j = 0; j < ship_count; ++j) {
            int row = rand() % 10;
            int col = rand() % 10;
            int is_row_col = rand() % 2 + 1;
            if (1 == is_row_col) {
                while ((10 - col) < ship_length || is_call_empty_array(gen_board,row,col,ship_length,is_row_col) != true) {
                    row = rand() % 10;
                    col = rand() % 10;
                }
                for (int l = col; l < col + ship_length; ++l) {
                    gen_board[row][l] = 'X';
                }
            } else if (2 == is_row_col){
                while ((10 - row) < ship_length || is_call_empty_array(gen_board,row,col,ship_length,is_row_col) != true) {
                    row = rand() % 10;
                    col = rand() % 10;
                }
                for (int l = row; l < row + ship_length; ++l) {
                    gen_board[l][col] = 'X';
                }
            }
        }
        ++ship_count;
        --ship_length;
   }
}
//gets input, checked and return it
bool get_checked_input(char gen_board[10][10], int& row, int& col) {
    bool b = false;
    std::string str("");
    std::cout << "Input your hit. " << std::endl;
    getline(std::cin,str);
    do {
        b = false;
        if (catch_error(str,gen_board)) {
            b = true;
        }
    } while(b);
    std::stringstream num1;
    num1 << str[0];
    num1 >> row;
    std::stringstream num2;
    num2 << str[2];                  
    num2 >> col;
    return b;
}
//checks input of one length according to the program rule
bool one_size(std::string& str, char gen_board[10][10]) {
    bool b = false;   
    while (1 == str.size()) {
        switch (str[0]) 
        { 
            case 'e': int e;
                      _Exit(e);
                      b = true;
                      break;
            case 'h': help();
                      b = true;
                      break;
            case 's': is_print_board(gen_board);
                      break;
                      b = true;
            default: std::cout << "Incorrect input. " << std::endl;
        }      
        std::cout << "Input your hit. " << std::endl;
        getline(std::cin,str);
   }
   return b;
}
//input hit and catch error
bool catch_error(std::string& str, char gen_board [10][10]) {
    bool b = false;
    int result = 0;
    do {
        b = false;
        while ((1 != str.size()) && (3 != str.size())) {
                std::cout << "Incorrect input. " << std::endl;
                std::cout << "Please input number between 0 to 9 in this form - number.number (e.g. 1.2). " << std::endl;
                getline(std::cin,str);
        }
        if (one_size(str,gen_board) == true) {
                b = true;
        }
        if((str[0] < '0' || str[0] > '9') || (str[1] != '.') || (str[2] < '0' || str[2] > '9')) {
            std::cout << "Incorrect input. " << std::endl;
            std::cout << "Please input number between 0 to 9 in this form - number.number (e.g. 1.2). " << std::endl;
            b = true;
            std::cout << "Input your hit. " << std::endl;
            getline(std::cin, str);
            break;
        }
    } while(b);
    return b;
}
//check if ship has been sank
bool is_sunk(char gen_board[10][10], char player_board[10][10], int row, int col, int& dir) {
    int count = 1;
    dir = 0; //vertical
    while ('X' == gen_board[row - 1][col] && row - 1 >= 0) {
        if ('X' == player_board[row - 1][col]) {
            ++count;
            --row;
        } else {
            return false;
        }
    }
    while ('X' == gen_board[row + 1][col] && row + 1 <= 9) {
        if ('X' == player_board[row + 1][col]) {
            ++count;
            ++row;
        } else {
            return false;
        }
    }
    if (1 == count) {
        while ('X' == gen_board[row][col - 1] && col - 1 >= 0) {
            if ('X' == player_board[row][col - 1]) {
                --col;
            } else {
                  return false;
            }
        }
        while ('X' == gen_board[row][col + 1] && col + 1 <= 9) {
            if ('X' == player_board[row][col + 1]) {
                ++col;
            } else {
                  return false;
            }
        }
        dir = 1; // horizonal
    }
    return true;  
}
//calls check_fill funtion in the appropriate direction
void is_call_fill_around_sunk_ship(char player_board[10][10], int row, int col, int& dir) {
    if (0 == dir) {
        is_check_fill_around_sunk_ship (player_board, row, 1, col, 0);
    } else if (1 == dir) {
        is_check_fill_around_sunk_ship (player_board, row, 0, col, 1);
    }
}

//check around sunk ship and fill around it *
void is_check_fill_around_sunk_ship(char player_board[10][10], int row, int row_up_down, int col, int col_up_down) { 
    while ('X' == player_board[row][col]) {
        player_board[row][col] = 'x';
        for (int i = row - 1; i <= row + 1; ++i) {
            for (int j = col -1; j <= col + 1; ++j) {
                if (i < 0 || i > 9 || j < 0 || j > 9) {
                    continue;
                }
                if ('-' == player_board[i][j]) {
                    player_board[i][j] = '*';
                }      
            }
        } 
        if ('X' == player_board[row - row_up_down][col - col_up_down]) {
            row = (1 == row_up_down) ? --row : row;
            col = (1 == col_up_down) ? --col : col;
        } else if ('X' == player_board[row + row_up_down][col + col_up_down]) {
            row = (1 == row_up_down) ? ++row : row;
            col = (1 == col_up_down) ? ++col : col;
        }
    }
}
//run program
void run () {
    int row = 0;
    int col = 0;
    int shot = 1;
    char gen_board[10][10] = {}; 
    char player_board[10][10] = {};
    for (int i = 0; i < 10; ++i) {
        for (int  j = 0; j <= 10; ++j) {
            gen_board[i][j] = '-';
            player_board[i][j] = '-';
        }
    }
    int ship_count = 0;
    int dir = -1;
    std::string s("");
    is_gen_ship(gen_board);
    game_preface();
    while (get_checked_input(gen_board,row,col) == false) {
        switch (gen_board[row][col])
        {
            case '-': if (player_board[row][col] == '*') {
                          std::cout << "Duplicate value.\n";
                      }
                      player_board[row][col] = '*';
                      std::cout << "You missed!" << std::endl;
                      break;
            case 'X': if (player_board[row][col] == 'x') {
                          std::cout << "The ship is already sunk!!!! " << std::endl;
                          std::cout << "Try again. " << std::endl;
                          break;
                      }
                      player_board[row][col] = 'X';
                      ++ship_count;
                      if (is_sunk (gen_board, player_board, row, col, dir)  == true) {
                          std::cout << "The ship is sunk" << std::endl;
                          is_call_fill_around_sunk_ship(player_board, row, col, dir);
                      } else {
                          std::cout << "The ship is injured\n";
                      }
                      break;
        }
        is_print_board(player_board);
        if (ship_count == 20) {
            std::cout << "You win!!! "<<std::endl;
            break;
        }
    }
}

/*int main() {
    run();
    return 0;
}*/
