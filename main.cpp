#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class Node_1; // Forward declaration

class Node {
public:
    Node* next;
    Node_1* pre;
    int data;

    Node() : next(nullptr), pre(nullptr), data(0) {}
    Node(int d) : next(nullptr), pre(nullptr), data(d) {}
};

class Node_1 {
public:
    Node_1* next;
    int accountNumber;
    int password;

    Node_1() : next(nullptr), accountNumber(0), password(0) {}
    Node_1(int a, int p) : next(nullptr), accountNumber(a), password(p) {}
};

class Hashtable {
public:
    Node* start;

    Hashtable() : start(nullptr) {}

    void starthash() {
        for (int i = 0; i < 12; i++) {
            Node* temp1 = new Node(i);
            if (!start) {
                start = temp1;
            }
            else {
                Node* current = start;
                while (current->next) {
                    current = current->next;
                }
                current->next = temp1;
            }
        }
        loadhashtable();
    }

    void loadhashtable() {
        int acc = 0, pass;

        std::ifstream read("hashtable.txt");
        while (read >> acc >> pass) {
            if (match(acc, pass)) continue;

            int r = acc % 10;
            Node* c = start;
            while (c->data != r) {
                c = c->next;
            }

            Node_1* temp = new Node_1(acc, pass);
            if (!c->pre) {
                c->pre = temp;
            }
            else {
                Node_1* root = c->pre;
                while (root->next) {
                    root = root->next;
                }
                root->next = temp;
            }
        }
    }

    void add(int a, int p) {
        std::ofstream write("hashtable.txt", std::ios::app);
        write << a << '\n' << p << '\n';
        starthash();
    }

    bool match(int a, int p) {
        int r = a % 10;
        Node* c = start;
        while (c->data != r) {
            c = c->next;
        }

        Node_1* c1 = c->pre;
        while (c1) {
            if (c1->accountNumber == a && c1->password == p) {
                return true;
            }
            c1 = c1->next;
        }
        return false;
    }

    void display() {
        Node* current = start;
        while (current) {
            std::cout << current->data << '\n';
            current = current->next;
        }
    }

    void displayPasswords() {
        starthash();
        Node* c = start;
        while (c) {
            Node_1* c1 = c->pre;
            while (c1) {
                std::cout << c1->accountNumber << '\n' << c1->password << '\n';
                c1 = c1->next;
            }
            c = c->next;
        }
    }

    void delete_password(int accountno) {
        std::ifstream read("hashtable.txt");
        std::vector<int> v;
        int acc = 0, pass = 0;

        while (read >> acc >> pass) {
            if (acc == accountno) continue;
            v.push_back(acc);
            v.push_back(pass);
        }

        std::ofstream write("hashtable.txt", std::ios::trunc);
        for (size_t i = 0; i < v.size(); i += 2) {
            write << v[i] << '\n' << v[i + 1] << '\n';
        }
    }
};

class BST_Node {
public:
    BST_Node* left;
    BST_Node* right;
    std::string name;
    std::string address;
    int account_number;
    int password;
    int balance;

    BST_Node() : left(nullptr), right(nullptr), name(""), address(""), account_number(0), password(0), balance(0) {}
    BST_Node(const std::string& name, const std::string& address, int accountno, int password, int balance)
        : left(nullptr), right(nullptr), name(name), address(address), account_number(accountno), password(password), balance(balance) {}
};

class BST_Tree {
    std::vector<int> v;

public:
    BST_Node* Root;
    Hashtable h;

    BST_Tree() : Root(nullptr) {}

    void add_Account(const std::string& name, const std::string& address, int accountno, int password, int balance) {
        h.add(accountno, password);
        std::ofstream write("server.txt", std::ios::app);
        write << name << '\n' << address << '\n' << accountno << '\n' << password << '\n' << balance << '\n';

        BST_Node* temp = new BST_Node(name, address, accountno, password, balance);
        if (!Root) {
            Root = temp;
        }
        else {
            BST_Node* current = Root;
            while (true) {
                if (accountno < current->account_number) {
                    if (!current->left) {
                        current->left = temp;
                        break;
                    }
                    current = current->left;
                }
                else if (accountno > current->account_number) {
                    if (!current->right) {
                        current->right = temp;
                        break;
                    }
                    current = current->right;
                }
            }
        }
    }

