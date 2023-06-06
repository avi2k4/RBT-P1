#include <iostream>
#include <fstream>

struct Node {
    int value;
    int color; // 0 = red, 1 = black
    struct Node * parent;
    struct Node * left;
    struct Node * right;
};

class RBTree {
private:
    struct Node * root;

    // Recursive print function to be called by main print function
    void printRecursively(struct Node * current, int spacing) {
        if (current == NULL) {
            return;
        }
        
        this->printRecursively(current->right, spacing + 3);
        
        // Prevents text from condensing
        std::cout << std::endl;

        // Increment till 'spacing' value
        for (int i = 0; i < spacing; i++) {
            std::cout << " ";
        }
        
        std::cout << (current->color == 0 ? "r" : "b") << current->value << std::endl;
        this->printRecursively(current->left, spacing + 3);
    }

    // Utility function to configure a new node to avoid memory leaks
    struct Node * newNode(int value) {
        struct Node * new_node = new Node();
        new_node->value = value;
        // Initially red
        new_node->color = 0;
        new_node->parent = NULL;
        new_node->left = NULL;
        new_node->right = NULL;

        return new_node;
    }

    // Handle left rotation at input node
    void leftRotate(struct Node * node) {
        struct Node * right = node->right;
        node->right = right->left;

        if (node->right != NULL) {
            node->right->parent = node;
        }

        right->parent = node->parent;

        if (node->parent == NULL) {
            this->root = right;
        }
        else if (node == node->parent->left) {
            node->parent->left = right;
        }
        else {
            node->parent->right = right;
        }

        right->left = node;
        node->parent = right;
    }

    // Handle right rotation at input node
    void rightRotate(struct Node * node) {
        struct Node * left = node->left;
        node->left = left->right;

        if (node->left != NULL) {
            node->left->parent = node;
        }

        left->parent = node->parent;

        if (node->parent == NULL) {
            this->root = left;
        }
        else if (node == node->parent->left) {
            node->parent->left = left;
        }
        else {
            node->parent->right = left;
        }

        left->right = node;
        node->parent = left;
    }

    void swapColors(int & a, int & b) {
        int temp = a;
        a = b;
        b = temp;
    }

    // Fixes the tree after insertion
    void fix(struct Node * node) {
        struct Node * parent = NULL;
        struct Node * grandparent = NULL;
    
        while (node != this->root && node->color != 1 && node->parent->color == 0) {
            parent = node->parent;
            grandparent = parent->parent;

            // Parent of node is left child of grandparent of node
            if (parent == grandparent->left) {
                struct Node * uncle = grandparent->right;

                // Uncle of node is also red, so only fix colors
                if (uncle != NULL && uncle->color == 0) {
                    grandparent->color = 0;
                    parent->color = 1;
                    uncle->color = 1;
                    node = grandparent;
                }
                else {
                    // Node is right child of its parent, so do left rotation
                    if (node == parent->right) {
                        leftRotate(parent);
                        node = parent;
                        parent = node->parent;
                    }

                    // Node is left child of its parenr so right rotation required
                    rightRotate(grandparent);
                    swapColors(parent->color, grandparent->color);
                    node = parent;
                }
            }
            // Parent of node is right child of grandparent of node 
            else {
                struct Node * uncle = grandparent->left;

                // Uncle of node is also red, so only fix colors
                if (uncle != NULL && uncle->color == 0) {
                    grandparent->color = 0;
                    parent->color = 1;
                    uncle->color = 1;
                    node = grandparent;
                }
                else {
                    // Node is left child of its parent, so do right rotation
                    if (node == parent->left) {
                        rightRotate(parent);
                        node = parent;
                        parent = node->parent;
                    }

                    // Node is right child of its parent, so do left rotation
                    leftRotate(grandparent);
                    swapColors(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }

        // Set root to black
        this->root->color = 1;
    }

public:
    RBTree() {
        this->root = NULL;
    }

    void add(int value) {
        struct Node * new_node = this->newNode(value);
        
        // If root doesn't exist then new_node is new root
        if (this->root == NULL) {
            // Because is root, color is black
            new_node->color = 1;
            this->root = new_node;
            return;
        }
        
        struct Node * current = this->root;
        while (true) {
            // If value to the right is greater, then look at left
            if (current->value > value) {
                if (current->left != NULL) {
                    current = current->left;
                }
                // Can end loop early because spot is found
                else {
                    current->left = new_node;
                    break;
                }
            }
            else {
                if (current->right != NULL) {
                    current = current->right;
                }
                // Can end loop early because spot is found
                else {
                    current->right = new_node;
                    break;
                }
            }
        }

        new_node->parent = current;

        // If the parent is NULL then is root
        if (new_node->parent == NULL) {
            new_node->color = 1;
            return;
        }

        // If the grandparent is null, exit
        if (new_node->parent->parent == NULL) {
            return;
        }

        this->fix(new_node);
    }

    void print() {
        if (this->root == NULL) {
            std::cout << "Tree is empty!" << std::endl;
            return;
        }
        
        this->printRecursively(this->root, 0);
    }
};

int main() {
    RBTree * tree = new RBTree();

    // Commands
    std::cout << "Here are the commands for interact with the Red-Black Tree:" << std::endl;
    std::cout << "[1] to add a number" << std::endl;
    std::cout << "[2] to add in numbers from a file" << std::endl;
    std::cout << "[3] to print the tree" << std::endl;
    std::cout << "[4] to quit" << std::endl;

    while (true) {
        std::cout << "\nPerform a command" << std::endl;

        int cmd_input;
        std::cin >> cmd_input;
        
        // Insert 1 number from console
        if (cmd_input == 1) {
            std::cout << "Enter the number you want to add:" << std::endl;
            
            int input;
            std::cin >> input;
            
            tree->add(input);
            
            std::cout << "Successfully added " << input << std::endl;
        }
        // Insert from file
        else if (cmd_input == 2) {
            std::cout << "Enter the name of the file" << std::endl;

            char file_name[100];
            std::cin >> file_name;
            
            std::ifstream file_input(file_name);
            
            if (!file_input) {
                std::cout << "File doesn't exit. Exiting." << std::endl;
                return 1;
            }
            
            int num_input;
            while (file_input >> num_input) {
                tree->add(num_input);
            }
            
            file_input.close();
        }
        // Print
        else if (cmd_input == 3) {
            tree->print();
        }
        // Quit
        else if (cmd_input == 4) {
            break;
        }
    }

    return 0;
}