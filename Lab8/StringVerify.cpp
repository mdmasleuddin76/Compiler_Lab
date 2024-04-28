#include <bits/stdc++.h>
using namespace std;
int findrow(char s, vector<vector<string>> &table)
{
    for (int i = 0; i < table.size(); i++)
    {
        if (table[i][0] == string(1, s))
        {
            return i;
        }
    }
    return -1;
}
int findcol(char s, vector<vector<string>> &table)
{
    for (int i = 0; i < table[0].size(); i++)
    {
        if (table[0][i] == string(1, s))
        {
            return i;
        }
    }
    return -1;
}
void printstack(stack<char> st, string s, string prod, int i)
{
    string temp = "";
    while (!st.empty())
    {
        temp.push_back(st.top());
        st.pop();
    }
    reverse(temp.begin(), temp.end());
    cout << setw(10) << left << temp << setw(10) << left << s.substr(i, s.size()) << setw(50) << left << prod << endl;
}
void verify(vector<vector<string>> table, string s)
{
    stack<char> st;
    st.push('$');
    st.push('S');
    int i = 0;
    cout << endl
         << setw(10) << left << "Stack" << setw(10) << left << "Input" << setw(50) << left << "Action" << endl;
    printstack(st, s, "Initial Stack", i);
    while (st.size() > 1)
    {
        if (st.top() == s[i])
        {
            st.pop();
            i++;
            printstack(st, s, "Terminal Poped and incremented i", i);
        }
        else
        {
            int row = findrow(st.top(), table);
            int col = findcol(s[i], table);
            if (row == -1 || col == -1)
            {
                cout << "Invalid String" << endl;
                return;
            }
            string temp = table[row][col];
            if (temp == "-")
            {
                cout << "Invalid String" << endl;
                return;
            }
            string message = "";
            message.push_back(st.top());
            message += " Poped and Pushed " + temp;
            st.pop();
            for (int j = temp.size() - 1; j > 2; j--)
            {
                if (temp[j] != 'e')
                    st.push(temp[j]);
            }
            printstack(st, s, message, i);
        }
    }
    if (i == s.size() - 1)
    {
        cout << "Valid String" << endl;
    }
    else
    {
        cout << "Invalid String" << endl;
    }
}
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

void parserll1(vector<char> row, map<char, set<char>> first, map<char, set<char>> follow, vector<vector<string>> &parsertable)
{
    string production = string(1, row[0]) + "->";
    for (int i = 1; i < row.size(); i++)
    {
        production += row[i];
    }
    for (int i = 1; i < row.size(); i++)
    {
        int rowindex = findrow(row[0], parsertable);
        if (row[i] == 'e')
        {
            for (auto it = follow[row[0]].begin(); it != follow[row[0]].end(); it++)
            {
                if (parsertable[rowindex][findcol(*it, parsertable)] != "-")
                {
                    cout << "Not LL(1) Grammar" << endl;
                    exit(0);
                }
                parsertable[rowindex][findcol(*it, parsertable)] = production;
            }
        }
        else if (row[i] <= 'Z' && row[i] >= 'A')
        {
            bool flag = false;
            for (auto it = first[row[i]].begin(); it != first[row[i]].end(); it++)
            {
                if (*it != 'e')
                {
                    if (parsertable[rowindex][findcol(*it, parsertable)] != "-")
                    {
                        cout << "Not LL(1) Grammar" << endl;

                        exit(0);
                    }
                    parsertable[rowindex][findcol(*it, parsertable)] = production;
                }
                else
                    flag = true;
            }
            if (flag && i == row.size() - 1)
            {
                for (auto it = follow[row[0]].begin(); it != follow[row[0]].end(); it++)
                {
                    if (parsertable[rowindex][findcol(*it, parsertable)] != "-")
                    {
                        cout << "Not LL(1) Grammar" << endl;
                        exit(0);
                    }
                    parsertable[rowindex][findcol(*it, parsertable)] = production;
                }
            }
        }
        else
        {
            if (parsertable[rowindex][findcol(row[i], parsertable)] != "-")
            {
                cout << "Not LL(1) Grammar" << endl;
                exit(0);
            }
            parsertable[rowindex][findcol(row[i], parsertable)] = production;
            break;
        }
    }
}
void printTable(vector<vector<string>> &table)
{
    for (const auto &row : table)
    {
        for (int i = 0; i < row.size(); ++i)
        {
            cout << setw(10) << left << row[i] << "";
            if (i == 0)
            {
                cout << setw(10) << left << "|";
            }
            else
                cout << "  ";
        }
        if (row[0] == "")
        {
            cout << endl
                 << "---------------------------------------------------------------------------------------------";
        }
        cout << endl;
    }
}
int main()
{
    // *******************************File Read****************************
    ifstream file;
    file.open("StringVerify.txt", ios::out);
    vector<vector<char>> table;
    set<char> Terminal;
    set<char> NonTerminal;

    // ***********************************Extract Data***************************

    while (!file.eof())
    {
        string temp = "";
        vector<char> temp2;
        getline(file, temp);
        for (int i = 0; i < temp.size(); i++)
        {
            if (temp[i] != ' ')
            {
                temp2.push_back(temp[i]);
                if (temp[i] <= 'Z' && temp[i] >= 'A')
                {
                    NonTerminal.insert(temp[i]);
                }
                else
                {
                    if (temp[i] != 'e')
                        Terminal.insert(temp[i]);
                }
            }
        }
        table.push_back(temp2);
    }
    file.close();
    cout << "Name: Md Masleuddin\nRoll:21BCS028\n"
         << endl;
    // *******************************First and Follow***************************
    map<char, set<char>> firstmp;
    map<char, set<char>> followmp;
    vector<vector<string>> parsertable;
    vector<string> temp;
    temp.push_back("");
    for (auto it = Terminal.begin(); it != Terminal.end(); it++)
    {
        string s = "";
        s.push_back(*it);
        temp.push_back(s);
    }
    temp.push_back("$");
    parsertable.push_back(temp);
    followmp['S'].insert('$');
    for (int i = 0; i < table.size(); i++)
    {
        first(table[i][0], table, firstmp);
    }
    for (int i = 0; i < table.size(); i++)
    {
        follow(table[i][0], table, firstmp, followmp);
    }
    for (int i = 0; i < NonTerminal.size(); i++)
    {
        vector<string> temp;
        string s = "";
        auto it = next(NonTerminal.begin(), i);
        s.push_back(*(it));
        temp.push_back(s);
        for (int j = 0; j <= Terminal.size(); j++)
        {
            temp.push_back("-");
        }
        parsertable.push_back(temp);
    }
    for (int i = 0; i < table.size(); i++)
    {
        parserll1(table[i], firstmp, followmp, parsertable);
    }
    // *************************Printing************************

    cout << "Given Table: " << endl;
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
    cout << "e->epsilon" << endl
         << endl;
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
    //*************************Printing************************
    cout << endl;
    cout << "LL(1) Parsing Table: " << endl;
    printTable(parsertable);
    string s;
    cout << "Enter the string to verify: ";
    cin >> s;
    s.push_back('$');
    verify(parsertable, s);
    return 0;
}