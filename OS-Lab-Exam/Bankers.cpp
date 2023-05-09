#include <bits/stdc++.h>
using namespace std;

void isSafe(int &n, int &m, vector<vector<int>> &allocated_matrix, vector<vector<int>> &need_matrix, vector<int> available_matrix, vector<int> &total, vector<int> &sequence)
{
	vector<bool> completed(n, false);
	while (sequence.size() != n)
	{
		bool found = false;
		for (int i = 0; i < n; i++)
		{
			bool flag = true;
			for (int j = 0; j < m; j++)
			{
				if (available_matrix[j] < need_matrix[i][j])
				{
					flag = false;
					break;
				}
			}
			if (flag && !completed[i])
			{
				sequence.push_back(i);
				completed[i] = true;
				for (int j = 0; j < m; j++)
					available_matrix[j] += need_matrix[i][j];
				found = true;
				break;
			}
		}
		if (!found)
		{
			cout << "System is not in a safe state" << endl;
			return;
		}
	}
}

void safetyallocation(int &n, int &m, vector<vector<int>> &allocated_matrix, vector<vector<int>> &need_matrix, vector<int> &available_matrix, vector<int> &total)
{
	int process;
	vector<int> request(m);
	cout << "Type the process for which additional resources are required : ";
	cin >> process;
	cout << "Enter additional resources required for each type " << endl;
	for (int i = 0; i < m; i++)
		cin >> request[i];
	vector<bool> completed(n, false);
	vector<int> sequence;
	for (int i = 0; i < m; i++)
	{
		if (request[i] > need_matrix[process][i])
		{
			cout << "Safe State cannot be achieved for " << process << " with request resources";
			return;
		}
		if (request[i] > available_matrix[i])
		{
			cout << "Safe State cannot be achieved for " << process << " with request resources";
			return;
		}
	}
	vector<int> available(m);
	for (int i = 0; i < m; i++)
	{
		available_matrix[i] -= request[i];
		allocated_matrix[process][i] += request[i];
		need_matrix[process][i] -= request[i];
	}
	available = available_matrix;
	while (sequence.size() != n)
	{
		bool found = false;
		for (int i = 0; i < n; i++)
		{
			bool flag = true;
			for (int j = 0; j < m; j++)
			{
				if (available_matrix[j] < need_matrix[i][j])
				{
					flag = false;
					break;
				}
			}
			if (flag && !completed[i])
			{
				sequence.push_back(i);
				completed[i] = true;
				for (int j = 0; j < m; j++)
					available_matrix[j] += allocated_matrix[i][j];
				found = true;
				break;
			}
		}
		if (!found)
		{
			cout << "System is not in a safe state" << endl;
			for (int i = 0; i < m; i++)
			{
				available_matrix = available;
				available_matrix[i] += request[i];
				allocated_matrix[process][i] -= request[i];
				need_matrix[process][i] += request[i];
			}
			return;
		}
	}
	cout << "Safe sequence can be generated if " << process << " is allocated its resources" << endl;
	for (int it : sequence)
		cout << it << " ";
	available_matrix = available;
	cout << endl;
}

int main()
{
	int n, m;
	cout << "Enter number of processes ";
	cin >> n;
	cout << "Enter number of resources ";
	cin >> m;
	vector<vector<int>> max_matrix(n, vector<int>(m, 0));
	vector<vector<int>> allocated_matrix(n, vector<int>(m, 0));
	vector<int> total(m, 0);
	vector<int> sequence;
	cout << "Enter the max matrix" << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> max_matrix[i][j];
	cout << endl;
	cout << "Enter the allocation matrix" << endl;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> allocated_matrix[i][j];
	cout << endl;
	cout << "Enter the total matrix" << endl;
	for (int i = 0; i < m; i++)
		cin >> total[i];
	cout << endl;
	vector<vector<int>> need_matrix(n, vector<int>(m, 0));
	vector<int> available_matrix(m, 0), temp(m);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			need_matrix[i][j] = max_matrix[i][j] - allocated_matrix[i][j];
	temp = total;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			temp[i] -= allocated_matrix[j][i];
		available_matrix[i] = temp[i];
	}
	isSafe(n, m, allocated_matrix, need_matrix, available_matrix, total, sequence);
	cout << "Safe sequence is: ";
	if (sequence.size() == n)
	{
		for (int i = 0; i < sequence.size(); i++)
			cout << sequence[i] << " ";
		cout << endl;
	}
	safetyallocation(n, m, allocated_matrix, need_matrix, available_matrix, total);
	safetyallocation(n, m, allocated_matrix, need_matrix, available_matrix, total);
	return 0;
}