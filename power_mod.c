#include <stdio.h>
#include <malloc.h>
#include <math.h>

#define longint unsigned long long

typedef int test_func (longint* x, int p);

longint find_7 (longint n);
unsigned long find_best_mod (longint n, unsigned long up_to, longint **lst);
void find_all_mod (longint n, unsigned long up_to, longint **lst);
unsigned long list_to_set (longint *lst, unsigned long size);
void quicksort (longint *lst, unsigned long low, unsigned long high);
longint pow_l (longint a, longint b);
longint pow_l_mod (longint a, longint b, longint k);
longint choose (longint n, longint k);
longint fact_from (longint n, longint k);
void powerSum_10 (longint n);
int sumEqual(longint* arr, longint n);

int main ()
{
  /*
  longint n = 10;
  unsigned long k = 40;

  longint **lst = malloc ((sizeof (longint *)) * (k - 2));

  unsigned long best = find_best_mod (n, k, lst);

  printf ("The best modulo is %u ", lst[best][0]);
  printf ("with %u unique values.\n", lst[best][1]);

  for (int i = 0; i < k - 2; i++)
    {
      free (lst[i]);
    }
  
  free (lst);
  */

  powerSum_10 (10);
}

int sumEqual(longint* arr, longint n) {
    longint res = 0;
    // for (int i = 1; i <= n; i++) res += power(arr[i],n);
    // return power(arr[0],n) == res;
    for (int i = 0; i < n; i++) res += pow_l(arr[i],n);
    return pow_l(arr[n],n) == res;
}

