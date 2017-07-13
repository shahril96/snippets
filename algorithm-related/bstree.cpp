
/*
 * Ayam implementation of Binary Search Tree
 *
 * references :-
 *   https://en.wikipedia.org/wiki/Binary_search_tree
 *   http://geeksquiz.com/binary-search-tree-set-2-delete/
 *
 * ~ not very descriptive compile guide (linux) ~
 * $ g++ bstree.cpp -o bstree -std=c++11
 * $ ./bstree
 *
 */

#include <iostream>

using namespace std;

template <typename T>
class BSTree {

private:

    typedef struct Node {
        T key;
        Node *left, *right;

        Node() {
            left = right = NULL;
        }
    } Node;

    Node *root;

    // in-order traversal tree deletion
    template<typename Func>
    void inOrder(Node *node, Func f) {
        if(node != NULL) {
            inOrder(node->left, f); // recurse to left subtree
            f(node);
            inOrder(node->right, f); // recurse to right subtree
        }
    }

    Node *insert(Node *node, T n) {

        // if we hit the jackpot
        // then create new node here with new value
        if (node == NULL) {
            node = new Node;
            node->key = n;

        // not hitting the jackpot yet!??!!?!

        // value is less than root's key? then recurse to left
        } else if(n < node->key) {
            node->left = insert(node->left, n);

        // or recurse right if value is more than root's key
        } else if(n > node->key) {
            node->right = insert(node->right, n);
        }

        return node;
    }

    Node *search(Node *node, T n) {

        // if root = NULL (empty tree)
        // or root = what we want to find for
        // then return root itself
        if(node == NULL || node->key == n) {
            return node;

        // if key is less than root's key, then go find in left-subtree
        } else if(n < node->key) {
            return search(node->left, n);

        // if key is more than root's key, then go find in right-subtree
        } else if(n > node->key) {
            return search(node->right, n);
        }

    }

    Node *deleteNode(Node *node, T n) {

        if(node == NULL)
            return NULL;

        else if(n < node->key)
            node->left = deleteNode(node->left, n);

        else if(n > node->key)
            node->right = deleteNode(node->right, n);

        else { // if found node that we want to delete

            Node *current, *tmp;

            // if only have right child node
            if(node->left == NULL) {
                tmp = node->right;
                delete node;
                return tmp;

            // if only have left child node
            } else if(node->right == NULL) {

                tmp = node->left;
                delete node;
                return tmp;

            // if have both childs
            } else {

                for(current = node->right;
                    current != NULL;
                    current = current->left) {} // lowest below in right subtree

                node->key = current->key;
                deleteNode(current, current->key);
            }
        }

        return node;
    }

public:

    BSTree() {
        root = NULL;
    }

    ~BSTree() {
        inOrder([](Node *node) {
            delete node;
        });
    }

    void insert(T n) {
        root = insert(root, n);
    }

    bool search(T n) {
        Node *get = search(root, n);
        return get != NULL;
    }

    void deleteNode(T n) {
        root = deleteNode(root, n);
    }

    template<typename Func>
    void inOrder(Func f) {
        inOrder(root, f);
    }

    void inOrder_print() {

        cout << "Element inside BSTree : ";

        inOrder([](Node *node) {
            cout << node->key << ' ';
        });

        cout << endl;
    }
};

int main(int argc, char const *argv[]) {

    BSTree<int> bt;

    // insert some dummy value
    bt.insert(12);
    bt.insert(1);
    bt.insert(2);
    bt.insert(1000);

    bt.inOrder_print();

    // delete some node
    bt.deleteNode(1);

    bt.inOrder_print();

    // search some node
    cout << "54 was " << (bt.search(54) ? "found" : "not found") << " inside BSTree" << endl;

    return 0;
}
