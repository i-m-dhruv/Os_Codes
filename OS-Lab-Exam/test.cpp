#include <bits/stdc++.h>
using namespace std;

struct Process
{
	int pid; // process id
	int at;	 // arrival time
	int bt;	 // burst time
};

bool compare(Process a, Process b)
{
	if (a.at != b.at)
		return a.at < b.at;
	else
		return a.bt < b.bt;
}

void findWaitingTime(Process proc[], int n, int wt[])
{
	int rt[n];
	for (int i = 0; i < n; i++)
		rt[i] = proc[i].bt;

	int complete = 0, t = 0, minm = INT_MAX;
	int shortest = 0, finish_time;
	bool check = false;

	while (complete != n)
	{
		for (int j = 0; j < n; j++)
		{
			if ((proc[j].at <= t) && (rt[j] < minm) && rt[j] > 0)
			{
				shortest = j;
				minm = rt[j];
				check = true;
			}
		}

		if (check == false)
		{
			t++;
			continue;
		}

		rt[shortest]--;
		minm = rt[shortest];

		if (minm == 0)
			minm = INT_MAX;

		if (rt[shortest] == 0)
		{
			complete++;
			check = false;
			finish_time = t + 1;
			wt[shortest] = finish_time - proc[shortest].bt - proc[shortest].at;
			if (wt[shortest] < 0)
				wt[shortest] = 0;
		}
		t++;
	}
}

void findTurnAroundTime(Process proc[], int n, int wt[], int tat[])
{
	for (int i = 0; i < n; i++)
		tat[i] = proc[i].bt + wt[i];
}

void findavgTime(Process proc[], int n)
{
	int wt[n], tat[n], total_wt = 0, total_tat = 0;

	findWaitingTime(proc, n, wt);
	findTurnAroundTime(proc, n, wt, tat);

	cout << "Processes  "
		 << "Arrival Time   "
		 << " Burst time  "
		 << " Waiting time  "
		 << " Completion Time "
		 << " Turn around time\n";

	for (int i = 0; i < n; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		cout << "   " << proc[i].pid << "\t\t"
			 << proc[i].at << "\t\t"
			 << proc[i].bt << "\t    " << wt[i]
			 << "\t\t  " << proc[i].at + tat[i] << "\t\t  " << tat[i] << endl;
	}

	cout << "Average waiting time = " << (float)total_wt / (float)n;
	cout << "\nAverage turn around time = " << (float)total_tat / (float)n;
}

int main()
{
	Process proc[] = {{1, 0, 2}, {1, 2, 4}, {5, 3, 8}, {6, 4, 12}};
	int n = sizeof(proc) / sizeof(proc[0]);

	sort(proc, proc + n, compare);

	findavgTime(proc, n);
	return 0;
}
