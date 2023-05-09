#include <iostream>
using namespace std;

int main()
{
	int i, j, x, y, z, r, p;

	cout << "Enter the no of Processes: ";
	cin >> p;
	cout << "Enter the no of resource instances: ";
	cin >> r;
	int maximum[p][r];
	int allotment[p][r];
	// int requirement [100][100];
	int available[r];

	//  List P0, P1, P2 and P3

	cout << "Enter the Max Matrix\n";
	for (i = 0; i < p; i++)
	{
		for (j = 0; j < r; j++)
		{
			cin >> maximum[i][j];
		}
	}
	cout << "Enter the Allocation Matrix\n";
	for (i = 0; i < p; i++)
	{
		for (j = 0; j < r; j++)
		{
			cin >> allotment[i][j];
		}
	}
	cout << "Enter the available Resources\n";
	for (j = 0; j < r; j++)
	{
		cin >> available[j];
	}

	int f[p], res[p], ind = 0;
	for (z = 0; z < p; z++)
	{
		f[z] = 0;
	}

	int requirement[p][r];
	for (x = 0; x < p; x++)
	{
		for (y = 0; y < r; y++)
			requirement[x][y] = maximum[x][y] - allotment[x][y];
	}

	int a = 0;
	for (z = 0; z < 4; z++)
	{
		for (x = 0; x < p; x++)
		{
			if (f[x] == 0)
			{
				int flag = 0;
				for (y = 0; y < r; y++)
				{
					if (requirement[x][y] > available[y])
					{
						flag = 1;
						break;
					}
				}
				if (flag == 0)
				{
					res[ind++] = x;
					for (a = 0; a < r; a++)
						available[a] += allotment[x][a];
					f[x] = 1;
				}
			}
		}
	}

	int flag = 1;
	/*
	 Sequence is not safe or not
	 based on the number of asked requirement
	*/
	for (int x = 0; x < p; x++)
	{
		if (f[x] == 0)
		{
			flag = 0;
			cout << "the given sequence is not safe" << endl;
			break;
		}
	}
	if (flag == 1)
	{
		cout << "Safe Sequence" << endl;
		for (x = 0; x < p - 1; x++)
			cout << " P" << res[x] << " ->";
		cout << " P" << res[p - 1] << endl;
	}
	return (0);
}
