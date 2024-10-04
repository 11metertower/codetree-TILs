#include <iostream>
#include <algorithm>
using namespace std;
int point[10002];
int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, l, i, minp, maxp, curr=1, ans=0, flag, p1, p2;
    cin>>n>>l;
    for(i=1;i<=n;i++)
        cin>>point[i];
    sort(point+1, point+n+1);
    minp=point[1], maxp=point[n];
    for(i=minp+1;i<maxp;i++) {
        flag = 0;
        if(i==point[curr+1])
            curr++;
        if(i-minp<=maxp-i) {
            if(i==point[curr])
                p1=curr-1, p2=curr+1;
            else
                p1=curr, p2=curr+1;
            while(p1>0) {
                if(i-point[p1] != point[p2]-i) {
                    flag=1;
                    break;
                }
                p1--, p2++;
            }
        }
        else {
            if(i==point[curr])
                p1=curr-1, p2=curr+1;
            else
                p1=curr, p2=curr+1;
            while(p2<=n) {
                if(i-point[p1] != point[p2]-i) {
                    flag=1;
                    break;
                }
                p1--, p2++;
            }
        }
        if(!flag)
            ans++;
    }
    cout<<ans;
    return 0;
}