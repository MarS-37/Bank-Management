#include <iostream>
#include <fstream>
#include <string>
#include <vector>


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


class Node
{
public:
	Node()
	{
		// двунаправленный узел, указателя на следующий и предыдущий узел.
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


class Hashtable
{
public:	
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

	Node* start;
};


void boot()
{
	Hashtable H;
}


int main()
{
	int condition = 0;

	while (condition != 4) {
		std::cout << "YOU want to login as:\t\t\t\t\t\t" << std::endl << std::endl;
		std::cout << "1-ADMIN" << std::endl;
		std::cout << "2-STAFF" << std::endl;
		std::cout << "3-CUSTOMER" << std::endl;
		std::cin >> condition;

		if (condition == 1) {
		
		}
		if (condition == 2) {

		}
		if (condition == 3) {

		}
		if (condition == 4) {

		}
	}


	std::cin.get();
	return 0;
}