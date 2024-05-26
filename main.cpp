#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <string>


class Node
{
public:	
	Node()
	{
		next = nullptr;
		pre = nullptr;
		data = 0;
	}
	Node(int d)
	{
		next = nullptr;
		pre = nullptr;
		data = d;
	}

	Node* next;
	Node_1* pre;
	int data;
};


class Node_1
{
public:
	Node_1()
	{
		next = nullptr;
		accountNumber = 0;
		password = 0;
	}
	Node_1(int a, int p)
	{
		next = nullptr;
		accountNumber = a;
		password = p;
	}

	Node_1* next;
	int accountNumber;
	int password;
};


class Hashtable
{
public:
	Node* start;

	Hashtable()
	{
		start = nullptr;
	}
	void starthash()
	{
		for (int i = 0; i < 12; i++)
		{
			Node* temp1 = new Node(i);
			if (start == nullptr)
			{
				start = temp1;
			}
			else
			{
				Node* current = start;
				while (current->next != nullptr)
				{
					current = current->next;
				}
				current->next = temp1;
			}
		}
		loadhashtable();
	}
	void loadhashtable()
	{
		int acc = 0, r, pass;

		std::ifstream read;
		read.open("hashtable.txt");
		while (!read.eof())
		{

			read >> acc;
			read >> pass;
			if (match(acc, pass))
			{
				continue;
			}
			if (acc != -858993460 && pass != -858993460)
			{
				r = acc % 10;

				Node* c = start;
				while (c->data != r)
				{
					c = c->next;
				}
				Node_1* temp = new Node_1(acc, pass);
				if (c->pre == nullptr)
				{
					c->pre = temp;
				}
				else
				{
					Node_1* root;
					root = c->pre;
					while (root->next != nullptr)
					{
						root = root->next;
					}
					root->next = temp;
				}
			}
			else
			{
				std::cout << "NO password present" << std::endl;
			}
		}
		read.close();
	}
	void add(int a, int p)
	{
		static int i = 0;
		std::ofstream write;
		write.open("hashtable.txt", std::ios::app);
		if (i != 0)
		{
			write << std::endl;
			write << a << std::endl << p;
		}
		else
		{
			i++;
			write << a << std::endl << p;
		}
		write.close();

		starthash();
	}
	bool match(int a, int p)
	{
		bool flag = false;
		int r = a % 10;
		Node* c = start;
		while (c->data != r)
		{
			c = c->next;
		}
		Node_1* c1 = c->pre;
		while (c1 != nullptr)
		{
			if (c1->accountNumber == a && c1->password == p)
			{
				flag = true;
				break;
			}
			c1 = c1->next;
		}
		return flag;
	}
	void display()
	{
		Node* current = start;
		while (current != nullptr)
		{
			std::cout << current->data << std::endl;
			current = current->next;
		}
	}
	void displayPasswords()
	{
		starthash();
		Node* c = start;
		while (c != nullptr)
		{
			Node_1* c1 = c->pre;
			while (c1 != nullptr)
			{
				std::cout << c1->accountNumber << std::endl;
				std::cout << c1->password << std::endl << std::endl;
				c1 = c1->next;
			}
			c = c->next;
		}
	}
	void delete_password(int accountno)
	{
		std::ifstream read;
		read.open("hashtable.txt");
		std::vector <int> v;
		int acc = 0, pass = 0;
		int i = 0;
		while (!read.eof())
		{
			i++;
			read >> acc;
			read >> pass;
			if (acc == accountno)
			{
				continue;
			}
			v.push_back(acc);
			v.push_back(pass);
		}
		read.close();
		std::ofstream write;
		write.open("temp.txt", std::ios::app);

		for (int i = 0; i < v.size(); i++)
		{
			if (v[i] != 0)
			{
				write << v[i] << std::endl;
			}
		}


		write.close();
		remove("hashtable.txt");
		rename("temp.txt", "hashtable.txt");
	}
};


class BST_Node
{
public:
	BST_Node* left;
	BST_Node* right;
	std::string name;
	std::string adress;
	int account_number;
	int password;
	int balance;

	BST_Node()
	{
		left = nullptr;
		right = nullptr;
		name = "";
		adress = "";
		account_number = 0;
		password = 0;
		balance = 0;
	}
	BST_Node(std::string name, std::string adress, int accountno, int password, int balance)
	{
		left = nullptr;
		right = nullptr;
		this->name = name;
		this->account_number = accountno;
		this->adress = adress;
		this->balance = balance;
		this->password = password;
	}
};


