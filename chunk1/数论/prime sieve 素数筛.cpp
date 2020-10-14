
//单纯求素数，本地60ms+
const int MAXN = -1;//10000005
int prime[MAXN], pnum;
bool is_composite[MAXN];

void sieve(const int &n) {
    // 1 is exception
    for (int i = 2; i < n; ++i) {
        if (!is_composite[i]) prime[++pnum] = i;
        for (int j = 1; j <= pnum && i * prime[j] < n; ++j) {
            is_composite[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
}

//求素数和最小素因子，本地90ms+
const int MAXN = -1;//10000005
int prime[MAXN], pnum;
int min_composite[MAXN];

void sieve(const int &n) {
    // 1 is exception
    for (int i = 2; i < n; ++i) {
        if (!min_composite[i]) {

            prime[++pnum] = i;
            min_composite[i] = i;
        }
        for (int j = 1; j <= pnum 
            && prime[j] <= min_composite[i] 
            && i * prime[j] < n; ++j) {
            min_composite[i * prime[j]] = prime[j];
//            if (i % prime[j] == 0) break;
        }
    }
}



