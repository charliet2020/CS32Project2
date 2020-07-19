#include "Set.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Set ss;
	assert(ss.insert("roti"));
	assert(ss.insert("pita"));
	assert(!ss.insert("pita"));
	assert(ss.size() == 2);
	assert(ss.contains("pita"));
	ItemType x = "laobing";
	assert(ss.get(0, x) && x == "pita");
	assert(ss.get(1, x) && x == "roti");
	assert(ss.erase("roti") && ss.size() == 1 && ss.get(0, x) && x == "pita");
	assert(ss.size() == 1);
	Set tt;
	assert(tt.empty()); //testing empty
	assert(tt.size() == 0); //test size
	assert(!tt.erase("laobing")); //nothing to remove
	assert(tt.insert("laobing")); //test insert
	assert(tt.insert("roti")); //test insert for bigger list
	assert(tt.insert("bread")); //test insert again
	assert(tt.size() == 3); //test size for bigger list
	
	ss.swap(tt); //testing swap
	assert(ss.size() == 3 && tt.size() == 1);
	assert(ss.contains("laobing") && tt.contains("pita"));
	assert(ss.get(1, x) && x == "laobing"); //test get for middle case

	cerr << "done with swap" << endl;
	Set result;
	unite(ss, tt, result); //testing unite, which will indirectly test copy constructor
	cerr << "result: " << result.size() << endl;
	assert(result.size() == 4);
	assert(result.contains("pita") && result.contains("laobing") && result.contains("roti") && result.contains("bread"));
	result = ss;  //testing assignment operator and get
	assert(result.size() == 3);
	assert(result.get(0, x) && x == "bread" && result.get(1, x) && x == "laobing"
		&& result.get(2, x) && x == "roti");

	Set temp = result; //copy constructor test
	cerr << "created tempt from result" << endl;
	assert(temp.insert("food") && temp.insert("carb") && temp.size() == 5);

	unite(ss, tt, temp); //unite for non empty result
	assert(temp.size() == 4);

	cerr << "testing subtract" << endl;
	Set uu; //testing subtract along with nonempty result
	assert(uu.insert("bread"));
	subtract(ss, uu, result); //testing when result is not empty
	cerr << "result.size(): " << result.size() << endl;
	assert(result.size() == 2 && !result.contains("bread"));
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
}