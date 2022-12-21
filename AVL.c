#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define _BBST_DATA_TYPE_ int
typedef struct Node {
	struct Node *left, *right;
	int height, cnt; _BBST_DATA_TYPE_ x;
} node;
typedef struct {
	node *root;
} bbst;
void preorder(node *);
bbst *createBbst();
void destroyBbst(bbst *);
void _destroyBbst(node *);
void insertBbst(bbst *, _BBST_DATA_TYPE_);
node *_insertBbst(node *, _BBST_DATA_TYPE_);
void deleteBbst(bbst *, _BBST_DATA_TYPE_);
node *_deleteBbst(node *, _BBST_DATA_TYPE_);
int findBbst(bbst *, _BBST_DATA_TYPE_);
int _findBbst(node *, _BBST_DATA_TYPE_);
node *balanceBbst(node *);
node *leftRotate(node *);
node *rightRotate(node *);
node *beginBbst(bbst *);
node *endBbst(bbst *);
node *_beginBbst(node *);
node *_endBbst(node *);
int compare(_BBST_DATA_TYPE_, _BBST_DATA_TYPE_);
int abs(int);
int max(int, int);
int getSafe(node *);
int main() {
	int t; scanf("%d", &t);
	while (t--) {
		bbst *s = createBbst();
		int q; scanf("%d", &q);
		while (q--) {
			char op; scanf("\n%c", &op);
			if (op == 'I') {
				int x; scanf("%d", &x);
				insertBbst(s, x);
			} else {
				int mode, x; scanf("%d", &mode);
				if (s->root == NULL) continue;
				if (mode == -1) x = beginBbst(s)->x;
				else x = endBbst(s)->x;
				deleteBbst(s, x);
			}
		}
		if (s->root == NULL) printf("EMPTY\n");
		else printf("%d %d\n", endBbst(s)->x, beginBbst(s)->x);
		destroyBbst(s);
	}
	return 0;
}
void preorder(node *root) {
	if (root == NULL) return;
    preorder(root->right);
    printf("%d ", root->x);
    preorder(root->left);
}
bbst *createBbst() {
	bbst *s = (bbst *)malloc(sizeof(bbst));
	assert(s);
	s->root = NULL;
	return s;
}
void destroyBbst(bbst *s) {
	_destroyBbst(s->root); free(s);
}
void _destroyBbst(node *root) {
	if (root == NULL) return;
	_destroyBbst(root->left);
	_destroyBbst(root->right);
	free(root);
}
void deleteBbst(bbst *s, _BBST_DATA_TYPE_ x) {
	s->root = _deleteBbst(s->root, x);
}
node *_deleteBbst(node *root, _BBST_DATA_TYPE_ x) {
	if (root == NULL) return root;
	if (compare(x, root->x)) root->left = _deleteBbst(root->left, x);
	else if (compare(root->x, x)) root->right = _deleteBbst(root->right, x);
	else if (root->cnt > 1) {root->cnt--; return root;}
	else {
		if (root->left == NULL || root->right == NULL) {
			node *tmp = root->left;
			if (tmp == NULL) tmp = root->right;
			if (tmp == NULL) {tmp = root; root = NULL;}
			else *root = *tmp;
			free(tmp);
		} else {
			node *tmp = _beginBbst(root->right);
			root->x = tmp->x; root->cnt = tmp->cnt;
			root->right = _deleteBbst(root->right, tmp->x);
		}
	}
	if (root == NULL) return root;
	root->height = 1 + max(getSafe(root->left), getSafe(root->right));
	root = balanceBbst(root);
	return root;
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
		v->cnt = 1;
		return v;
	}
	if (compare(x, root->x)) root->left = _insertBbst(root->left, x);
	else if (compare(root->x, x)) root->right = _insertBbst(root->right, x);
	else {root->cnt++; return root;}
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
node *beginBbst(bbst *s) {
	node *root = s->root;
	return _beginBbst(s->root);
}
node *endBbst(bbst *s) {
	return _endBbst(s->root);
}
node *_beginBbst(node *root) {
	while (root->left) root = root->left;
	return root;
}
node *_endBbst(node *root) {
	while (root->right) root = root->right;
	return root;
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