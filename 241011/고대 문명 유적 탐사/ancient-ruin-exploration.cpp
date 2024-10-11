#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <queue>
using namespace std;

int k, m, sum, maxx, partscnt = 1;
int mapp[6][6], cpy[6][6], best[6][6], visit[6][6], parts[301];
int loc[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };
queue<pair<int, int>> start, start_tmp;

void get(int x, int y)
{
	int dx, dy, i, num = cpy[x][y], same = 1;
	queue<pair<int, int>> q;
	q.push({ x, y });
	while (!q.empty()) {
		auto curr = q.front();
		q.pop();
		int xx = curr.first, yy = curr.second;
		for (i = 0; i < 4; i++) {
			dx = xx + loc[i][0], dy = yy + loc[i][1];
			if (dx > 0 && dy > 0 && dx <= 5 && dy <= 5 && !visit[dx][dy] && cpy[dx][dy] == num) {
				visit[dx][dy] = 1;
				q.push({ dx, dy });
				same++;
			}
		}
	}
	if (same >= 3) {
		start_tmp.push({ x,y });
		sum += same;
	}
}

void turn(int x, int y)
{
	int t1, t2, t3;
	t1 = cpy[x - 1][y + 1], t2 = cpy[x - 1][y], t3 = cpy[x - 1][y - 1];
	cpy[x - 1][y + 1] = cpy[x - 1][y - 1], cpy[x - 1][y] = cpy[x][y - 1], cpy[x - 1][y - 1] = cpy[x + 1][y - 1];
	cpy[x - 1][y - 1] = cpy[x + 1][y - 1], cpy[x][y - 1] = cpy[x + 1][y], cpy[x + 1][y - 1] = cpy[x + 1][y + 1];
	cpy[x + 1][y - 1] = cpy[x + 1][y + 1], cpy[x + 1][y] = cpy[x][y + 1], cpy[x + 1][y + 1] = cpy[x - 1][y + 1];
	cpy[x + 1][y + 1] = t1, cpy[x][y + 1] = t2, cpy[x - 1][y + 1] = t3;
}

void score(void)
{
	int ret = 0, i, dx, dy;
	memset(visit, 0, sizeof(visit));
	queue<pair<int, int>> q;
	while (!start.empty()) {
		int x, y;
		auto ttmp = start.front();
		x = ttmp.first, y = ttmp.second;
		start.pop();
		int num = best[x][y];
		visit[x][y] = 1;
		q.push({ x,y });
		while (!q.empty()) {
			auto curr = q.front();
			q.pop();
			int xx = curr.first, yy = curr.second;
			best[xx][yy] = 0;
			for (i = 0; i < 4; i++) {
				dx = xx + loc[i][0], dy = yy + loc[i][1];
				if (dx > 0 && dy > 0 && dx <= 5 && dy <= 5 && !visit[dx][dy] && best[dx][dy] == num) {
					visit[dx][dy] = 1;
					q.push({ dx, dy });
				}
			}
		}
	}
}

void fill(void)
{
	int i, j;
	for (j = 1; j <= 5; j++) {
		for (i = 5; i >= 1; i--) {
			if (best[i][j] == 0) {
				best[i][j] = parts[partscnt];
				if (partscnt + 1 > m)
					partscnt = 1;
				else
					partscnt++;
			}
		}
	}
}

int main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);
	int i, j, tc, x, y, tt;
	cin >> k >> m;
	for (i = 1; i <= 5; i++)
		for (j = 1; j <= 5; j++)
			cin >> mapp[i][j];
	for (i = 1; i <= m; i++)
		cin >> parts[i];
	for (tc = 1; tc <= k; tc++) {
		maxx = 0;
		for (tt = 0; tt < 4; tt++) {
			for (i = 2; i <= 4; i++) {
				for (j = 2; j <= 4; j++) {
					sum = 0;
					memset(visit, 0, sizeof(visit));
					memcpy(cpy, mapp, sizeof(cpy));
					for (int it = 1; it <= tt; it++)
						turn(i, j);
					for (x = 1; x <= 5; x++) {
						for (y = 1; y <= 5; y++) {
							if (!visit[x][y]) {
								visit[x][y] = 1;
								get(x, y);
							}
						}
					}
					if (maxx < sum) {
						maxx = sum;
						memcpy(best, cpy, sizeof(best));
						while (!start.empty())
							start.pop();
						while (!start_tmp.empty()) {
							start.push(start_tmp.front());
							start_tmp.pop();
						}
					}
					else {
						while (!start_tmp.empty()) {
							start_tmp.pop();
						}
					}
				}
			}
		}
		if (!maxx)
			return 0;
		score();
		fill();
		memcpy(mapp, best, sizeof(mapp));
		while (1) {
			sum = 0;
			memset(visit, 0, sizeof(visit));
			memcpy(cpy, mapp, sizeof(cpy));
			for (x = 1; x <= 5; x++) {
				for (y = 1; y <= 5; y++) {
					if (!visit[x][y]) {
						visit[x][y] = 1;
						get(x, y);
					}
				}
			}
			maxx += sum;
			memcpy(best, cpy, sizeof(best));
			while (!start.empty())
				start.pop();
			while (!start_tmp.empty()) {
				start.push(start_tmp.front());
				start_tmp.pop();
			}
			score();
			fill();
			memcpy(mapp, best, sizeof(mapp));
			if (!sum)
				break;
		}
		cout << maxx << " ";
	}
	return 0;
}