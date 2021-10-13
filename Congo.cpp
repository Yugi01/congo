#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

void pieceListOutput(map<char, vector<string>> pieceList)
{
    for (auto ii = pieceList.begin(); ii != pieceList.end(); ++ii)
    {
        cout << (*ii).first << ": ";
        vector<string> inVect = (*ii).second;
        for (unsigned j = 0; j < inVect.size(); j++)
        {
            cout << inVect[j] << " ";
        }
        cout << endl;
    }
}

void printPawns(map<char, vector<string>> pieceList)
{
    cout << "white pawn: ";
    for (int i = 0; i < pieceList['P'].size(); i++)
    {
        cout << pieceList['P'][i] << " ";
    }
    cout << endl;
    cout << "black pawn: ";
    for (int i = 0; i < pieceList['p'].size(); i++)
    {
        cout << pieceList['p'][i] << " ";
    }
    cout << endl;
}

void printSuperpawns(map<char, vector<string>> pieceList)
{
    cout << "white Superpawn: ";
    for (int i = 0; i < pieceList['S'].size(); i++)
    {
        cout << pieceList['S'][i] << " ";
    }
    cout << endl;
    cout << "black Superpawn: ";
    for (int i = 0; i < pieceList['s'].size(); i++)
    {
        cout << pieceList['s'][i] << " ";
    }
    cout << endl;
}

void printGiraffe(map<char, vector<string>> pieceList)
{
    cout << "white giraffe: ";
    for (int i = 0; i < pieceList['G'].size(); i++)
    {
        cout << pieceList['G'][i] << " ";
    }
    cout << endl;
    cout << "black giraffe: ";
    for (int i = 0; i < pieceList['g'].size(); i++)
    {
        cout << pieceList['g'][i] << " ";
    }
    cout << endl;
}

void printMonkey(map<char, vector<string>> pieceList)
{
    cout << "white Monkey: ";
    for (int i = 0; i < pieceList['M'].size(); i++)
    {
        cout << pieceList['M'][i] << " ";
    }
    cout << endl;
    cout << "black Monkey: ";
    for (int i = 0; i < pieceList['m'].size(); i++)
    {
        cout << pieceList['m'][i] << " ";
    }
    cout << endl;
}

void printElephant(map<char, vector<string>> pieceList)
{
    cout << "white Elephant: ";
    for (int i = 0; i < pieceList['E'].size(); i++)
    {
        cout << pieceList['E'][i] << " ";
    }
    cout << endl;
    cout << "black Elephant: ";
    for (int i = 0; i < pieceList['e'].size(); i++)
    {
        cout << pieceList['e'][i] << " ";
    }
    cout << endl;
}

void printLion(map<char, vector<string>> pieceList)
{
    cout << "white Lion: ";
    for (int i = 0; i < pieceList['L'].size(); i++)
    {
        cout << pieceList['L'][i] << " ";
    }
    cout << endl;
    cout << "black Lion: ";
    for (int i = 0; i < pieceList['l'].size(); i++)
    {
        cout << pieceList['l'][i] << " ";
    }
    cout << endl;
}

void printCrocodile(map<char, vector<string>> pieceList)
{
    cout << "white Crocodile: ";
    for (int i = 0; i < pieceList['C'].size(); i++)
    {
        cout << pieceList['C'][i] << " ";
    }
    cout << endl;
    cout << "black Crocodile: ";
    for (int i = 0; i < pieceList['c'].size(); i++)
    {
        cout << pieceList['c'][i] << " ";
    }
    cout << endl;
}

void printZebra(map<char, vector<string>> pieceList)
{
    cout << "white Zebra: ";
    for (int i = 0; i < pieceList['Z'].size(); i++)
    {
        cout << pieceList['Z'][i] << " ";
    }
    cout << endl;
    cout << "black Zebra: ";
    for (int i = 0; i < pieceList['z'].size(); i++)
    {
        cout << pieceList['z'][i] << " ";
    }
    cout << endl;
}

void mapInit(map<char, vector<string>> &pieceList, string fen)
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
            pieceList['p'].push_back(col[colPos] + to_string(row));
        }
        else if (fen[i] == 's')
        {
            pieceList['s'].push_back(col[colPos] + to_string(row));
        }
        else if (fen[i] == 'g')
        {
            pieceList['g'].push_back(col[colPos] + to_string(row));
        }
        else if (fen[i] == 'm')
        {
            pieceList['m'].push_back(col[colPos] + to_string(row));
        }
        else if (fen[i] == 'e')
        {
            pieceList['e'].push_back(col[colPos] + to_string(row));
        }
        else if (fen[i] == 'l')
        {
            pieceList['l'].push_back(col[colPos] + to_string(row));
        }
        else if (fen[i] == 'c')
        {
            pieceList['c'].push_back(col[colPos] + to_string(row));
        }
        else if (fen[i] == 'z')
        {
            pieceList['z'].push_back(col[colPos] + to_string(row));
        }
        //white pieces
        else if (fen[i] == 'P')
        {
            pieceList['P'].push_back(col[colPos] + to_string(row));
        }
        else if (fen[i] == 'S')
        {
            pieceList['S'].push_back(col[colPos] + to_string(row));
        }
        else if (fen[i] == 'G')
        {
            pieceList['G'].push_back(col[colPos] + to_string(row));
        }
        else if (fen[i] == 'M')
        {
            pieceList['M'].push_back(col[colPos] + to_string(row));
        }
        else if (fen[i] == 'E')
        {
            pieceList['E'].push_back(col[colPos] + to_string(row));
        }
        else if (fen[i] == 'L')
        {
            pieceList['L'].push_back(col[colPos] + to_string(row));
        }
        else if (fen[i] == 'C')
        {
            pieceList['C'].push_back(col[colPos] + to_string(row));
        }
        else if (fen[i] == 'Z')
        {
            pieceList['Z'].push_back(col[colPos] + to_string(row));
        }

        if (num == false)
        {
            colPos++;
        }
        num = false;
    }
}

int main()
{
    //black is lowercase
    //white is uppercase

    map<char, vector<string>> pieceList;
    string fen;
    cin >> fen;
    char colourTurn;
    cin >> colourTurn;
    int numTurn;
    cin >> numTurn;

    mapInit(pieceList, fen);
    //pieceListOutput(pieceList);

    printPawns(pieceList);
    printSuperpawns(pieceList);
    printGiraffe(pieceList);
    printMonkey(pieceList);
    printElephant(pieceList);
    printLion(pieceList);
    printCrocodile(pieceList);
    printZebra(pieceList);

    // cout << fen.length() << endl;
    if (colourTurn == 'b')
    {
        cout << "side to play: black" << endl;
    }
    else
    {
        cout << "side to play: white" << endl;
    }
    // cout << numTurn << endl;
}
