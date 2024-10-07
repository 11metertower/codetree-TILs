#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;
int n, m, x, y, k;
int mapp[21][21];
int dice[7], tmp_dice[7];
int main()
{
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	//freopen("input.txt", "r", stdin);
	int i, j, num;
	cin >> n >> m >> x >> y >> k;
	x++, y++;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			cin >> mapp[i][j];
	for (i = 1; i <= k; i++) {
		cin >> num;
		if (num == 1) {
			if (y + 1 > m)
				continue;
			y++;
			tmp_dice[1] = dice[4];
			tmp_dice[2] = dice[3];
			tmp_dice[3] = dice[1];
			tmp_dice[4] = dice[2];
			tmp_dice[5] = dice[5];
			tmp_dice[6] = dice[6];
			memcpy(dice, tmp_dice, sizeof(dice));
			if (mapp[x][y] == 0)
				mapp[x][y] = dice[1];
			else {
				dice[1] = mapp[x][y];
				mapp[x][y] = 0;
			}
			cout << dice[2] << "\n";
		}
		else if (num == 2) {
			if (y - 1 < 1)
				continue;
			y--;
			tmp_dice[1] = dice[3];
			tmp_dice[2] = dice[4];
			tmp_dice[3] = dice[2];
			tmp_dice[4] = dice[1];
			tmp_dice[5] = dice[5];
			tmp_dice[6] = dice[6];
			memcpy(dice, tmp_dice, sizeof(dice));
			if (mapp[x][y] == 0)
				mapp[x][y] = dice[1];
			else {
				dice[1] = mapp[x][y];
				mapp[x][y] = 0;
			}
			cout << dice[2] << "\n";
		}
		else if (num == 3) {
			if (x - 1 < 1)
				continue;
			x--;
			tmp_dice[1] = dice[6];
			tmp_dice[2] = dice[5];
			tmp_dice[3] = dice[3];
			tmp_dice[4] = dice[4];
			tmp_dice[5] = dice[1];
			tmp_dice[6] = dice[2];
			memcpy(dice, tmp_dice, sizeof(dice));
			if (mapp[x][y] == 0)
				mapp[x][y] = dice[1];
			else {
				dice[1] = mapp[x][y];
				mapp[x][y] = 0;
			}
			cout << dice[2] << "\n";
		}
		else {
			if (x + 1 > n)
				continue;
			x++;
			tmp_dice[1] = dice[5];
			tmp_dice[2] = dice[6];
			tmp_dice[3] = dice[3];
			tmp_dice[4] = dice[4];
			tmp_dice[5] = dice[2];
			tmp_dice[6] = dice[1];
			memcpy(dice, tmp_dice, sizeof(dice));
			if (mapp[x][y] == 0)
				mapp[x][y] = dice[1];
			else {
				dice[1] = mapp[x][y];
				mapp[x][y] = 0;
			}
			cout << dice[2] << "\n";
		}
	}
	return 0;
}