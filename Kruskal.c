#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef struct {
	int u, v, w;
} edge;
void mergeSort(edge *, int);
int Find(int *, int);
void Union(int *, int, int);
int main() {
	int v, e, ans = 0; scanf("%d %d", &v, &e);
	edge *edges = (edge *)malloc(e * sizeof(edge)); assert(edges);
	int *dsu = (int *)malloc((v + 1) * sizeof(int)); assert(dsu);
	for (int i = 1; i <= v; i++) dsu[i] = i;
	for (int i = 0; i < e; i++) {
		scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
	}
	mergeSort(edges, e);
	for (int i = 0; i < e; i++) {
		if (Find(dsu, edges[i].u) != Find(dsu, edges[i].v)) {
			Union(dsu, edges[i].u, edges[i].v); ans += edges[i].w;
		}
	}
	printf("%d\n", ans);
	free(edges); free(dsu);
	return 0;
}
void mergeSort(edge *a, int n) {
	if (n <= 1) return;
	mergeSort(a, n / 2);
	mergeSort(a + n / 2, (n + 1) / 2);
	int idx = 0;
	edge *tmp = (edge *)malloc(n * sizeof(edge)), *p = a, *q = a + n / 2;
	assert(tmp);
	while (p < a + n / 2 && q < a + n) {
		if (p->w < q->w) tmp[idx++] = *p++;
		else tmp[idx++] = *q++;
	}
	while (p < a + n / 2) tmp[idx++] = *p++;
	while (q < a + n) tmp[idx++] = *q++;
	for (int i = 0; i < n; i++) a[i] = tmp[i];
	free(tmp);
}
int Find(int *dsu, int i) {
	if (dsu[i] == i) return i;
	else return dsu[i] = Find(dsu, dsu[i]);
}
void Union(int *dsu, int a, int b) {
	int x = Find(dsu, a), y = Find(dsu, b);
	if (x != y) dsu[x] = y;	
}