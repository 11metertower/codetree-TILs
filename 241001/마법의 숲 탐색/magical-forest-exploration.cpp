#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;

int r, c, k;
struct ss {
    int c;
    int d;
};

ss golem[1001];
int mmap[74][74], max_r[1001], visit[1001], loc[1001][2];
vector<int> adj[1001];

int turn_left(int x)
{
    if (x > 0)
        return x - 1;
    return 3;
}

void reset(void)
{
    memset(mmap, 0, sizeof(mmap));
}

int bfs(int n)
{
    int maxx = max_r[n];
    if (maxx == r + 2)
        return maxx;
    for (auto i : adj[n]) {
        if (!visit[i]) {
            visit[i] = 1;
            maxx = max(maxx, bfs(i));
            if (maxx == r + 2)
                return maxx;
        }
    }
    return maxx;
}

int move(int n)
{
    int x, y;
    bool flag = true;
    x = 1, y = golem[n].c;
    while (flag) {
        flag = false;
        if ((y - 1 >= 1 && x + 2 <= r + 2 && !mmap[x + 1][y - 1]) && !mmap[x + 2][y] && !mmap[x + 1][y + 1]) {
            flag = true;
            x++;
        }
        else if (y - 2 >= 1 && x - 1 >= 0 && x + 2 <= r + 2 && !mmap[x - 1][y - 1] && !mmap[x][y - 2] && !mmap[x + 1][y - 1] && !mmap[x + 1][y - 2] && !mmap[x + 2][y - 1]) {
            flag = true;
            x++;
            y--;
            golem[n].d = turn_left(golem[n].d);
        }
        else if (x - 1 >= 0 && x + 2 <= r + 2 && y + 2 <= c && !mmap[x - 1][y + 1] && !mmap[x][y + 2] && !mmap[x + 1][y + 1] && !mmap[x + 1][y + 2] && !mmap[x + 2][y + 1]) {
            flag = true;
            x++;
            y++;
            golem[n].d = (golem[n].d + 1) % 4;
        }
    }
    if (x <= 3)
        return 0;
    
    mmap[x][y] = mmap[x + 1][y] = mmap[x - 1][y] = mmap[x][y + 1] = mmap[x][y - 1] = n;
    max_r[n] = x + 1;

    if (y - 1 >= 1 && loc[mmap[x - 1][y - 1]][0] == x - 1 && loc[mmap[x - 1][y - 1]][1] == y - 1)
        adj[mmap[x - 1][y - 1]].push_back(n);
    if (y + 1 <= c && loc[mmap[x - 1][y + 1]][0] == x - 1 && loc[mmap[x - 1][y + 1]][1] == y + 1)
        adj[mmap[x - 1][y + 1]].push_back(n);
    if (loc[mmap[x - 2][y]][0] == x - 2 && loc[mmap[x - 2][y]][1] == y)
        adj[mmap[x - 2][y]].push_back(n);
    if (y + 2 <= c && loc[mmap[x][y + 2]][0] == x && loc[mmap[x][y + 2]][1] == y + 2)
        adj[mmap[x][y + 2]].push_back(n);
    if (y + 1 <= c && loc[mmap[x + 1][y + 1]][0] == x + 1 && loc[mmap[x + 1][y + 1]][1] == y + 1)
        adj[mmap[x + 1][y + 1]].push_back(n);
    if (y - 1 >= 1 && loc[mmap[x + 1][y - 1]][0] == x + 1 && loc[mmap[x + 1][y - 1]][1] == y - 1)
        adj[mmap[x + 1][y - 1]].push_back(n);
    if (loc[mmap[x + 2][y]][0] == x + 2 && loc[mmap[x + 2][y]][1] == y)
        adj[mmap[x + 2][y]].push_back(n);
    if (y - 2 >= 1 && loc[mmap[x][y - 2]][0] == x && loc[mmap[x][y - 2]][1] == y - 2)
        adj[mmap[x][y - 2]].push_back(n);
    
    if (golem[n].d == 0) {
        loc[n][0] = x - 1, loc[n][1] = y;
        if (y - 1 >= 1 && mmap[x - 1][y - 1]) {
            adj[n].push_back(mmap[x - 1][y - 1]);
        }
        if (y + 1 <= c && mmap[x - 1][y + 1]) {
            adj[n].push_back(mmap[x - 1][y + 1]);
        }
        if (mmap[x - 2][y]) {
            adj[n].push_back(mmap[x - 2][y]);
        }
    }
    else if (golem[n].d == 1) {
        loc[n][0] = x, loc[n][1] = y + 1;
        if (y + 1 <= c && mmap[x - 1][y + 1]) {
            adj[n].push_back(mmap[x - 1][y + 1]);
        }
        if (y + 2 <= c && mmap[x][y + 2]) {
            adj[n].push_back(mmap[x][y + 2]);
        }
        if (y + 1 <= c && mmap[x + 1][y + 1]) {
            adj[n].push_back(mmap[x + 1][y + 1]);
        }
    }
    else if (golem[n].d == 2) {
        loc[n][0] = x + 1, loc[n][1] = y;
        if (y - 1 >= 1 && mmap[x + 1][y - 1]) {
            adj[n].push_back(mmap[x + 1][y - 1]);
        }
        if (y + 1 <= c && mmap[x + 1][y + 1]) {
            adj[n].push_back(mmap[x + 1][y + 1]);
        }
        if (x <= r && mmap[x + 2][y]) {
            adj[n].push_back(mmap[x + 2][y]);
        }
    }
    else if (golem[n].d == 3) {
        loc[n][0] = x, loc[n][1] = y - 1;
        if (y - 1 >= 1 && mmap[x - 1][y - 1]) {
            adj[n].push_back(mmap[x - 1][y - 1]);
        }
        if (y - 2 >= 1 && mmap[x][y - 2]) {
            adj[n].push_back(mmap[x][y - 2]);
        }
        if (y - 1 >= 1 && mmap[x + 1][y - 1]) {
            adj[n].push_back(mmap[x + 1][y - 1]);
        }
    }
    memset(visit, 0, sizeof(visit));
    return bfs(n) - 2;
}

int main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //freopen("input.txt", "r", stdin);
    int i, ans = 0, chk;
    cin >> r >> c >> k;
    for (i = 1; i <= k; i++)
        cin >> golem[i].c >> golem[i].d;
    for (i = 1; i <= k; i++) {
        chk = move(i);
        if (!chk)
            reset();
        ans += chk;
    }
    cout << ans;
    return 0;
}