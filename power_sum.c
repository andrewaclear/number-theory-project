#include<stdio.h>
#include<math.h>

/**
 * Diophantine Equations to the Power of n
 * 
 * Andre D'Amario
 * March 2021
 */

int reduceResidue(int x, int N) {
    return x%N;
}

int main() {
    int a;
    int N = 2;
    for (int i = 0; i < 200; i++) {
        printf("%d, ", (int)reduceResidue(pow((double)i, (double)N), pow((double)N,(double)N)));
    }
}