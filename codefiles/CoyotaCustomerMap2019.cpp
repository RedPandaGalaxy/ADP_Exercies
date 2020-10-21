#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

class Person
{
public:
	Person(string n, string adr, int a) : name(n), address(adr), age(a) {}
	void print(void) const { cout << name << "  " << address << "  " << age << " "; }
	string get_name(void) const { return name; }
private:
	string name, address;
	int age;
};

class Coyota_dealer_affiliated
{
public:
	virtual string write_letter_to(string text) = 0;
};

class Customer : public Coyota_dealer_affiliated
{
public:
	Customer(const Person &p, int c_no, double ac)
		: person_ptr(&p), customer_number(c_no), account(ac), credit_maximum(0) {}
	void print(void) { cout << " Customer " << customer_number << "  " << account << "  "; person_ptr->print(); }
	string get_name(void) const { return person_ptr->get_name(); }
	virtual string write_letter_to(string text) { return " Dear Customer " + get_name() + " " + text; }
	int get_credit(void) { return credit_maximum; }
	void set_credit(int c) { credit_maximum = c; }
private:
	const Person *person_ptr;
	int customer_number;
	double account;
	int credit_maximum;
};

class Employee : public Coyota_dealer_affiliated
{
public:
	Employee(const Person *p_ptr, int e_no)
		: person_ptr(p_ptr), employee_number(e_no) {}
	virtual double calculate_salary(void) = 0;
	void virtual print(void) { cout << " employee_number " << employee_number << "  "; person_ptr->print(); }
	string get_name(void) const { return person_ptr->get_name(); }
private:
	const Person *person_ptr;
	int employee_number;
};

class Mechanic : public Employee
{
public:
	Mechanic(const Person &p, int e_no) :Employee(&p, e_no) {}
	void set_hourly_salary(double s) { hourly_salary = s; }
	void set_hours(int h) { hours = h; }
	virtual double calculate_salary(void) { return hours*hourly_salary; }
	void virtual print(void) { cout << " mechanic " << hourly_salary << "  " << hours; Employee::print(); }
	virtual string write_letter_to(string text)
	{
		return " Dear Mechanic " + get_name() + " " + text;
	}
private:
	int hours;
	double hourly_salary;
};

class Secretary : public Employee
{
public:
	Secretary(const Person &p, int e_no) :Employee(&p, e_no) {}
	void set_monthly_salary(double s) { monthly_salary = s; }
	virtual double calculate_salary(void) { return monthly_salary; }
	void virtual print(void) { cout << " Secretary " << monthly_salary << "  "; Employee::print(); }
	virtual string write_letter_to(string text)
	{
		return " Dear Secretary " + get_name() + " " + text;
	}
private:
	double monthly_salary;
};

class Salesman : public Employee
{
public:
	Salesman(const Person &p, int e_no) :Employee(&p, e_no) {}
	void set_provision(double p) { provision = p; }
	void set_sale(double s) { sale = s; }
	virtual double calculate_salary(void) { return provision*sale; }
	void virtual  print(void) { cout << " Salesman " << sale << "  " << provision; Employee::print(); }
	virtual string write_letter_to(string text)
	{
		return " Dear Salesman " + get_name() + " " + text;
	}
private:
	double sale, provision;
};

class Director : public Employee
{
public:
	Director(const Person &p, int e_no) :Employee(&p, e_no) {}
	void set_monthly_salary(double s) { monthly_salary = s; }
	void assign_free_car(string m) { free_car = m; }
	virtual double calculate_salary(void) { return monthly_salary; }
	void virtual print(void)
	{
		cout << " Director " << monthly_salary << " and free car " << free_car;
		Employee::print();
	}
	virtual string write_letter_to(string text)
	{
		return " Dear Director " + get_name() + " " + text;
	}
private:
	double monthly_salary;
	string free_car;
};

class Coyota_employee
{
public:
	Coyota_employee(const Person &p)
		: person_ptr(&p) {}
	void set_monthly_salary(double s) { monthly_salary = s; }
	double calculate_salary(void) { return monthly_salary; }
	void print() { cout << " Coyota employee "; person_ptr->print(); }
	string get_name(void) const { return person_ptr->get_name(); }
	string write_letter_to(string text)
	{
		return " Dear Coyota employee " + get_name() + " " + text;
	}
private:
	const Person *person_ptr;
	double monthly_salary;
};
//////////////////////////////////////////////////////////////////////////
void clear_customer_credit(pair<string, Customer*>  pnc)
{
	pnc.second->set_credit(0);
}

