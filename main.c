#include "memmgnt.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  int* first;
  int* second;
} pair;

int kth(int* ar, size_t n, pair (*split)(int*, size_t, int*), int* (*choose)(int*, size_t), size_t k) {
  if (n <= 1)
    return ar[0];
  int* piv = choose(ar, n);
  pair slice = split(ar, n, piv);

  size_t t = (size_t) (slice.second - ar) - 1; //index of pivot elements
  if (t + 1 == k) {
    return *(slice.second - 1);
  }
  if (t + 1 > k)
    return kth(ar, t, split, choose, k);
  else
    return kth(slice.second, n - t - 1, split, choose, k - t - 1);
}

int* rchoose(int* ar, size_t n) { return ar + ((size_t) rand() % n); }

pair lomuto(int* ar, size_t n, int* ppivot) {
  int pivot = *ppivot;
  int *l = ar, *h = ar, *end = ar + n;
  for (int* c = ar; c < end; c++) {
    if (*c < pivot) {
      int tmp = *c;
      *c = *h;
      *(h++) = *l;
      *l++ = tmp;
    } else if (*c == pivot) {
      *c = *h;
      *(h++) = pivot;
    }
  }
  return (pair){.first = l, .second = h};
}

int main() {
  srand((unsigned int) time(NULL));
  size_t n, k;
  scanf("%zu", &n);
  k = (n + 1) / 2;

  int* ar = (int*) smalloc(n * sizeof(int));
  for (size_t i = 0; i < n; i++) {
    scanf("%d", (ar + i));
  }
  int r = kth(ar, n, lomuto, rchoose, k);
  printf("%d\n", r);
  free(ar);

  return 0;
}