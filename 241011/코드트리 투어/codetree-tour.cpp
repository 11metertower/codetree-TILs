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
bool visit[2001], id_exist[2001];
int adj_list[2001][2001];
vector<pair<int, int>> adj[2001];

struct good {
	int id, revenue, dest;
};

bool operator<(pair<int, good> a, pair<int, good> b)
{
	if (a.first == b.first)
		return a.second.id > b.second.id;
	return a.first < b.first;
}

priority_queue<pair<int, good>, vector<pair<int, good>>> goods;
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
	int maxx = -1, ret = -1, flag = 0;
	while (!goods.empty()) {
		auto g = goods.top();
		if (!id_exist[g.second.id])
			goods.pop();
		else
			break;
	}
	if (goods.empty())
		return -1;
	auto g = goods.top();
	if (g.first >= 0) {
		goods.pop();
		id_exist[g.second.id] = 0;
		ret = g.second.id;
	}
	return ret;
}

int main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);
	int q, tc, num, i, j, v, u, w;
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

			pq.push({ 0, start });
			dijkstra();
		}
		else if (num == 200) {
			int id, revenue, dest;
			good tmp;
			cin >> id >> revenue >> dest;
			id_exist[id] = 1;
			tmp.id = id, tmp.revenue = revenue, tmp.dest = dest;
			goods.push({ revenue - least[dest], tmp });
		}
		else if (num == 300) {
			int id;
			cin >> id;
			id_exist[id] = 0;
		}
		else if (num == 400) {
			int output = sell();
			cout << output << "\n";
			if (output != -1)
				id_exist[output] = 0;
		}
		else {
			cin >> start;
			pq.push({ 0, start });
			dijkstra();
			priority_queue<pair<int, good>> tmpq;
			while (!goods.empty()) {
				auto g = goods.top();
				goods.pop();
				if (!id_exist[g.second.id])
					continue;
				tmpq.push(g);
			}
			while (!tmpq.empty()) {
				auto g = tmpq.top();
				tmpq.pop();
				g.first = g.second.revenue - least[g.second.dest];
				goods.push(g);
			}
		}
	}
	return 0;
}