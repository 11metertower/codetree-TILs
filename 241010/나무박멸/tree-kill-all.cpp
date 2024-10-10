#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int n, m, k, c;
int mapp[21][21];
int loc[4][2] = { {0,1},{0,-1},{1,0},{-1,0} };
int loc2[4][2] = { {-1,1},{-1,-1},{1,-1},{1,1} };

void grow(void)
{
	int i, j, t, x, y;
	int tmp_mapp[21][21];
	memset(tmp_mapp, 0, sizeof(tmp_mapp));
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			if (mapp[i][j] > 0) {
				for (t = 0; t < 4; t++) {
					x = i + loc[t][0], y = j + loc[t][1];
					if (x >= 1 && x <= n && y >= 1 && y <= n && mapp[x][y] > 0)
						tmp_mapp[i][j]++;
				}
			}
		}
	}
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			mapp[i][j] += tmp_mapp[i][j];
}

void divide(void)
{
	int i, j, t, cnt, x, y;
	int tmp_mapp[21][21];
	memset(tmp_mapp, 0, sizeof(tmp_mapp));
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			if (mapp[i][j] > 0) {
				cnt = 0;
				for (t = 0; t < 4; t++) {
					x = i + loc[t][0], y = j + loc[t][1];
					if (x >= 1 && x <= n && y >= 1 && y <= n && mapp[x][y] == 0)
						cnt++;
				}
				for (t = 0; t < 4; t++) {
					x = i + loc[t][0], y = j + loc[t][1];
					if (x >= 1 && x <= n && y >= 1 && y <= n && mapp[x][y] == 0)
						tmp_mapp[x][y] += mapp[i][j] / cnt;
				}
			}
		}
	}
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			mapp[i][j] += tmp_mapp[i][j];
}

int kill(void)
{
	int i, j, t, it, x, y, tx, ty;
	long maxx = 0, cnt;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			if (mapp[i][j] > 0) {
				cnt = mapp[i][j];
				for (t = 0; t < 4; t++) {
					for (it = 1; it <= k; it++) {
						x = i + loc2[t][0] * it, y = j + loc2[t][1] * it;
						if (x >= 1 && x <= n && y >= 1 && y <= n) {
							if (mapp[x][y] <= 0)
								break;
							cnt += mapp[x][y];
						}
					}
				}
				if (maxx < cnt) {
					maxx = cnt;
					tx = i, ty = j;
				}
			}
		}
	}
	i = tx, j = ty;
	mapp[i][j] = -c;
	for (t = 0; t < 4; t++) {
		for (it = 1; it <= k; it++) {
			x = i + loc2[t][0] * it, y = j + loc2[t][1] * it;
			if (x >= 1 && x <= n && y >= 1 && y <= n) {
				if (mapp[x][y] <= 0)
					break;
				mapp[x][y] = -c;
			}
		}
	}
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			if (mapp[i][j] < 0 && mapp[i][j] != -c)
				mapp[i][j]++;
		}
	}
	return maxx;
}

int main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);
	int i, j;
	long ans = 0;
	cin >> n >> m >> k >> c;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= n; j++) {
			int input;
			cin >> input;
			if (input == -1)
				mapp[i][j] = 0x80000000;
			else
				mapp[i][j] = input;
		}
	}
	for (i = 1; i <= m; i++) {
		grow();
		divide();
		ans += kill();
	}
	cout << ans;
	return 0;
}