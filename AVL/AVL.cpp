#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

int get_height(Node* node) {
    if (node == NULL)
        return 0;
    return node->height;
}

int get_balance(Node* node) {
    if (node == NULL)
        return 0;
    return get_height(node->left) - get_height(node->right);
}

Node* create_node(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

Node* right_rotate(Node* z) {
    Node* y = z->left;
    Node* T3 = y->right;

    y->right = z;
    z->left = T3;

    z->height = 1 + (get_height(z->left) > get_height(z->right) ? get_height(z->left) : get_height(z->right));
    y->height = 1 + (get_height(y->left) > get_height(y->right) ? get_height(y->left) : get_height(y->right));

    return y;
}

Node* left_rotate(Node* z) {
    Node* y = z->right;
    Node* T2 = y->left;

    y->left = z;
    z->right = T2;

    z->height = 1 + (get_height(z->left) > get_height(z->right) ? get_height(z->left) : get_height(z->right));
    y->height = 1 + (get_height(y->left) > get_height(y->right) ? get_height(y->left) : get_height(y->right));

    return y;
}

Node* insert(Node* node, int key) {
    if (node == NULL)
        return create_node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + (get_height(node->left) > get_height(node->right) ? get_height(node->left) : get_height(node->right));

    int balance = get_balance(node);

    // Left heavy
    if (balance > 1 && key < node->left->key)
        return right_rotate(node);

    // Right heavy
    if (balance < -1 && key > node->right->key)
        return left_rotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

void pre_order(Node* node) {
    if (node != NULL) {
        printf("%d ", node->key);
        pre_order(node->left);
        pre_order(node->right);
    }
}

int main() {
    Node* root = NULL;
    int keys[] = { 10, 20, 30, 40, 50, 25 };
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, keys[i]);
    }

    printf("Pre-ordem da Árvore AVL:\n");
    pre_order(root);

    return 0;
}
