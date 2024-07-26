// C++ Code Challenges, LinkedIn Learning

// Challenge #10: Playing Tic-Tac-Toe
// Write an application that plays Tic-Tac-Toe against the user.

#include <iostream>
#include <string>
#include <vector>

// ask_for_move()
// Summary: This function asks the user to make a move.
// Arguments:
//           game[3][3]: The state of the game.
//           mark: The user's mark: 'X' or 'O'.
// Returns: Nothing.
void ask_for_move(char game[][3], char mark){
    std::string str;
    int row, col;
    do{
        std::cout << "Place your mark (" << mark << ") in row: " << std::flush;
        std::cin >> str;
        row = stoi(str);
        std::cout << "Place your mark (" << mark << ") in column: " << std::flush;
        std::cin >> str;
        col = stoi(str);
    }while(game[row-1][col-1]!=' ');
    game[row-1][col-1] = mark;
    return;
}

// make_move()
// Summary: This AI function makes a move on behalf of the computer in an ongoing tic-tac-toe game.
// Arguments:
//           game[3][3]: The state of the game.
//           mark: The AI's mark: 'X' or 'O'.
// Returns: Nothing.

int win_index(char a, char b, char c, char mark) {
    char arr[] = { a, b, c };

    int nmark = 0;
    int ispace = -1;
    for(int i = 0; i < 3; ++i){
        if(arr[i] == ' ') {
            ispace = i;
        }
        else if(arr[i] == mark)
            nmark++;
        else
            return -1;
    }

    if(nmark == 2) return ispace;
    return -1;
}

bool winning_row(char game[][3], char mark, int i) {
    int nmatch = 0, iempty = -1;
    for(int icol = 0; icol < 3; ++icol) {
        char c = game[i][icol];
        if(c == mark) nmatch++;
        if(c == ' ') iempty = icol;
    }

    if(nmatch == 2) {
        if(iempty != -1) {
            game[i][iempty] = mark;
            return true;
        }
    }

    return false;
}

bool winning_col(char game[][3], char mark, int i) {
    int nmatch = 0, iempty = -1;
    for(int irow = 0; irow < 3; ++irow) {
        char c = game[irow][i];
        if(c == mark) nmatch++;
        if(c == ' ') iempty = irow;
    }

    if(nmatch == 2) {
        if(iempty != -1) {
            game[iempty][i] = mark;
            return true;
        }
    }

    return false;
}

bool make_winning_move(char game[][3], char mark) {
    for(int i = 0; i < 3; ++i) {
        if(winning_row(game, mark, i))
            return true;

        if(winning_col(game, mark, i))
            return true;

        int wtlbr = win_index(game[0][0], game[1][1], game[2][2], mark);
        switch(wtlbr) {
            case 0:
            game[0][0] = mark; return true;
            case 1:
            game[1][1] = mark; return true;
            case 2:
            game[2][2] = mark; return true;
            case -1:
                break;
            default:
                std::cout << __LINE__ << " computer or programmer has gone mad" << std::endl;
        }

        int wtrbl = win_index(game[0][2], game[1][1], game[2][0], mark);
        switch(wtrbl) {
            case 0:
            game[0][2] = mark; return true;
            case 1:
            game[1][1] = mark; return true;
            case 2:
            game[2][0] = mark; return true;
            case -1:
                break;
            default:
                std::cout << __LINE__ << " computer or programmer has gone mad" << std::endl;

        }
    }

    return false;
}

int moves_to_win(char a, char b, char c, char mark) {
    int nmoves = 3;
    if(a == mark) nmoves--;
    else if(a != ' ') return -1;

    if(b == mark) nmoves--;
    else if(b != ' ') return -1;

    if(c == mark) nmoves--;
    else if(c != ' ') return -1;

    return nmoves;
}

