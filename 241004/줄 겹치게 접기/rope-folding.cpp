#include <iostream>
#include <algorithm>
using namespace std;
int point[10002];

int curr=1, minp, maxp, n;

int fold(float i)
{
    int flag, p1, p2;
    flag = 0;
    if(i-minp<=maxp-i) {
        if(i==point[curr])
            p1=curr-1, p2=curr+1;
        else
            p1=curr, p2=curr+1;
        while(p1>0) {
            if(i-(float)point[p1] != (float)point[p2]-i) {
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
            if(i-(float)point[p1] != (float)point[p2]-i) {
                flag=1;
                break;
            }
            p1--, p2++;
        }
    }
    return !flag;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t, l, ans=0, flag;
    double i;
    cin>>n>>l;
    for(t=1;t<=n;t++)
        cin>>point[t];
    sort(point+1, point+n+1);
    minp=point[1], maxp=point[n];
    for(t=1;t<n;t++) {
        if(t!=1) {
            i=(float)point[t];
            curr++;
            if(fold(i))
                ans++;
        }
        i=((float)point[t]+(float)point[t+1])/2;
        if(fold(i))
            ans++;
    }
    cout<<ans;
    return 0;
}