class BST_Tree
{
	std::vector <int> v;

public:
	BST_Tree() {

	}	
	void add_Account(std::string name, std::string adress, int accountno, int password, int balance)
	{
		h.add(accountno, password);
		std::ofstream write;
		write.open("server.txt", std::ios::app);
		write << name << std::endl << adress << std::endl << accountno << std::endl << password << std::endl << balance << std::endl;
		write.close();
		BST_Node* temp = new BST_Node(name, adress, accountno, password, balance);

		BST_Node* current = Root;
		if (Root == nullptr)
		{
			Root = temp;
		}
		else
		{
			while (true)
			{
				if (accountno < current->account_number)
				{
					if (current->left == nullptr)
					{
						current->left = temp;
						break;
					}
					current = current->left;
				}

				if (accountno > current->account_number)
				{
					if (current->right == nullptr)
					{
						current->right = temp;
						break;
					}
					current = current->right;
				}
			}
		}
	}
	BST_Node* delete_Account(BST_Node* root, int accountno)
	{
		//cout << "accountno"<<root->account_number;
		if (root == nullptr)
			std::cout << "it seems that Tree is empty OR You have entered wrong data" << std::endl;
		else if (accountno < root->account_number)
			root->left = delete_Account(root->left, accountno);
		else if (accountno > Root->account_number)
			root->right = delete_Account(root->right, accountno);
		else
		{
			if (root->left && root->right)
			{
				findMax(root->left);
				root->account_number = v.back();
				root->left = delete_Account(root->left, root->account_number);
			}
			else
			{
				std::cout << "aya" << std::endl;
				BST_Node* temp = root;
				if (root->left == nullptr)
					root = root->right;
				else if (root->right == nullptr)
					root = root->left;
				delete temp;
			}
		}
		return(root);
	}
	void withdraw(int accountno, int amount)
	{
		load_Server();
		BST_Node* temp = search(Root, accountno);
		temp->balance = temp->balance - amount;
		std::vector <int> data;
		std::ifstream read;
		read.open("transaction.txt", std::ios::app);
		int line = 0;
		while (!read.eof())
		{
			read >> line;
			if (line == accountno)
			{
				data.push_back(line);
				line = (amount * -1);
				data.push_back(line);
				continue;
			}
			data.push_back(line);
		}
		read.close();

		std::ofstream write;
		write.open("temp.txt", std::ios::app);
		for (int i = 0; i < data.size(); i++)
		{
			write << data[i] << std::endl;
		}
		write.close();
		remove("transaction.txt");
		rename("temp.txt", "transaction.txt");

		update_server(Root);
	}
	void deposit(int accountno, int amount)
	{
		load_Server();
		BST_Node* temp = search(Root, accountno);
		temp->balance = temp->balance + amount;

		std::vector <int> data;
		std::ifstream read;
		read.open("transaction.txt", std::ios::app);
		int line = 0;
		while (!read.eof())
		{
			read >> line;
			if (line == accountno)
			{
				data.push_back(line);
				line = amount;
				data.push_back(line);
				continue;
			}
			data.push_back(line);
		}
		read.close();

		std::ofstream write;
		write.open("temp.txt", std::ios::app);
		for (int i = 0; i < data.size(); i++)
		{
			write << data[i] << std::endl;
		}
		write.close();
		remove("transaction.txt");
		rename("temp.txt", "transaction.txt");


		update_server(Root);
	}
	void editaccount_byAdmin()
	{

	}
	void transfer(int sender_accountno, int reciever_accountno, int sender_amount)
	{
		BST_Node* sender = search(Root, sender_accountno);
		sender->balance = sender->balance - sender_amount;
		BST_Node* reciever = search(Root, reciever_accountno);
		reciever->balance = reciever->balance + sender_amount;
		update_server(Root);

		std::vector <int> data;
		std::ifstream read;
		read.open("transaction.txt", std::ios::app);
		int line = 0;
		while (!read.eof())
		{
			read >> line;
			if (line == sender_accountno)
			{
				data.push_back(line);
				line = (sender_amount * -1);
				data.push_back(line);
				continue;
			}
			data.push_back(line);
		}
		read.close();

		std::ofstream write;
		write.open("temp.txt", std::ios::app);
		for (int i = 0; i < data.size(); i++)
		{
			write << data[i] << std::endl;
		}
		write.close();
		remove("transaction.txt");
		rename("temp.txt", "transaction.txt");

		std::vector <int> data;
		std::ifstream read;
		read.open("transaction.txt", std::ios::app);
		int line = 0;
		while (!read.eof())
		{
			read >> line;
			if (line == reciever_accountno)
			{
				data.push_back(line);
				line = sender_amount;
				data.push_back(line);
				continue;
			}
			data.push_back(line);
		}
		read.close();

		std::ofstream write;
		write.open("temp.txt", std::ios::app);
		for (int i = 0; i < data.size(); i++)
		{
			write << data[i] << std::endl;
		}
		write.close();
		remove("transaction.txt");
		rename("temp.txt", "transaction.txt");
	}
	void transaction_history()
	{

	}
	void findMax(BST_Node* root)
	{
		if (root)
		{
			findMax(root->left);
			v.push_back(root->account_number);
			findMax(root->right);
		}
	}
	void load_Server()
	{
		std::ifstream read;
		read.open("server.txt", std::ios::app);

		std::string name = "";
		std::string adress = "";
		int accountno = 0;
		int password = 0;
		int balance = 0;
		//cin.ignore();
		while (!read.eof())
		{



			getline(read, name);
			getline(read, adress);
			read >> accountno;
			read >> password;
			read >> balance;
			read.ignore();
			read.ignore();
			/*
					cout << name << endl;
					cout << adress << endl;
					cout << accountno << endl;
					cout << password << endl;
					cout << balance << endl;

					*/
			if (name != "" && adress != "" && accountno != 0 && password != 0)
			{
				//cout << "enter hua" << endl;
				BST_Node* temp = new BST_Node(name, adress, accountno, password, balance);
				BST_Node* current = Root;
				if (Root == nullptr)
				{

					Root = temp;
				}
				else
				{
					while (true)
					{

						if (accountno < current->account_number)
						{
							if (current->left == nullptr)
							{
								current->left = temp;
								break;
							}
							current = current->left;
						}

						if (accountno > current->account_number)
						{
							if (current->right == nullptr)
							{
								current->right = temp;
								break;
							}
							current = current->right;
						}
						if (accountno == current->account_number)
						{
							break;
						}
					}
				}
			}
		}
		read.close();
	}
	void update_server(BST_Node* root)
	{
		static int i = 0;
		if (i == 0)
		{
			i++;
			remove("server.txt");
		}
		std::ofstream write;
		write.open("server.txt");
		if (root)
		{
			update_server(root->left);
			write << root->name << std::endl;
			write << root->adress << std::endl;
			write << root->account_number << std::endl;
			write << root->password << std::endl;
			write << root->balance << std::endl;
			update_server(root->right);
		}
		write.close();
	}
	BST_Node* search(BST_Node* root, int accountno)
	{
		if (root == nullptr)
			return (nullptr);
		else if (accountno < root->account_number)
			return (search(root->left, accountno));
		else if (accountno > root->account_number)
			return (search(root->right, accountno));
		return (root);

	}
	void printoinfo(BST_Node* root)
	{
		if (root)
		{
			printoinfo(root->left);
			std::cout << root->name << std::endl;
			std::cout << root->adress << std::endl;
			std::cout << root->account_number << std::endl;
			std::cout << root->password << std::endl;
			std::cout << root->balance << std::endl;
			printoinfo(root->right);
		}
	}

