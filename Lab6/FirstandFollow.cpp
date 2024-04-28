#include <bits/stdc++.h>
using namespace std;

// *************************Follow Function************************
void follow(char s, vector<vector<char>> table, map<char, set<char>> first, map<char, set<char>> &mp)
{
    int j = 1;
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 1; j < table[i].size(); j++)
        {

            if (table[i][j] == s)
            {
                for (int k = j + 1; k <= table[i].size(); k++)
                {
                    bool flag = false;
                    if (k < table[i].size())
                    {
                        if (table[i][k] <= 'Z' && table[i][k] >= 'A')
                        {
                            for (auto it = first[table[i][k]].begin(); it != first[table[i][k]].end(); it++)
                            {
                                if (*it != 'e')
                                {
                                    mp[s].insert(*it);
                                }
                                else
                                    flag = true;
                            }
                        }
                        else
                        {
                            mp[s].insert(table[i][k]);
                            break;
                        }
                    }
                    else
                    {
                        if (table[i][0] == s)
                            break;
                        follow(table[i][0], table, first, mp);
                        for (auto it = mp[table[i][0]].begin(); it != mp[table[i][0]].end(); it++)
                        {
                            mp[s].insert(*it);
                        }
                    }
                    if (!flag)
                        break;
                }
            }
        }
    }
}

// *************************First Function************************
void first(char s, vector<vector<char>> table, map<char, set<char>> &mp)
{
    int j = 1;
    for (int i = 0; i < table.size(); i++)
    {
        if (table[i][0] == s)
        {
            for (int k = 1; k < table[i].size(); k++)
            {
                if (table[i][k] == s)
                {
                    break;
                }
                bool flag = false;
                first(table[i][k], table, mp);
                for (auto it = mp[table[i][k]].begin(); it != mp[table[i][k]].end(); it++)
                {
                    if (*it != 'e')
                    {
                        mp[s].insert(*it);
                    }
                    else if (k == table[i].size() - 1)
                    {
                        mp[s].insert('e');
                    }
                    else
                    {
                        flag = true;
                        continue;
                    }
                }
                if (!flag)
                {
                    break;
                }
            }
        }
    }
    if (!(s <= 'Z' && s >= 'A'))
    {
        mp[s].insert(s);
    }
}
int main()
{
    // *******************************File Read****************************
    ifstream file;
    file.open("FirstansFollow.txt", ios::out);
    vector<vector<char>> table;

    // ***********************************Extract Data***************************

    while (!file.eof())
    {
        string temp = "";
        vector<char> temp2;
        getline(file, temp);
        for (int i = 0; i < temp.size(); i++)
        {
            if (temp[i] != ' ')
                temp2.push_back(temp[i]);
        }
        table.push_back(temp2);
    }
    file.close();
    // *******************************First and Follow***************************
    map<char, set<char>> firstmp;
    map<char, set<char>> followmp;
    followmp['S'].insert('$');
    for (int i = 0; i < table.size(); i++)
    {
        first(table[i][0], table, firstmp);
    }
    for (int i = 0; i < table.size(); i++)
    {
        follow(table[i][0], table, firstmp, followmp);
    }
    // *************************Printing************************
    cout<<"Name: Md Masleuddin\nRoll:21BCS028\n"<<endl;
    cout << "Given CFG: " << endl;
    for (int i = 0; i < table.size(); i++)
    {
        cout << table[i][0] << " -> ";
        for (int j = 1; j < table[i].size(); j++)
        {
            cout << table[i][j];
        }
        cout << endl;
    }
    cout << endl;
    cout<<"e->epsilon"<<endl<<endl;
    // **********Print First***********
    for (auto it = firstmp.begin(); it != firstmp.end(); it++)
    {
        if (it->first == 'S')
        {
            cout << "First ( " << it->first << " ) = ";
            for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
            {
                cout << *it2 << " ";
            }
            cout << endl;
        }
    }
    for (auto it = firstmp.begin(); it != firstmp.end(); it++)
    {
        if (!(it->first <= 'Z' && it->first >= 'A') || it->first == 'S')
            continue;
        cout << "First ( " << it->first << " ) = ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            cout << *it2 << " ";
        }
        cout << endl;
    }
    cout << endl;
    // **********Print Follow***********
    for (auto it = followmp.begin(); it != followmp.end(); it++)
    {
        if (it->first == 'S')
        {
            cout << "Follow ( " << it->first << " ) = ";
            for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
            {
                cout << *it2 << " ";
            }
            cout << endl;
        }
    }
    for (auto it = followmp.begin(); it != followmp.end(); it++)
    {
        if (!(it->first <= 'Z' && it->first >= 'A') || it->first == 'S')
            continue;
        cout << "Follow ( " << it->first << " ) = ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++)
        {
            cout << *it2 << " ";
        }
        cout << endl;
    }
    return 0;
}
