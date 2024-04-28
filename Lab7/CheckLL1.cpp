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

bool parserll1(vector<char> row, map<char, set<char>> first, map<char, set<char>> follow, vector<vector<string>> &parsertable)
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
                    return true;
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
                        return true;
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
                        return true;
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
                return true;
                exit(0);
            }
            parsertable[rowindex][findcol(row[i], parsertable)] = production;
            break;
        }
    }
    return false;
}
// *************************Print Function************************

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
string returnleft(string s)
{
    string ans = "";
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '-')
        {
            ans = s.substr(0, i);
            break;
        }
    }
    return ans;
}
char returnright(string s)
{
    string ans = "";
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '>')
        {
            return s[i + 1];
        }
    }
    return 'e';
}
int returnindex(string s)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '>')
        {
            return i + 1;
        }
    }
    return -1;
}
void left_recursion(vector<string> &prod)
{
    vector<string> x, y, ans;
    int i = 0;
    for (int i = 0; i < prod.size();)
    {
        x.clear();
        y.clear();
        char st = prod[i][0];
        while (i < prod.size() && prod[i][0] == st)
        {
            if (prod[i][0] == prod[i][3])
            {
                x.push_back(prod[i].substr(4, prod[i].size() - 4));
            }
            else
            {
                y.push_back(prod[i].substr(3, prod[i].size() - 3));
            }
            i++;
        }
        string t(1, st);
        for (int j = 0; j < y.size(); j++)
        {
            ans.push_back(t + "->" + y[j]);
        }
        for (int j = 0; j < x.size(); j++)
        {
            ans.push_back(t + "'->" + x[j] + t + "'");
        }
        if (x.size())
            ans.push_back(t + "'->" + "e");
    }
    prod = ans;
}
void left_factoring(vector<string> &prod)
{
    vector<string> x, y, ans;
    int i = 0;
    for (int i = 0; i < prod.size();)
    {
        x.clear();
        y.clear();
        string st1 = "";
        char st2 = returnright(prod[i]);
        int store = i;
        st1 = returnleft(prod[i]);
        i++;
        while (i < prod.size() && returnleft(prod[i]) == st1)
        {
            int from = returnindex(prod[i]);
            if (st2 == returnright(prod[i]))
            {
                x.push_back(prod[i].substr(from, prod[i].size() - from));
            }
            else
            {
                y.push_back(prod[i].substr(from, prod[i].size() - from));
            }
            i++;
        }
        int count = 0;
        if (x.size())
        {
            int from = returnindex(prod[store]);
            x.push_back(prod[store].substr(from, prod[store].size() - from));
            for (int j = 0; j < x[0].size(); j++)
            {
                bool flag = true;
                for (int k = 1; k < x.size(); k++)
                {
                    if (x[0][j] != x[k][j])
                    {
                        flag = false;
                        break;
                    }
                }
                if (flag)
                {
                    count++;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            int from = returnindex(prod[store]);
            y.push_back(prod[store].substr(from, prod[store].size() - from));
        }

        // string t(1, st1);
        string t = st1;
        if (x.size())
            ans.push_back(t + "->" + x[0].substr(0, count) + t + "'");
        for (int j = 0; j < y.size(); j++)
        {
            ans.push_back(t + "->" + y[j]);
        }
        for (int j = 0; j < x.size(); j++)
        {
            if (count != x[j].size())
                ans.push_back(t + "'->" + x[j].substr(count, x[j].size() - count));
            else
                ans.push_back(t + "'->" + "e");
        }
    }
    prod = ans;
}
int main()
{
    // *******************************File Read****************************
    ifstream file;
    file.open("CheckLL1.txt", ios::out);
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
    cout<<"Name: Md Masleuddin\nRoll:21BCS028\n"<<endl;
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
    bool flag = true;
    for (int i = 0; i < table.size(); i++)
    {
        if (
            parserll1(table[i], firstmp, followmp, parsertable))
        {
            flag = false;
            break;
        };
    }
    // *************************Printing************************
    cout << "Given Grammar: " << endl;
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
    if (flag)
    {
        cout << "This is a LL(1) Grammar" << endl;
        cout << "Parsing Table: " << endl;
        printTable(parsertable);
    }
    else
    {
        vector<string> prod;
        for (int i = 0; i < table.size(); i++)
        {
            string production = string(1, table[i][0]) + "->";
            for (int j = 1; j < table[i].size(); j++)
            {
                production += table[i][j];
            }
            prod.push_back(production);
        }
        cout << "After Applying Left Recursion: "<< endl;
        left_recursion(prod);
        for (int i = 0; i < prod.size(); i++)
        {
            cout << prod[i] << endl;
        }
        cout << endl;
        cout << "After Applying Left Factoring: " << endl;
        left_factoring(prod);
        for (int i = 0; i < prod.size(); i++)
        {
            cout << prod[i] << endl;
        }
    }
    return 0;
}