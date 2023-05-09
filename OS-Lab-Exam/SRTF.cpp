#include <bits/stdc++.h>
#include "utils.h"
using namespace std;
#define pipii pair<int, pair<int, int>>

void check(vector<Process> &process, priority_queue<pipii, vector<pipii>, greater<pipii>> &pq, int &index, int &time)
{
	while (index < process.size())
	{
		if (time >= process[index].AT)
		{
			pq.push({process[index].RT, {process[index].AT, process[index].PID}});
			index++;
		}
		else
			break;
	}
}

void helper(vector<Process> &process, priority_queue<pipii, vector<pipii>, greater<pipii>> &pq, unordered_map<int, int> &m, int &index, int &time)
{
	if (index < process.size() && pq.empty())
	{
		time = process[index].AT;
		pq.push({process[index].RT, {process[index].AT, process[index].PID}});
		index++;
	}
	else if (!pq.empty())
	{
		auto it = pq.top();
		int id = it.second.second;
		pq.pop();
		if (process[m[id]].RT == 1)
		{
			process[m[id]].CT = time + process[m[id]].RT;
			time = process[m[id]].CT;
		}
		else
		{
			process[m[id]].RT -= 1;
			time += 1;
			it.first -= 1;
			pq.push(it);
		}
	}
	else
		return;
	check(process, pq, index, time);
	helper(process, pq, m, index, time);
}

int main()
{
	int n;
	cout << "Enter total number of processes: ";
	cin >> n;
	vector<Process> process(n);
	cout << "Enter PID, AT, BT of the processes sequentially: " << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> process[i].PID >> process[i].AT >> process[i].BT;
		process[i].RT = process[i].BT;
	}
	sort(process.begin(), process.end(), SortByAT);
	unordered_map<int, int> m;
	for (int i = 0; i < n; i++)
		m[process[i].PID] = i;
	int index = 0;
	int time = 0;
	priority_queue<pipii, vector<pipii>, greater<pipii>> pq;
	helper(process, pq, m, index, time);
	sort(process.begin(), process.end(), SortByPID);
	printTabular(process);
	return 0;
}

// #include "utils.h"
// #define pipii pair<int, pair<int, int>>

// void check(vector<Process> &process, priority_queue<pipii, vector<pipii>, greater<pipii>> &pq, int &index, int &time)
// {
// 	while (index < process.size())
// 	{
// 		if (process[index].AT <= time)
// 		{
// 			pq.push({process[index].RT, {process[index].AT, process[index].PID}});
// 			index++;
// 		}
// 		else
// 			break;
// 	}
// }

// void helper(vector<Process> &process, priority_queue<pipii, vector<pipii>, greater<pipii>> &pq, unordered_map<int, int> &m, int &index, int &time)
// {
// 	if (index < process.size() && pq.empty())
// 	{
// 		time = process[index].AT;
// 		pq.push({process[index].RT, {process[index].AT, process[index].PID}});
// 		index++;
// 	}
// 	else if (!pq.empty())
// 	{
// 		auto it = pq.top();
// 		pq.pop();
// 		int id = m[it.second.second];
// 		if (process[m[id]].RT == 1)
// 		{
// 			time = process[m[id]].CT = time + process[m[id]].RT;
// 		}
// 		else
// 		{
// 			process[m[id]].RT--;
// 			time++;
// 			it.first--;
// 			pq.push(it);
// 		}
// 	}
// }

// int main()
// {
// 	int n;
// 	cout << "Enter the no. of processes: ";
// 	cin >> n;
// 	vector<Process> process(n);
// 	unordered_map<int, int> m;
// 	priority_queue<pipii, vector<pipii>, greater<pipii>> pq;
// 	cout << "Enter PID, AT, BT of the process sequentially: ";
// 	for (int i = 0; i < n; i++)
// 	{
// 		cin >> process[i].PID >> process[i].AT >> process[i].BT;
// 		process[i].RT = process[i].BT;
// 	}
// 	sort(process.begin(), process.end(), SortByAT);
// 	for (int i = 0; i < n; i++)
// 		m[process[i].PID] = i;
// 	int time = 0;
// 	int i = 0;
// 	helper(process, pq, m, i, time);
// 	sort(process.begin(), process.end(), SortByPID);
// 	printTabular(process);
// }
