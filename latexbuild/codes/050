/**
 *  @Source: myself
 *  @Author: Tieway59
 *  @Complexity: $O(N)$
 *  @Description:
 *      筛法求素数
 *      p[0] 素数个数
 *      p[1] ... p[*p] 所有素数
 *      v[]  合数标记, false的是素数
 *      // 没有标记1
 *
 *  @Example:
 *
 *  @Verification:
 *
 */

void PrimeInit(int p[], bool v[], int size) {
    for (int i = 2; i <= size; i++) {
        if (!v[i]) p[++*p] = i;
        for (int j = 1; j <= *p && i * p[j] <= size; j++) {
            v[i * p[j]] = true;
            if (i % p[j] == 0)break;
        }
    }
}

int prime[MAXN];
bool vised[MAXN];
