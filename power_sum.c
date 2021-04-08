#include<stdio.h>
#include<math.h>
#include<malloc.h>

/**
 * Diophantine Equations to the Power of n
 *
 * Andrew D'Amario
 * co-author: Dawson Brown
 * March 2021
 */
typedef unsigned long long big;

big reduceResidue(big x, long N) {
    return x%N;
}

big power(big x, int p) {
    big result = 1;
    while (p > 0) {
        result = result*x;
        p--;
    }
    return result;
}

void printReducedPowers(int n, int minN, int maxN, int maxY) {
    big a;
    for (int N = minN; N <= maxN; N++) {
        printf("n = %u, N = %u:  ",n,N);
        for (int y = 0; y <= maxY; y++) {
            a = reduceResidue(power(y, n), N);
            printf("%u, ", a);
        }
        printf("...\n");
        // printf("\n-------------------------------\n");
    }
}

void everyOtherZero(int n) {
    long a, N = 2*n, i = 0;
    while (1) {
        a = reduceResidue(pow(2,n), N);
        printf("2^%d === %d, N = %d;  ",n,a,N);
        if (a==0) break;
        N++;
    }
    printf("\n");
}

void countUp(int n) {
    // big arr[5] = {};
    // while (1) {

    // }
    
}


void repeatTwoLength(int n) {
    big a, b, aP, bP, N, i = 0;
    N = 2*n;       // for next jump
    // N = n+1;        // for closer
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
    big res = 0;
    // for (int i = 1; i <= n; i++) res += power(arr[i],n);
    // return power(arr[0],n) == res;
    for (int i = 0; i < n; i++) res += power(arr[i],n);
    return power(arr[n],n) == res;
}

void powerSum(int n) {
    big* arr = (big*)malloc((n+1)*sizeof(big));
    // arr[0] = n-1;                                     // initialize x to n
    // int j = -1, maxY, b;
    // while (!sumEqual(arr, n)) {
    //     // start at first bit j = 1
    //     // initialize y_i's to 1
    //     if (j == -1 || arr[j] < maxY) arr[j]++;
    //     else if (j == n) {
    //         j = 1;
    //         arr[0]++;
    //         for (int i = 1; i <= n; i++) arr[i] = 1;
    //         maxY = ceil(pow(pow(arr[0],n)-n+1, 0.5));
    //     // increment up to maxY
    //     // then go to next bit and set all previous bits to that value
    //     } else {

    //         j++;
    //         arr[j]++;
    //         for (int i = 1; i < j; i++) arr[i] = arr[j];
    //     }
    //     // for (int i = 1; i <= n; i++) {
    //     //     b = j%(int)(j/pow(maxY, i-1));
    //     //     arr[i] = b;
    //     //     printf("%d, ",j);
    //     // }
    //     // printf("\n");
    //     // arr[0]++;
    //     // j++;
    // // }
    arr[n] = 353;
    int maxY = ceil(pow(pow(arr[n],n)-n+1, 0.5));
    for (int i = 0; i < n; i++) arr[i] = 1;
    arr[0] = 0;
    while (arr[n] <= 10000) {
        arr[0]++;
        int i = 0;
        int last_modified = 0;

        while (i < n-1 && arr[i] > maxY) {
            arr[i + 1]++;
            i++;
            last_modified = i;
        }

        if (arr[n-1] > maxY) {
            arr[n]++;
            for (int i = 0; i < n; i++) arr[i] = 1;
            maxY = floor(pow(pow(arr[n],n)-n+1, 1/(float)n));
            printf("n = %u, maxY = %u\n", arr[n], maxY);
            last_modified = 0;
        }

        for (int j = 0; j < last_modified; j++) arr[j] = arr[last_modified];

        if (sumEqual(arr, n)) {
            printf("%u^%d = %u^%d",arr[n],n,arr[n-1],n);
            for (int i = n-2; i >= 0; i--) printf(" + %u^%d",arr[i],n);
            printf("\n");
            break;
        }
    }
    // printf("%u^%d = %u^%d",arr[0],n,arr[1],n);
    // for (int i = 2; i <= n; i++) printf(" + %u^%d",arr[i],n);
    // printf("\n");
    // }
    free(arr);
}

// int xModCheck()

// void powerSumModCheck(int n) {
//     big* arr = (big*)malloc((n+1)*sizeof(big));
//     arr[n] = 353;
//     int maxY = ceil(pow(pow(arr[n],n)-n+1, 0.5));
//     for (int i = 0; i < n; i++) arr[i] = 1;
//     arr[0] = 0;
//     while (arr[n] <= 10000) {
//         arr[0]++;
//         int i = 0;
//         int last_modified = 0;

//         while (i < n-1 && arr[i] > maxY) {
//             arr[i + 1]++;
//             i++;
//             last_modified = i;
//         }

//         if (arr[n-1] > maxY) {
//             arr[n]++;
//             for (int i = 0; i < n; i++) arr[i] = 1;
//             maxY = floor(pow(pow(arr[n],n)-n+1, 1/(float)n));
//             printf("n = %u, maxY = %u\n", arr[n], maxY);
//             last_modified = 0;
//         }