	BST_Node* Root;
	Hashtable h;
};


void admin()
{
	BST_Tree t;
	Hashtable h;
	int condition = 0;
	while (condition != 6)
	{
		std::cout << "welcome ADMIN" << std::endl;
		std::cout << "choose the following please" << std::endl;
		std::cout << "press 1 to add account " << std::endl;
		std::cout << "press 2 to delete account " << std::endl;
		std::cout << "press 3 to check all account " << std::endl;
		std::cout << "press 4 to see password of account " << std::endl;
		std::cout << "press 5 to edit account " << std::endl;
		std::cout << "press 6 to exit" << std::endl;
		std::cin >> condition;
		if (condition == 1)
		{
			std::string n = "", a = "";
			int acc, p, b;
			std::cout << "enter name" << std::endl;
			std::cin >> n;
			std::cout << "enter adress" << std::endl;
			std::cin >> a;
			std::cout << "enter account number" << std::endl;
			std::cin >> acc;
			std::cout << "enter password" << std::endl;
			std::cin >> p;
			std::cout << "enter balance" << std::endl;
			std::cin >> b;
			t.add_Account(n, a, acc, p, b);
		}
		if (condition == 2)
		{
			int acc = 0;
			std::cout << "enter account number" << std::endl;
			std::cin >> acc;
			t.load_Server();
			t.Root = t.delete_Account(t.Root, acc);
			std::cout << "bar a gia delete se" << std::endl;
			h.delete_password(acc);
			std::cout << "delete pass" << std::endl;
			t.update_server(t.Root);
			std::cout << "update h gia" << std::endl;
		}
		if (condition == 3)
		{
			t.load_Server();
			t.printoinfo(t.Root);
		}
		if (condition == 4)
		{
			h.displayPasswords();
		}
		if (condition == 5)
		{

		}
		if (condition == 6)
		{
			condition = 6;
		}
	}
}


