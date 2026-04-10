#include <iostream>
#include <omp.h>
using namespace std;

struct Node {
    Node* left;
    Node* right;
};

extern void process(Node* p);

void postorder_traverse(Node* p) {
    if (p->left) {
        #pragma omp task
        postorder_traverse(p->left);
    }

    if (p->right) {
        #pragma omp task
        postorder_traverse(p->right);
    }

    #pragma omp taskwait
    process(p);
}

void process(Node* p) {
    #pragma omp critical
    {
        cout << "Processing node: " << p << endl;
    }
}

Node* create_test_tree() {
    Node* root = new Node{nullptr, nullptr};
    root->left = new Node{nullptr, nullptr};
    root->right = new Node{nullptr, nullptr};
    root->left->left = new Node{nullptr, nullptr};
    root->left->right = new Node{nullptr, nullptr};
    root->right->left = new Node{nullptr, nullptr};
    root->right->right = new Node{nullptr, nullptr};
    return root;
}

void delete_tree(Node* p) {
    if (!p) return;
    delete_tree(p->left);
    delete_tree(p->right);
    delete p;
}

int main() {
    omp_set_num_threads(4);

    Node* root = create_test_tree();

    cout << "Starting parallel postorder traversal..." << endl;

    #pragma omp parallel
    {
        #pragma omp single
        {
            postorder_traverse(root);
        }
    }

    cout << "Traversal completed!" << endl;

    delete_tree(root);
    return 0;
}