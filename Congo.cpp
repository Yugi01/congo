#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <map>
#include <utility>

using namespace std;

// void pieceListOutput(map<char, vector<pair<char, int>>> pieceList)
// {
//     for (auto ii = pieceList.begin(); ii != pieceList.end(); ++ii)
//     {
//         cout << (*ii).first << ": ";
//         vector<string> inVect = (*ii).second;
//         for (unsigned j = 0; j < inVect.size(); j++)
//         {
//             cout << inVect[j] << " ";
//         }
//         cout << endl;
//     }
// }

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

void mapInit(map<char, vector<pair<char, int>>> &pieceList, string fen)
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
        }
        else if (fen[i] == 'l')
        {
            pieceList['l'].push_back(make_pair(col[colPos], row));
        }
        else if (fen[i] == 'c')
        {
            pieceList['c'].push_back(make_pair(col[colPos], row));
        }
        else if (fen[i] == 'z')
        {
            pieceList['z'].push_back(make_pair(col[colPos], row));
        }
        //white pieces
        else if (fen[i] == 'P')
        {
            pieceList['P'].push_back(make_pair(col[colPos], row));
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
        }
        else if (fen[i] == 'L')
        {
            pieceList['L'].push_back(make_pair(col[colPos], row));
        }
        else if (fen[i] == 'C')
        {
            pieceList['C'].push_back(make_pair(col[colPos], row));
        }
        else if (fen[i] == 'Z')
        {
            pieceList['Z'].push_back(make_pair(col[colPos], row));
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

    map<char, vector<pair<char, int>>> pieceList;
    int n;
    cin >> n;
    vector<string> fen(n);
    vector<char> colourTurn(n);
    vector<int> numTurn(n);

    for (int i = 0; i < n; i++)
    {
        cin >> fen[i];
        cin >> colourTurn[i];
        cin >> numTurn[i];
    }

    for (int i = 0; i < n; i++)
    {
        mapInit(pieceList, fen[i]);
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
        if (colourTurn[i] == 'b')
        {
            cout << "side to play: black" << endl;
        }
        else
        {
            cout << "side to play: white" << endl;
        }
        // cout << numTurn << endl;
        cout << endl;
        pieceList.clear();
    }
}