class Customers_element_compare {
public:
	bool operator()(pair<string, Customer*> pnc1, pair<string, Customer*> pnc2)
	{
		return pnc1.second->get_credit() < pnc2.second->get_credit();
	}
};
/////////////////////////////////////////////////////////////////////////////
class Coyota_dealer
{
public:
	Coyota_dealer(Person &o, string adr) :owner_ptr(&o), address(adr) {}
	void hire(Employee &e) { employees.push_back(&e); }
	void fire(Employee &e)
	{
		unsigned int i;
		for (i = 0; i<employees.size(); i++)
		{
			if (employees[i] == &e)
			{
				employees.erase(employees.begin() + i);
			}
		}
	}
	void register_customer(Customer &c) { customers[c.get_name()] = &c; }
	double calculate_total_salary(void)
	{
		unsigned int i; double total_salary = 0;
		for (i = 0; i<employees.size(); i++)
		{
			total_salary += employees[i]->calculate_salary();
		}
		return total_salary;
	}
	void write_letter_to_employees(string text)
	{
		for (auto c_ptr : employees)
		{
			cout << endl;
			cout << c_ptr->write_letter_to(text);
		}
	}
	void write_letter_to_customers(string text)
	{

		for (auto pnc : customers)
		{
			cout << endl;
			cout << pnc.second->write_letter_to(text);
		}
	}
	void write_letter_to_affiliates(string text)
	{
		write_letter_to_customers(text);
		write_letter_to_employees(text);
	}
	void print(void)
	{
		cout << " owner ";
		owner_ptr->print();
		cout << endl << " employees: ";
		vector<Employee*>::iterator it;
		for (it = employees.begin(); it<employees.end(); it++)
		{
			cout << endl; (*it)->print();
		}
		cout << endl << " customers: ";
		for (auto pnc : customers)
		{
			cout << endl; pnc.second->print();
		}
	}

	int get_credit(const string n)
	{
		map<string, Customer*>::iterator cit;

		cit = customers.find(n);
		if (cit != customers.end())
		{
			return cit->second->get_credit();
		}
		else
		{
			return -1;
		}
	}

	void set_credit(string n, int c)
	{
		map<string, Customer*>::iterator cit;

		cit = customers.find(n);
		if (cit != customers.end())
		{
			cit->second->set_credit(c);
		}

	}

	int sum_of_credits(void)
	{
		int sum = 0;
		map<string, Customer*>::iterator cit;
		for (cit = customers.begin(); cit != customers.end(); cit++)
		{
			sum += cit->second->get_credit();
		}
		return sum;
	}

	void clear_all_credits(void)
	{
		for_each(customers.begin(), customers.end(), clear_customer_credit);
	}

	int get_credit_maximum(void)
	{
		//much simpler: return max_element(customers.begin(), customers.end(), Customers_element_compare() )->second->get_credit();

		map<string, Customer*>::iterator cit;
		pair<string, Customer*> max_pnc;
		max_pnc = *customers.begin();
		for (cit = customers.begin(); cit != customers.end(); cit++)
		{
			pair<string, Customer*> candidate_pnc = *cit;
			max_pnc = max(candidate_pnc, max_pnc , Customers_element_compare());
		}
		return max_pnc.second->get_credit();
	}

private:
	Person *owner_ptr;
	string address;
	vector<Employee*> employees;
	//vector<Customer*> customers;
	map<string, Customer*> customers;
};


int main(void)
{
	Person p1("Jens", "Odense", 20);
	Mechanic m1(p1, 1);
	m1.set_hourly_salary(100.5);
	m1.set_hours(10);
	m1.print();

	cout << endl;

	Person p2("Ole", "Fynshav", 22);
	Secretary s1(p2, 2);
	s1.set_monthly_salary(20000.7);
	s1.print();

	cout << endl;

	Person p3("Ib", "Skovby", 42);
	Salesman sm1(p3, 3);
	sm1.set_provision(0.1);
	sm1.set_sale(1000);
	sm1.print();

	cout << endl;

	Person p4("Stefan", "Nordborg", 37);
	Director d1(p4, 4);
	d1.set_monthly_salary(200000.8);
	d1.assign_free_car("Tesla-X");
	d1.print();

	cout << endl;

	Person p5("Rudolf", "Augustenborg", 25);
	Customer c1(p5, 1, 100);
	c1.print();
	cout << endl;

	Person p7("Gandalf", "Fynshav", 82);
	Customer c2(p7, 2, 0);
	c2.print();
	cout << endl;

	Person p6("Wolf", "Broager", 35);
	Coyota_dealer Broager_coyota(p6, "Broager");

	Broager_coyota.hire(d1);
	Broager_coyota.hire(sm1);
	Broager_coyota.hire(s1);
	Broager_coyota.hire(m1);
	//	Broager_coyota.hire(f1);

	Broager_coyota.register_customer(c1);
	Broager_coyota.register_customer(c2);

	cout << endl;
	Broager_coyota.print();
	Broager_coyota.fire(s1);
	cout << endl << " after firing of the secretary: " << endl;
	Broager_coyota.print();

	cout << endl << endl << " total salary: " << Broager_coyota.calculate_total_salary();

	cout << endl;
	Broager_coyota.write_letter_to_employees(" labor party on Friday ");
	cout << endl;
	Broager_coyota.write_letter_to_customers(" come and try the new Coyota yaugo ");
	cout << endl;
	Broager_coyota.write_letter_to_affiliates(" We have a speeder problem ");
	cout << endl;

	Broager_coyota.set_credit("Rudolf",100);
	Broager_coyota.set_credit("Gandalf", 10);
	cout << endl << "Rudolf credit: " << Broager_coyota.get_credit("Rudolf");
	cout << endl << "sum of credits: " << Broager_coyota.sum_of_credits();
	cout << endl << " maximum of credits: " << Broager_coyota.get_credit_maximum();
	Broager_coyota.clear_all_credits();
	cout << endl << " sum after clearing all credits: " << Broager_coyota.sum_of_credits();


	int kk; cin >> kk;
	return 0;
}