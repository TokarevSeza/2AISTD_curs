#include "List.h"

using namespace std;

void List::push_back(int add)
{
	if (size == 0) //if list is empty
	{
		head = new Node(add); //create head
		tail = head;
	}
	else
	{
		Node* curr = new Node(add);
		curr->prev = tail;
		tail->next = curr;
		tail = curr;  //set new tail
	}
	size++;
}

void List::push_front(int add)
{
	if (size == 0)
	{
		head = new Node(add);
		tail = head;
	}
	else
	{
		Node* curr = new Node(add);
		curr->next = head;
		head->prev = curr;
		head = curr;  //set new head
	}
	size++;
}

size_t List::get_size()
{
	return size;
}

void List::pop_back()
{
	if (size == 1)
	{
		size = 0;  //setup zero position
		head = NULL;
		tail = NULL;
	}
	else if (size > 1) //if list is not empty
	{
		tail = tail->prev; //set new tail
		delete tail->next;
		tail->next = NULL;
		size--;
	}
	else  //else return error
		throw out_of_range("Segmentation fault");
}

void List::pop_front()
{
	if (size == 1)
	{
		size = 0;  //setup zero position
		head = NULL;
		tail = NULL;
	}
	else if (size > 1) //if list is not empty
	{
		head = head->next; //set new head
		delete head->prev;
		head->prev = NULL;
		size--;
	}
	else //else return error
		throw out_of_range("Segmentation fault");
}

void List::remove(size_t i)
{
	if (i >= size) //if index is larger than size return error
		throw out_of_range("Index is greater than list size");
	else if (i == 0) // if index points to first
		pop_front();
	else if (i == size - 1)	 // if index points to first
		pop_back();
	else
	{
		Node* cur = head;
		while (i) //go to "i" item
		{
			cur = cur->next;
			i--;
		}
		cur->prev->next = cur->next; //cut item from list
		size--;
		delete cur;
	}
}

int List::at(size_t i)
{
	if (i >= size) //if index is larger than size return error
		throw out_of_range("Index is greater than list size");
	else if (i == size - 1)
	{
		return tail->data;
	}
	else {
		Node* cur = head;
		while (i) //go to "i" item
		{
			cur = cur->next;
			i--;
		}
		return cur->data;
	}
}

void List::insert(int add, size_t i)
{
	if (i >= size)  //if index is larger than size return error
		throw out_of_range("Index is greater than list size");
	else if (i == 0) //if insert prev first item
		push_front(add);
	else
	{
		Node* cur = head;
		while (i)
		{
			cur = cur->next;
			i--;
		}
		Node* nadd = new Node(add, cur->prev, cur);  //create new Node with new connection
		cur->prev->next = nadd; //add poin to new Node
		cur->prev = nadd;
		size++;
	}
}

void List::print_to_console()
{
	Node* cur = head;
	while (cur != NULL)
	{
		cout << cur->data << "| ";
		cur = cur->next;
	}
}

void List::clear()
{
	if (head != NULL)
	{
		while (head->next != NULL)  //delete all item
		{
			head = head->next;
			delete head->prev;
		}
		size = 0;  //setup zero position
		head = NULL;
		tail = NULL;
	}
}

void List::set(size_t i, int ins)
{
	if (i >= size) //if index is larger than size return error
		throw out_of_range("Index is greater than list size");
	else {
		Node* cur = head;
		while (i) //go to "i" item
		{
			cur = cur->next;
			i--;
		}
		cur->data = ins; //change data
	}
}

bool List::isEmpty()
{
	if (head == NULL)
		return true;
	return false;
}

void List::push_back(List AddToEnd)
{
	Node* head_AddToEnd = AddToEnd.head;
	while (head_AddToEnd != NULL)
	{
		this->push_back(head_AddToEnd->data); //push new item to the end with data from transmitted list
		head_AddToEnd = head_AddToEnd->next;
	}
}

Iterator* List::create_iterator(int start) {
	return new List_Iterator(head, start, size);
}

bool List::List_Iterator::has_next() {
	return (current != NULL);
}

int List::List_Iterator::next() {
	if (!has_next()) {
		throw std::out_of_range("No more elements");
	}
	int temp = current->data;
	current = current->next;
	return temp;
}