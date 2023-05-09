#include <bits/stdc++.h>
#include "utils.h"
using namespace std;
// Assume 0 AT
// 0 Context Switching
// Three Levels Are :
// First -> Priority Based Scheduling
// Second -> Round Robin
// Third -> FCFS
class MultiLvlQ
{
public:
	static vector<Process> PBS(vector<Process> process, int st, int tq,
							   vector<Process> &solution)
	{
		sort(process.begin(), process.end(), [](Process &a, Process &b)
			 { return a.Priority > b.Priority; });
		int t = st, i = 0;
		while (t < st + tq)
		{
			if (i >= process.size())
				break;
			Process &curr = process[i];
			cout << "|P" << curr.PID << "|";
			if (t + curr.RT <= st + tq)
			{
				curr.CT = t + curr.RT;
				t += curr.RT;
				curr.RT = 0;
				solution.push_back(curr);
				cout << "->" << t << "->";
			}
			else
			{
				curr.RT = (t + curr.RT) - (st + tq);
				t = st + tq;
				cout << "->" << t << "->";
				break;
			}
			i++;
		}
		return vector<Process>(process.begin() + i, process.end());
	}
	static vector<Process> RoundRobin(vector<Process> process, int st, int tq, int tqrr, vector<Process> &solution)
	{
		queue<Process> q;
		for (int i = 0; i < process.size(); i++)
		{
			q.push(process[i]);
		}
		int t = st;
		while (t <= st + tq)
		{
			if (q.empty())
				break;
			Process curr = q.front();
			cout << "|P" << curr.PID << "|";
			q.pop();
			if (curr.RT <= tqrr)
			{
				if (t + curr.RT <= st + tq)
				{
					curr.CT = t + curr.RT;
					t += curr.RT;
					curr.RT = 0;
					solution.push_back(curr);
					cout << "->" << t << "->";
				}
				else
				{
					curr.RT = (t + curr.RT) - (tq + st);
					t = st + tq;
					q.push(curr);
					cout << "->" << t << "->";
					break;
				}
			}
			else
			{
				if (t + tqrr <= st + tq)
				{
					curr.RT = curr.RT - tqrr;
					t += tqrr;
					q.push(curr);
					cout << "->" << t << "->";
				}
				else
				{
					curr.RT = (t + curr.RT) - (tq + st);
					t = st + tq;
					q.push(curr);
					cout << "->" << t << "->";
					break;
				}
			}
		}
		vector<Process> left;
		while (!q.empty())
		{
			Process curr = q.front();
			q.pop();
			left.push_back(curr);
		}
		return left;
	}
	static vector<Process> FCFS(vector<Process> process, int st, int tq,
								vector<Process> &sln)
	{
		sort(process.begin(), process.end(), [](Process &a, Process &b)
			 { return a.PID < b.PID; });
		int t = st, i = 0;
		while (t < st + tq)
		{
			if (i >= process.size())
				break;
			Process &curr = process[i];
			cout << "|P" << curr.PID << "|";
			if (t + curr.RT <= st + tq)
			{
				curr.CT = t + curr.RT;
				t += curr.RT;
				curr.RT = 0;
				sln.push_back(curr);
				cout << "->" << t << "->";
			}
			else
			{
				curr.RT = curr.RT + t - (st + tq);
				t = st + tq;
				cout << "->" << t << "->";
				break;
			}
			i++;
		}
		return vector<Process>(process.begin() + i, process.end());
	}
};
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	int n;
	cout << "Enter the Number of Processes : " << endl;
	cin >> n;
	vector<Process> processes(n);
	cout << "assuming AT to be 0, Please Enter ProcessID, Burst Time and Priority " << endl;
	cout
		<< "pid\tbt\tpriority" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> processes[i].PID >> processes[i].BT >>
			processes[i].Priority;
		processes[i].RT = processes[i].BT;
		// cout << processes[i].pid << ' ' << processes[i].at << ' '<<
		// processes[i].bt << ' ' << processes[i].ct << ' ' << processes[i].wt << ' ' << processes[i].tat << endl;
	}
	cout << endl
		 << endl;
	int tqp, tqr, tqf;
	cout << "Please Enter the Time Quanta for Priority Scheduling, Round Robin and FCFS respectively " << endl;
	cin >>
		tqp >> tqr >> tqf;
	int tqrr, t = 0;
	cout << "Please Enter the Time Quanta for Round Robin Scheduling itself " << endl;
	cin >>
		tqrr;
	vector<Process> solutionVector;
	MultiLvlQ q;
	cout << "Gantt Chart : " << endl;
	cout << 0 << "->";
	while (processes.size() != 0)
	{
		processes = q.PBS(processes, t, tqp, solutionVector);
		t += tqp;
		if (processes.empty())
		{
			break;
		}
		processes = q.RoundRobin(processes, t, tqr, tqrr, solutionVector);
		t += tqr;
		if (processes.empty())
		{
			break;
		}
		processes = q.FCFS(processes, t, tqf, solutionVector);
		t += tqf;
	}
	cout << "end" << endl;
	;
	cout << "pid\tat\tbt\tct\twt\ttat" << endl;
	for (int i = 0; i < solutionVector.size(); i++)
	{
		solutionVector[i].TAT = solutionVector[i].CT - solutionVector[i].AT;
		solutionVector[i].WT = solutionVector[i].TAT - solutionVector[i].BT;
		cout << solutionVector[i].PID << '\t' << solutionVector[i].AT << '\t' << solutionVector[i].BT << '\t' << solutionVector[i].CT << '\t' << solutionVector[i].WT << '\t' << solutionVector[i].TAT << endl;
	}
	avg_tat(solutionVector);
	avg_wt(solutionVector);
	return 0;
}