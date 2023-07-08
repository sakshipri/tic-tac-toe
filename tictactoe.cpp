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
pair<int, pair<int, int>> intelligence(vector<vector<string>> vect, string comp, int depth, bool isMax) {
    // first check if the win is possible, if it is, win
    // if not, then check if loss is possible, if it is, not lose
    // if not, play to make two in a row,  if possible
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

    vector<int> values;
    vector<pair<int, int>> options;

    for (int i = 0; i < vect.size(); i++) {
        for (int j = 0; j < vect[i].size(); j++) {
            if (vect[i][j] == "_") {
                vect[i][j] = comp;
                winner = checkwinner(vect, chance);
                if (winner == "") {
                    vect[i][j] = "_";
                } else {
                    int val;
                    if (isMax) {
                        val = 20;
                    } else {
                        val = -20;
                    }
                    return make_pair(val, make_pair(i, j));
                }
            }
        }
    }
    // chance++;
    // for (int i = 0; i < vect.size(); i++) {
    //     for (int j = 0; j < vect[i].size(); j++) {
    //         if (vect[i][j] == "_") {
    //             vect[i][j] = human;
    //             winner = checkwinner(vect, chance);
    //             if (winner == "") {
    //                 vect[i][j] = "_";
    //             } else {
    //                 int val;
    //                 if (isMax) {
    //                     val = 10;
    //                 } else {
    //                     val = -10;
    //                 }
    //                 return make_pair(val, make_pair(i, j));
    //             }
    //         }
    //     }
    // }
    // chance++;

    if (depth == 0) {
        for (int i = 0; i < vect.size(); i++) {
            for (int j = 0; j < vect[i].size(); j++) {
                if (vect[i][j] == "_") {
                    vect[i][j] = comp;

                    int val = 0;

                    // winner = checkwinner(vect, chance);
                    // if (winner != "") {
                    //     // if (isMax) {
                    //     //     val = 20;
                    //     // } else {
                    //     //     val = 20;
                    //     // }
                    //     val = 20;
                    // } else {
                    //     vect[i][j] = human;
                    //     winner = checkwinner(vect, chance + 1);

                    //     if (winner != "") {
                    //         // if (isMax) {
                    //         //     val = -10;
                    //         // } else {
                    //         //     val = 10;
                    //         // }
                    //         val = 10;
                    //     } else {
                    //         val = 0;
                    //     }
                    // }

                    vect[i][j] = "_";

                    values.push_back(val);
                    options.push_back(make_pair(i, j));
                }
            }
        }
    } else {
        for (int i = 0; i < vect.size(); i++) {
            for (int j = 0; j < vect[i].size(); j++) {
                if (vect[i][j] == "_") {
                    vect[i][j] = comp;

                    pair<int, pair<int, int>> intelOutput = intelligence(vect, human, depth - 1, !isMax);
                    
                    int val = intelOutput.first;
                    values.push_back(val);
                    
                    options.push_back(make_pair(i, j));
                    
                    vect[i][j] = "_";
                }
            }
        }
    }
    
    int selectedValue;
    pair<int, int> selectedOption;

    if (isMax) {
        selectedValue = -100;
        for (int i = 0; i < values.size(); i++) {
            // selectedValue = max(selectedValue, values[i]);
            selectedValue = selectedValue < values[i] ? values[i] : selectedValue;
            selectedOption = selectedValue < values[i] ? options[i] : selectedOption;
        }
    } else {
        selectedValue = 100;
        for (int i = 0; i < values.size(); i++) {
            // selectedValue = min(selectedValue, values[i]);
            selectedValue = selectedValue > values[i] ? values[i] : selectedValue;
            selectedOption = selectedValue > values[i] ? options[i] : selectedOption;
        }
    }
    
    vector<pair<int, int>> sameValueOptions;
    for (int i = 0; i < options.size(); i++) {
        if (values[i] == selectedValue) {
            sameValueOptions.push_back(options[i]);
        }
    }

    int optionIdx = rand() % sameValueOptions.size();
    selectedOption = sameValueOptions[optionIdx];

    return make_pair(selectedValue, selectedOption);
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
            cout << "Choose level, enter:" << endl;
            cout << "1 for Easy" << endl;
            cout << "2 for Medium" << endl;
            cout << "3 for Hard" << endl;
            int level;
            cin >> level;
            if (level != 1 && level != 2 && level != 3) {
                cout << "It's not an the option. Choose again." << endl;
                cin >> level;
            }
            int depth;
            if (level == 1) {
                depth = 0;
            }
            if (level == 2) {
                depth = 4;
            }
            if (level == 3) {
                depth = 8;
            }

            cout << "What do you want to play as? x or o? o always starts the game." << endl;
            string choose;
            cin >> choose;
            int x, y;
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
                        int maxDepth = 8 - i;
                        pair<int, pair<int, int>> intelOutput = intelligence(v, "x", min(depth, maxDepth), true);
                        pair<int, int> comp_turn = intelOutput.second;
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
                                if (winner == "Player2") {
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
                        int maxDepth = 8 - i;
                        pair<int, pair<int, int>> intelOutput = intelligence(v, "o", min(depth, maxDepth), true);
                        pair<int, int> comp_turn = intelOutput.second;
                        x = comp_turn.first;
                        y = comp_turn.second;
                        updategame("o", x, y, v);
                        printgame(v);
                        if (i >= 4) {
                            winner = checkwinner(v, i);
                            if (winner == "Player1") {
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