    BST_Node* delete_Account(BST_Node* root, int accountno) {
        if (!root) {
            std::cout << "Tree is empty or account not found.\n";
            return nullptr;
        }

        if (accountno < root->account_number) {
            root->left = delete_Account(root->left, accountno);
        }
        else if (accountno > root->account_number) {
            root->right = delete_Account(root->right, accountno);
        }
        else {
            if (root->left && root->right) {
                findMax(root->left);
                root->account_number = v.back();
                root->left = delete_Account(root->left, root->account_number);
            }
            else {
                BST_Node* temp = root;
                root = (root->left) ? root->left : root->right;
                delete temp;
            }
        }
        return root;
    }

    void withdraw(int accountno, int amount) {
        load_Server();
        BST_Node* temp = search(Root, accountno);
        if (temp) temp->balance -= amount;
        update_transactions(accountno, -amount);
        update_server(Root);
    }

    void deposit(int accountno, int amount) {
        load_Server();
        BST_Node* temp = search(Root, accountno);
        if (temp) temp->balance += amount;
        update_transactions(accountno, amount);
        update_server(Root);
    }

    void transfer(int sender_accountno, int reciever_accountno, int sender_amount) {
        load_Server();
        BST_Node* sender = search(Root, sender_accountno);
        BST_Node* receiver = search(Root, reciever_accountno);

        if (sender && receiver) {
            sender->balance -= sender_amount;
            receiver->balance += sender_amount;
            update_server(Root);

            update_transactions(sender_accountno, -sender_amount);
            update_transactions(reciever_accountno, sender_amount);
        }
    }

    void load_Server() {
        std::ifstream read("server.txt");
        std::string name, address;
        int accountno, password, balance;

        while (read >> name >> address >> accountno >> password >> balance) {
            BST_Node* temp = new BST_Node(name, address, accountno, password, balance);
            if (!Root) {
                Root = temp;
            }
            else {
                BST_Node* current = Root;
                while (true) {
                    if (accountno < current->account_number) {
                        if (!current->left) {
                            current->left = temp;
                            break;
                        }
                        current = current->left;
                    }
                    else if (accountno > current->account_number) {
                        if (!current->right) {
                            current->right = temp;
                            break;
                        }
                        current = current->right;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }

    void update_server(BST_Node* root) {
        std::ofstream write("server.txt", std::ios::trunc);
        if (root) {
            update_server_helper(root, write);
        }
    }

    BST_Node* search(BST_Node* root, int accountno) {
        if (!root || root->account_number == accountno) {
            return root;
        }
        if (accountno < root->account_number) {
            return search(root->left, accountno);
        }
        return search(root->right, accountno);
    }

    void printoinfo(BST_Node* root) {
        if (root) {
            printoinfo(root->left);
            std::cout << "Name: " << root->name << "\nAddress: " << root->address << "\nAccount Number: " << root->account_number << "\nPassword: " << root->password << "\nBalance: " << root->balance << '\n';
            printoinfo(root->right);
        }
    }

private:
    void findMax(BST_Node* root) {
        while (root) {
            v.push_back(root->account_number);
            root = root->right;
        }
    }

    void update_transactions(int accountno, int amount) {
        std::ofstream write("transactions.txt", std::ios::app);
        write << "Account: " << accountno << "\tAmount: " << amount << '\n';
    }

    void update_server_helper(BST_Node* root, std::ofstream& write) {
        if (root) {
            write << root->name << '\n' << root->address << '\n' << root->account_number << '\n' << root->password << '\n' << root->balance << '\n';
            update_server_helper(root->left, write);
            update_server_helper(root->right, write);
        }
    }
};

int main() {
    // Example usage
    BST_Tree bank;
    bank.add_Account("Alice", "123 Main St", 1001, 1234, 500);
    bank.add_Account("Bob", "456 Oak Ave", 1002, 5678, 1000);
    bank.withdraw(1001, 100);
    bank.deposit(1002, 200);
    bank.transfer(1001, 1002, 50);

    bank.printoinfo(bank.Root);
    return 0;
}
