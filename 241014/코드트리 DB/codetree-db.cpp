#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
using namespace std;

int q, cnt;
map<string, int> m;
set<int> m2;
string names[100001];
int values[100001];

struct node {
	int left = 0, right = 0, index = 0;
	int count = 0;
	long long sum = 0;
};

vector<node> tree;

void update(int id, int left, int right, int value, int index, int count, long long sum)
{
	if (right < value || value < left)
		return;
	if (left == right) {
		tree[id].index = index;
		tree[id].count = count;
		tree[id].sum = sum;
		return;
	}
	int mid = (left + right) / 2;
	if (value <= mid) {
		if (tree[id].left == 0) {
			tree[id].left = tree.size();
			node new_node;
			tree.push_back(new_node);
		}
		update(tree[id].left, left, mid, value, index, count, sum);
	}
	else {
		if (tree[id].right == 0) {
			tree[id].right = tree.size();
			node new_node;
			tree.push_back(new_node);
		}
		update(tree[id].right, mid + 1, right, value, index, count, sum);
	}
	tree[id].count = tree[tree[id].left].count + tree[tree[id].right].count;
	tree[id].sum = tree[tree[id].left].sum + tree[tree[id].right].sum;
	return;
}

int count_rank(int id, int left, int right, int value)
{
	if (left == right)
		return tree[id].index;
	int mid = (left + right) / 2;
	if (tree[id].left) {
		if (tree[tree[id].left].count >= value)
			return count_rank(tree[id].left, left, mid, value);
		return count_rank(tree[id].right, mid + 1, right, value - tree[tree[id].left].count);
	}
	return count_rank(tree[id].right, mid + 1, right, value);
}

long long count_sum(int id, int left, int right, int ql, int qr)
{
	if (qr < left || right < ql)
		return 0;
	long long ret = 0;
	if (ql <= left && right <= qr)
		return tree[id].sum;
	int mid = (left + right) / 2;
	if (tree[id].left)
		ret += count_sum(tree[id].left, left, mid, ql, qr);
	if (tree[id].right)
		ret += count_sum(tree[id].right, mid + 1, right, ql, qr);
	return ret;
}

void init(void)
{
	m.clear();
	m2.clear();
	tree.clear();
	cnt = 0;
	node tmp, tmp2;
	tree.push_back(tmp);
	tree.push_back(tmp2);
}

void insert(string name, int value)
{
	if (m.find(name) != m.end() || m2.find(value) != m2.end()) {
		cout << "0\n";
		return;
	}
	m[name] = ++cnt;
	names[cnt] = name, values[cnt] = value;
	m2.insert(value);
	update(1, 1, 1e9, value, cnt, 1, value);
	cout << "1\n";
	return;
}

void del(string name)
{
	if (m.find(name) == m.end()) {
		cout << "0\n";
		return;
	}
	cout << values[m[name]] << "\n";
	update(1, 1, 1e9, values[m[name]], m[name], 0, 0);
	m2.erase(values[m[name]]);
	m.erase(name);
	return;
}

void rankk(int k)
{
	if (tree[1].count < k) {
		cout << "None\n";
		return;
	}
	cout << names[count_rank(1, 1, 1e9, k)] << "\n";
}

void sum(int k)
{
	cout << count_sum(1, 1, 1e9, 1, k) << "\n";
}

int main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);
	int i, a;
	string query, name;
	cin >> q;
	for (i = 1; i <= q; i++) {
		cin >> query;
		if (query == "init")
			init();
		else if (query == "insert") {
			cin >> name >> a;
			insert(name, a);
		}
		else if (query == "delete") {
			cin >> name;
			del(name);
		}
		else if (query == "rank") {
			cin >> a;
			rankk(a);
		}
		else if (query == "sum") {
			cin >> a;
			sum(a);
		}
	}
	return 0;
}