void powerSum_10 (longint n) {
    longint* arr = (longint*)malloc((n+1)*sizeof(longint));
    
    arr[n] = 12;
    int maxY = ceil(pow(pow(arr[n],n)-n+1, 1/(float)n));
    for (int i = 0; i < n; i++) arr[i] = 11;
    arr[0] = 0;
    arr[n - 1] = 1;
    while (arr[n] <= 10000) {
        arr[0] += 11;
        int i = 0;
        int last_modified = 0;

        while (i < n-2 && arr[i] > maxY) {
            arr[i + 1] += 11;
            i++;
            last_modified = i;
        }

        if (arr[n - 2] > maxY)
          {
            arr[n - 1]++;
            last_modified = n - 1;
          }

        if (arr[n-1] > maxY) {
            arr[n]++;
            for (int i = 0; i < n; i++) arr[i] = 1;
            maxY = floor(pow(pow(arr[n],n)-n+1, 1/(float)n));
            printf("n = %u, maxY = %u\n", arr[n], maxY);
            last_modified = 0;
        }

        if (last_modified == n - 1)
        {
          longint nearest_11 = arr[n - 1] - (arr[n - 1] % 11);
          for (int j = 0; j < last_modified; j++) arr[j] = nearest_11;
        }
        else {
          for (int j = 0; j < last_modified; j++) arr[j] = arr[last_modified];
        }
        
        

        if (sumEqual(arr, n)) {
          printf("%u",arr[n],n,arr[n-1],n); printf ("^%u", n);
          printf (" = %u", arr[n - 1]); printf ("^%u", n);
          for (int i = n-2; i >= 0; i--) 
          {
            printf (" + %u", arr[i]); printf ("^%u", n);
          }
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

void count_to_size (int n, int * arr, int max, test_func test)
{
  while (arr[n] <= max)
  {
    arr[0]++;
    int i = 0;
    int last_modified = 0;

    while (i < n && arr[i] > max)
    {
      arr[i + 1]++;
      i++;
      last_modified = i;
    }

    for (int j = 0; j < last_modified; j++)
    {
      arr[j] = arr[last_modified];
    }

    /* int success = test (arr, n);

    if (success)
    {
      // print
    } */

    for (int j = 0; j < n + 1; j++)
    {
      printf ("%d, ", arr[j]);
    }

    printf ("\n");
  }
}

unsigned long find_best_mod (longint n, unsigned long up_to, longint **lst)
{
  find_all_mod (n, up_to, lst);

  unsigned long best_idx = 0;
  unsigned long best_info = 0;

  for (unsigned long i = 0; i < up_to - 2; i++)
  {
    long long information = 0;

    longint c = choose (n + lst[i][1], lst[i][1]);
    
    printf ("Choose: %u\n", c);
    if (lst[i][0] != lst[i][1] && c > lst[i][1])
      {
        information = (4294967296 - up_to + lst[i][0]) - c;
      }
    
    printf ("n: %u, ", n);
    printf ("k: %u, ", lst[i][0]);
    printf ("Unique Values: %u\n", lst[i][1]);
    printf ("Information (larger is better): %u\n", information);
    printf ("Mods: ");

    for (int j = 2; j < lst[i][1] + 2; j++)
      {
        printf ("%u, ", lst[i][j]);
      }

    printf ("\n\n");

    if (information > best_info)
      {
        best_idx = i;
        best_info = information;
      }
  }

  return best_idx;
}

/* Considers all values of x^n mod k for all k from 3 up to up_to for 
   the given n. Modifies lst so each element is of the form [k, a, ...],
   where k is the value of k, a is the number of unique mods, and ... is
   the values of the unique mods. lst must be of size k - 2. */
void find_all_mod (longint n, unsigned long up_to, longint **lst)
{
  if (up_to < 3)
    {
      return;
    }

  for (unsigned long k = 3; k <= up_to; k++)
    {
      longint *mods = malloc (sizeof (longint) * k);
      mods[0] = 0;
      mods[1] = 1;

      for (unsigned long i = 2; i < k; i++)
        {
          longint exp = pow_l_mod (i, n, k);
          mods[i] = exp;
        }
      
      unsigned long num_unique = list_to_set (mods, k);
      
      unsigned long lst_idx = k - 3;

      lst[lst_idx] = malloc ((sizeof (longint)) * (num_unique + 2));

      lst[lst_idx][0] = k;
      lst[lst_idx][1] = num_unique;

      for (int i = 2; i < num_unique + 2; i++)
        {
          lst[lst_idx][i] = mods[i - 2];
        }
      
      free (mods);
    }
}

/* Modifies lst so all elements in lst are unique, where lst is of length size.
   The k unique elements occupy the first k indexes, while every other element
   is -1. Returns the number of unique elements. */
unsigned long list_to_set (longint *lst, unsigned long size)
  {
    if (size == 0)
      {
        return 0;
      }

    quicksort (lst, 0, size - 1);

    unsigned long num_unique = 1;

    for (unsigned long i = 1; i < size; i++)
      {
        if (lst[i] != lst[i - 1])
          {
            lst[num_unique] = lst[i];
            num_unique++;
          }
      }
    
    unsigned long result = num_unique;

    while (num_unique < size)
      {
        lst[num_unique] = -1;
        num_unique++;
      }
    
    return result;
  }

void quicksort (longint *lst, unsigned long low, unsigned long high)
  {
    if (low >= high)
      {
        return;
      }

    unsigned long pivot_idx = (low + high) / 2;
    unsigned long pivot = lst[pivot_idx];

    unsigned long i = low - 1;
    unsigned long j = high + 1;

    while (1)
      {
        i++;
        while (lst[i] < pivot)
          {
            i++;
          }
        j--;
        while (lst[j] > pivot)
          {
            j--;
          }
        if (i >= j)
          {
            break;
          }
        longint temp = lst[i];
        lst[i] = lst[j];
        lst[j] = temp;
      }
    
    if (j < low)
      {
        j = low;
      }

    quicksort (lst, low, j);
    quicksort (lst, j + 1, high);
  }

longint pow_l (longint a, longint b)
  {
    longint result = 1;

    while (b > 0)
      {
        result = result * a;
        b--;
      }
    
    return result;
  }

longint pow_l_mod (longint a, longint b, longint k)
{
  longint result = 1;
  longint mod = a % k;

  while (b > 0)
    {
      result = result * mod;
      result = result % k;
      b--;
    }
  
  return result;
}

longint choose (longint n, longint k)
{
  longint num = fact_from (n, n - k + 1);
  longint denom = fact_from (k, 1);

  return num / denom;
}

longint fact_from (longint n, longint k)
{
  if (n == 0)
    {
      return 1;
    }

  if (k < 1)
    {
      k = 1;
    }

  longint result = k;

  for (longint i = k + 1; i <= n; i++)
    {
      result = result * i;
    }
  
  return result;
}