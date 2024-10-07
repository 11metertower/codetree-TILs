#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct node {
	int p = 0;
	int color = 0;
	int max_depth = 0;
	int remain_depth = 0;
	vector<int> sibling;
};

struct colorr {
	int value = 0;
	int colors[6] = { 0, };
};

int q;
node nodes[100001];
vector<int> roots;

void change_color(int m, int color)
{
	nodes[m].color = color;
	for (auto i : nodes[m].sibling) {
		change_color(i, color);
	}
}

colorr cal_values(int m)
{
	int ret = 0, t = 0;
	colorr tmp;
	int colors[6] = { 0, };
	for (auto i : nodes[m].sibling) {
		tmp = cal_values(i);
		ret += tmp.value;
		for (int j = 1; j <= 5; j++) {
			if (tmp.colors[j] == 1)
				colors[j] = 1;
		}
	}
	colors[nodes[m].color] = 1;
	for (int i = 1; i <= 5; i++) {
		if (colors[i] == 1)
			t++;
		tmp.colors[i] = colors[i];
	}
	ret += t * t;
	tmp.value = ret;
	return tmp;
}

int main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);
	int i, num, m, p, color, max_depth, ans;
	colorr tmp;
	cin >> q;
	for (i = 1; i <= q; i++) {
		cin >> num;
		if (num == 100) {
			cin >> m >> p >> color >> max_depth;
			if (p == -1) {
				nodes[m].remain_depth = max_depth - 1;
				roots.push_back(m);
			}
			else {
				if (nodes[p].remain_depth == 0)
					continue;
				nodes[m].remain_depth = min(max_depth - 1, nodes[p].remain_depth - 1);
				nodes[p].sibling.push_back(m);
			}
			nodes[m].p = p;
			nodes[m].color = color;
			nodes[m].max_depth = max_depth;
		}
		else if (num == 200) {
			cin >> m >> color;
			change_color(m, color);
		}
		else if (num == 300) {
			cin >> m;
			cout << nodes[m].color << "\n";
		}
		else {
			ans = 0;
			for (auto j : roots) {
				tmp = cal_values(j);
				ans += tmp.value;
			}
			cout << ans << "\n";
		}
	}
	return 0;
}