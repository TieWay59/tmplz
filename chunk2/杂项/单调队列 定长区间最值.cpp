#define _debug(x) cerr<<#x<<" = "<<x<<endl

#include <iostream>
#include <algorithm>
#include <deque>

using namespace std;

typedef long long ll;

const int INF = 0x3f3f3f3f;
const int MOD = 998244353;
const int MAXN = 1e6 + 59;

int Kase, n, m;

int a[MAXN];
int ans1[MAXN], ans2[MAXN];
deque<int> qMAX, qMIN;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        while (!qMIN.empty() && i - qMIN.front() >= m)
            qMIN.pop_front();
        while (!qMAX.empty() && i - qMAX.front() >= m)
            qMAX.pop_front();

        while (!qMIN.empty() && a[qMIN.back()] > a[i])
            qMIN.pop_back();

        while (!qMAX.empty() && a[qMAX.back()] < a[i])
            qMAX.pop_back();

        if (qMIN.empty() || a[qMIN.back()] <= a[i])
            qMIN.push_back(i);

        if (qMAX.empty() || a[qMAX.back()] >= a[i])
            qMAX.push_back(i);

        if (i >= m) {
            ans1[i] = a[qMIN.front()];
            ans2[i] = a[qMAX.front()];
        }
    }
    for (int j = m; j <= n; ++j) {
        cout << ans1[j] << " \n"[j == n];
    }
    for (int j = m; j <= n; ++j) {
        cout << ans2[j] << " \n"[j == n];
    }
    return 0;
}

/*


 2
2 0
1 2
1 1

 3 2
 1 2 1
 5 3 1
 1 5 1


*/
