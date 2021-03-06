#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <map>
#include <utility>

using namespace std;
string ABbestMove = "";
string playMoveAB = "";
string miniBestMove = "";
string playMoveMini = "";

//may ignore crocodiles, monkeys and giraffes and superpawns going forward.

enum BoardState
{
    empty = 0,

    wLion = 1,
    wElephant = 2,
    wZebra = 3,
    wPawn = 4,

    bLion = 5,
    bElephant = 6,
    bZebra = 7,
    bPawn = 8,

    river = 9,
    wDen = 11,
    bDen = 55,

};

vector<vector<BoardState>> boardSetup(vector<vector<BoardState>> &board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (i == 3 && board[i][j] == NULL)
            {
                board[i][j] = river;
            }
            if (i >= 0 && i < 3 && j > 1 && j < 5 && board[i][j] == NULL)
            {
                //11 is wDen
                board[i][j] = wDen;
            }
            if (i > 3 && j > 1 && j < 5 && board[i][j] == NULL)
            {
                //55 is bDen
                board[i][j] = bDen;
            }
            if (board[i][j] == NULL)
            {
                board[i][j] = empty;
            }
        }
    }
    return board;
}

string makeFen(vector<vector<BoardState>> board)
{
    int counter = 0;
    string out = "";
    for (int i = board.size() - 1; i >= 0; i--)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (board[i][j] >= 1 && board[i][j] <= 8 && counter > 0)
            {
                out += to_string(counter);
                counter = 0;
            }
            if (board[i][j] == 0 || board[i][j] >= 9)
            {
                counter++;
                if (counter == 7 || j == board.size() - 1)
                {
                    out += to_string(counter);
                }
                else
                {
                    continue;
                }
            }
            else if (board[i][j] == 1)
            {
                out += "L";
            }
            else if (board[i][j] == 2)
            {
                out += "E";
            }
            else if (board[i][j] == 3)
            {
                out += "Z";
            }
            else if (board[i][j] == 4)
            {
                out += "P";
            }
            else if (board[i][j] == 5)
            {
                out += "l";
            }
            else if (board[i][j] == 6)
            {
                out += "e";
            }
            else if (board[i][j] == 7)
            {
                out += "z";
            }
            else if (board[i][j] == 8)
            {
                out += "p";
            }
        }
        counter = 0;
        if (i != 0)
        {
            out += "/";
        }
    }

    return out;
}


map<char, vector<pair<char, int>>> updatePieceList(map<char, vector<pair<char, int>>> pieceList, vector<vector<BoardState>> board)
{

    vector<char> col = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] == wLion)
            {
                pieceList['L'].push_back(make_pair(col[j], i + 1));
            }
            if (board[i][j] == bLion)
            {
                pieceList['l'].push_back(make_pair(col[j], i + 1));
            }
            if (board[i][j] == wZebra)
            {
                pieceList['Z'].push_back(make_pair(col[j], i + 1));
            }
            if (board[i][j] == bZebra)
            {
                pieceList['z'].push_back(make_pair(col[j], i + 1));
            }
            if (board[i][j] == wElephant)
            {
                pieceList['E'].push_back(make_pair(col[j], i + 1));
            }
            if (board[i][j] == bElephant)
            {
                pieceList['e'].push_back(make_pair(col[j], i + 1));
            }
            if (board[i][j] == wPawn)
            {
                pieceList['P'].push_back(make_pair(col[j], i + 1));
            }
            if (board[i][j] == bPawn)
            {
                pieceList['p'].push_back(make_pair(col[j], i + 1));
            }
        }
    }
    return pieceList;
}


void printBoard(vector<vector<BoardState>> board)
{
    //cout << board.size();
    for (int i = board.size() - 1; i >= 0; i--)
    {
        for (int j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] == 55 || board[i][j] == 11)
            {
                cout << board[i][j] << " ";
            }
            else
            {
                cout << "0" << board[i][j] << " ";
            }
        }
        cout << endl;
    }
}

void sortPieces(map<char, vector<pair<char, int>>> pieceList)
{
    sort(pieceList['l'].begin(), pieceList['l'].end());
    sort(pieceList['L'].begin(), pieceList['L'].end());
    sort(pieceList['e'].begin(), pieceList['e'].end());
    sort(pieceList['E'].begin(), pieceList['E'].end());
    sort(pieceList['z'].begin(), pieceList['z'].end());
    sort(pieceList['Z'].begin(), pieceList['Z'].end());
    sort(pieceList['p'].begin(), pieceList['p'].end());
    sort(pieceList['P'].begin(), pieceList['P'].end());
    sort(pieceList['s'].begin(), pieceList['s'].end());
    sort(pieceList['S'].begin(), pieceList['S'].end());
    sort(pieceList['m'].begin(), pieceList['m'].end());
    sort(pieceList['M'].begin(), pieceList['M'].end());
    sort(pieceList['c'].begin(), pieceList['c'].end());
    sort(pieceList['C'].begin(), pieceList['C'].end());
    sort(pieceList['g'].begin(), pieceList['g'].end());
    sort(pieceList['G'].begin(), pieceList['G'].end());
}

void printPawns(map<char, vector<pair<char, int>>> pieceList)
{
    sort(pieceList['P'].begin(), pieceList['P'].end());
    sort(pieceList['p'].begin(), pieceList['p'].end());
    cout << "white pawn: ";
    for (int i = 0; i < pieceList['P'].size(); i++)
    {
        cout << pieceList['P'][i].first << pieceList['P'][i].second << " ";
    }
    cout << endl;
    cout << "black pawn: ";
    for (int i = 0; i < pieceList['p'].size(); i++)
    {
        cout << pieceList['p'][i].first << pieceList['p'][i].second << " ";
    }
    cout << endl;
}

void printSuperpawns(map<char, vector<pair<char, int>>> pieceList)
{
    sort(pieceList['S'].begin(), pieceList['S'].end());
    sort(pieceList['s'].begin(), pieceList['s'].end());
    cout << "white Superpawn: ";
    for (int i = 0; i < pieceList['S'].size(); i++)
    {
        cout << pieceList['S'][i].first << pieceList['S'][i].second << " ";
    }
    cout << endl;
    cout << "black Superpawn: ";
    for (int i = 0; i < pieceList['s'].size(); i++)
    {
        cout << pieceList['s'][i].first << pieceList['s'][i].second << " ";
    }
    cout << endl;
}

void printGiraffe(map<char, vector<pair<char, int>>> pieceList)
{
    sort(pieceList['G'].begin(), pieceList['G'].end());
    sort(pieceList['g'].begin(), pieceList['g'].end());
    cout << "white giraffe: ";
    for (int i = 0; i < pieceList['G'].size(); i++)
    {
        cout << pieceList['G'][i].first << pieceList['G'][i].second << " ";
    }
    cout << endl;
    cout << "black giraffe: ";
    for (int i = 0; i < pieceList['g'].size(); i++)
    {
        cout << pieceList['g'][i].first << pieceList['g'][i].second << " ";
    }
    cout << endl;
}

