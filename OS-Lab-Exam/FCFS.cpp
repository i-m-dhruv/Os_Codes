#include "utils.h"

int main()
{
	int n, t;
	cout << "Enter the no. of Processes: ";
	cin >> n;
	vector<Process> P(n);
	cout << "Enter PID, AT, BT of the processes sequentially: " << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> P[i].PID >> P[i].AT >> P[i].BT;
	}
	sort(P.begin(), P.end(), SortByAT);
	t = P[0].AT;
	for (int i = 0; i < n - 1; i++)
	{
		if (P[i].AT < P[i].BT + t)
		{
			P[i].CT = P[i].BT + t;
		}
		else
		{
			P[i].CT = P[i + 1].AT;
		}
		t = P[i].CT;
	}
	P[n - 1].CT = t + P[n - 1].BT;
	sort(P.begin(), P.end(), SortByPID);
	printTabular(P);
}