#include<iostream>
#include<cmath>
#include<algorithm>
#include<limits.h>
#include<queue>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<list>
#include<stack>
#include<deque>
#include<string>

using namespace std;

#define int long long
#define endl "\n"
#define pb push_back
#define mp make_pair
#define ll long long
#define ld long double
#define vi vector<int>


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    int ans = LLONG_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans = min(ans, abs(a[i] - b[j]));
        }
    }

    cout << ans << endl;

    return 0;
}
// This code finds the minimum absolute difference between elements of two arrays a and b.

