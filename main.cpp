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

public:
    RBTree() {
        this->root = NULL;
    }

    void add(int value) {
        this->root = this->newNode(value);
        this->root->left = this->newNode(150);
        this->root->right = this->newNode(300);
        this->root->right->right = this->newNode(600);
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

    std::cout << "Here are the commands for interact with the Red-Black Tree:" << std::endl;
    std::cout << "[1] to add a number" << std::endl;
    std::cout << "[2] to add in numbers from a file" << std::endl;
    std::cout << "[3] to print the tree" << std::endl;
    std::cout << "[4] to quit" << std::endl;

    while (true) {
        std::cout << "\nPerform a command" << std::endl;

        int cmd_input;
        std::cin >> cmd_input;
        
        if (cmd_input == 1) {
            std::cout << "Enter the number you want to add:" << std::endl;
            
            int input;
            std::cin >> input;
            
            tree->add(input);
            
            std::cout << "Successfully added " << input << std::endl;
        }
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
        else if (cmd_input == 3) {
            tree->print();
        }
        else if (cmd_input == 4) {
            break;
        }
    }

    return 0;
}