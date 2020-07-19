#include "Set.h"
#include <cassert>
#include <iostream>
using namespace std;

/////////////////////////////////////
//Set Implementations
/////////////////////////////////////

Set::Set()
{
	head = new Node;
	head->next = head;
	head->prev = head;
	m_size = 0;

	
}

bool Set::empty() const
{
	return m_size == 0;
	
}

int Set::size() const
{
	return m_size;
}

bool Set::insert(const ItemType& value)
{
	if (contains(value)) //avoid inserting duplicates
		return false;

	Node *p;
	p = head->next; 
	// dummy.next;

	while (p->next != head) 
		p = p->next;

	Node* n = new Node;
	n->m_value = value;

	//at this point, we know p->next is pointing to dummy, so p is pointing to final node

	if (m_size == 0) //empty list case
	{

		p->next = n;
		n->next = head; 

		n->prev = p; 
		head->prev = n; 

		m_size++;
	}

	else //dummy node, so 1 or n nodes are the same
	{
		n->next = p->next;
		p->next = n;
		
		n->prev = p;
		head->prev = n;

		m_size++;
	}

	return true;
}

bool Set::erase(const ItemType& value)
{
	if (!contains(value) || size() == 0) //don't delete value that doesn't exist
		return false;

	Node* p = head;

	while (p->next != head)
	{
		if (p->next->m_value == value)
			break;
		p = p->next;
	}

	if (m_size == 1) //simplest deletion case
	{
		Node* killMe = p->next;

		p->next = killMe->next;
		p->prev = p;

		delete killMe;

		m_size--;
	}
	else //general case, but dummy node allows us to ignore special cases
	{
		Node* killMe = p->next;

		p->next = killMe->next;
		(killMe->next)->prev = killMe->prev; // parenthesis in case precedence mattered

		delete killMe;

		m_size--;
	}
	return true;
}

bool Set::contains(const ItemType& value) const
{
	if (empty()) 
		return false;
	Node* p;
	p = head->next; 

	while (p != head) //traverse through nodes until value matches
	{
		if (p->m_value == value)
			return true;
		p = p->next;
	}

	return false;
}

bool Set::get(int pos, ItemType& value) const
{
	int counter = 0;
	if (pos >= 0 && pos < size()) //will only iterate as long as inputs are valid
	{
		cerr << "entered get condition" << endl;
		Node* p = head->next; 
		//dummy.next;
		Node* q = p;
		for (;q != head; q = q->next) //nested loop to compare each pair of nodes
		{
			cerr << "q->m_value: " << q->m_value << endl;
			for (p = head->next;p != head;p = p->next)
			{
				cerr << "p->m_value: " << p->m_value << endl;
				if (q->m_value > p->m_value)
				{
					cerr << "successful counter inc, ";
					cerr << "q->m_value: " << q->m_value << " > " << "p->m_value: " << p->m_value << endl;
					counter++;
				}
				else
				{
					cerr << "no counter increase, ";
					cerr << "q->m_value: " << q->m_value << " < " << "p->m_value: " << p->m_value << endl;
				}
			}
			if (counter == pos) //check if inner loop matches i
			{
				cerr << "get success" << endl;
				value = q->m_value;
				return true;
			}
			else //increment outer loop and restart
			{
				cerr << "reset counter" << endl;
				counter = 0;
			}
		}
	}
	cerr << "value: " << value << endl;
	return false;
}

void Set::swap(Set& other)
{
	//swap sizes
	int tempSize = m_size;
	m_size = other.m_size;
	other.m_size = tempSize;
	
	//swap head pointers to dummy nodes
	Node* temp = head;
	head = other.head;
	other.head = temp;


}

Set::~Set()
{
	cerr << "destructor called" << endl;
	Node* p = head->next;

	while (p != head) //loop to delete each dynamically allocated node
	{
		Node* n = p->next;
		delete p;
		p = n;
		cerr << "deleting node" << endl;
	}
	//p now points to head, or dummy node
	cerr << "deleting head to dummy node" << endl;
	delete p;
}

Set::Set(const Set& other) //copy constructor
{
	m_size = other.m_size;
	cerr << "copy constructor called" << endl;
	//creating a new set from scratch
	head = new Node; 
	head->next = head;
	head->prev = head;

	Node* p = other.head->next;

	for (;p != other.head ;p = p->next) //from Set other, not new node Head
	{
	//more general case of inserting
		cerr << "entered copy loop" << endl;
		Node* copy = new Node;
		copy->m_value = p->m_value;
		
		copy->next = head;
		copy->prev = head->prev;

		(head->prev)->next = copy; //added parenthesis, in case of precedence
		head->prev = copy;

	}

}

Set& Set::operator=(const Set& rhs) //assignment operator
{
	if (this != &rhs)
	{
		Set temp(rhs);
		swap(temp);
	}
	return *this;
}



/////////////////////////////////////
//Algorithm Implementations
/////////////////////////////////////

void unite(const Set& s1, const Set& s2, Set& result)
{
	cerr << "entered unite" << endl;

	if (result.size() != 0)
	{
		cerr << "must erase previous stuff in result" << endl;
		for (int i = 0; i < result.size(); i++)
		{
			ItemType x;
			result.get(i, x);
			result.erase(x);
		}
	}

	if (s1.size() == 0)
	{
		result = s2;
		cerr << "s1 is empty" << endl;
		return;
	}
	else if (s2.size() == 0)
	{
		result = s1;
		cerr << "s2 is empty" << endl;
		return;
	}
	//if one of the sets is empty, then result is consequently the other set
	result = s1;
	cerr << "s2.size(): " << s2.size() << endl;
	for (int i = 0; i < s2.size(); i++)
	{
		ItemType value;
		s2.get(i, value); //allows me to get a value in node since these functions have no access

		if (!result.contains(value))
			result.insert(value);
	}


}

void subtract(const Set& s1, const Set& s2, Set& result)
{
	cerr << "entered subtract" << endl;
	if (result.size() != 0)
	{
		cerr << "must erase previous stuff in result" << endl;
		cerr << "result size: " << result.size() << endl;
		for (int i = 0; i < result.size(); i++)
		{
			ItemType x;
			result.get(i, x);
			result.erase(x);
		}
	}
	
	if (s1.size() == 0 || s2.size() == 0)
	{
		result = s1; //cannot remove values from an empty set
		//also, we can't remove s2 from s1 if s2 is an empty set. 
		return;
	}

	result = s1;

	for (int i = 0; i < s2.size(); i++)
	{
		ItemType value;
		s2.get(i, value); //allows me to get a value in node since these functions have no access

		if (result.contains(value))
			result.erase(value);
	}

}
