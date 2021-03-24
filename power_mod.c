#include <stdio.h>
#include <malloc.h>

#define longint unsigned long long

unsigned long find_best_mod (longint n, unsigned long up_to, longint **lst);
void find_all_mod (longint n, unsigned long up_to, longint **lst);
unsigned long list_to_set (longint *lst, unsigned long size);
void quicksort (longint *lst, unsigned long low, unsigned long high);
longint pow_l (longint a, longint b);
longint choose (longint n, longint k);
longint fact_from (longint n, longint k);

int main ()
{
  choose (6, 4);
  longint n = 4;
  unsigned long k = (unsigned long)pow_l (4, 2);
  printf ("%u\n", k);

  longint **lst = malloc ((sizeof (longint *)) * (k - 2));

  unsigned long best = find_best_mod (n, k, lst);

  printf ("The best modulo is %u ", lst[best][0]);
  printf ("with %u unique values.\n", lst[best][1]);

  for (int i = 0; i < k - 2; i++)
    {
      printf ("n: %u,", n);
      printf ("k: %u\n", lst[i][0]);
      printf ("Mods: ");

      for (int j = 2; j < lst[i][1] + 2; j++)
        {
          printf ("%u, ", lst[i][j]);
        }
      
      free (lst[i]);
      printf ("\n\n");
    }
  
  free (lst);
}

unsigned long find_best_mod (longint n, unsigned long up_to, longint **lst)
{
  find_all_mod (n, up_to, lst);

  unsigned long best_idx = 0;
  unsigned long best_info = 0;

  for (unsigned long i = 0; i < up_to - 2; i++)
  {
    unsigned long c = choose (n + lst[i][1], lst[i][1]);
    unsigned long information = 0;
    if (c < lst[i][0])
      {
        information = lst[i][0] - c;
      }

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
          longint exp = pow_l (i, n);
          mods[i] = exp % k;
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
    
    printf ("Done quicksort\n");

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