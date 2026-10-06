#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node *root;

struct Node *CreateTree(struct Node *root, struct Node *r, int data, int level)
{
    if (r == NULL) {
        r = (struct Node *)malloc(sizeof(struct Node));
        if (r == NULL) {
            printf("Oshibka vydeleniya pamyati\n");
            exit(0);
        }
        r->left = NULL;
        r->right = NULL;
        r->data = data;
        if (root == NULL) return r;
        if (data > root->data) root->left = r;
        else root->right = r;
        return r;
    }
    if (data == r->data){
        printf("Incorrect value. Level:%i\n", level);
        return root;
    }    
    if (data > r->data) CreateTree(r, r->left, data, level+1);
    else CreateTree(r, r->right, data, level+1);
    return root;
}

struct Node *Search(struct Node *r, int data)
{
    if (r == NULL) return NULL;
    if (data == r->data) return r;
    if (data > r->data) return Search(r->left, data);
    return Search(r->right, data);
}

int Count(struct Node *r, int data)
{
    if (r == NULL) return 0;
    if (data == r->data) return 1 + Count(r->right, data);
    if (data > r->data) return Count(r->left, data);
    return Count(r->right, data);
}

struct Node *Delete(struct Node *r, int data)
{
    struct Node *tmp;
    if (r == NULL) return NULL;
    if (data > r->data) r->left = Delete(r->left, data);
    else if (data < r->data) r->right = Delete(r->right, data);
    else {
        if (r->left == NULL) { tmp = r->right; free(r); return tmp; }
        if (r->right == NULL) { tmp = r->left; free(r); return tmp; }
        tmp = r->left;
        
        while (tmp->right != NULL) tmp = tmp->right;
        
        r->data = tmp->data;
        r->left = Delete(r->left, tmp->data);
    }
    return r;
}

void Change(int old, int val)
{
    if (Search(root, old) == NULL) {
        printf("Znachenie %d ne naydeno\n", old);
        return;
    }
    if (Search(root, val) != NULL) {
        printf("Znachenie %d uzhe est v dereve\n", val);
        return;
    }
    root = Delete(root, old);
    root = CreateTree(root, root, val, 0);
    printf("Znachenie %d izmeneno na %d\n\n", old, val);
}

void print_tree(struct Node *r, int l)
{
    static int d[256];
    if (r == NULL) return;
    d[l + 1] = 1;
    print_tree(r->right, l + 1);
    for (int i = 1; i < l; i++) printf(d[i] != d[i + 1] ? "│   " : "    ");
    if (l > 0) printf(d[l] == 1 ? "┌── " : "└── ");
    printf("%d\n", r->data);
    d[l + 1] = -1;
    print_tree(r->left, l + 1);
}

int main()
{
    int D, N, start = 1;
    root = NULL;

    printf("-1 - okonchanie postroeniya dereva\n");
    while (start) {
        printf("Vvedite chislo: ");
        scanf("%d", &D);
        if (D == -1) {
            printf("Postroenie dereva okoncheno\n\n");
            start = 0;
        }
        else root = CreateTree(root, root, D, 1);
    }

    print_tree(root, 0);

    printf("\nVvedite iskomoe znachenie: ");
    scanf("%d", &D);
    if (Search(root, D) != NULL) printf("Znachenie %d naydeno\n", D);
    else printf("Znachenie %d ne naydeno\n", D);
    printf("Chislo vhozhdeniy: %d\n", Count(root, D));

    printf("\nVvedite staroe i novoe znachenie: ");
    scanf("%d %d", &D, &N);
    Change(D, N);
    print_tree(root, 0);

    return 0;
}
