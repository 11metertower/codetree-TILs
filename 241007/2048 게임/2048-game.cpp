#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int n;
int first_mapp[21][21];

void move(int direction, int (*mapp)[21])
{
	int i, j, k;
	int visit[21][21];
	memset(visit, 0, sizeof(visit));
	if (direction == 1) {
		for (j = n - 1; j >= 1; j--) {
			for (i = 1; i <= n; i++) {
				if (!mapp[i][j])
					continue;
				k = j;
				while (k < n) {
					if (mapp[i][k + 1] == 0) {
						mapp[i][k + 1] = mapp[i][k];
						mapp[i][k] = 0;
						visit[i][k + 1] = visit[i][k];
						visit[i][k] = 0;
					}
					else if (mapp[i][k + 1] == mapp[i][k] && !visit[i][k + 1] && !visit[i][k]) {
						mapp[i][k] = 0;
						mapp[i][k + 1] *= 2;
						visit[i][k + 1] = 1;
					}
					else
						break;
					k++;
				}
			}
		}
	}
	else if (direction == 2) {
		for (j = 2; j <= n; j++) {
			for (i = 1; i <= n; i++) {
				if (!mapp[i][j])
					continue;
				k = j;
				while (k > 1) {
					if (mapp[i][k - 1] == 0) {
						mapp[i][k - 1] = mapp[i][k];
						mapp[i][k] = 0;
						visit[i][k - 1] = visit[i][k];
						visit[i][k] = 0;
					}
					else if (mapp[i][k - 1] == mapp[i][k] && !visit[i][k - 1] && !visit[i][k]) {
						mapp[i][k] = 0;
						mapp[i][k - 1] *= 2;
						visit[i][k - 1] = 1;
					}
					else
						break;
					k--;
				}
			}
		}
	}
	else if (direction == 3) {
		for (i = n - 1; i >= 1; i--) {
			for (j = 1; j <= n; j++) {
				if (!mapp[i][j])
					continue;
				k = i;
				while (k < n) {
					if (mapp[k + 1][j] == 0) {
						mapp[k + 1][j] = mapp[k][j];
						mapp[k][j] = 0;
						visit[k + 1][j] = visit[k][j];
						visit[k][j] = 0;
					}
					else if (mapp[k + 1][j] == mapp[k][j] && !visit[k + 1][j] && !visit[k][j]) {
						mapp[k][j] = 0;
						mapp[k + 1][j] *= 2;
						visit[k + 1][j] = 1;
					}
					else
						break;
					k++;
				}
			}
		}
	}
	else {
		for (i = 2; i <= n; i++) {
			for (j = 1; j <= n; j++) {
				if (!mapp[i][j])
					continue;
				k = i;
				while (k > 1) {
					if (mapp[k - 1][j] == 0) {
						mapp[k - 1][j] = mapp[k][j];
						mapp[k][j] = 0;
						visit[k - 1][j] = visit[k][j];
						visit[k][j] = 0;
					}
					else if (mapp[k - 1][j] == mapp[k][j] && !visit[k - 1][j] && !visit[k][j]) {
						mapp[k][j] = 0;
						mapp[k - 1][j] *= 2;
						visit[k - 1][j] = 1;
					}
					else
						break;
					k--;
				}
			}
		}
	}
}

int func(int level, int direction, int (*mapp)[21])
{
	int i, j, ret = 0;
	move(direction, mapp);
	if (level == 5) {
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				ret = max(mapp[i][j], ret);
		return ret;
	}
	for (i = 1; i <= 4; i++) {
		ret = max(func(level + 1, i, mapp), ret);
	}
	return ret;
}

int main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);
	int i, j, ans;
	int mapp[21][21];
	cin >> n;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			cin >> first_mapp[i][j];
	for (i = 1; i <= 4; i++) {
		memcpy(mapp, first_mapp, sizeof(mapp));
		ans = max(ans, func(0, i, mapp));
	}
	cout << ans;
	return 0;
}