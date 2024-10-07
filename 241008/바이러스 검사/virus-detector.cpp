#include <iostream>
#include <vector>
using namespace std;
vector<int> cus;
int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, c, j, w, i, t, ans=0;
    cin>>n;
    for(i=1;i<=n;i++) {
        cin>>t;
        cus.push_back(t);
    }
    cin>>j>>w;
    for(i=0;i<n;i++) {
        t=cus[i]-j;
        ans++;
        if(t>0) {
            if(t%w==0)
                ans+=t/w;
            else
                ans+=(t/w+1);
        }
    }
    cout<<ans;
    return 0;
}