#include <bits/stdc++.h>
#include "utils.h"
using namespace std;

void check(vector<Process> &process, queue<int> &q, int &index, int &time)
{
	while (index < process.size())
	{
		if (time >= process[index].AT)
		{
			q.push(process[index].PID);
			index++;
		}
		else
			break;
	}
}

void helper(vector<Process> &process, queue<int> &q, unordered_map<int, int> &m, int &tq, int &index, int &time)
{
	if (index < process.size() && q.empty())
	{
		time = process[index].AT;
		q.push(process[index].PID);
		index++;
		check(process, q, index, time);
	}
	else if (!q.empty())
	{
		while (!q.empty())
		{
			int id = q.front();
			q.pop();
			if (process[m[id]].RT <= tq)
			{
				process[m[id]].CT = time + process[m[id]].RT;
				time = process[m[id]].CT;
				check(process, q, index, time);
			}
			else
			{
				process[m[id]].RT -= tq;
				time += tq;
				check(process, q, index, time);
				q.push(id);
			}
		}
	}
	else
		return;
	helper(process, q, m, tq, index, time);
}

int main()
{
	int n, tq;
	cout << "Enter total number of processes: ";
	cin >> n;
	vector<Process> process(n);
	queue<int> q;
	cout << "Enter PID, AT, BT of the processes sequentially: " << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> process[i].PID >> process[i].AT >> process[i].BT;
		process[i].RT = process[i].BT;
	}
	cout << "Enter time quanta for the scheduling: ";
	cin >> tq;
	sort(process.begin(), process.end(), SortByAT);
	unordered_map<int, int> m;
	for (int i = 0; i < n; i++)
		m[process[i].PID] = i;
	int index = 0;
	int time = 0;
	helper(process, q, m, tq, index, time);
	sort(process.begin(), process.end(), SortByPID);
	printTabular(process);
	return 0;
}

// #include "utils.h"

// void check(vector<Process> &process, queue<int> &q, int &i, int &t)
// {
// 	while (i < process.size())
// 	{
// 		if (process[i].AT <= t)
// 		{
// 			q.push(process[i].PID);
// 			i++;
// 		}
// 		else
// 			break;
// 	}
// }

// void helper(vector<Process> &process, queue<int> &q, int &tq, unordered_map<int, int> &m, int &i, int &t)
// {
// 	if (i < process.size() && q.empty())
// 	{
// 		t = process[i].AT;
// 		q.push(process[i].PID);
// 		i++;
// 		check(process, q, i, t);
// 	}
// 	else if (!q.empty())
// 	{
// 		while (!q.empty())
// 		{
// 			int id = q.front();
// 			q.pop();
// 			if (process[m[id]].RT <= tq)
// 			{
// 				t = process[m[id]].CT = t + process[m[id]].BT;
// 				check(process, q, i, t);
// 			}
// 			else
// 			{
// 				process[m[id]].RT--;
// 				t++;
// 				check(process, q, i, t);
// 				q.push(id);
// 			}
// 		}
// 	}
// }

// int main()
// {
// 	int n, tq, t = 0, i = 0;
// 	cout << "Enter the no. of processes: ";
// 	cin >> n;
// 	vector<Process> process(n);
// 	queue<int> q;
// 	unordered_map<int, int> m;
// 	cout << "Enter PID, AT, BT of the processes sequentially: " << endl;
// 	for (int i = 0; i < n; i++)
// 	{
// 		cin >> process[i].PID >> process[i].AT >> process[i].BT;
// 		process[i].RT = process[i].BT;
// 	}
// 	cout << "Enter time quanta: ";
// 	cin >> tq;
// 	sort(process.begin(), process.end(), SortByAT);
// 	for (int i = 0; i < n; i++)
// 		m[process[i].PID] = i;
// 	helper(process, q, tq, m, i, t);
// 	sort(process.begin(), process.end(), SortByPID);
// 	printTabular(process);
// }