#include <iostream>
#include <vector>

// one node of thetree
struct Node {
int key;
 Node* left;    // smaller keys
    Node* right;   //bigger keys

    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

      class BinarySearchTree { public:
 BinarySearchTree() : root(nullptr), count(0) {}   // start empty
   ~BinarySearchTree() { destroy(root); }   // free all nodes

    // no copying, two trees would delete the same nodes
    BinarySearchTree(const BinarySearchTree&) = delete;
BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    // true if added, false if duplicate
    bool insert(int key) {
        bool added = false;
    root = insert(root, key, added);
        if (added) count++;
    return added;
    }
    bool search(int key) const {
    const Node* current = root;   // start at the top
        while (current != nullptr) {
        if (key == current->key) return true;
 current = (key < current->key) ? current->left : current->right;   // go left or right
        }
        return false;   // fell off the tree
    }
    // true if removed, false if not found
    bool remove(int key) {
bool removed = false;
    root = remove(root, key, removed);
        if (removed) count--;
return removed;
    }



    // height in edges: empty = -1, one node = 0
    int height() const { return height(root); }

int size() const { return count; }
    bool isEmpty() const { return root == nullptr; }

 void printInorder() const   { inorder(root);   std::cout << "\n"; }
    void printPreorder() const  { preorder(root);  std::cout << "\n"; }
void printPostorder() const { postorder(root); std::cout << "\n"; }

    // checks that inorder really comes out sorted
bool inorderIsSorted() const {
        std::vector<int> keys;
collectInorder(root, keys);
        for (std::size_t i = 1; i < keys.size(); i++) {
            if (keys[i - 1] >= keys[i]) return false;   // out of order
        }
        return true;
    }
private:
    Node* root;
int count;   // how many keys are stored

    Node* insert(Node* node, int key, bool& added) {
if (node == nullptr) {   // empty spot, put it here
        added = true;
    return new Node(key);
        }
    if (key < node->key) {
node->left = insert(node->left, key, added);
        } else if (key > node->key) {
     node->right = insert(node->right, key, added);
       }
        return node;   // equal key = duplicate, nothing changes
    }

    Node* remove(Node* node, int key, bool& removed) {
        if (node == nullptr) return nullptr;   // not in the tree

    if (key < node->key) {
node->left = remove(node->left, key, removed);
} else if (key > node->key) {
node->right = remove(node->right, key, removed);
} else {
            removed = true;   // found it

// leaf or one child: the other child moves up
if (node->left == nullptr) {
         Node* child = node->right;
            delete node;
        return child;
            }
     if (node->right == nullptr) {
         Node* child = node->left;
    delete node;
    return child;
            }
            // two children: copy the successor in, then delete it
Node* successor = findMin(node->right);
        node->key = successor->key;
    bool ignored = false;
    node->right = remove(node->right, successor->key, ignored);
    }
        return node;
    }

    // smallest key means keep going left
Node* findMin(Node* node) const {
             while (node->left != nullptr) node = node->left;
        return node;
    }

int height(const Node* node) const {
     if (node == nullptr) return -1;
        int leftHeight = height(node->left);
         int rightHeight = height(node->right);
     return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);   // taller side + 1
    }

// leftnode, right
    void inorder(const Node* node) const {
        if (node == nullptr) return;
    inorder(node->left);
        std::cout << node->key << " ";
    inorder(node->right);
    }

    // nodeleft right
    void preorder(const Node* node) const {
        if (node == nullptr) return;
    std::cout << node->key << " ";
preorder(node->left);
        preorder(node->right);
    }

    //left rightnode
    void postorder(const Node* node) const {
if (node == nullptr) return;
        postorder(node->left);
postorder(node->right);
        std::cout << node->key << " ";
    }

    // same as inorder butsaves the keys instead of printing it
    void collectInorder(const Node* node, std::vector<int>& keys) const {
if (node == nullptr) return;
       collectInorder(node->left, keys);
        keys.push_back(node->key);
    collectInorder(node->right, keys);
    }

    void destroy(Node* node) {
    if (node == nullptr) return;
        destroy(node->left);    // children first
destroy(node->right);
 delete node;            // then the node itself
    }
};

// prints the result of one search
void showSearch(const BinarySearchTree& tree, int key) {
    std::cout << "search(" << key << "): "
    << (tree.search(key) ? "FOUND" : "NOT FOUND") << "\n";
}

// removes a key and prints the tree after
void showRemove(BinarySearchTree& tree, int key, const char* label) {
    std::cout << "\nremove(" << key << ") - " << label << "\n";
bool removed = tree.remove(key);
    std::cout << "  removed:     " << (removed ? "yes" : "no") << "\n";
    std::cout << "  inorder:      ";
    tree.printInorder();
    std::cout << "  still sorted:   " << (tree.inorderIsSorted() ? "yes" : "NO") << "\n";
std::cout << "  size / height:  " << tree.size() << " / " << tree.height() << "\n";
}

int main() {
    BinarySearchTree tree;

    std::cout << "=== Empty tree ===\n";
    std::cout << "isEmpty: " << (tree.isEmpty() ? "yes" : "no")
        << ", size: " << tree.size()
            << ", height: " << tree.height() << "\n";

       std::cout << "\n=== Insert 12 distinct integers ===\n";
    int keys[] = {50, 30, 70, 20, 40, 60, 80, 10, 35, 45, 65, 90};
    std::cout << "insert order: ";
    for (int key : keys) {
        tree.insert(key);
        std::cout << key << " ";
    }
        std::cout << "\nsize: " << tree.size() << ", height: " << tree.height() << "\n";

    // duplicate should be rejected
    std::cout << "\ninsert(40) again (duplicate): "
    << (tree.insert(40) ? "  added" : "rejected")
        << ",  size is still " << tree.size() << "\n";

       std::cout << "\n=== Traversals ===\n";
    std::cout << "  inorder:   "; tree.printInorder();
      std::cout << "   preorder:  "; tree.printPreorder();
    std::cout << " postorder: "; tree.printPostorder();

    std::cout << "\n===   Search ===\n";
    showSearch(tree, 65);   // in the tree
      showSearch(tree, 55);   // not in the tree

    std::cout << "\n=== Removal ===";
       showRemove(tree, 10, "Case 1: leaf");
           showRemove(tree, 60, "Case   2: one child (65)");
      showRemove(tree, 30, "Case 3: two.  children (20 and 40). ");
      showRemove(tree, 50, "Case 3 again: the root");
       showRemove(tree, 99, "key that is not in the tree");

      std::cout << "\n=== Final tree ===\n";
    std::cout << "inorder: "; tree.printInorder();
      std::cout << "preorder:"; tree.printPreorder();
    std::cout << "postorder "; tree.printPostorder();

    std::cout << "\n=== Worst case: keys inserted in sorted order ===\n";
        BinarySearchTree chain;
    for (int key = 1; key <= 10; key++) chain.insert(key);
       std::cout << "   10 keys inserted as 1..10 -> height " << chain.height()
              << " ( the tree is one long chain)\n";

    return 0;
}