void staff()
{
	BST_Tree t;
	Hashtable h;
	int condition = 0;
	while (condition != 5)
	{
		std::cout << "welcome STAFF" << std::endl;
		std::cout << "choose the following please" << std::endl;
		std::cout << "press 1 to see transaction history  " << std::endl;
		std::cout << "press 2 to transfer " << std::endl;
		std::cout << "press 3 to withdraw " << std::endl;
		std::cout << "press 4 to deposit " << std::endl;
		std::cout << "press 5 to exit" << std::endl;
		std::cin >> condition;
		if (condition == 1)
		{
			// transaction file print karani ha account search kr k
		}
		if (condition == 2)
		{
			int senderaccountno = 0, amount = 0, recieveraccountno = 0;
			std::cout << "please enter  sender account number" << std::endl;
			std::cin >> senderaccountno;
			std::cout << "please enter  receiver account number" << std::endl;
			std::cin >> recieveraccountno;
			std::cout << "please enter amount" << std::endl;
			std::cin >> amount;
			t.transfer(senderaccountno, amount, recieveraccountno);
		}
		if (condition == 3)  // withdraw
		{
			int accountno = 0, amount = 0;
			std::cout << "please enter account number" << std::endl;
			std::cin >> accountno;
			std::cout << "please enter amount" << std::endl;
			std::cin >> amount;
			t.withdraw(accountno, amount);
		}
		if (condition == 4)
		{
			int accountno = 0, amount = 0;
			std::cout << "please enter account number" << std::endl;
			std::cin >> accountno;
			std::cout << "please enter amount" << std::endl;
			std::cin >> amount;
			t.deposit(accountno, amount);
		}
		if (condition == 5)
		{
			condition = 5;
		}
	}
}


void customer()
{
	BST_Tree t;
	Hashtable h;
	int condition = 0;
	while (condition != 3)
	{
		std::cout << "welcome CUSTOMER" << std::endl;
		std::cout << "choose the following please" << std::endl;
		std::cout << "press 1 to see account details" << std::endl;
		std::cout << "press 2 to see transaction history  " << std::endl;
		std::cout << "press 3 to exit" << std::endl;
		std::cin >> condition;
		if (condition == 1)
		{
			int accountno;
			std::cout << "please enter account number" << std::endl;
			std::cin >> accountno;
			BST_Node* temp = t.search(t.Root, accountno);
			std::cout << "Account Details Are :\t\t\t\t\t\t " << std::endl << std::endl;
			std::cout << "NAME :" << temp->name << std::endl;
			std::cout << "ADRESS :" << temp->adress << std::endl;
			std::cout << "ACCOUNT NUMBER :" << temp->account_number << std::endl;
			std::cout << "PASSWORD :" << temp->password << std::endl;
			std::cout << "BALANCE :" << temp->balance << std::endl;
		}
		if (condition == 2)
		{
			// transaction file print karani ha account search kr k
		}
		if (condition == 3)
		{
			condition = 3;
		}
	}
}


void boot()
{
	Hashtable H;
	BST_Tree T;
	H.starthash();
	T.load_Server();
}


int main()
{
	void boot();

	int condition = 0;
	while (condition != 4)
	{
		std::cout << "YOU want to login as:\t\t\t\t\t\t" << std::endl << std::endl;
		std::cout << "1-ADMIN" << std::endl;
		std::cout << "2-STAFF" << std::endl;
		std::cout << "3-CUSTOMER" << std::endl;
		std::cin >> condition;
		if (condition == 1)
		{
			admin();
		}
		if (condition == 2)
		{

		}
		if (condition == 3)
		{
			customer();
		}
		if (condition == 4)
		{
			condition = 4;
		}
	}


	system("pause");
	return 0;
}