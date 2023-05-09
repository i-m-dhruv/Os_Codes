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
	int frameSize, i = 0, fault = 0;
	cin >> frameSize;
	map<char, int> mp;
	for (auto c : frame)
	{
		if (mp.size() == frameSize)
		{
			auto t = *min_element(mp.begin(), mp.end(), [](auto i, auto j)
								  { return i.second < j.second; });
			fault++;
			mp.erase(t.first);
		}
		mp[c] = i++;
	}
	cout << fault + mp.size();
}