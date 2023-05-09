#include <bits/stdc++.h>
using namespace std;
class Process
{
public:
	int PID, Priority, AT, BT, WT, TAT, CT, RT;
};

bool SortByAT(Process &a, Process &b)
{
	return a.AT <= b.AT;
}

bool SortByPID(Process &a, Process &b)
{
	return a.PID <= b.PID;
}
bool SortByBT(Process &a, Process &b)
{
	return a.BT <= b.BT;
}

void avg_wt(vector<Process> &v)
{
	double avg_wt = 0;
	for (int i = 0; i < v.size(); i++)
	{
		avg_wt += (double)v[i].WT / v.size();
	}
	cout << "Average WT(Wait Time): " << avg_wt << endl;
}

void avg_tat(vector<Process> &v)
{
	double avg_tat = 0;
	for (int i = 0; i < v.size(); i++)
	{
		avg_tat += (double)v[i].TAT / v.size();
	}
	cout << "Average WT(Wait Time): " << avg_tat << endl;
}
void printTabular(vector<Process> &v)
{
	cout << endl
		 << endl;
	cout << "PID\tAT\tBT\tWT\tTAT\tCT\t" << endl;
	for (int i = 0; i < v.size(); i++)
	{
		v[i].TAT = v[i].CT - v[i].AT;
		v[i].WT = v[i].TAT - v[i].BT;
		cout << v[i].PID << "\t" << v[i].AT << "\t" << v[i].BT << "\t" << v[i].WT << "\t" << v[i].TAT << "\t" << v[i].CT << endl;
	}
	avg_tat(v);
	avg_wt(v);
}
