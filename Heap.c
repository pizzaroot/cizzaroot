#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define _HEAP_DATA_TYPE_ int
typedef struct {
	_HEAP_DATA_TYPE_ *H; int n;
} heap;
heap *createHeap(int);
void destroyHeap(heap *);
void insertItem(heap *, _HEAP_DATA_TYPE_);
_HEAP_DATA_TYPE_ removeMax(heap *);
int compare(_HEAP_DATA_TYPE_, _HEAP_DATA_TYPE_);
int main() {
	int n; scanf("%d", &n);
	heap *pq = createHeap(n);
	while (n--) {
		int x; scanf("%d", &x);
		if (x) insertItem(pq, x);
		else printf("%d\n", removeMax(pq));
	}
	destroyHeap(pq);
	return 0;
}
heap *createHeap(int sz) {
	heap *pq = (heap *)malloc(sizeof(heap));
	assert(pq);
	pq->n = 0;
	pq->H = (_HEAP_DATA_TYPE_ *)malloc((sz + 1) * sizeof(_HEAP_DATA_TYPE_));
	assert(pq->H);
	return pq;
}
void destroyHeap(heap *pq) {
	free(pq->H); free(pq);
}
void insertItem(heap *pq, _HEAP_DATA_TYPE_ x) {
	int i = ++pq->n;
	while (i > 1 && compare(pq->H[i >> 1], x)) {
		pq->H[i] = pq->H[i >> 1];
		i >>= 1;
	}
	pq->H[i] = x;
}
_HEAP_DATA_TYPE_ removeMax(heap *pq) {
	if (pq->n == 0) return 0;
	_HEAP_DATA_TYPE_ M = pq->H[1];
	pq->H[1] = pq->H[pq->n--];
	_HEAP_DATA_TYPE_ tmp = pq->H[1]; int i = 1;
	while ((i << 1) <= pq->n && compare(tmp, pq->H[i << 1]) || (i << 1 | 1) <= pq->n && compare(tmp, pq->H[i << 1 | 1])) {
		if ((i << 1 | 1) <= pq->n && compare(tmp, pq->H[i << 1 | 1])) {
			if (compare(tmp, pq->H[i << 1]) && compare(pq->H[i << 1 | 1], pq->H[i << 1])) {
				pq->H[i] = pq->H[i << 1];
				i <<= 1;
			} else {
				pq->H[i] = pq->H[i << 1 | 1];
				i <<= 1; i |= 1;
			} 
		} else {
			pq->H[i] = pq->H[i << 1];
			i <<= 1;
		}
	}
	pq->H[i] = tmp;
	return M;
}
int compare(_HEAP_DATA_TYPE_ a, _HEAP_DATA_TYPE_ b) {
	return a > b; // Min Heap
}