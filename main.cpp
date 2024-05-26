#include <iostream>
#include <fstream>
#include <vector>
#include <string>


// Класс Node_1 для хранения данных учетных записей
class Node_1 {
public:
    Node_1* next;       // Указатель на следующий узел
    int accountNumber;  // Номер счета
    int password;       // Пароль

    Node_1() : next(nullptr), accountNumber(0), password(0) {}
    Node_1(int a, int p) : next(nullptr), accountNumber(a), password(p) {}
};


// Класс Node для хранения основных данных хеш-таблицы
class Node {
public:
    Node* next;   // Указатель на следующий узел
    Node_1* pre;  // Указатель на связанный узел типа Node_1
    int data;     // Хранимые данные

    Node() : next(nullptr), pre(nullptr), data(0) {}
    Node(int d) : next(nullptr), pre(nullptr), data(d) {}
};


// Класс Hashtable для управления хеш-таблицей
class Hashtable {
public:
    Node* start;    // Начальный узел хеш-таблицы

    Hashtable() : start(nullptr) {}

    // Метод для инициализации хеш-таблицы
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

    // Метод для загрузки данных в хеш-таблицу из файла
    void loadhashtable() {
        int acc = 0, pass;

        std::ifstream read("hashtable.txt");
        while (read >> acc >> pass) {
            if (match(acc, pass)) continue;     // Пропустить дублирующиеся записи

            int r = acc % 10;   // Определение индекса в хеш-таблице
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

    // Метод для добавления новой учетной записи
    void add(int a, int p) {
        std::ofstream write("hashtable.txt", std::ios::app);
        write << a << '\n' << p << '\n';
        starthash();    // Обновление хеш-таблицы
    }

    // Метод для проверки соответствия учетной записи и пароля
    bool match(int a, int p) {
        int r = a % 10;     // Определение индекса в хеш-таблице
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

    // Метод для отображения данных хеш-таблицы
    void display() {
        Node* current = start;
        while (current) {
            std::cout << current->data << '\n';
            current = current->next;
        }
    }

    // Метод для отображения паролей учетных записей
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

    // Метод для удаления учетной записи по номеру счета
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


// Класс BST_Node для узлов бинарного дерева поиска
class BST_Node {
public:
    BST_Node* left;   // Указатель на левый дочерний узел
    BST_Node* right;  // Указатель на правый дочерний узел
    std::string name;  // Имя пользователя
    std::string address;  // Адрес пользователя
    int account_number;  // Номер счета
    int password;  // Пароль
    int balance;  // Баланс

    BST_Node() : left(nullptr), right(nullptr), name(""), address(""), account_number(0), password(0), balance(0) {}
    BST_Node(const std::string& name, const std::string& address, int accountno, int password, int balance)
        : left(nullptr), right(nullptr), name(name), address(address), account_number(accountno), password(password), balance(balance) {}
};


// Класс BST_Tree для управления бинарным деревом поиска
class BST_Tree {
    std::vector<int> v;     // Вектор для временного хранения данных

public:
    BST_Node* Root;     // Корень дерева
    Hashtable h;    // Хеш-таблица для управления учетными записями

    BST_Tree() : Root(nullptr) {}

    // Метод для добавления новой учетной записи в дерево
    void add_Account(const std::string& name, const std::string& address, int accountno, int password, int balance) {
        h.add(accountno, password);     // Добавление данных в хеш-таблицу
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

    // Метод для удаления учетной записи из дерева
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

    // Метод для снятия средств с учетной записи
    void withdraw(int accountno, int amount) {
        load_Server();
        BST_Node* temp = search(Root, accountno);
        if (temp) temp->balance -= amount;
        update_transactions(accountno, -amount);
        update_server(Root);
    }

    // Метод для внесения средств на учетную запись
    void deposit(int accountno, int amount) {
        load_Server();
        BST_Node* temp = search(Root, accountno);
        if (temp) temp->balance += amount;
        update_transactions(accountno, amount);
        update_server(Root);
    }

    // Метод для перевода средств между учетными записями
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

    // Метод для загрузки данных сервера в дерево
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

    // Метод для обновления данных сервера
    void update_server(BST_Node* root) {
        std::ofstream write("server.txt", std::ios::trunc);
        if (root) {
            update_server_helper(root, write);
        }
    }

    // Метод для поиска учетной записи в дереве
    BST_Node* search(BST_Node* root, int accountno) {
        if (!root || root->account_number == accountno) {
            return root;
        }
        if (accountno < root->account_number) {
            return search(root->left, accountno);
        }
        return search(root->right, accountno);
    }

    // Метод для загрузки данных сервера в дерево
    void printoinfo(BST_Node* root) {
        if (root) {
            printoinfo(root->left);
            std::cout << "Name: " << root->name << "\nAddress: " << root->address << "\nAccount Number: " << root->account_number << "\nPassword: " << root->password << "\nBalance: " << root->balance << '\n';
            printoinfo(root->right);
        }
    }

private:
    // Метод для нахождения максимального значения в поддереве
    void findMax(BST_Node* root) {
        while (root) {
            v.push_back(root->account_number);
            root = root->right;
        }
    }
    // Метод для обновления транзакций
    void update_transactions(int accountno, int amount) {
        std::ofstream write("transactions.txt", std::ios::app);
        write << "Account: " << accountno << "\tAmount: " << amount << '\n';
    }
    // Вспомогательный метод для обновления данных сервера
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
