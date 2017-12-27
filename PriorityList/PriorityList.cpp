/* ������ 9:
����������� ������ � ����������� PriorityList<X,Y>, ��� X - ��� ���������, Y - ��� ����������.
����������� ������� ���������� ��������, ������ ������ �������������, ������ ������ ���������������, �������� ������ �������������,
�������� ������ ���������������, �������� �������������, ������ ���� ���������. ������� ���������� ���������� � ����.

�������� ����, 9 ������*/

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iomanip>

using namespace std;

class ConsoleInput
{
public:

	/*�����, ������� �������� ��� ��������� ����������� ������� (�� ��������� �������) � ���������� ������ � ������ � �����. 
	������������ ��� ��������������� ����� ��� TryParse(string) � �������� �������� TrimStart/TrimEnd.*/
	static string TrimStartEnd(string str, char separator = ' ')												
	{																		
		int strBegin = str.find_first_not_of(separator);	
		if (strBegin == std::string::npos)
			return "";

		int strEnd = str.find_last_not_of(separator);
		int strRange = strEnd - strBegin + 1;

		return str.substr(strBegin, strRange);
	}

	//�����, ����������� ����������� �������������� ������ � �����.
	//���������� true, ���� ��� �������� � false, ���� ���.
	//�������� �������� System.Int32.TryParse(string, out int);
	static bool TryParse(string data) {											
		if (data.length() == 0) return false;									
		data = TrimStartEnd(data);												
		bool negative = false;
		int number = 0;
		if (data[0] == '-' && data.length() > 1) {
			negative = true;
			data = data.substr(1, data.length() - 1);

		}

		for (unsigned int i = 0; i < data.length(); i++)
		{
			if (!isdigit(data[i])) return false;
		}
		return true;

	}

	//�����, ������������� ������ � �����.
	static int IntParse(string data) {		 
		if (data.length() == 0) throw new exception("Wrong parameter");
		data = TrimStartEnd(data);
		bool negative = false;
		int number = 0;
		if (data[0] == '-' && data.length() > 1) {	//���� � ������ ������ �������� ���� �����, �� ����� ������� �������������.
			negative = true;
			data = data.substr(1, data.length() - 1);

		}

		for (unsigned int i = 0; i < data.length(); i++)
		{
			if (isdigit(data[data.length() - 1 - i])) number += (data[data.length() - 1 - i] - '0') * (int)pow(10, i);
			else throw new exception("Wrong parameter");
		}
		return negative ? -number : number;

	}

	//����� ��� ��������� �� ������������ ����� ��� ����� � �������.
	static int GetIntFromConsole()												
	{																			
		string data;															
		cin >> data;
		while (!TryParse(data)) {
			cout << "Enter correct value." << endl;
			cin >> data;

		}

		return IntParse(data);
	}




};

