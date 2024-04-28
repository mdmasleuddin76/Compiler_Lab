#include <bits/stdc++.h>
using namespace std;

// *******************************check unreachable state***********************
bool isdeadstate(vector<vector<string>> table, string state)
{
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 1; j < table[0].size(); j++)
        {
            if (table[i][j] == state)
            {
                return false;
            }
        }
    }
    return true;
}
// *******************************Remove Unreachable State***************************
void remove(vector<vector<string>> &table)
{
    for (int i = 1; i < table.size(); i++)
    {
        if (isdeadstate(table, table[i][0]))
        {
            table.erase(table.begin() + i);
            i--;
        }
    }
}
// *******************************Find String for new state***************************
string findstring(int j, string input, vector<vector<string>> table)
{
    string ans = "";
    for (int i = 0; i < table.size(); i++)
    {
        if (table[i][0] == input)
        {
            return table[i][j];
        }
    }
    return "-1";
}
// ***************Replace Multiple state with single state************************
void replacetab(vector<vector<string>> &table, string t, string replace)
{
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 0; j < table[0].size(); j++)
        {
            if (table[i][j] == t)
            {
                table[i][j] = replace;
            }
        }
    }
}
// *******************************Check State in Table***************************
bool check(vector<vector<string>> table, string t)
{
    for (int i = 0; i < table.size(); i++)
    {
        if (t == table[i][0])
            return true;
    }
    return false;
}
bool stringnotcome(string st, string ch)
{
    for (int i = 0; i < st.size(); i++)
    {
        // if (st[i] == ch[0])
        //     return false;
        string temp = "";
        while (i < st.size() && st[i] != ',')
        {
            temp.push_back(st[i]);
        }
        if (temp == ch)
            return false;
    }
    return true;
}
void nfatodfa(int initial, vector<int> &final, vector<vector<string>> &table)
{
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 1; j < table[0].size(); j++)
        {
            if (table[i][j].size() && table[i][j] != "-1" && !check(table, table[i][j]))
            {
                vector<string> temp;
                temp.push_back(table[i][j]);
                for (int p = 1; p < table[0].size(); p++)
                {
                    string temp2;
                    set<char> mp;
                    for (int k = 0; k < table[i][j].size(); k++)
                    {
                        string find;
                        while (k < table[i][j].size() && ('0' <= table[i][j][k] && table[i][j][k] <= '9'))
                        {
                            find.push_back(table[i][j][k]);
                            k++;
                        }
                        string returnstring = findstring(p, find, table);
                        if (returnstring.size() && returnstring != "-1")
                        {
                            for (int l = 0; l < returnstring.size(); l++)
                            {
                                if (returnstring[l] != ',')
                                    mp.insert(returnstring[l]);
                                
                            }
                        }
                    }
                    for (auto it = mp.begin(); it != mp.end(); it++)
                    {
                        temp2.push_back(',');
                        temp2.push_back(*it);
                    }
                    if (temp2.size())
                    {
                        temp2.erase(temp2.begin(), temp2.begin() + 1);
                        temp.push_back(temp2);
                    }
                    else
                    {
                        temp.push_back("-1");
                    }
                }
                table.push_back(temp);
            }
        }
    }
}
int main()
{
    // *******************************File Read****************************
    ifstream file;
    file.open("NFA-to-DFA.txt", ios::out);

    // ****************************Variable Declaration*************************
    vector<vector<string>> table;
    vector<int> final;
    int initial;
    string initialtemp = "";
    string finaltemp = "";
    // ***********************************Extract Data***************************

    getline(file, initialtemp);
    initial = initialtemp[0] - '0';
    getline(file, finaltemp);
    for (int i = 0; i < finaltemp.size(); i++)
    {
        if ('0' <= finaltemp[i] && finaltemp[i] <= '9')
        {
            final.push_back(finaltemp[i] - '0');
        }
    }
    while (!file.eof())
    {
        string temp = "";
        vector<string> temp2;
        char t = table.size() + '0';
        temp = t;
        temp2.push_back(temp);
        getline(file, temp);
        for (int i = 0; i < temp.size(); i++)
        {
            string state = "";
            while (i < temp.size() && (('0' <= temp[i] && temp[i] <= '9') || (temp[i] == ',')))
            {
                if (0 < i && temp[i - 1] == '-')
                {
                    state.push_back('-');
                }
                state.push_back(temp[i]);
                i++;
            }
            if (state.size())
                temp2.push_back(state);
        }
        table.push_back(temp2);
    }
    table.pop_back();
    file.close();
    cout<<"Name:Md Masleuddin\nRoll:21BCS028\n"<<endl;
    cout<<"NFA Table: "<<endl;
    cout << "Initial State: q" << initial << endl;
    cout << "Final State: ";
    for (int i = 0; i < final.size(); i++)
    {
        cout << "q" << final[i] << " , ";
    }
    cout << endl;
    cout<<"NFA Table: "<<endl;
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 0; j < table[i].size(); j++)
        {
            for(int k=0;k<table[i][j].size();k++){
                if(table[i][j][k]==','){
                    cout<<",";
                }
                else{
                    cout<<"q"<<table[i][j][k]<<" ";
                }
            }
            cout<<"       ";
        }
        cout << endl;
    }
    nfatodfa(initial, final, table);
    //**************add new final sate and replace with new state*******************
    for (int i = 0; i < table.size(); i++)
    {
        if (table[i][0].size() > 1)
        {
            for (int k = 0; k < table[i][0].size(); k++)
            {
                bool flag = false;
                string find;
                while (k < table[i][0].size() && ('0' <= table[i][0][k] && table[i][0][k] <= '9'))
                {
                    find.push_back(table[i][0][k]);
                    k++;
                }
                for (int j = 0; j < final.size(); j++)
                {
                    if (find[0] - '0' == final[j])
                    {
                        final.push_back(i);
                        flag = true;
                        break;
                    }
                }
                if (flag)
                    break;
            }
            string replace = to_string(i);

            replacetab(table, table[i][0], replace);
            table[i][0] = replace;
        }
    }
    //*************************Remove Unreachable State************************
    // remove(table);
    //*************************Printing************************
    cout<<endl<<endl<<"DFA Table: "<<endl;
    cout << "Initial State: q" << initial << endl;
    cout << "Final State: ";
    for (int i = 0; i < final.size(); i++)
    {
        cout << "q" << final[i] << " , ";
    }
    cout << endl;
    cout << "Table: " << endl;
    for(int i=0;i<table[0].size();i++){
        char ch='a'+i-1;
        if(i==0)
        cout<<setw(5)<<left<<" ";
        else
        cout<<setw(5)<<left<<ch;
    }
    cout<<endl;
    cout<<"------------------------------------------"<<endl;
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 0; j < table[i].size(); j++)
        {
            if (table[i][j] != "-1")
            {
                string temp="q"+table[i][j];
                cout<<setw(5)<<left  << temp;
            }
            else
            {
                cout<<setw(5)<<left  << "-1 ";
            }
        }
        cout << endl;
    }
    return 0;
}