//         for (int j = 0; j < last_modified; j++) arr[j] = arr[last_modified];

//         if (xModCheck && yModCheck sumEqual(arr, n)) {
//             printf("%u^%d = %u^%d",arr[n],n,arr[n-1],n);
//             for (int i = n-2; i >= 0; i--) printf(" + %u^%d",arr[i],n);
//             printf("\n");
//             break;
//         }
//     }
//     // printf("%u^%d = %u^%d",arr[0],n,arr[1],n);
//     // for (int i = 2; i <= n; i++) printf(" + %u^%d",arr[i],n);
//     // printf("\n");
//     // }
//     free(arr);
// }

int main() {
    // x^4 === 0%16 or 1%16
    // printReducedPowers(4, 16, 16, 500);

    // printReducedPowers(5, 4, 4, 100);

    // everyOtherZero(7);
    // printReducedPowers(5, 8, 8, 100);
    
    // everyOtherZero(4);
    // printReducedPowers(4, 8, 8, 100);

    // everyOtherZero(6);
    // printReducedPowers(6, 16, 16, 100);
    // repeatTwoLength(6);

    // everyOtherZero(8);
    // printReducedPowers(8, 16, 16, 100);

    // everyOtherZero(10);
    // printReducedPowers(10, 32, 32, 100);

    // everyOtherZero(11);
    // printReducedPowers(10, 32, 32, 100);
    // printReducedPowers(10, 11, 11, 100);
    
    // repeatTwoLength(36);
    // printReducedPowers(6, 64, 64, 100);

    // everyOtherZero(4);
    // printReducedPowers(4, 4, 4, 100);

    // everyOtherZero();
    // printReducedPowers(4, 4, 4, 100);

    // powerSum(4);




    /*
    // Conjecture 2.1
    printReducedPowers(1,2,2,15);
    // printReducedPowers(1,4,4,15);

    printReducedPowers(2,2,2,15);
    printReducedPowers(2,4,4,15);
    // printReducedPowers(2,8,8,15);
    
    printReducedPowers(4,2,2,15);
    printReducedPowers(4,4,4,15);
    printReducedPowers(4,8,8,15);
    printReducedPowers(4,16,16,15);
    
    printReducedPowers(8,2,2,15);
    printReducedPowers(8,4,4,15);
    printReducedPowers(8,8,8,15);
    printReducedPowers(8,16,16,15);
    printReducedPowers(8,32,32,15);
    // printReducedPowers(8,64,64,15);

    printReducedPowers(16,2,2,15);
    printReducedPowers(16,4,4,15);
    printReducedPowers(16,8,8,15);
    printReducedPowers(16,16,16,15);
    printReducedPowers(16,32,32,15);
    printReducedPowers(16,64,64,15);

    printReducedPowers(32,2,2,15);
    printReducedPowers(32,4,4,15);
    printReducedPowers(32,8,8,15);
    printReducedPowers(32,16,16,15);
    printReducedPowers(32,32,32,15);
    printReducedPowers(32,64,64,15);
    printReducedPowers(32,128,128,15);

    printReducedPowers(64,2,2,15);
    printReducedPowers(64,4,4,15);
    printReducedPowers(64,8,8,15);
    printReducedPowers(64,16,16,15);
    printReducedPowers(64,32,32,15);
    printReducedPowers(64,64,64,15);
    printReducedPowers(64,128,128,15);
    printReducedPowers(64,256,256,15);
    */


    /*
    // Conjecture 2
    // everyOtherZero(6);
    printReducedPowers(24,2,2,15);
    printReducedPowers(24,4,4,15);
    printReducedPowers(24,8,8,15);
    printReducedPowers(24,16,16,15);
    printReducedPowers(24,32,32,15);
    printReducedPowers(24,64,64,15);
    printReducedPowers(24,128,128,15);
    printReducedPowers(24,256,256,15);
    printReducedPowers(24,512,512,15);
    printReducedPowers(24,1024,1024,15);
    printReducedPowers(24,8192,8192,15);

    // everyOtherZero(10);
    // printReducedPowers(10,16,16,15);
    printReducedPowers(10,32,32,15);
    // everyOtherZero(12);
    printReducedPowers(12,64,64,15);
    // everyOtherZero(14);
    printReducedPowers(14,512,512,15);
    // everyOtherZero(18);
    printReducedPowers(18,2,2,15);
    // everyOtherZero(20);
    // everyOtherZero(22);
    // everyOtherZero(24);
    // everyOtherZero(26);
    // everyOtherZero(28);
    // everyOtherZero(30);
    // everyOtherZero(34);
    printReducedPowers(34,128,128,15);
    printReducedPowers(235676,128,128,15);
    */








    // Conjecture 3
    // printReducedPowers(3,3,3,15);
    // printReducedPowers(5,5,5,15);
    // printReducedPowers(7,7,7,20);
    // printReducedPowers(11,11,11,35);
    // printReducedPowers(13,13,13,15);
    // printReducedPowers(17,17,17,100);
    // printReducedPowers(19,19,19,100);






    // more
    // printReducedPowers(10,11,11,25);
    // printReducedPowers(20,21,21,50);


    printReducedPowers(18,256,256,50);
}