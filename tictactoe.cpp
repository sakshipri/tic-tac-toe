#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void printgame(vector<vector<string>> vect) {
    for (int i = 0; i < vect.size(); i++)
    {
        for (int j = 0; j < vect[i].size(); j++)
        {
            cout << vect[i][j] << " ";
        }    
        cout << endl;
    }
    return;
    
}

vector<vector<string>> resetboard(vector<vector<string>> vect) {
    for (int i = 0; i < vect.size(); i++) {
        for (int j = 0; j < vect[i].size(); j++) {
            vect[i][j] = "_";
        }
    }
    return vect;
}

vector<vector<string>> updategame(string s, int x, int y, vector<vector<string>>& vect) {
    vect[x][y] = s;
    return vect;
}

string checkwinner(vector<vector<string>> board, int chance) {
    if (((board[0][0]==board[0][1])&&(board[0][1]==board[0][2])&&(board[0][2]!="_"))||
        ((board[0][0]==board[1][0])&&(board[1][0]==board[2][0])&&(board[2][0]!="_"))||
        ((board[1][0]==board[1][1])&&(board[1][1]==board[1][2])&&(board[1][2]!="_"))||
        ((board[0][1]==board[1][1])&&(board[1][1]==board[2][1])&&(board[2][1]!="_"))||
        ((board[2][0]==board[2][1])&&(board[2][1]==board[2][2])&&(board[2][2]!="_"))||
        ((board[0][2]==board[1][2])&&(board[1][2]==board[2][2])&&(board[2][2]!="_"))||
        ((board[0][0]==board[1][1])&&(board[1][1]==board[2][2])&&(board[2][2]!="_"))||
        ((board[0][2]==board[1][1])&&(board[1][1]==board[2][0])&&(board[2][0]!="_"))) {
        if (chance%2==0) {
            return "Player1";
        } else {
            return "Player2";
        }
    } else {
        return "";
    }

}
pair<int, int> zero_intelligence(vector<vector<string>> vect, string comp) {
    // first check if the win is possible, if it is, win
    // if not, then check if loss is possible, if it is, not lose
    // if not, play to make to in a row,  if possible
    // if not, play random
    int chance;
    string human;
    string winner;
    if (comp == "o") {
        chance = 0;
        human = "x";
    } else if (comp == "x") {
        chance = 1;
        human = "o";
    } else {
        chance = -1;
    }
    for (int i = 0; i < vect.size(); i++) {
        for (int j = 0; j < vect[i].size(); j++) {
            if (vect[i][j] == "_") {
                vect[i][j] = comp;
                winner = checkwinner(vect, chance);
                if (winner == "") {
                    vect[i][j] = "_";
                } else {
                    return make_pair(i, j);
                }
            }
        }
    }
    chance++;
    for (int i = 0; i < vect.size(); i++) {
        for (int j = 0; j < vect[i].size(); j++) {
            if (vect[i][j] == "_") {
                vect[i][j] = human;
                winner = checkwinner(vect, chance);
                if (winner == "") {
                    vect[i][j] = "_";
                } else {
                    return make_pair(i, j);
                }
            }
        }
    }
    chance++;
    int i, j;
    while (true) {
        i = rand()%3;
        j = rand()%3;
        if (vect[i][j] == "_") {
            return make_pair(i, j);
        }
    }
}

