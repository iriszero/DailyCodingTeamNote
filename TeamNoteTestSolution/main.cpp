#include <stdio.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <unordered_map>

#define MX 1000
#define DIVIDER 1234567891
#define lld long long int
#define ll pair<lld, lld>
#define lll pair<lld, ll>
#define PAIRS(x,y,z) make_pair( (x), make_pair( (y), (z)) )
using namespace std;


int main(void) {
	int t; scanf("%d", &t);
	unordered_map<int, int> mm;


	while (t--) {
		unordered_map<ll, lld> m;
		unordered_map<int, int> dat;
		queue<lll> q;

		int N, M;
		scanf("%d %d", &N, &M);

		q.push(PAIRS(1, N, M));

		while (!q.empty()) {
			lll now = q.front();
			q.pop();

			lld mul = now.first;
			lld x = now.second.first;
			lld y = now.second.second;

			if (x == 1) {
				auto it = m.find(y);
				if (it != m.end()) {
					it->second ++ mul;
					it->second %= DIVIDER;
				}
				else {
					m[y] = mul % DIVIDER;
				}
			}

			auto it = m.find(now.second);
			if (it != m.end()) {
				it->second += mul;
				it->second %= DIVIDER;
			}
			else {
				m[now.second] = mul % DIVIDER;
			}
		}
	}

	return 0;
}