void printMonkey(map<char, vector<pair<char, int>>> pieceList)
{
    sort(pieceList['M'].begin(), pieceList['M'].end());
    sort(pieceList['m'].begin(), pieceList['m'].end());
    cout << "white Monkey: ";
    for (int i = 0; i < pieceList['M'].size(); i++)
    {
        cout << pieceList['M'][i].first << pieceList['M'][i].second << " ";
    }
    cout << endl;
    cout << "black Monkey: ";
    for (int i = 0; i < pieceList['m'].size(); i++)
    {
        cout << pieceList['m'][i].first << pieceList['m'][i].second << " ";
    }
    cout << endl;
}

void printElephant(map<char, vector<pair<char, int>>> pieceList)
{
    sort(pieceList['E'].begin(), pieceList['E'].end());
    sort(pieceList['e'].begin(), pieceList['e'].end());
    cout << "white Elephant: ";
    for (int i = 0; i < pieceList['E'].size(); i++)
    {
        cout << pieceList['E'][i].first << pieceList['E'][i].second << " ";
    }
    cout << endl;
    cout << "black Elephant: ";
    for (int i = 0; i < pieceList['e'].size(); i++)
    {
        cout << pieceList['e'][i].first << pieceList['e'][i].second << " ";
    }
    cout << endl;
}

void printLion(map<char, vector<pair<char, int>>> pieceList)
{
    sort(pieceList['L'].begin(), pieceList['L'].end());
    sort(pieceList['l'].begin(), pieceList['l'].end());
    cout << "white Lion: ";
    for (int i = 0; i < pieceList['L'].size(); i++)
    {
        cout << pieceList['L'][i].first << pieceList['L'][i].second << " ";
    }
    cout << endl;
    cout << "black Lion: ";
    for (int i = 0; i < pieceList['l'].size(); i++)
    {
        cout << pieceList['l'][i].first << pieceList['l'][i].second << " ";
    }
    cout << endl;
}

void printCrocodile(map<char, vector<pair<char, int>>> pieceList)
{
    sort(pieceList['C'].begin(), pieceList['C'].end());
    sort(pieceList['c'].begin(), pieceList['c'].end());
    cout << "white Crocodile: ";
    for (int i = 0; i < pieceList['C'].size(); i++)
    {
        cout << pieceList['C'][i].first << pieceList['C'][i].second << " ";
    }
    cout << endl;
    cout << "black Crocodile: ";
    for (int i = 0; i < pieceList['c'].size(); i++)
    {
        cout << pieceList['c'][i].first << pieceList['c'][i].second << " ";
    }
    cout << endl;
}

void printZebra(map<char, vector<pair<char, int>>> pieceList)
{
    sort(pieceList['Z'].begin(), pieceList['Z'].end());
    sort(pieceList['z'].begin(), pieceList['z'].end());
    cout << "white Zebra: ";
    for (int i = 0; i < pieceList['Z'].size(); i++)
    {
        cout << pieceList['Z'][i].first << pieceList['Z'][i].second << " ";
    }
    cout << endl;
    cout << "black Zebra: ";
    for (int i = 0; i < pieceList['z'].size(); i++)
    {
        cout << pieceList['z'][i].first << pieceList['z'][i].second << " ";
    }
    cout << endl;
}

tuple<map<char, vector<pair<char, int>>>, vector<vector<BoardState>>> mapInit(map<char, vector<pair<char, int>>> pieceList, string fen, vector<vector<BoardState>> board)
{
    int row = 7;
    vector<char> col = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    vector<char> spaces = {'1', '2', '3', '4', '5', '6', '7'};
    int colPos = 0;
    bool num = false;

    for (int i = 0; i < fen.length(); i++)
    {
        //should handle the numbers for spacing in the input
        for (int j = 0; j < spaces.size(); j++)
        {
            if (fen[i] == spaces[j])
            {
                num = true;
                colPos = colPos + (spaces[j] - '0');
                break;
            }
        }

        if (fen[i] == '/')
        {
            row--;
            colPos = 0;
            continue;
        }
        //black pieces
        else if (fen[i] == 'p')
        {
            pieceList['p'].push_back(make_pair(col[colPos], row));
            board[row - 1][colPos] = bPawn;
            //cout << board[colPos][row] << endl;
        }
        else if (fen[i] == 's')
        {
            pieceList['s'].push_back(make_pair(col[colPos], row));
        }
        else if (fen[i] == 'g')
        {
            pieceList['g'].push_back(make_pair(col[colPos], row));
        }
        else if (fen[i] == 'm')
        {
            pieceList['m'].push_back(make_pair(col[colPos], row));
        }
        else if (fen[i] == 'e')
        {
            pieceList['e'].push_back(make_pair(col[colPos], row));
            board[row - 1][colPos] = bElephant;
        }
        else if (fen[i] == 'l')
        {
            pieceList['l'].push_back(make_pair(col[colPos], row));
            board[row - 1][colPos] = bLion;
        }
        else if (fen[i] == 'c')
        {
            pieceList['c'].push_back(make_pair(col[colPos], row));
        }
        else if (fen[i] == 'z')
        {
            pieceList['z'].push_back(make_pair(col[colPos], row));
            board[row - 1][colPos] = bZebra;
        }
        //white pieces
        else if (fen[i] == 'P')
        {
            pieceList['P'].push_back(make_pair(col[colPos], row));
            board[row - 1][colPos] = wPawn;
        }
        else if (fen[i] == 'S')
        {
            pieceList['S'].push_back(make_pair(col[colPos], row));
        }
        else if (fen[i] == 'G')
        {
            pieceList['G'].push_back(make_pair(col[colPos], row));
        }
        else if (fen[i] == 'M')
        {
            pieceList['M'].push_back(make_pair(col[colPos], row));
        }
        else if (fen[i] == 'E')
        {
            pieceList['E'].push_back(make_pair(col[colPos], row));
            board[row - 1][colPos] = wElephant;
        }
        else if (fen[i] == 'L')
        {
            pieceList['L'].push_back(make_pair(col[colPos], row));
            board[row - 1][colPos] = wLion;
        }
        else if (fen[i] == 'C')
        {
            pieceList['C'].push_back(make_pair(col[colPos], row));
        }
        else if (fen[i] == 'Z')
        {
            pieceList['Z'].push_back(make_pair(col[colPos], row));
            board[row - 1][colPos] = wZebra;
        }

        if (num == false)
        {
            colPos++;
        }
        num = false;
    }
    return make_tuple(pieceList, board);
}