int main() { 
    vector<vector<string>> v;

    for (int i = 0; i < 3; ++i) {
        vector<string> rowV;

        for (int j = 0; j < 3; ++j) {
            rowV.push_back("_");
        }

        v.push_back(rowV);
    }
    cout << "___________________________________________________________________________________________________________________________" << endl;
    cout << "Welcome to tic-tac-toe. Enter 1 to start." << endl;
    int g;
    cin >> g;
    printgame(v);
    if (g!=1) {
        cout << "Arey yeh kya enter kardiya!!" << endl;
    }
    while (g==1) {
        int num_players;
        cout << "Enter 1 for 1 Player" << endl;
        cout << "Enter 2 for 2 Player" << endl;
        cin >> num_players;
        while (num_players != 2 && num_players != 1) {
            cout << "Ayee this is not in the option. Enter 1 or 2 to choose number of players. Enter 0 to exit the game." << endl;
            cin >> num_players;
            if (num_players == 0) {
                exit(0);
            }
        }
        cout << "Game has started. Enjoy! :)" << endl;
        string winner;
        if (num_players == 2) {
            int x, y;
            for(int i = 0; i < 9; i++) {
                if (i % 2 == 0) {
                    cout << "Player1's turn. Enter position(Row(Space)Column, ex- 2 3)." << endl;
                } else {
                    cout << "Player2's turn. Enter position(Row(Space)Column, ex- 2 3)." << endl;
                }
                cin >> x >> y;
                x = x - 1;
                y = y - 1;
                if ((x>=0)&&(x<3)&&(y>=0)&&(y<3)) {
                    if ((v[x][y] != "x")&&(v[x][y] != "o")) {
                        if (i%2==0) {
                            updategame("o", x, y, v);
                        } else {
                            updategame("x", x, y, v);
                        }
                    printgame(v); 
                    } else {
                        cout << "Ek hi position kitni baar daloge? Position already filled!!" << endl;
                        i = i - 1;
                        continue;
                    }
                    if (i>=4) {
                        winner = checkwinner(v, i);
                        if ((winner == "Player1") || (winner == "Player2")) {
                            cout << winner << " has won. Party do! :D" << endl;
                            v = resetboard(v);
                            break;
                        }    
                    }
                } else {
                    cout << "Arey yaar tic-tac-toe khelna nhi aata kya? Invalid Position!!" << endl;
                    i = i - 1;
                    continue;
                }    
            }
        }
        else if (num_players == 1) {
            cout << "What do you want to play as? x or o? o always starts the game." << endl;
            int x, y;
            string choose;
            cin >> choose;
            while (choose != "o" && choose != "x") {
                cout << "Ayee this is not in the option. Enter o or x to choose. Enter 0 to exit the game." << endl;
                cin >> choose;
                if (choose == "0") {
                    exit(0);
                }
            }
            if (choose == "o") {
                for(int i = 0; i < 9; i++) {
                    if (i % 2 == 0) {
                        cout << "Your turn. Enter position(Row(Space)Column, ex- 2 3)." << endl;
                        cin >> x >> y;
                        x = x - 1;
                        y = y - 1;
                        if ((x>=0)&&(x<3)&&(y>=0)&&(y<3)) {
                            if ((v[x][y] == "_")) {
                                updategame("o", x, y, v);
                                printgame(v); 
                            } else {
                                cout << "Ek hi position kitni baar daloge? Position already filled!!" << endl;
                                i = i - 1;
                                continue;
                            }
                            if (i>=4) {
                                winner = checkwinner(v, i);
                                if (winner == "Player1") {
                                    cout << "Congrats, You won!" << endl;
                                    v = resetboard(v);
                                    break;
                                }
                            }
                        } else {
                            cout << "Arey yaar tic-tac-toe khelna nhi aata kya? Invalid Position!!" << endl;
                            i = i - 1;
                            continue;
                        }    
                    } else {
                        cout << "Computer's turn" << endl;
                        pair<int, int> comp_turn = zero_intelligence(v, "x");
                        x = comp_turn.first;
                        y = comp_turn.second;
                        updategame("x", x, y, v);
                        printgame(v);
                        if (i >= 4) {
                            winner = checkwinner(v, i);
                            if (winner == "Player2") {
                                cout << "Computer won. Well played!" << endl;
                                v = resetboard(v);
                                break;
                            }
                        }
                        
                    }
                }
            }
            if (choose == "x") {
                for(int i = 0; i < 9; i++) {
                    if (i % 2 == 1) {
                        cout << "Your turn. Enter position(Row(Space)Column, ex- 2 3)." << endl;
                        cin >> x >> y;
                        x = x - 1;
                        y = y - 1;
                        if ((x>=0)&&(x<3)&&(y>=0)&&(y<3)) {
                            if ((v[x][y] == "_")) {
                                updategame("x", x, y, v);
                                printgame(v); 
                            } else {
                                cout << "Ek hi position kitni baar daloge? Position already filled!!" << endl;
                                i = i - 1;
                                continue;
                            }
                            if (i>=4) {
                                winner = checkwinner(v, i);
                                if (winner == "Player1") {
                                    cout << "Congrats, You won!" << endl;
                                    v = resetboard(v);
                                    break;
                                }
                            }
                        } else {
                            cout << "Arey yaar tic-tac-toe khelna nhi aata kya? Invalid Position!!" << endl;
                            i = i - 1;
                            continue;
                        }    
                    } else {
                        cout << "Computer's turn" << endl;
                        pair<int, int> comp_turn = zero_intelligence(v, "o");
                        x = comp_turn.first;
                        y = comp_turn.second;
                        updategame("o", x, y, v);
                        printgame(v);
                        if (i >= 4) {
                            winner = checkwinner(v, i);
                            if (winner == "Player2") {
                                cout << "Computer won. Well played!" << endl;
                                v = resetboard(v);
                                break;
                            }
                        }
                        
                    }
                }
            }
        }
        if (winner == "") {
            cout << "Game Draw. Maanna pdega barabari ki takkar hai dono ki!" << endl;
            v = resetboard(v);
        }
        cout << "Press 1 to play again and 0 to close game." << endl;
        int t;
        cin >> t;
        g = t;
        if (g==1) {
            continue;
        } else if (g==0) {
            exit(0);
        } else {
            cout << "Arey yeh kya enter kardiya!!" << endl;
            exit(0);
        }
    }
    return 0;
} 