template <typename T, typename F> class PriorityList
{
public:
	struct Node
	{
		T Data;
		F Priority;
		Node* Next;
	};

	PriorityList()
	{
		Front = NULL;
	}

	//���������� �������� �������� � ����� ��������� �����������
	Node* GetLowestPriorNode() {
		return this->Front;
	}

	//���������� �������� �������� � ����� ������� �����������
	Node* GetHighestPriorNode() {
		Node* node = Front;
		if (node != NULL)
			while (node->Next != NULL)
				node = node->Next;
		return node;
	}

	//������� ������ ��������� ���� � ���������� ��������� ����������
	Node* FindNodeByValue(T element) {
		Node* node = Front;
		while (node != NULL && node->Data != element)
			node = node->Next;
		return node;
	}

	//������� ������ ��������� ���� � ���������� ��������� ���������� � ����������
	Node* FindNodeByValueAndPriority(T element, F priority) {
		Node* node = Front;
		while (node != NULL && (node->Data != element || node->Priority < priority))
			node = node->Next;
		return node;
	}

	//��������� ������� � ������ �����������
	void Add(T item, F priority)
	{
		Node* temp;
		temp = new Node;
		temp->Data = item;
		temp->Priority = priority;
		if (Front == NULL || priority < Front->Priority)
		{
			temp->Next = Front;
			Front = temp;
		}
		else
		{
			Node* node = Front;
			while (node->Next != NULL && node->Next->Priority <= priority)
				node = node->Next;

			temp->Next = node->Next;
			node->Next = temp;
		}
	}


	//������� ������� � ����� ������ �����������
	void RemoveLowestPrior()
	{
		Node* temp = this->Front;
		if (temp == NULL)
			cout << "This list is empty already" << endl;
		else
		{
			cout << "Deleted element: " << temp->Data << ". Priority: " << temp->Priority << endl;
			Front = Front->Next;
			free(temp);
		}
	}

	//������� ������� � ����� ������� �����������
	void RemoveHighestPrior()
	{
		Node* temp = this->Front;
		if (temp == NULL)
			cout << "This list is empty already" << endl;
		else if (temp->Next == NULL)
		{
			this->Front = NULL;
			cout << "Deleted element: " << temp->Data << ". Priority: " << temp->Priority << endl;
			free(temp);
		}
		else
		{
			while (temp->Next->Next != NULL)
				temp = temp->Next;
			cout << "Deleted element: " << temp->Next->Data << ". Priority:" << temp->Next->Priority << endl;
			free(temp->Next);
			temp->Next = NULL;
		}
	}


	//������� ������ ��������� �������� �� ������� ��������
	void Remove(T element)
	{
		Node* node = this->Front;
		if (node == NULL)
			cout << "This list is empty already" << endl;
		else if (node->Data == element)
		{
			cout << "Deleting element: " << node->Data << ". Priority:" << node->Priority << endl;
			Front = node->Next;
			free(node);
		}
		else
		{
			while (node->Next != NULL && (node->Next->Data != element))
				node = node->Next;

			if (node->Next != NULL) {
				Node* temp = node->Next->Next;
				cout << "Deleting element: " << node->Next->Data << ". Priority:" << node->Next->Priority << endl;
				free(node->Next);
				node->Next = temp;
			}
		}
	}

	//������� ������ ��������� �������� �� ������� �������� � ����������
	void Remove(T element, F priority)
	{
		Node* node = this->Front;
		if (node == NULL)
			cout << "This list is empty already" << endl;
		else if (node->Data == element && node->Priority == priority)
		{
			cout << "Deleting element: " << node->Next->Data << ". Priority:" << node->Next->Priority << endl;
			Front = node->Next;
			free(node);
		}
		else
		{
			while (node->Next != NULL && (node->Next->Data != element || node->Next->Priority != priority))
				node = node->Next;

			if (node->Next != NULL) {
				Node* temp = node->Next->Next;
				cout << "Deleting element: " << node->Next->Data << ". Priority:" << node->Next->Priority << endl;
				free(node->Next);
				node->Next = temp;
			}
		}
	}


	//������� ��� ��������
	void PrintAll()
	{
		Node* node;
		node = Front;
		if (node == NULL)
			cout << "List is empty." << endl;
		else
		{
			cout << "Printing list:" << endl;
			while (node != NULL)
			{
				cout << "Data: " << node->Data << ". Priority: " << node->Priority << "." << endl;
				node = node->Next;
			}
		}
	}

private:
	Node* Front;


};

struct Point {
public:
	int X;
	int Y;
	friend std::ostream & operator<<(std::ostream & str, Point const & v) {
		str << "X = " << v.X << "; Y = " << v.Y << ";";
		return str;
	}
};


