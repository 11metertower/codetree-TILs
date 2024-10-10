#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>
#define INF 0x7fffffff
using namespace std;
int n, m, start;
int least[2001];
bool visit[2001];
int adj_list[2001][2001];
vector<pair<int, int>> adj[2001];
map<int, pair<int, int>> goods;
priority_queue<pair<int, int>> pq;

void reset(void)
{
	int i;
	for (i = 0; i < n; i++) {
		least[i] = INF;
		visit[i] = 0;
	}
	least[start] = 0;
}

void dijkstra(void)
{
	reset();
	while (!pq.empty()) {
		auto curr = pq.top();
		visit[curr.second] = 1;
		pq.pop();
		for (auto next : adj[curr.second]) {
			if (!visit[next.first]) {
				if (least[next.first] > least[curr.second] + next.second) {
					least[next.first] = least[curr.second] + next.second;
					pq.push({ -least[next.first], next.first });
				}
			}
		}
	}
}

int sell()
{
	int maxx = -1, ret = -1, idx = 0;
	for (auto i : goods) {
		int id = i.first, revenue = i.second.first, dest = i.second.second;
		int cost = least[dest];
		if (cost != INF || cost <= revenue) {
			if (revenue - cost > maxx) {
				maxx = revenue - cost;
				ret = id;
			}
			else if (revenue - cost == maxx) {
				if (ret > id) {
					ret = id;
				}
			}
		}
	}
	return ret;
}

int main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);
	int q, tc, num, i, j, v, u, w, flag = 1;
	cin >> q;
	for (tc = 1; tc <= q; tc++) {
		cin >> num;
		if (num == 100) {
			cin >> n >> m;
			for (i = 1; i <= m; i++) {
				cin >> v >> u >> w;
				if (v == u)
					continue;
				if (adj_list[v][u] != 0 && adj_list[v][u] > w || adj_list[v][u] == 0)
					adj_list[v][u] = w;
				if (adj_list[u][v] != 0 && adj_list[u][v] > w || adj_list[u][v] == 0)
					adj_list[u][v] = w;
			}
			for (i = 0; i < n; i++)
				for (j = i + 1; j < n; j++)
					if (adj_list[i][j])
						adj[i].push_back({ j, adj_list[i][j] }), adj[j].push_back({ i, adj_list[i][j] });
		}
		else if (num == 200) {
			int id, revenue, dest;
			cin >> id >> revenue >> dest;
			goods.insert({ id,{revenue,dest} });
		}
		else if (num == 300) {
			int id;
			cin >> id;
			goods.erase(id);
		}
		else if (num == 400) {
			if (flag) {
				pq.push({ 0, start });
				dijkstra();
				flag = 0;
			}
			int output = sell();
			cout << output << "\n";
			if (output != -1)
				goods.erase(output);
		}
		else {
			cin >> start;
			flag = 1;
		}
	}
	return 0;
}