#include<stdio.h>
#include<math.h>

/**
 * Diophantine Equations to the Power of n
 * 
 * Andre D'Amario
 * March 2021
 */

long reduceResidue(long x, long N) {
    return x%N;
}

void printReducedPowers(int n, int minN, int maxN, int maxY) {
    long a;
    for (int N = minN; N <= maxN; N++) {
        printf("N = %d:\n",N);
        for (int y = 0; y <= maxY; y++) {
            a = reduceResidue(pow(y, n), N);
            printf("%d, ", a);
        }
        printf("\n-------------------------------\n");
    }
}

void everyOtherZero(int n) {
    long a, N = 9, i = 0;
    while (1) {
        a = reduceResidue(pow(2,n), N);
        printf("2^%d === %d, N = %d;  ",n,a,N);
        if (a==0) break;
        N++;
    }
    printf("\n");
}

typedef unsigned long long big;

big power(big x, int p) {
    big result = 1;
    while (p > 0) {
        result = result*x;
        p--;
    }
    return result;
}

void repeatTwoLength(int n) {
    big a, b, aP, bP, N = 2*n, i = 0;
    while (1) {
        aP = power(2,n);
        bP = power(3,n);
        a = reduceResidue(aP, N);
        b = reduceResidue(bP, N);
        printf("N = %d;  ",N);
        if (a==0 && b==1) break;
        N++;
    }
    printf("2^%d = %d === 0, 3^%d = %d === 1 mod N = %d\n", n,aP,n,bP,N);
}

int main() {
    // x^4 === 0%16 or 1%16
    // printReducedPowers(4, 16, 16, 500);

    // printReducedPowers(5, 4, 4, 100);

    // everyOtherZero(7);
    // printReducedPowers(5, 8, 8, 100);


    // everyOtherZero(6);
    // printReducedPowers(6, 8, 8, 100);

    repeatTwoLength(32);
    // printReducedPowers(6, 64, 64, 100);


    // everyOtherZero(4);
    // printReducedPowers(4, 4, 4, 100);

//     everyOtherZero();
//     printReducedPowers(4, 4, 4, 100);
}