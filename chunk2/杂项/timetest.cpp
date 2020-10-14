
#include <bits/stdc++.h>

using namespace std;

int main() {

    clock_t begin = clock();
    int x = 0;
    for (int i = 1; i <= 800000000; ++i) {
        x++;
    }
    printf("%.3f ms\n", (double) (clock() - begin));
    return 0;
}