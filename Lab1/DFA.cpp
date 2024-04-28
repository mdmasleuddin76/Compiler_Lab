#include <bits/stdc++.h>
using namespace std;
bool checkdfa(int j, vector<int> final, vector<vector<int>> table, string input)
{
	for (int i = 0; i < input.size(); i++)
	{
		int x = input[i] - '0';
		if (x > table[j].size())
		{
			return false;
		}
		j = table[j][x];
		if (j < 0)
		{
			return false;
		}
	}
	for (int i = 0; i < final.size(); i++)
	{
		if (j == final[i])
		{
			return true;
		}
	}
	return false;
}
int main()
{
	// *******************************File Read****************************
	ifstream file;
	file.open("DFA.txt", ios::out);

	// ****************************Variable Declaration*************************
	vector<vector<int>> table;
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
		string temp;
		vector<int> temp2;
		getline(file, temp);
		for (int i = 0; i < temp.size(); i++)
		{
			if (0 < i && temp[i - 1] == '-')
			{
				temp2.push_back(-1 * (temp[i] - '0'));
			}
			else if ('0' <= temp[i] && temp[i] <= '9')
			{
				temp2.push_back(temp[i] - '0');
			}
		}
		table.push_back(temp2);
	}
	file.close();
	cout<<"Name: Md Masleuddin\nRoll:21BCS028"<<endl<<endl;
	cout<<"Initial State: "<<initial<<endl;
	cout<<"Final State: ";
	for(int i=0;i<final.size();i++)
	{
		cout<<final[i]<<" ";
	}
	cout<<endl;
	cout<<"Transition Table: "<<endl;
	for(int i=0;i<table.size();i++)
	{
		for(int j=0;j<table[i].size();j++)
		{
			cout<<table[i][j]<<" ";
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
		if (checkdfa(initial, final, table, input))
		{
			cout << "Accepted" << endl;
		}
		else
		{
			cout << "Not Accepted" << endl;
		}
	}
	return 0;
}