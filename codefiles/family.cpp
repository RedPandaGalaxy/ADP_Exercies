#include<iostream>
#include <vector>
#include <string>
using namespace std;

class Date
{
	friend class Period;	
public:
	Date(int d = 1, int m = 1, int y = 0) :  day(d), month(m), year(y) { count++; } // default arguments here is bad taste, but shorter
	Date(const Date &d) :  day(d.day), month(d.month), year(d.year) { count++; } 
	void print(void) const 
	{
		cout << this->day << "/" << this->month << "/" << this->year;
	}
	void set_date(const Date  * const d_ptr)
	{
		this->day = d_ptr->day; this->month = d_ptr->month; this->year = d_ptr->year;
	}
	Date& set_day(int d){ this->day = d; return *this; }
	Date& set_month(int m) { this->month = m; return *this; }
	Date& set_year(int y) { this->year = y; return *this; }
	static int get_count(void) { return count; }
private:
	int day, month, year;
	static int count; 
};
int Date::count = 0;

class Marriage;

class Person
{
	friend class Marriage;
public:
	Person(string n, Date b_d, Marriage  &f_m);
	Person(string n, Date b_d);
	void print(void) const;
	void print_children(void) const;
	void print_parents(void) const;
	bool no_parents(void) const;
private:
  void add_marriage(const Marriage * const marriage_ptr);
  string name;
  const Date BIRTHDAY;
  vector< const Marriage* > marriages;
  Marriage *from_marriage_ptr; 
};
Person::Person(string n, Date b_d, Marriage  &f_m)
	:name(n), BIRTHDAY(b_d), from_marriage_ptr(&f_m)
{
	this->from_marriage_ptr->add_child(*this);
}
Person::Person(string n, Date b_d)
	: name(n), BIRTHDAY(b_d), from_marriage_ptr(0)
{
}
void Person::print(void) const
{
	cout << this->name << " birthday: ";
	BIRTHDAY.print();
}
void Person::print_children(void) const
{
	unsigned int i;
	for (i = 0; i < marriages.size(); i++)
	{
		this->marriages.at(i)->print_children();
		cout << endl;
	}
}
void Person::print_parents(void) const
{
	this->from_marriage_ptr->print_parents();
}
void Person::add_marriage(const Marriage * const marriage_ptr)
{
	this->marriages.push_back(marriage_ptr);
}

bool Person::no_parents(void) const
{
	return this->from_marriage_ptr == 0;
}

class Marriage
{ 
public:
	Marriage(Person &female, Person &male);
	void print_children(void) const;
	void print_parents(void) const;
	void print(void) const;
	void add_child(const Person &c);
private:
	Person * const mother_ptr, * const father_ptr;
	vector< const Person*  > children;
};

Marriage::Marriage(Person &m_ptr, Person &f_ptr)
	:mother_ptr(&m_ptr), father_ptr(&f_ptr)
{
	this->mother_ptr->add_marriage(this);
	this->father_ptr->add_marriage(this);
}
void Marriage::print_children(void) const
{
	vector< const Person* >::const_iterator  cit;
	for (cit = children.begin(); cit < children.end(); cit++)
	{
		(*cit)->print();
		cout << endl;
	}
}
void Marriage::print_parents(void) const
{
	this->mother_ptr->print();
	cout << endl;
	this->father_ptr->print();
}
void Marriage::print(void) const
{
	this->print_parents();
	cout << endl;
	this->print_children();
}
void Marriage::add_child(const Person &c)
{
	if (!c.no_parents()) this->children.push_back(&c);
}

int main(void)
{  
	Person joe("Joe", Date(1, 2, 1980)), heinz("Heinz", Date(3, 4, 1981)), eva("Eva", Date(5,6, 1973));
	
    joe.print();
	cout << endl;
    
    Marriage eva_joe(eva,joe);
	Person john("John", Date(1, 2, 2004), eva_joe), jill("Jill", Date(11, 2, 2006), eva_joe);
	Marriage eva_heinz(eva, heinz);
	Person fritz("Fritz", Date(1, 2, 2010), eva_heinz), gertrud("Gertrud", Date(1, 2, 2012), eva_heinz);
   
    cout << endl << " children of the marriage eva_joe: "<< endl;
	eva_joe.print_children();
	cout << endl << " parents in the marriage eva_joe: " << endl;
	eva_joe.print_parents();
    cout << endl << " children of Eva: " << endl;
	eva.print_children();
    cout << endl << " parents of John: " << endl;
	john.print_parents();

	cout << endl << " children of the marriage eva_heinz: " << endl;
	eva_heinz.print_children();
	cout << endl << " parents in the marriage eva_heinz: " << endl;
	eva_heinz.print_parents();
	cout << endl << " children of Heinz: " << endl;
	heinz.print_children();
	cout << endl << " parents of Gertrud: " << endl;
	if (!gertrud.no_parents()) gertrud.print_parents();
	
    return 0;
}
