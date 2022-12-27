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
            vect[i][j] = " ";
        }
    }
    return vect;
}

vector<vector<string>> updategame(string s, int x, int y, vector<vector<string>>& vect) {
    vect[x][y] = s;
    return vect;
}

string checkwinner(vector<vector<string>> board, int chance) {
    if (((board[0][0]==board[0][1])&&(board[0][1]==board[0][2])&&(board[0][2]!=""))||((board[0][0]==board[1][0])&&(board[1][0]==board[2][0])&&(board[2][0]!=""))||((board[1][0]==board[1][1])&&(board[1][1]==board[1][2])&&(board[1][2]!=""))||((board[0][1]==board[1][1])&&(board[1][1]==board[2][1])&&(board[2][1]!=""))||((board[2][0]==board[2][1])&&(board[2][1]==board[2][2])&&(board[2][2]!=""))||((board[0][2]==board[1][2])&&(board[1][2]==board[2][2])&&(board[2][2]!=""))||((board[0][0]==board[1][1])&&(board[1][1]==board[2][2])&&(board[2][2]!=""))||((board[0][2]==board[1][1])&&(board[1][1]==board[2][0])&&(board[2][0]!=""))) {
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
            rowV.push_back(" ");
        }

        v.push_back(rowV);
    }
    //define coordinates
    //input(valid,invalid), update, print, check
    cout << "_______________________________________________________________________________________________________________________________________" << endl;
    cout << "Tic Tac Toe mein aapka swagat hai. Khel shuru karne keliye 1 enter kariye." << endl;
    int g;
    cin >> g;
    if (g!=1) {
        cout << "Arey yeh kya enter kardiya!!" << endl;
    }
    while (g==1) {
        cout << "Khel shuru. Maze karo! :)" << endl;
        int x, y;
        string winner;
        for(int i = 0; i < 9; i++) {
            if (i % 2 == 0) {
                cout << "Player1 ki baari. Position daaliye." << endl;
            } else {
                cout << "Player2 ki baari. Position daaliye." << endl;

            }
            cin >> x >> y;
            x = x - 1;
            y = y - 1;
            if ((x>=0)&&(x<3)&&(y>=0)&&(y<3)) {
                if ((v[x][y] != "x")&&(v[x][y] != "o")) {
                    if (i%2==0) {
                        // cout << "o";
                        updategame("o", x, y, v);
                    } else {
                        // cout << "x";
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
                        cout << winner << " aap jeet gaye. Party do! :D" << endl;
                        v = resetboard(v);
                        break;
                    }    
                }
            } else {
                cout << "Arey yaar tic tac toe khelna nhi aata kya? Invalid Position!!" << endl;
                i = i - 1;
                continue;
            }    
        } 
        if (winner == "") {
            cout << "Game Draw. Maanna pdega barabari ki takkar hai dono ki!" << endl;
        }
        cout << "Fir se khlne keliye 1 enter kariye aur game band karna hai to 0 enter kariye." << endl;
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