#include <iostream>
#include <sstream>
#include <cstdlib>

void help();
void game_preface();
void print_board(char [10][10]);
void gen_ship(char [10][10]);
bool catch_error(std::string&, char [10][10]);
void get_checked_input(char [10][10], int&, int&);
bool check_one_size_input(std::string&, char [10][10]);
bool is_sunk(char [10][10], char [10][10], int, int, int&);
void run();
bool check_empty_area(char [10][10], int, int, int, int, const int&,const int&);
bool is_empty_area(char [10][10], int, int, const int&, const int&);
void call_fill_around_sunk_ship(char [10][10], int, int, int&);
void fill_around_sunk_ship(char [10][10], int, int, int, int);
void row_col(char [10][10], int&, int&, const int&, const int&, const int&);
