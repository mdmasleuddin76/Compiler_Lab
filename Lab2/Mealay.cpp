#include <bits/stdc++.h>
using namespace std;
string mooreymachine(int j, vector<vector<int>> table, string input, vector<vector<int>> output)
{
    string ans = "";
    for (int i = 0; i < input.size(); i++)
    {
        int x = input[i] - '0';
        if (x > table[j].size() - 1)
        {
            ans += "\nError Wrong Input";
            return ans;
        }
        if (table[j][x] != -1)
            ans += output[j][x] + '0';
        j = table[j][x];
        if (j < 0)
        {
            ans += "\nError Wrong Input";
            return ans;
        }
    }
    return ans;
}
int main()
{
    // *******************************File Read****************************
    ifstream file;
    file.open("Mealay.txt", ios::out);

    // ****************************Variable Declaration*************************
    vector<vector<int>> table;
    vector<vector<int>> output;
    int initial;
    string initialtemp = "";
    // ***********************************Extract Data***************************
    getline(file, initialtemp);
    initial = initialtemp[0] - '0';
    while (!file.eof())
    {
        string temp;
        vector<int> temptransition;
        vector<int> tempoutput;
        getline(file, temp);
        for (int i = 0; i < temp.size(); i++)
        {
            bool flag = false;
            if (0 < i && temp[i - 1] == '-')
            {
                temptransition.push_back(-1 * (temp[i] - '0'));
                flag = true;
            }
            else if ('0' <= temp[i] && temp[i] <= '9')
            {
                temptransition.push_back(temp[i] - '0');
                flag = true;
            }
            if (flag)
                i += 2;
            if (0 < i && temp[i - 1] == '-')
            {
                tempoutput.push_back(-1 * (temp[i] - '0'));
            }
            else if ('0' <= temp[i] && temp[i] <= '9')
            {
                tempoutput.push_back(temp[i] - '0');
            }
        }
        table.push_back(temptransition);
        output.push_back(tempoutput);
    }
    file.close();
	cout<<"Name: Md Masleuddin\nRoll: 21BCS028\n"<<endl;
    cout<<"Mealey Machine\n";
    cout<<"Initial State: "<<initial<<endl;
    cout<<"Table: "<<endl;
    for(int i=0;i<table.size();i++)
    {
        for(int j=0;j<table[i].size();j++)
        {
            cout<<table[i][j]<<"/"<<output[i][j]<<" ";
        }
        cout<<endl;
    }
    //*************************Taking input and Checking*******************
    while (1)
    {
        string inputtemp;
        cout << "Enter the string: ";
        cin >> inputtemp;
        string input = "";
        // ************************Convert abc to 123***************************
        for (int i = 0; i < inputtemp.size(); i++)
        {
            input += (inputtemp[i] - 'a' + '0');
        }
        // ******************************Checking********************************
        string ans = mooreymachine(initial, table, input, output);
        cout << "Output : " << ans << endl;
    }
    return 0;
}