// #define TWO_PLAYERS
void make_move(char game[][3], char mark){ 
    #ifdef TWO_PLAYERS
    ask_for_move(game,mark);
    #else

    /*

    if ai has a winning move in this turn, make that move
    if opp has a winning move in next turn, make that move
    
    otherwise, find the streak in which opp needs least no
    of turns to win hijack it
y
    */
   
   if(make_winning_move(game, mark)) return;

    //  for each streak, count how many turns user needs to win
    //  hijack the one with the least

    const int streaks[8][3][2] = {
        { {0,0}, {0,1}, {0,2} },
        { {1,0}, {1,1}, {1,2} },
        { {2,0}, {2,1}, {2,2} },
        { {0,0}, {1,0}, {2,0} },
        { {0,1}, {1,1}, {2,1} },
        { {0,2}, {1,2}, {2,2} },
        { {0,0}, {1,1}, {2,2} },
        { {0,2}, {1,1}, {2,0} }
    };

    std::vector<int> sblocked, s0, s1, s2, s3;
    char user_mark = (mark == 'O') ? 'X' : 'O';
    for(int istr = 0; istr < 8; ++istr) {
        auto& str1 = streaks[istr];
        int nmoves = moves_to_win(game[str1[0][0]][str1[0][1]],
            game[str1[1][0]][str1[1][1]], game[str1[2][0]][str1[2][1]], user_mark);

        switch(nmoves) {
            case -1:
                sblocked.push_back(istr); continue;
            case 1:
                s1.push_back(istr); continue;
            case 2:
                s2.push_back(istr); continue;
            case 3:
                s3.push_back(istr); continue;
            default:
                std::cout << __LINE__ << " computer or programmer has gone mad" << std::endl;

                return;
        }
        
    }

    if(s1.size() > 0) {
    //  there exists an opp streak with just one move pending
    //  hijack it
        auto& str1 = streaks[s1[0]];
        { char& c = game[str1[0][0]][str1[0][1]];
        if(c == ' '){ c = mark; return; } }
        { char& c = game[str1[1][0]][str1[1][1]];
        if(c == ' '){ c = mark; return; } }
        { char& c = game[str1[2][0]][str1[2][1]];
        if(c == ' '){ c = mark; return; } }

    }
    else if(s3.size() == 8){ game[1][1] = mark; return; }   //  empty board; take center
    else if(s2.size() > 0) {    // streaks with one opp mark and rest empty
        auto& str1 = streaks[s2[0]];
        for(int i = 0; i < 3; ++i) {
            if(game[str1[i][0]][str1[i][1]] == ' ') {
                game[str1[i][0]][str1[i][1]] = mark; return;
            }
        }
    }
    else {
        for(int i = 0; i < 3; ++i) {
            for(int j = 0; j < 3; ++j) {
                if(game[i][j] == ' '){ game[i][j] = mark; return; }
            }
        }
    }
    #endif
    return;
}

bool active(char game[][3]) {
    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
            if(game[i][j] == ' ') return true;

    return false;
}

bool row_win(char game[][3], int row) {
    if(game[row][0] == ' ') return false;
    return (game[row][0] == game[row][1] && game[row][1] == game[row][2]);

}

bool col_win(char game[][3], int col) {
    if(game[0][col] == ' ') return false;
    return (game[0][col] == game[1][col] && game[1][col] == game[2][col]);

}

bool diag_win(char game[][3]){
    if(game[1][1] == ' ') return false;
    return ((game[0][0] == game[1][1] && game[1][1] == game[2][2]) || 
        (game[1][1] == game[0][2] && game[1][1] == game[2][0]));
}

// game_state()
// Summary: This function returns the state of a game.
// Arguments:
//           game[3][3]: The state of the game.
// Returns: A character encoded as:
//                                  'a': An active game.
//                                  'X': X won.
//                                  'O': O won.
//                                  't': A tie.
char game_state(char game[][3]){

    if(diag_win(game))
        return game[1][1];

    for(int i = 0; i < 3; ++i)
        if(row_win(game, i))
            return game[i][0];
        else if(col_win(game, i)) {
            return game[0][i];
        }

    return active(game) ? 'a' : 't';
}

// print_game()
// Summary: This function prints an ongoing tic-tac-toe game.
// Arguments:
//           game[3][3]: The state of the game.
// Returns: Nothing.
void print_game(char game[][3]){
    std::cout << std::endl << std::endl;
    std::cout << "    1   2   3\n\n";
    std::cout << "1   " << game[0][0] << " | "<< game[0][1] << " | " << game[0][2] << "\n";
    std::cout << "   " << "---+---+---\n";
    std::cout << "2   " << game[1][0] << " | "<< game[1][1] << " | " << game[1][2] << "\n";
    std::cout << "   " << "---+---+---\n";
    std::cout << "3   " << game[2][0] << " | "<< game[2][1] << " | " << game[2][2] << "\n";

    std::cout << std::endl << std::endl;
    return;
}

// Main function
int main(){
    char game[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
    char user_mark = 'X', ai_mark = 'O', turn = 'X';
    std::string str;

    std::cout << "Pick your mark (X goes first): " << std::flush;
    std::cin >> str;
    if(str[0]== 'O' || str[0]== 'o'){
        user_mark = 'O';
        ai_mark = 'X';
    }
    std::cout << "      User: " << user_mark << "     AI: " << ai_mark << "\n";    

    print_game(game);

    while(game_state(game)=='a'){
        std::cout << turn << "'s turn...\n";    
        if(turn==user_mark)
            ask_for_move(game,user_mark);
        else
            make_move(game,ai_mark);
        print_game(game);
        turn = turn == 'X' ? 'O' : 'X';
    }
    if(game_state(game)=='t')
        std::cout << "It's a tie.\n\n";
    else    
        std::cout << game_state(game) << " is the winner.\n\n";
    std::cout << std::flush;
    return 0;
}
