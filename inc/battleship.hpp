#include <iostream>
#include <sstream>
#include <cstdlib>

void help();
void game_preface();
void is_print_board(char [10][10]);
void is_gen_ship(char [10][10]);
bool catch_error(std::string&, char [10][10]);
bool get_checked_input(char [10][10], int&, int&);
bool one_size(std::string&, char [10][10]);
bool is_sunk(char [10][10], char [10][10], int, int, int&);
void run ();
bool check_empty_array(char [10][10], int, int, int, int, const int&,const int&);
bool is_call_empty_array(char [10][10], int, int, const int&, const int&);
void is_call_fill_around_sunk_ship(char [10][10], int, int, int&);
void is_check_fill_around_sunk_ship(char [10][10], int, int, int, int);

