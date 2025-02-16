#include <stdio.h>
#include <stdlib.h>

typedef struct Tree {
    int data;
    struct Tree* parent;
    struct Tree* left;
    struct Tree* right;
} Tree;

Tree* create_node(int data)
{
    Tree* node = (Tree*)malloc(sizeof(Tree));
    if (!node) return NULL;

    node->data = data;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;

    return node;
}

void insert_tree(Tree** tree, int data)
{
    if (!*tree) {
        *tree = create_node(data);
        return;
    }

    if (data < (*tree)->data) {
        if (!(*tree)->left) {
            Tree* node = create_node(data);
            node->parent = *tree;
            (*tree)->left = node;
        } else {
            insert_tree(&(*tree)->left, data);
        }
    } else {
        if (!(*tree)->right) {
            Tree* node = create_node(data);
            node->parent = *tree;
            (*tree)->right = node;
        } else {
            insert_tree(&(*tree)->right, data);
        }
    }
}

Tree* find_min(Tree* tree)
{
    if (!tree) return NULL;

    while (tree->left) 
      tree = tree->left;

    return tree;
}

Tree* find_max(Tree* tree)
{
    if (!tree) return NULL;

    while (tree->right) 
      tree = tree->right;

    return tree;
}

Tree* delete_tree(Tree* root, int data)
{
    if (root == NULL) return root;

    if (data < root->data) {
        root->left = delete_tree(root->left, data);
    } else if (data > root->data) {
        root->right = delete_tree(root->right, data);
    } else {
        // Nó encontrado
        if (root->left == NULL) {
            Tree* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Tree* temp = root->left;
            free(root);
            return temp;
        }

        // Nó com dois filhos: obter o sucessor em ordem (menor na subárvore direita)
        Tree* temp = find_min(root->right);

        // Copiar o valor do sucessor em ordem para este nó
        root->data = temp->data;

        // Deletar o sucessor em ordem
        root->right = delete_tree(root->right, temp->data);
    }
    return root;
}

Tree* search(Tree* tree, int data)
{
    if (!tree) return NULL;

    if (tree->data == data) return tree;

    if (data < tree->data) 
      return search(tree->left, data);
    else 
      return search(tree->right, data);
}

void traverse_tree(Tree* tree)
{
    if (!tree) return;

    traverse_tree(tree->left);
    printf("%d ", tree->data);
    traverse_tree(tree->right);
}

int main()
{
    Tree* tree = NULL;

    insert_tree(&tree, 10);
    insert_tree(&tree, 5);
    insert_tree(&tree, 15);
    insert_tree(&tree, 3);
    insert_tree(&tree, 7);
    insert_tree(&tree, 12);
    insert_tree(&tree, 18);

    printf("Árvore binária de busca: ");
    traverse_tree(tree);
    printf("\n");

    Tree* node = search(tree, 7);
    if (node) {
        printf("Nó encontrado: %d\n", node->data);
    } else {
        printf("Nó não encontrado\n");
    }

    printf("Deletando nó 5\n");
    tree = delete_tree(tree, 5);
    printf("Árvore binária de busca: ");
    traverse_tree(tree);
    printf("\n");

    printf("Deletando nó 15\n");
    tree = delete_tree(tree, 15);
    printf("Árvore binária de busca: ");
    traverse_tree(tree);
    printf("\n");

    printf("Mínimo: %d\n", find_min(tree)->data);
    printf("Máximo: %d\n", find_max(tree)->data);

    return EXIT_SUCCESS;
}