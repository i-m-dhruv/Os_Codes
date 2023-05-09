#include <bits/stdc++.h>
using namespace std;

bool compare(std::pair<std::string, int> i, pair<std::string, int> j)
{
	return i.second < j.second;
}

int main()
{
	string frame;
	cin >> frame;
	int frameSize;
	cin >> frameSize;

	queue<int> q;
	map<int, int> mp;
	int t = 0;
	int cnt = 0;

	for (auto c : frame)
	{
		int num = c - '0';
		if (!mp[num])
		{
			if (q.size() == frameSize)
			{
				mp.erase(q.front());
				q.pop();
			}
			q.push(num);
			mp[num]++;
			cnt++;
		}
	}
	cout << cnt;

	return 0;
}