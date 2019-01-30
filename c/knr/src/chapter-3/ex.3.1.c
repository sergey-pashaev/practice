/* ex.3.1 */

/* Our binary search makes two tests inside the loop, when one would */
/* suffice (at the price of more tests outside.) Write a version with */
/* only one test inside the loop and measure the difference in */
/* run-time. */

#include <stdio.h>
#include <stdlib.h>

int binsearch(int x, int v[], int n) {
    int lo = 0;
    int hi = n - 1;
    int mid;
    /* make it strictly less than to avoid calculating mid for hen lo
     * == hi (mid = (lo + lo) / 2) */
    while (lo < hi) {
        mid = (lo + hi) / 2;
        /* use less or equal to exclude third case */
        if (x <= v[mid]) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    /* move case hen lo == hi here */
    return (x == v[lo]) ? lo : -1;
}

int main(int argc, char* argv[]) {
    if (argc < 2) return 1;
    const int n = 1000000;
    int* v = malloc(sizeof(int) * n);
    if (!v) return 2;
    for (int i = 0; i < n; ++i) v[i] = i + 1;
    int x = atoi(argv[1]);
    if (x < 1) return 3;
    printf("%d\n", binsearch(x, v, n));
    free(v);
    return 0;
}
