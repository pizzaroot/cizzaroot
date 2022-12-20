#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define _BBST_DATA_TYPE_ int
typedef struct Node {
	struct Node *left, *right;
	int height; _BBST_DATA_TYPE_ x;
} node;
typedef struct {
	node *root;
} bbst;
bbst *createBbst();
void insertBbst(bbst *, _BBST_DATA_TYPE_);
node *_insertBbst(node *, _BBST_DATA_TYPE_);
int findBbst(bbst *, _BBST_DATA_TYPE_);
int _findBbst(node *, _BBST_DATA_TYPE_);
node *balanceBbst(node *);
node *leftRotate(node *);
node *rightRotate(node *);
int compare(_BBST_DATA_TYPE_, _BBST_DATA_TYPE_);
int abs(int);
int max(int, int);
int getSafe(node *);
int main() {
	bbst *s = createBbst();
	int n; scanf("%d", &n);
	while (n--) {
		int tmp; scanf("%d", &tmp);
		insertBbst(s, tmp);
	}
	int m; scanf("%d", &m);
	while (m--) {
		int tmp; scanf("%d", &tmp);
		printf("%d%c", findBbst(s, tmp), " \n"[m == 0]);
	}
	return 0;
}
bbst *createBbst() {
	bbst *s = (bbst *)malloc(sizeof(bbst));
	assert(s);
	s->root = NULL;
	return s;
}
void insertBbst(bbst *s, _BBST_DATA_TYPE_ x) {
	s->root = _insertBbst(s->root, x);
}
int findBbst(bbst *s, _BBST_DATA_TYPE_ x) {
	return _findBbst(s->root, x);
}
int _findBbst(node *root, _BBST_DATA_TYPE_ x) {
	if (root == NULL) return 0;
	if (compare(x, root->x)) return _findBbst(root->left, x);
	else if (compare(root->x, x)) return _findBbst(root->right, x);
	else return 1;
}
node *_insertBbst(node *root, _BBST_DATA_TYPE_ x) {
	if (root == NULL) {
		node *v = (node *)malloc(sizeof(node));
		assert(v);
		v->x = x;
		v->left = NULL;
		v->right = NULL;
		v->height = 1;
		return v;
	}
	if (compare(x, root->x)) root->left = _insertBbst(root->left, x);
	else if (compare(root->x, x)) root->right = _insertBbst(root->right, x);
	else return root;
	root->height = 1 + max(getSafe(root->left), getSafe(root->right));
	root = balanceBbst(root);
	return root;
}
node *balanceBbst(node *root) {
	int f = getSafe(root->left) - getSafe(root->right);
	if (abs(f) <= 1) return root;
	if (f > 1) {
		if (getSafe(root->left->left) <= getSafe(root->left->right)) root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	if (f < -1) {
		if (getSafe(root->right->right) <= getSafe(root->right->left)) root->right = rightRotate(root->right);
		return leftRotate(root);
	}
}
node *leftRotate(node *z) {
	node *y = z->right; node *T2 = y->left;
	y->left = z; z->right = T2;
	z->height = 1 + max(getSafe(z->left), getSafe(z->right));
	y->height = 1 + max(getSafe(y->left), getSafe(y->right));
	return y;
}
node *rightRotate(node *z) {
	node *y = z->left; node *T2 = y->right;
	y->right = z; z->left = T2;
	z->height = 1 + max(getSafe(z->left), getSafe(z->right));
	y->height = 1 + max(getSafe(y->left), getSafe(y->right));
	return y;
}
int compare(_BBST_DATA_TYPE_ a, _BBST_DATA_TYPE_ b) {
	return a < b;
}
int abs(int x) {
	return x > 0 ? x : -x;
}
int max(int a, int b) {
	return a > b ? a : b;
}
int getSafe(node *z) {
	if (z) return z->height;
	else return 0;
}