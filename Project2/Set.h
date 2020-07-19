// File: Set.h

#ifndef SET_H
#define SET_H

#include <string>
using ItemType = std::string;
//unsigned long;

class Set
{
public:
	Set();
	bool empty() const;
	int size() const;
	bool insert(const ItemType& value);
	bool erase(const ItemType& value);
	bool contains(const ItemType& value) const;
	bool get(int pos, ItemType& value) const;
	void swap(Set& other);

	// Housekeeping functions
	~Set();
	Set(const Set& other);
	Set& operator=(const Set& rhs);

private:
	struct Node
	{
		ItemType m_value;
		Node* next;
		Node* prev;
	};

	Node dummy;
	int m_size; //number of items linked together, excluding dummy
	Node* head; //= &dummy;
	//Node* tail;

	
	// Return the position of the smallest item in m_data that is >= value,
	// or m_size if there are no such items.
};

void unite(const Set& s1, const Set& s2, Set& result);
/*
//When this function returns, result must contain one copy of each of the values 
//that appear in s1 or s2 or both, and must not contain any other values. 
//(You must not assume result is empty when it is passed in to this function; it might not be.) 
//Since result is a Set, it must, of course, not have any duplicates.
*/
void subtract(const Set& s1, const Set& s2, Set& result);
/*
//When this function returns, result must contain one copy of each of the values that appear
//in s1 but not s2, and must not contain any other values. 
//(You must not assume result is empty when it is passed in to this function; it might not be.)
*/
#endif //for SET_H