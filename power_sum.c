#include<stdio.h>
#include<math.h>
#include<malloc.h>

/**
 * Diophantine Equations to the Power of n
 * 
 * Andrew D'Amario
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
    big a, b, aP, bP, N, i = 0;
    // N = 2*n+1;       // for next jump
    N = n+1;        // for closer
    while (1) {
        aP = power(2,n);
        bP = power(3,n);
        a = reduceResidue(aP, N);
        b = reduceResidue(bP, N);
        printf("N = %d;  ",N);
        if (a==0 && b==1) break;
        N++;
    }
    printf("\n2^%d = %u === %d, 3^%d = %u === %d mod N = %d\n", n,aP,a,n,bP,b,N);
    // if (N==20) break;
    // }
}


int sumEqual(big* arr, int n) {
    big res;
    for (int i = 1; i <= n; i++) res += power(arr[i],n);
    return power(arr[0],n) == res;
}

void powerSum(int n) {
    big* arr = (big*)malloc((n+1)*sizeof(big));
    arr[0] = n;                                     // initialize x to n
    // for (int i = 1; i <= n; i++) arr[i] = 1;        // initialize y_i's to 1
    int j = 1, maxY = ceil(pow(pow(arr[0],n)-n+1, 0.5)), b;
    while (!sumEqual(arr, n)) {
        // start at first bit j = 1
        // increment up to maxY
        if () {

        } else if (arr[j] < maxY) arr[j]++;
        // then go to next bit and set all previous bits to that value
        else {
            j++;
            arr[j]++;
            for (int i = 1; i < j; i++) arr[i] = arr[j];
        }
        // for (int i = 1; i <= n; i++) {
        //     b = j%(int)(j/pow(maxY, i-1));
        //     arr[i] = b;
        //     printf("%d, ",j);
        // }
        // printf("\n");
        // arr[0]++;
        // j++;
    }
    printf("%u^%d = %u^%d",arr[0],n,arr[1],n);
    for (int i = 2; i <= n; i++) printf(" + %u^%d",arr[i],n);
    printf("\n");
    // }
    free(arr);
}



int main() {
    // x^4 === 0%16 or 1%16
    // printReducedPowers(4, 16, 16, 500);

    // printReducedPowers(5, 4, 4, 100);

    // everyOtherZero(7);
    // printReducedPowers(5, 8, 8, 100);


    // everyOtherZero(6);
    // printReducedPowers(6, 8, 8, 100);

    // repeatTwoLength(36);
    powerSum(2);
    // printReducedPowers(6, 64, 64, 100);


    // everyOtherZero(4);
    // printReducedPowers(4, 4, 4, 100);

//     everyOtherZero();
//     printReducedPowers(4, 4, 4, 100);
}