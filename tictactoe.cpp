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

int main() { 
    vector<vector<string>> v;

    for (int i = 0; i < 3; ++i) {
        vector<string> rowV;

        for (int j = 0; j < 3; ++j) {
            rowV.push_back("_");
        }

        v.push_back(rowV);
    }
    cout << "_______________________________________________________________________________________________________________________________________" << endl;
    cout << "Welcome to tic-tac-toe. Enter 1 to start." << endl;
    int g;
    cin >> g;
    printgame(v);
    if (g!=1) {
        cout << "Arey yeh kya enter kardiya!!" << endl;
    }
    while (g==1) {
        cout << "Game has started. Enjoy! :)" << endl;
        int x, y;
        string winner;
        for(int i = 0; i < 9; i++) {
            if (i % 2 == 0) {
                cout << "Player1's turn. Enter position(RowSpaceColumn, ex- 2 3)." << endl;
            } else {
                cout << "Player2's turn. Enter position(RowSpaceColumn, ex- 2 3)." << endl;
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
        if (winner == "") {
            cout << "Game Draw. Maanna pdega barabari ki takkar hai dono ki!" << endl;
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
