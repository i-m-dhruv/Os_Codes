#include <bits/stdc++.h>
#include "utils.h"
#define pipii pair<int, pair<int, int>>

void check(vector<Process> &p, priority_queue<pipii, vector<pipii>, greater<pipii>> &pq, int &i, int &time)
{
	while (i < p.size())
	{
		if (p[i].AT <= time)
		{
			pq.push({p[i].BT, {p[i].AT, p[i].PID}});
			i++;
		}
		else
			break;
	}
}

void helper(vector<Process> &p, priority_queue<pipii, vector<pipii>, greater<pipii>> &pq, unordered_map<int, int> &m, int &i, int &time)
{
	if (i < p.size() && pq.empty())
	{
		p[i].CT = p[i].AT + p[i].BT;
		time = p[i].CT;
		i++;
	}
	else if (!pq.empty())
	{
		auto it = pq.top();
		pq.pop();
		int index = m[it.second.second];
		p[index].CT = time + p[index].BT;
		time = p[index].CT;
	}
	else
		return;
	check(p, pq, i, time);
	helper(p, pq, m, i, time);
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
	}
	unordered_map<int, int> m;
	sort(process.begin(), process.end(), SortByAT);
	for (int i = 0; i < n; i++)
		m[process[i].PID] = i;
	process[0].CT = process[0].AT + process[0].BT;
	priority_queue<pipii, vector<pipii>, greater<pipii>> pq;
	int i = 1;
	int time = process[0].CT;
	check(process, pq, i, time);
	helper(process, pq, m, i, time);
	sort(process.begin(), process.end(), SortByPID);
	printTabular(process);
	return 0;
}

// #include "utils.h"
// #define pipii pair<int, pair<int, int>>

// void check(vector<Process> &process, priority_queue<pipii, vector<pipii>, greater<pipii>> &pq, int &i, int &time)
// {
// 	while (i < process.size())
// 	{
// 		if (process[i].AT <= time)
// 		{
// 			pq.push({process[i].BT, {process[i].AT, process[i].PID}});
// 			i++;
// 		}
// 		else
// 			break;
// 	}
// }
// void helper(vector<Process> &process, priority_queue<pipii, vector<pipii>, greater<pipii>> &pq, unordered_map<int, int> &m, int &i, int &time)
// {
// 	if (i < process.size() && pq.empty())
// 	{
// 		time = process[i].CT = process[i].AT + process[i].BT;
// 		i++;
// 	}
// 	else if (!pq.empty())
// 	{
// 		auto it = pq.top();
// 		pq.pop();
// 		int index = m[it.second.second];
// 		time = process[index].CT = time + process[index].BT;
// 	}
// 	else
// 		return;
// 	check(process, pq, i, time);
// 	helper(process, pq, m, i, time);
// }

// int main()
// {
// 	int n;
// 	cout << "Enter th no. of processes: ";
// 	cin >> n;
// 	vector<Process> process(n);
// 	cout << "Enter PID, AT, BT of the processes sequentially: " << endl;
// 	for (int i = 0; i < n; i++)
// 	{
// 		cin >> process[i].PID >> process[i].AT >> process[i].BT;
// 	}
// 	sort(process.begin(), process.end(), SortByAT);
// 	unordered_map<int, int> m;
// 	for (int i = 0; i < n; i++)
// 		m[process[i].PID] = i;
// 	priority_queue<pipii, vector<pipii>, greater<pipii>> pq;
// 	int i = 0;
// 	int time = 0;
// 	time = process[0].CT = process[0].AT + process[0].BT;
// 	i++;
// 	check(process, pq, i, time);
// 	helper(process, pq, m, i, time);
// 	sort(process.begin(), process.end(), SortByPID);
// 	printTabular(process);
// }