vector<string> lionMoves(vector<vector<BoardState>> board, map<char, vector<pair<char, int>>> pieceList, char colourTurn)
{
    //init variables needed
    vector<char> column = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    vector<pair<char, int>> temp;
    vector<pair<char, int>> enemyTemp;
    vector<pair<char, int>> moves;
    vector<string> allMoves;

    int row = 0;
    int col = 0;

    //determine for which colour we are finding the moves for
    if (colourTurn == 'b')
    {
        temp = pieceList['l'];
        enemyTemp = pieceList['L'];
    }
    else
    {
        temp = pieceList['L'];
        enemyTemp = pieceList['l'];
    }

    //find the index for the col
    if (temp.size() > 0 && enemyTemp.size() > 0)
    {
        for (int j = 0; j < column.size(); j++)
        {
            if (temp[0].first == column[j])
            {
                col++;
                break;
            }
            col++;
        }
    }
    else
    {
        return allMoves;
    }

    // need to decrement both down by 1 to match the arrays starting at 0 rather than 1.
    int cols = col - 1;
    int rows = temp[0].second - 1;

    //black moves
    if (colourTurn == 'b')
    {
        //white pieces = 1-4
        //bDen = 55

        //TODO: make is so that the lion can capture across the river

        //need to check if the lion is unostracted from the same row from him to the opposing lion
        //first check if they are in the same column
        //part 1 captures down with no blocks done.
        if (temp[0].first == enemyTemp[0].first)
        {
            int distance = temp[0].second - enemyTemp[0].second;
            //cout << "same row: " << endl;
            //need to minus 2, 1 for the vector size the other to make sure it stop one square before it reaches the lion
            for (int i = enemyTemp[0].second - 1; i <= temp[0].second - 2; i++)
            {

                if (board[i][cols] >= 9 || board[i][cols] == 1)
                {
                    if (i == temp[0].second - 2)
                    {
                        //cout << "captures straight accross river" << endl;
                        moves.push_back((make_pair(column[cols], temp[0].second - distance)));
                    }
                }
                else
                {
                    break;
                }
            }
        }

        //part 2 captures diagonal left and right across the river
        //capture diagonal down right
        if (temp[0].first == 'c' && temp[0].second == 5 && enemyTemp[0].first == 'e' && enemyTemp[0].second == 3 && board[3][3] == 9)
        {
            //cout << "captures down right" << endl;
            moves.push_back((make_pair(column[cols + 2], rows - 1)));
        }

        //capture diagonal down left
        if (temp[0].first == 'e' && temp[0].second == 5 && enemyTemp[0].first == 'c' && enemyTemp[0].second == 3 && board[3][3] == 9)
        {
            //cout << "capture down left" << endl;
            moves.push_back((make_pair(column[cols - 2], rows - 1)));
        }

        //up

        if (rows != 6 && ((board[rows + 1][cols] >= 1 && board[rows + 1][cols] <= 4) || board[rows + 1][cols] == 55))
        {
            //cout << "up" << endl;
            moves.push_back((make_pair(column[cols], rows + 2)));
        }
        //down
        if (rows > 4 && (board[rows - 1][cols] >= 1 && board[rows - 1][cols] <= 4) || board[rows - 1][cols] == 55)
        {
            //cout << "down" << endl;
            moves.push_back((make_pair(column[cols], rows)));
        }
        //left
        if (cols > 2 && (board[rows][cols - 1] >= 1 && board[rows][cols - 1] <= 4) || board[rows][cols - 1] == 55)
        {
            //cout << "left" << endl;
            moves.push_back((make_pair(column[cols - 1], rows + 1)));
        }
        //right
        if (cols < 4 && ((board[rows][cols + 1] >= 1 && board[rows][cols + 1] <= 4) || board[rows][cols + 1] == 55))
        {
            //cout << "right" << endl;
            moves.push_back((make_pair(column[cols + 1], rows + 1)));
        }
        //up-left
        if ((rows != 6 && cols > 2) && ((board[rows + 1][cols - 1] >= 1 && board[rows + 1][cols - 1] <= 4) || board[rows + 1][cols - 1] == 55))
        {
            //cout << "up-left" << endl;
            moves.push_back((make_pair(column[cols - 1], rows + 2)));
        }
        //up-right
        if ((rows != 6 && cols < 4) && ((board[rows + 1][cols + 1] >= 1 && board[rows + 1][cols + 1] <= 4) || board[rows + 1][cols + 1] == 55))
        {
            // cout << "up-right" << endl;
            moves.push_back((make_pair(column[cols + 1], rows + 2)));
        }
        //down-left
        if (rows > 4 && cols > 2 && (board[rows - 1][cols - 1] >= 1 && board[rows - 1][cols - 1] <= 4) || board[rows - 1][cols - 1] == 55)
        {
            //cout << "down-left" << endl;
            moves.push_back((make_pair(column[cols - 1], rows)));
        }
        //down-right
        if (rows > 4 && cols < 4 && ((board[rows - 1][cols + 1] >= 1 && board[rows - 1][cols + 1] <= 4) || board[rows - 1][cols + 1] == 55))
        {
            //cout << "down-right" << endl;
            moves.push_back((make_pair(column[cols + 1], rows)));
        }
    }
    else
    {
        //white moves
        if (temp[0].first == enemyTemp[0].first)
        {
            //cout << "same row: " << endl;
            int distance = enemyTemp[0].second - temp[0].second;
            //need to fix error of lion capturing straight accross river
            for (int i = enemyTemp[0].second - 1; i >= temp[0].second - 1; i--)
            {
                if (temp[0].second == 1)
                {
                    if (board[i][cols] >= 9 || board[i][cols] == 5)
                    {
                        if (i == temp[0].second)
                        {
                            moves.push_back((make_pair(column[cols], temp[0].second + distance)));
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    if (board[i][cols] >= 9 || board[i][cols] == 5)
                    {
                        if (i == temp[0].second)
                        {
                            moves.push_back((make_pair(column[cols], temp[0].second + distance)));
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }

        //part 2 captures diagonal up-left and up-right across the river
        //capture diagonal up right
        if (temp[0].first == 'c' && temp[0].second == 3 && enemyTemp[0].first == 'e' && enemyTemp[0].second == 5 && board[3][3] == 9)
        {
            //   cout << "captures up right" << endl;
            moves.push_back((make_pair(column[cols + 2], rows + 3)));
        }

        //capture diagonal up left
        if (temp[0].first == 'e' && temp[0].second == 3 && enemyTemp[0].first == 'c' && enemyTemp[0].second == 5 && board[3][3] == 9)
        {
            //   cout << "capture up left" << endl;
            moves.push_back((make_pair(column[cols - 2], rows + 3)));
        }

        //up
        if (rows != 2 && ((board[rows + 1][cols] >= 5 && board[rows + 1][cols] <= 8) || board[rows + 1][cols] == 11))
        {
            //    cout << "up" << endl;
            moves.push_back((make_pair(column[cols], rows + 2)));
        }
        //down
        if (rows != 0 && ((board[rows - 1][cols] >= 5 && board[rows - 1][cols] <= 8) || board[rows - 1][cols] == 11))
        {
            //    cout << "down" << endl;
            moves.push_back((make_pair(column[cols], rows)));
        }
        //left
        if (cols > 2 && ((board[rows][cols - 1] >= 5 && board[rows][cols - 1] <= 8) || board[rows][cols - 1] == 11))
        {
            //   cout << "left" << endl;
            moves.push_back((make_pair(column[cols - 1], rows + 1)));
        }
        //right
        if (cols < 4 && ((board[rows][cols + 1] >= 5 && board[rows][cols + 1] <= 8) || board[rows][cols + 1] == 11))
        {
            //   cout << "right" << endl;
            moves.push_back((make_pair(column[cols + 1], rows + 1)));
        }
        //up-left
        if (rows != 2 && cols > 2 && ((board[rows + 1][cols - 1] >= 5 && board[rows + 1][cols - 1] <= 8) || board[rows + 1][cols - 1] == 11))
        {
            //    cout << "up-left" << endl;
            moves.push_back((make_pair(column[cols - 1], rows + 2)));
        }
        //up-right
        if (rows != 2 && cols < 4 && ((board[rows + 1][cols + 1] >= 5 && board[rows + 1][cols + 1] <= 8) || board[rows + 1][cols + 1] == 11))
        {
            //    cout << "up-right" << endl;
            moves.push_back((make_pair(column[cols + 1], rows + 2)));
        }
        //down-left
        if (rows != 0 && cols > 2 && ((board[rows - 1][cols - 1] >= 5 && board[rows - 1][cols - 1] <= 8) || board[rows - 1][cols - 1] == 11))
        {
            //    cout << "down-left" << endl;
            moves.push_back((make_pair(column[cols - 1], rows)));
        }
        //down-right
        if (rows != 0 && cols < 4 && ((board[rows - 1][cols + 1] >= 5 && board[rows - 1][cols + 1] <= 8) || board[rows - 1][cols + 1] == 11))
        {
            //    cout << "down-right" << endl;
            moves.push_back((make_pair(column[cols + 1], rows)));
        }
    }

    // cout << endl
    //      << endl;
    sort(moves.begin(), moves.end());
    allMoves.resize(moves.size());
    for (int i = 0; i < moves.size(); i++)
    {
        allMoves[i] = temp[0].first + to_string(temp[0].second) + moves[i].first + to_string(moves[i].second);
    }
    return allMoves;
}

vector<string> zebraMoves(vector<vector<BoardState>> board, map<char, vector<pair<char, int>>> pieceList, char colourTurn)
{
    //init variables needed
    vector<char> column = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    vector<pair<char, int>> temp;
    vector<pair<char, int>> enemyTemp;
    vector<pair<char, int>> moves;
    vector<string> allMoves;
    int row = 0;
    int col = 0;

    // determine for which colour we are finding the moves for
    if (colourTurn == 'b')
    {
        temp = pieceList['z'];
    }
    else
    {
        temp = pieceList['Z'];
    }

    //find the index for the col
    if (temp.size() > 0)
    {
        for (int j = 0; j < column.size(); j++)
        {
            if (temp[0].first == column[j])
            {
                col++;
                break;
            }
            col++;
        }
    }
    else
    {
        return allMoves;
    }

    // need to decrement both down by 1 to match the arrays starting at 0 rather than 1.
    int cols = col - 1;
    int rows = temp[0].second - 1;

    if (colourTurn == 'b')
    {
        //left
        if (cols >= 2)
        {
            //left-2 and up-1
            if (rows <= 5 && (board[rows + 1][cols - 2] <= 4 || board[rows + 1][cols - 2] >= 9))
            {
                moves.push_back(make_pair(column[cols - 2], rows + 2));
            }
            //left-2 and down-1
            if (rows >= 1 && (board[rows - 1][cols - 2] <= 4 || board[rows - 1][cols - 2] >= 9))
            {
                moves.push_back(make_pair(column[cols - 2], rows));
            }
        }
        //right
        if (cols <= 4)
        {
            //right-2 and up-1
            if (rows <= 5 && (board[rows + 1][cols + 2] <= 4 || board[rows + 1][cols + 2] >= 9))
            {
                moves.push_back(make_pair(column[cols + 2], rows + 2));
            }
            //right-2 and down-1
            if (rows >= 1 && (board[rows - 1][cols + 2] <= 4 || board[rows - 1][cols + 2] >= 9))
            {
                moves.push_back(make_pair(column[cols + 2], rows));
            }
        }
        //up
        if (rows <= 4)
        {
            //up-2 and left-1
            if (cols >= 1 && (board[rows + 2][cols - 1] <= 4 || board[rows + 2][cols - 1] >= 9))
            {
                moves.push_back(make_pair(column[cols - 1], rows + 3));
            }
            //up-2 and right-1
            if (cols <= 5 && (board[rows + 2][cols + 1] <= 4 || board[rows + 2][cols + 1] >= 9))
            {
                moves.push_back(make_pair(column[cols + 1], rows + 3));
            }
        }
        //down
        if (rows >= 2)
        {
            //down-2 and left-1
            if (cols >= 1 && (board[rows - 2][cols - 1] <= 4 || board[rows - 2][cols - 1] >= 9))
            {
                moves.push_back(make_pair(column[cols - 1], rows - 1));
            }
            //down-2 and right-1
            if (cols <= 5 && (board[rows - 2][cols + 1] <= 4 || board[rows - 2][cols + 1] >= 9))
            {
                moves.push_back(make_pair(column[cols + 1], rows - 1));
            }
        }
    }
    else
    {
        if (cols >= 2)
        {
            //left-2 and up-1
            if (rows <= 5 && (board[rows + 1][cols - 2] == 0 || board[rows + 1][cols - 2] >= 5))
            {
                moves.push_back(make_pair(column[cols - 2], rows + 2));
            }
            //left-2 and down-1
            if (rows >= 1 && (board[rows - 1][cols - 2] <= 0 || board[rows - 1][cols - 2] >= 5))
            {
                moves.push_back(make_pair(column[cols - 2], rows));
            }
        }
        //right
        if (cols <= 4)
        {
            //right-2 and up-1
            if (rows <= 5 && (board[rows + 1][cols + 2] <= 0 || board[rows + 1][cols + 2] >= 5))
            {
                moves.push_back(make_pair(column[cols + 2], rows + 2));
            }
            //right-2 and down-1
            if (rows >= 1 && (board[rows - 1][cols + 2] <= 0 || board[rows - 1][cols + 2] >= 5))
            {
                moves.push_back(make_pair(column[cols + 2], rows));
            }
        }
        //up
        if (rows <= 4)
        {
            //up-2 and left-1
            if (cols >= 1 && (board[rows + 2][cols - 1] <= 0 || board[rows + 2][cols - 1] >= 5))
            {
                moves.push_back(make_pair(column[cols - 1], rows + 3));
            }
            //up-2 and right-1
            if (cols <= 5 && (board[rows + 2][cols + 1] <= 0 || board[rows + 2][cols + 1] >= 5))
            {
                moves.push_back(make_pair(column[cols + 1], rows + 3));
            }
        }
        //down
        if (rows >= 2)
        {
            //down-2 and left-1
            if (cols >= 1 && (board[rows - 2][cols - 1] <= 0 || board[rows - 2][cols - 1] >= 5))
            {
                moves.push_back(make_pair(column[cols - 1], rows - 1));
            }
            //down-2 and right-1
            if (cols <= 5 && (board[rows - 2][cols + 1] <= 0 || board[rows - 2][cols + 1] >= 5))
            {
                moves.push_back(make_pair(column[cols + 1], rows - 1));
            }
        }
    }

    sort(moves.begin(), moves.end());
    allMoves.resize(moves.size());
    for (int i = 0; i < moves.size(); i++)
    {
        allMoves[i] = temp[0].first + to_string(temp[0].second) + moves[i].first + to_string(moves[i].second);
    }
    return allMoves;
}

vector<string> elephantMoves(vector<vector<BoardState>> board, map<char, vector<pair<char, int>>> pieceList, char colourTurn)
{
    //init variables needed
    vector<char> column = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    vector<pair<char, int>> temp;
    vector<pair<char, int>> enemyTemp;
    vector<string> totalMoves;
    int numPieces = 0;

    // determine for which colour we are finding the moves for
    if (colourTurn == 'b')
    {
        temp = pieceList['e'];
        numPieces = temp.size();
    }
    else
    {
        temp = pieceList['E'];
        numPieces = temp.size();
    }

    vector<vector<pair<char, int>>> moves(numPieces);

    if (numPieces == 0)
    {
        return totalMoves;
    }
    else
    {
        for (int i = 0; i < numPieces; i++)
        {
            int row = 0;
            int col = 0;
            //find the index for the col
            for (int j = 0; j < column.size(); j++)
            {
                if (temp[i].first == column[j])
                {
                    col++; //remove ++ and take out -1 from below ?
                    break;
                }
                col++;
            }
            // need to decrement both down by 1 to match the arrays starting at 0 rather than 1.
            int cols = col - 1;
            int rows = temp[i].second - 1;

            if (colourTurn == 'b')
            {
                //left-2
                if (cols >= 2 && (board[rows][cols - 2] <= 4 || board[rows][cols - 2] >= 9))
                {
                    moves[i].push_back(make_pair(column[cols - 2], rows + 1));
                }
                //left-1
                if (cols >= 1 && (board[rows][cols - 1] <= 4 || board[rows][cols - 1] >= 9))
                {
                    moves[i].push_back(make_pair(column[cols - 1], rows + 1));
                }
                //right-2
                if (cols <= 4 && (board[rows][cols + 2] <= 4 || board[rows][cols + 2] >= 9))
                {
                    moves[i].push_back(make_pair(column[cols + 2], rows + 1));
                }
                //right-1
                if (cols <= 5 && (board[rows][cols + 1] <= 4 || board[rows][cols + 1] >= 9))
                {
                    moves[i].push_back(make_pair(column[cols + 1], rows + 1));
                }
                //up-2
                if (rows <= 4 && (board[rows + 2][cols] <= 4 || board[rows + 2][cols] >= 9))
                {
                    moves[i].push_back((make_pair(column[cols], rows + 3)));
                }
                //up-1
                if (rows <= 5 && (board[rows + 1][cols] <= 4 || board[rows + 1][cols] >= 9))
                {
                    moves[i].push_back((make_pair(column[cols], rows + 2)));
                }
                //down-2
                if (rows >= 2 && (board[rows - 2][cols] <= 4 || board[rows - 2][cols] >= 9))
                {
                    moves[i].push_back((make_pair(column[cols], rows - 1)));
                }
                //down-1
                if (rows >= 1 && (board[rows - 1][cols] <= 4 || board[rows - 1][cols] >= 9))
                {
                    moves[i].push_back((make_pair(column[cols], rows)));
                }
            }
            else
            {
                //left-2
                if (cols >= 2 && (board[rows][cols - 2] <= 0 || board[rows][cols - 2] >= 5))
                {
                    moves[i].push_back(make_pair(column[cols - 2], rows + 1));
                }
                //left-1
                if (cols >= 1 && (board[rows][cols - 1] <= 0 || board[rows][cols - 1] >= 5))
                {
                    moves[i].push_back(make_pair(column[cols - 1], rows + 1));
                }
                //right-2
                if (cols <= 4 && (board[rows][cols + 2] <= 0 || board[rows][cols + 2] >= 5))
                {
                    moves[i].push_back(make_pair(column[cols + 2], rows + 1));
                }
                //right-1
                if (cols <= 5 && (board[rows][cols + 1] <= 0 || board[rows][cols + 1] >= 5))
                {
                    moves[i].push_back(make_pair(column[cols + 1], rows + 1));
                }
                //up-2
                if (rows <= 4 && (board[rows + 2][cols] <= 0 || board[rows + 2][cols] >= 5))
                {
                    moves[i].push_back((make_pair(column[cols], rows + 3)));
                }
                //up-1
                if (rows <= 5 && (board[rows + 1][cols] <= 0 || board[rows + 1][cols] >= 5))
                {
                    moves[i].push_back((make_pair(column[cols], rows + 2)));
                }
                //down-2
                if (rows >= 2 && (board[rows - 2][cols] <= 0 || board[rows - 2][cols] >= 5))
                {
                    moves[i].push_back((make_pair(column[cols], rows - 1)));
                }
                //down-1
                if (rows >= 1 && (board[rows - 1][cols] <= 0 || board[rows - 1][cols] >= 5))
                {
                    moves[i].push_back((make_pair(column[cols], rows)));
                }
            }
        }

        for (int i = 0; i < moves.size(); i++)
        {

            for (int j = 0; j < moves[i].size(); j++)
            {
                string moveString = "";
                moveString += temp[i].first;
                moveString += to_string(temp[i].second);
                moveString += moves[i][j].first;
                moveString += to_string(moves[i][j].second);

                totalMoves.push_back(moveString);
            }
        }

        sort(totalMoves.begin(), totalMoves.end());
        return totalMoves;
    }
}

vector<string> pawnMoves(vector<vector<BoardState>> board, map<char, vector<pair<char, int>>> pieceList, char colourTurn)
{
    vector<char> column = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    vector<pair<char, int>> temp;
    vector<pair<char, int>> enemyTemp;
    vector<string> totalMoves;

    int out = 0;
    int numPieces = 0;

    // determine for which colour we are finding the moves for
    if (colourTurn == 'b')
    {
        temp = pieceList['p'];
        numPieces = temp.size();
    }
    else
    {
        temp = pieceList['P'];
        numPieces = temp.size();
    }

    vector<vector<pair<char, int>>> moves(numPieces);

    if (numPieces == 0)
    {
        return totalMoves;
    }
    else
    {
        for (int i = 0; i < numPieces; i++)
        {
            int row = 0;
            int col = 0;
            //find the index for the col
            for (int j = 0; j < column.size(); j++)
            {
                if (temp[i].first == column[j])
                {
                    col++; //remove ++ and take out -1 from below ?
                    break;
                }
                col++;
            }
            // need to decrement both down by 1 to match the arrays starting at 0 rather than 1.
            int cols = col - 1;
            int rows = temp[i].second - 1;

            if (colourTurn == 'b')
            {
                //down-1
                if (rows >= 1 && (board[rows - 1][cols] <= 4 || board[rows - 1][cols] >= 9))
                {
                    moves[i].push_back((make_pair(column[cols], rows)));
                }
                //down-left
                if (rows >= 1 && cols >= 1 && (board[rows - 1][cols - 1] <= 4 || board[rows - 1][cols - 1] >= 9))
                {
                    //cout << "down-left" << endl;
                    moves[i].push_back((make_pair(column[cols - 1], rows)));
                }
                //down-right
                if (rows >= 1 && cols <= 5 && ((board[rows - 1][cols + 1] <= 4 || board[rows - 1][cols + 1] >= 9)))
                {
                    //cout << "down-right" << endl;
                    moves[i].push_back((make_pair(column[cols + 1], rows)));
                }
                //past river up-1
                if (rows <= 2 && (board[rows + 1][cols] == 0 || board[rows + 1][cols] >= 9))
                {
                    moves[i].push_back((make_pair(column[cols], rows + 2)));
                }
                //past river up-2
                if (rows <= 2 && (board[rows + 2][cols] == 0 || board[rows + 2][cols] >= 9) && (board[rows + 1][cols] == 0 || board[rows + 1][cols] >= 9))
                {
                    moves[i].push_back((make_pair(column[cols], rows + 3)));
                }
            }
            else
            {
                //up-1
                if (rows <= 5 && (board[rows + 1][cols] <= 0 || board[rows + 1][cols] >= 5))
                {
                    moves[i].push_back((make_pair(column[cols], rows + 2)));
                }
                //up-left
                if (rows <= 5 && cols >= 1 && (board[rows + 1][cols - 1] <= 0 || board[rows + 1][cols - 1] >= 5))
                {
                    moves[i].push_back((make_pair(column[cols - 1], rows + 2)));
                }
                //up-right
                if (rows <= 5 && cols <= 5 && ((board[rows + 1][cols + 1] <= 0 || board[rows + 1][cols + 1] >= 5)))
                {
                    moves[i].push_back((make_pair(column[cols + 1], rows + 2)));
                }
                //past river down-1
                if (rows >= 4 && (board[rows - 1][cols] == 0 || board[rows - 1][cols] >= 9))
                {
                    moves[i].push_back((make_pair(column[cols], rows)));
                }
                //past river down-2
                if (rows >= 4 && (board[rows - 2][cols] == 0 || board[rows - 2][cols] >= 9) && (board[rows - 1][cols] == 0 || board[rows - 1][cols] >= 9))
                {
                    moves[i].push_back((make_pair(column[cols], rows - 1)));
                }
            }
        }
        for (int i = 0; i < moves.size(); i++)
        {

            for (int j = 0; j < moves[i].size(); j++)
            {
                string moveString = "";
                moveString += temp[i].first;
                moveString += to_string(temp[i].second);
                moveString += moves[i][j].first;
                moveString += to_string(moves[i][j].second);

                totalMoves.push_back(moveString);
            }
        }

        sort(totalMoves.begin(), totalMoves.end());
        return totalMoves;
    }
}

vector<string> allMoves(vector<vector<BoardState>> board, map<char, vector<pair<char, int>>> pieceList, char colourTurn)
{

    vector<string> lMoves = lionMoves(board, pieceList, colourTurn);
    vector<string> zMoves = zebraMoves(board, pieceList, colourTurn);
    vector<string> eMoves = elephantMoves(board, pieceList, colourTurn);
    vector<string> pMoves = pawnMoves(board, pieceList, colourTurn);
    vector<string> totalMoves;

    totalMoves.insert(totalMoves.end(), lMoves.begin(), lMoves.end());
    totalMoves.insert(totalMoves.end(), zMoves.begin(), zMoves.end());
    totalMoves.insert(totalMoves.end(), eMoves.begin(), eMoves.end());
    totalMoves.insert(totalMoves.end(), pMoves.begin(), pMoves.end());

    return totalMoves;
}

tuple<vector<vector<BoardState>>, map<char, vector<pair<char, int>>>, string> doMove(vector<vector<BoardState>> board, map<char, vector<pair<char, int>>> pieceList, string fen, char colourTurn, string move)
{
    vector<char> column = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    int fCol = 0;
    int tCol = 0;
    //vector<string> riverPieces = {"-1", "-1", "-1", "-1", "-1", "-1", "-1"};
    bool riverPieces = false;
    //find the index for the col
    for (int j = 0; j < column.size(); j++)
    {
        if (move[0] == column[j])
        {
            fCol++;
            break;
        }
        fCol++;
    }
    for (int j = 0; j < column.size(); j++)
    {
        if (move[2] == column[j])
        {
            tCol++;
            break;
        }
        tCol++;
    }
    
    for (int i = 0; i < board[3].size(); i++)
    {
        if (colourTurn == 'b')
        {
            if ((board[3][i] >= 5 && board[3][i] <= 8))
            {
                //riverPieces[i] = "B-here";
                riverPieces = true;
            }
        }
        else
        {
            if (board[3][i] >= 1 && board[3][i] <= 4)
            {
                //riverPieces[i] = "W-here";
                riverPieces = true;
            }
        }
    }

    int fromCols = fCol - 1;
    int fromRows = ((int)move[1] - 48) - 1;

    int toCols = tCol - 1;
    int toRows = ((int)move[3] - 48) - 1;

    board[toRows][toCols] = board[fromRows][fromCols];
    board[fromRows][fromCols] = empty;

    if (colourTurn == 'b')
    {
        if (fromRows == 3 && toRows == 3)
        {
            board[toRows][toCols] = river;
        }
        for (int i = 0; i < board[3].size(); i++)
        {
            if (i != toCols)
            {
                if (board[3][i] >= 5 && board[3][i] <= 8)
                {
                    board[3][i] = river;
                }
            }
            if (i == toCols && toRows != 3)
            {
                if (board[3][i] >= 5 && board[3][i] <= 8)
                {
                    board[3][i] = river;
                }
            }
        }
    }
    else
    {
        if (fromRows == 3 && toRows == 3)
        {
            board[toRows][toCols] = river;
        }
        for (int i = 0; i < board[3].size(); i++)
        {
            if (i != toCols)
            {
                if (board[3][i] >= 1 && board[3][i] <= 4)
                {
                    board[3][i] = river;
                }
            }
            if (i == toCols && toRows != 3)
            {
                if (board[3][i] >= 1 && board[3][i] <= 4)
                {
                    board[3][i] = river;
                }
            }
        }
    }

    board = boardSetup(board);
    string newFen = makeFen(board);
    pieceList.clear();
    pieceList = updatePieceList(pieceList, board);

    return make_tuple(board, pieceList, newFen);
}

bool gameState(vector<vector<BoardState>> board, map<char, vector<pair<char, int>>> pieceList)
{

    if (pieceList['l'].size() == 0)
    {
        return true;
    }
    else if (pieceList['L'].size() == 0)
    {
        return true;
    }

    return false;
}

int scoreCheck(map<char, vector<pair<char, int>>> pieceList, char colourTurn)
{
    int score = 0;

    int side = colourTurn == 'w' ? 1 : -1;
    if (pieceList['l'].size() == 0)
    {
        return 10000 * side;
    }
    //black wins
    else if (pieceList['L'].size() == 0)
    {
        return -10000 * side;
    }

    score += pieceList['p'].size() * -100;
    score += pieceList['e'].size() * -200;
    score += pieceList['z'].size() * -300;

    score += pieceList['P'].size() * 100;
    score += pieceList['E'].size() * 200;
    score += pieceList['Z'].size() * 300;

    if (colourTurn == 'w')
    {
        //cout << "score checks value is: " << score << endl;
        return score;
    }
    else
    {
        score = -1 * score;
        //cout << "score checks value is: " << score << endl;
        return score;
    }
}

string isGameOver(map<char, vector<pair<char, int>>> pieceList)
{

    if (pieceList['l'].size() == 0)
    {
        return "White wins";
    }
    else if (pieceList['L'].size() == 0)
    {
        return "Black wins";
    }
    else
    {
        return "Continue";
    }
}

int numMoves(vector<vector<BoardState>> board, map<char, vector<pair<char, int>>> pieceList, char colourTurn)
{
    vector<string> totalMoves = allMoves(board, pieceList, colourTurn);
    return totalMoves.size();
}

int attackScore(vector<vector<BoardState>> board, map<char, vector<pair<char, int>>> pieceList, char colourTurn)
{
    int attackScore = 0;
    vector<string> totalMoves = allMoves(board, pieceList, colourTurn);
    for (string move : totalMoves)
    {
        vector<char> column = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
        int fCol = 0;
        int tCol = 0;

        for (int j = 0; j < column.size(); j++)
        {
            if (move[2] == column[j])
            {
                tCol++;
                break;
            }
            tCol++;
        }

        int toCols = tCol - 1;
        int toRows = ((int)move[3] - 48) - 1;
        if (board[toRows][toCols] == 1 || board[toRows][toCols] == 5)
        {
            attackScore = attackScore + 10;
        }
        if ((board[toRows][toCols] >= 1 && board[toRows][toCols] <= 5) || (board[toRows][toCols] >= 6 && board[toRows][toCols] <= 8))
        {
            attackScore++;
        }
    }

    return attackScore;
}

int checkLionCapture(vector<vector<BoardState>> board, map<char, vector<pair<char, int>>> pieceList, char colourTurn)
{
    vector<string> totalMoves = allMoves(board, pieceList, colourTurn);
    for (string move : totalMoves)
    {
        vector<char> column = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
        int fCol = 0;
        int tCol = 0;

        for (int j = 0; j < column.size(); j++)
        {
            if (move[2] == column[j])
            {
                tCol++;
                break;
            }
            tCol++;
        }

        int toCols = tCol - 1;
        int toRows = ((int)move[3] - 48) - 1;
        if (board[toRows][toCols] == 1 || board[toRows][toCols] == 5)
        {
            return 10000;
        }
    }
}

int rawScore(vector<vector<BoardState>> board, map<char, vector<pair<char, int>>> pieceList, char colourTurn)
{
    int deltaScore = scoreCheck(pieceList, colourTurn);
    if (abs(deltaScore) == 10000)
    {
        return deltaScore;
    }
    if (pieceList['l'].size() == 1 && pieceList['L'].size() == 1 && pieceList['p'].size() == 0 && pieceList['e'].size() == 0 && pieceList['z'].size() == 0 && pieceList['P'].size() == 0 && pieceList['E'].size() == 0 && pieceList['Z'].size() == 0)
    {
        return 0;
    }
    char enemyColour = colourTurn == 'w' ? 'b' : 'w';
    // int side = colourTurn == 'w' ? 1 : -1;
    int myMoves = numMoves(board, pieceList, colourTurn);
    int enemyMoves = numMoves(board, pieceList, enemyColour);
    int myAttackScore = attackScore(board, pieceList, colourTurn);
    int enemyAttackScore = attackScore(board, pieceList, enemyColour);
    int deltaAttackScore = myAttackScore - enemyAttackScore;
    int deltaMove = myMoves - enemyMoves;
    return deltaAttackScore + deltaScore + deltaMove;
}
//fix winning conditions above...

string prevMoveMini(string move)
{
    string oldMove = move[2] + to_string(move[3] - 48) + move[0] + to_string(move[1] - 48);
    return oldMove;
}

string prevMoveAB(string move)
{
    string oldMove = move[2] + to_string(move[3] - 48) + move[0] + to_string(move[1] - 48);
    return oldMove;
}

int miniMax(vector<vector<BoardState>> board, map<char, vector<pair<char, int>>> pieceList, string fen, char colourTurn, int depth)
{
    string tempMove = "";
    if (gameState(board, pieceList) || depth <= 0)
    {
        return scoreCheck(pieceList, colourTurn);
    }

    char colour = colourTurn == 'w' ? 'b' : 'w';

    int value = -100000;
    vector<string> moves = allMoves(board, pieceList, colourTurn);
    for (string move : moves)
    {
        if (move == prevMoveMini(playMoveMini))
        {
            continue;
        }
        tuple<vector<vector<BoardState>>, map<char, vector<pair<char, int>>>, string> nextState = doMove(board, pieceList, fen, colourTurn, move);
        int eval = -miniMax(get<0>(nextState), get<1>(nextState), get<2>(nextState), colour, depth - 1);
        if (eval > value)
        {
            value = eval;
            tempMove = move;
        }
    }
    miniBestMove = tempMove;
    return value;
}

int alphaBeta(vector<vector<BoardState>> board, map<char, vector<pair<char, int>>> pieceList, string fen, char colourTurn, int depth, int alpha, int beta)
{
    string tempMove = "";
    if (gameState(board, pieceList) || depth <= 0)
    {
        return rawScore(board, pieceList, colourTurn);
    }
    char colour = colourTurn == 'w' ? 'b' : 'w';
    vector<string> moves = allMoves(board, pieceList, colourTurn);
    for (string move : moves)
    {
        if (move == prevMoveAB(playMoveAB))
        {
            continue;
        }

        tuple<vector<vector<BoardState>>, map<char, vector<pair<char, int>>>, string> nextState = doMove(board, pieceList, fen, colourTurn, move);
        int eval = -alphaBeta(get<0>(nextState), get<1>(nextState), get<2>(nextState), colour, depth - 1, -beta, -alpha);

        if (eval >= beta)
        {
            return beta;
        }
        if (eval > alpha)
        {
            tempMove = move;
            alpha = eval;
        }
    }
    ABbestMove = tempMove;
    return alpha;
}

void simpleMove(vector<vector<BoardState>> &board, string bestMove, char colourTurn)
{
    vector<char> column = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    int fCol = 0;
    int tCol = 0;

    bool riverPieces = false;
    //find the index for the col
    for (int j = 0; j < column.size(); j++)
    {
        if (bestMove[0] == column[j])
        {
            fCol++;
            break;
        }
        fCol++;
    }
    for (int j = 0; j < column.size(); j++)
    {
        if (bestMove[2] == column[j])
        {
            tCol++;
            break;
        }
        tCol++;
    }

    int fromCols = fCol - 1;
    int fromRows = ((int)bestMove[1] - 48) - 1;

    int toCols = tCol - 1;
    int toRows = ((int)bestMove[3] - 48) - 1;

    board[toRows][toCols] = board[fromRows][fromCols];
    board[fromRows][fromCols] = empty;

    if (colourTurn == 'b')
    {
        if (fromRows == 3 && toRows == 3)
        {
            board[toRows][toCols] = river;
        }
        for (int i = 0; i < board[3].size(); i++)
        {
            if (i != toCols)
            {
                if (board[3][i] >= 5 && board[3][i] <= 8)
                {
                    board[3][i] = river;
                }
            }
            if (i == toCols && toRows != 3)
            {
                if (board[3][i] >= 5 && board[3][i] <= 8)
                {
                    board[3][i] = river;
                }
            }
        }
    }
    else
    {
        if (fromRows == 3 && toRows == 3)
        {
            board[toRows][toCols] = river;
        }
        for (int i = 0; i < board[3].size(); i++)
        {
            if (i != toCols)
            {
                if (board[3][i] >= 1 && board[3][i] <= 4)
                {
                    board[3][i] = river;
                }
            }
            if (i == toCols && toRows != 3)
            {
                if (board[3][i] >= 1 && board[3][i] <= 4)
                {
                    board[3][i] = river;
                }
            }
        }
    }
}

void miniVsAlpha()
{
    int counter = 1;
    vector<vector<BoardState>> board(7, vector<BoardState>(7));
    string fen = "2ele1z/ppppppp/7/7/7/PPPPPPP/2ELE1Z";
    map<char, vector<pair<char, int>>> pieceList;
    tuple<map<char, vector<pair<char, int>>>, vector<vector<BoardState>>> setUp = mapInit(pieceList, fen, board);
    pieceList = get<0>(setUp);
    board = get<1>(setUp);
    while (!gameState(board, pieceList) && counter != 100)
    {
        cout << "Turn Number: " << counter << endl;
        board = boardSetup(board);
        alphaBeta(board, pieceList, fen, 'w', 4, -1000000, 1000000);
        cout << "ABBestMove: " << ABbestMove << endl;
        playMoveAB = ABbestMove;
        simpleMove(board, ABbestMove, 'w');
        printBoard(board);
        cout << endl;
        fen = makeFen(board);
        pieceList.clear();
        pieceList = updatePieceList(pieceList, board);
        
        if (pieceList['l'].size() == 0)
        {
            cout << "white Wins! " << endl;
            break;
        }
        
        miniMax(board, pieceList, fen, 'b', 2);
        cout << "miniBestMove: " << miniBestMove << endl;
        playMoveMini = miniBestMove;
        simpleMove(board, miniBestMove, 'b');
        printBoard(board);
        cout << endl;
        fen = makeFen(board);
        pieceList.clear();
        pieceList = updatePieceList(pieceList, board);
        if (pieceList['L'].size() == 0)
        {
            cout << "Black Wins! " << endl;
            break;
        }
        counter++;
    }
    cout << "Draw!" << endl;
}

void alphaVsMini()
{
    int counter = 1;
    vector<vector<BoardState>> board(7, vector<BoardState>(7));
    string fen = "2ele1z/ppppppp/7/7/7/PPPPPPP/2ELE1Z";
    map<char, vector<pair<char, int>>> pieceList;
    tuple<map<char, vector<pair<char, int>>>, vector<vector<BoardState>>> setUp = mapInit(pieceList, fen, board);
    pieceList = get<0>(setUp);
    board = get<1>(setUp);
    while (!gameState(board, pieceList) && counter != 100)
    {
        cout << "Turn Number: " << counter << endl;
        board = boardSetup(board);

        miniMax(board, pieceList, fen, 'w', 2);
        cout << "miniBestMove: " << miniBestMove << endl;
        playMoveMini = miniBestMove;
        simpleMove(board, miniBestMove, 'b');
        printBoard(board);
        cout << endl;
        fen = makeFen(board);
        pieceList.clear();
        pieceList = updatePieceList(pieceList, board);
        if (pieceList['l'].size() == 0)
        {
            cout << "White Wins! " << endl;
            break;
        }

        alphaBeta(board, pieceList, fen, 'b', 4, -1000000, 1000000);
        cout << "ABBestMove: " << ABbestMove << endl;
        playMoveAB = ABbestMove;
        simpleMove(board, ABbestMove, 'w');
        printBoard(board);
        cout << endl;
        
        fen = makeFen(board);
        pieceList.clear();
        pieceList = updatePieceList(pieceList, board);
        if (pieceList['L'].size() == 0)
        {
            cout << "Black Wins! " << endl;
            break;
        }
        counter++;
    }
    cout << "Draw!" << endl;
}

int main()
{
    //black is lowercase
    //white is uppercase
    vector<vector<BoardState>> board(7, vector<BoardState>(7));
    map<char, vector<pair<char, int>>> pieceList;
    miniVsAlpha();
    
}