void main()
{
	while (true) {
		PriorityList<string, int> stringList;
		PriorityList<int, int> intList;
		int choice;
		enum Type { str, ints, customDemo, none };
		Type chosenType = Type::none;

		cout << "Choose the type of elements" << endl;
		cout << "1. String." << endl;
		cout << "2. Integer." << endl;
		cout << "3. Demonstrate work using custom struct (Point)." << endl;
		cout << "4. Quit.\n";
		cin >> choice;
		switch (choice)
		{
		case 1:
			chosenType = Type::str;
			break;
		case 2:
			chosenType = Type::ints;
			break;
		case 3:
			chosenType = Type::customDemo;
			break;
		case 4:
			break;
		default:
			cout << "Wrong choice." << endl;
			break;
		}



		if (chosenType == Type::none) break;
		else
			if (chosenType == Type::str || chosenType == Type::ints) {
				if (chosenType == Type::str)
					PriorityList<string, int> stringList = PriorityList<string, int>();
				else PriorityList<int, int> intList = PriorityList<int, int>();

				cout << "\n\n1. Insert" << endl;
				cout << "2. Get element with highest priority" << endl;
				cout << "3. Get element with lowest priority" << endl;
				cout << "4. Remove element with highest priority" << endl;
				cout << "5. Remove element with lowest priority" << endl;
				cout << "6. Find element by value" << endl;
				cout << "7. Find element by value and priority" << endl;
				cout << "8. Delete element by value" << endl;
				cout << "9. Delete element by value and priority" << endl;
				cout << "10. Print all list" << endl;
				cout << "11. Quit" << endl;

				do
				{
					cout << "\nDone!\n" << endl;
					cin >> choice;
					cout << endl;
					switch (choice)
					{
					case 1:
						cout << "Input the item value to be added to the list: ";
						if (chosenType == Type::ints)
						{
							int item = ConsoleInput::GetIntFromConsole();
							cout << "Enter its priority: ";
							int priority = ConsoleInput::GetIntFromConsole();
							intList.Add(item, priority);
						}
						else
						{
							string item;
							cin >> item;
							cout << "Enter its priority: ";
							int priority = ConsoleInput::GetIntFromConsole();
							stringList.Add(item, priority);
						}
						break;
					case 2:
						if (chosenType == Type::ints) {
							PriorityList<int, int>::Node* node = intList.GetHighestPriorNode();
							if (node != NULL)
								cout << "Highest priority item (int) has value of: " << node->Data << "; end priority of: " << node->Priority << endl;
							else cout << "List is empty. Can't extract nodes." << endl;

						}
						else {
							PriorityList<string, int>::Node* node = stringList.GetHighestPriorNode();
							if (node != NULL)
								cout << "Highest priority item (string) has value of: " << node->Data << "; end priority of: " << node->Priority << endl;
							else cout << "List is empty. Can't extract nodes." << endl;
						}
						break;
					case 3:
						if (chosenType == Type::ints) {
							PriorityList<int, int>::Node* node = intList.GetLowestPriorNode();
							if (node != NULL)
								cout << "Lowest priority item (int) has value of: " << node->Data << "; end priority of: " << node->Priority << endl;
							else cout << "List is empty. Can't extract nodes." << endl;

						}
						else {
							PriorityList<string, int>::Node* node = stringList.GetHighestPriorNode();
							if (node != NULL)
								cout << "Lowest priority item (string) has value of: " << node->Data << "; end priority of: " << node->Priority << endl;
							else cout << "List is empty. Can't extract nodes." << endl;
						}
						break;
					case 4:
						if (chosenType == Type::ints)
							intList.RemoveHighestPrior();
						else stringList.RemoveHighestPrior();
						break;
					case 5:
						if (chosenType == Type::ints)
							intList.RemoveLowestPrior();
						else stringList.RemoveLowestPrior();
						break;
					case 6:
						if (chosenType == Type::ints) {
							cout << "Enter element value (int)" << endl;
							int val = ConsoleInput::GetIntFromConsole();
							PriorityList<int, int>::Node* node = intList.FindNodeByValue(val);
							if (node != NULL)
								cout << "Element with value: " << node->Data << "; and priority: " << node->Priority << " was found." << endl;
							else cout << "Nothing was found with such value." << endl;

						}
						else {
							cout << "Enter element value (string)" << endl;
							string val;
							cin >> val;
							PriorityList<string, int>::Node* node = stringList.FindNodeByValue(val);
							if (node != NULL)
								cout << "Element with value: " << node->Data << "; and priority: " << node->Priority << " was found." << endl;
							else cout << "Nothing was found with such value." << endl;
						}
						break;
					case 7:
						if (chosenType == Type::ints) {
							cout << "Enter element value (int)" << endl;
							int val = ConsoleInput::GetIntFromConsole();
							cout << "Enter priority of searched item" << endl;
							int prior = ConsoleInput::GetIntFromConsole();
							PriorityList<int, int>::Node* node = intList.FindNodeByValueAndPriority(val, prior);
							if (node != NULL)
								cout << "Element with value: " << node->Data << "; and priority: " << node->Priority << " was found." << endl;
							else cout << "Nothing was found with such value and priority." << endl;

						}
						else {
							cout << "Enter element value (string)" << endl;
							string val;
							cin >> val;
							cout << "Enter priority of searched item " << endl;
							int prior = ConsoleInput::GetIntFromConsole();
							PriorityList<string, int>::Node* node = stringList.FindNodeByValueAndPriority(val, prior);
							if (node != NULL)
								cout << "Element with value: " << node->Data << "; and priority: " << node->Priority << " was found." << endl;
							else cout << "Nothing was found with such value and priority." << endl;
						}
						break;
					case 8:
						if (chosenType == Type::ints) {
							cout << "Enter element value to delete (int)" << endl;
							int val = ConsoleInput::GetIntFromConsole();
							intList.Remove(val);
						}
						else {
							cout << "Enter element value to delete (string)" << endl;
							string val;
							cin >> val;
							stringList.Remove(val);
						}
						break;
					case 9:
						if (chosenType == Type::ints) {
							cout << "Enter element value to delete (int)" << endl;
							int val = ConsoleInput::GetIntFromConsole();
							cout << "Enter priority of searched item" << endl;
							int prior = ConsoleInput::GetIntFromConsole();
							intList.Remove(val, prior);


						}
						else {
							cout << "Enter element value to delete (string)" << endl;
							string val;
							cin >> val;
							cout << "Enter priority of searched item" << endl;
							int prior = ConsoleInput::GetIntFromConsole();
							stringList.Remove(val, prior);
						}
						break;
					case 10:
						if (chosenType == Type::ints)
							intList.PrintAll();
						else stringList.PrintAll();
						break;
					case 11: break;
					default:
						cout << "Wrong choice" << endl;
					}
				} while (choice != 11);
			}
			else
			{
				cout << "Demonstrating work using struct Point" << endl;
				PriorityList<Point, int> pointList;
				for (int i = 0; i < 10; i++)
				{
					int x = rand() % 10;
					int y = rand() % 10;
					int prior = rand() % 10 - 3;
					cout << "Adding Point: X = " << x << "; Y = " << y << "; Priority: " << prior << "; to list." << endl;
					pointList.Add(Point{ x,y }, prior);
				}
				pointList.PrintAll();
				cout << "\nRemoving lowest priority item (twice):" << endl;
				pointList.RemoveLowestPrior();
				pointList.RemoveLowestPrior();
				pointList.PrintAll();
				cout << "\nRemoving highest priority item:" << endl;
				pointList.RemoveHighestPrior();
				pointList.PrintAll();
				cout << "\nGetting highest priority item:" << endl;
				cout << pointList.GetHighestPriorNode()->Data << endl;
				cout << "\nGetting lowest priority item:" << endl;
				cout << pointList.GetLowestPriorNode()->Data << endl;

			}
	}
}