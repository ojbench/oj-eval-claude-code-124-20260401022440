#include <cstdio>
#include <algorithm>

using namespace std;

int main() {
    int x, k, p;
    scanf("%d %d %d", &x, &k, &p);

    // available[i] tracks available seats for segment i to i+1 (0-indexed)
    int* available = new int[x];
    for (int i = 0; i < x; i++) {
        available[i] = k;
    }

    for (int i = 0; i < p; i++) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);

        // Find minimum available seats in the journey [u-1, v-2] (0-indexed)
        int min_seats = k;
        for (int j = u - 1; j < v - 1; j++) {
            min_seats = min(min_seats, available[j]);
        }

        if (min_seats >= n) {
            // Accept the order
            printf("T\n");
            for (int j = u - 1; j < v - 1; j++) {
                available[j] -= n;
            }
        } else {
            // Reject the order
            printf("N\n");
        }
    }

    delete[] available;
    return 0;
}
