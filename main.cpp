#include <iostream>
#include <fstream>

struct Node {
    int data;
    int color; // 0 = red, 1 = black
    struct Node * parent;
    struct Node * left;
    struct Node * right;
};

class RBTree {
private:
    struct Node * root;

public:
    RBTree() {
        this->root = NULL;
    }

    void add(int value) {

    }

    void print() {

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