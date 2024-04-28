#include <bits/stdc++.h>
using namespace std;
void gen_kill(vector<vector<string>> table)
{
    vector<string> temp;
    for (int i = 0; i < table.size(); i++)
    {
        vector<string> gen, kill;
        for (int j = 0; j < table[i].size(); j++)
        {
            for (int k = 0; k < table[i][j].size(); k++)
            {
                if (table[i][j][k] == '=' && (table[i][j][0] != 'i' && table[i][j][1] != 'f'))
                {
                    string t = "";
                    k = 0;
                    while (table[i][j][k] != '=')
                    {
                        t += table[i][j][k];
                        k++;
                    }
                    for (int l = 0; l < temp.size(); l++)
                    {
                        if (temp[l] == t)
                        {
                            kill.push_back(t);
                            break;
                        }
                    }
                    gen.push_back(t);
                    temp.push_back(t);
                    break;
                }
            }
        }
        cout << "Gen of Block " << i + 1 << " is: ";
        for (int j = 0; j < gen.size(); j++)
        {
            cout << gen[j] << " , ";
        }
        cout << endl;
        cout << "Kill of Block " << i + 1 << " is: ";
        for (int j = 0; j < kill.size(); j++)
        {
            cout << kill[j] << " , ";
        }
        cout << endl
             << endl
             << endl;
    }
}
int main()
{
    ifstream file;
    file.open("Gen_Kill.txt", ios::out);
    vector<vector<string>> table;
    set<int> leader;
    leader.insert(1);
    vector<string> temp;
    while (!file.eof())
    {
        string t = "";
        getline(file, t);
        if (t.size() == 0)
        {
            table.push_back(temp);
            temp.clear();
        }
        else
        {
            temp.push_back(t);
        }
    }
    table.push_back(temp);
    file.close();
    cout<<"Name: Md Masleuddin\nRoll:21BCS028\n"<<endl;
    gen_kill(table);
    return 0;
}