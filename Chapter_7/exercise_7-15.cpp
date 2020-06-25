#include <iostream>
#include <string>

using namespace std;

struct Person;
void read(istream &is, Person &p);
void print(Person &p);
struct Person
{
  // Constructors
  // Constructor 1
  Person():name("defaultName"), address("defaultAddr") {};
  // Constructor 2
  Person(string &n, string &addr):name(n), address(addr){};
  // Constructor 3
  Person(istream& is) { read(is, *this);};
  // member varibles
  string name;
  string address;
  // member functions
  string getName() const;
  string getAddress() const;
};

string Person::getName() const
{
  return name;
}

string Person::getAddress() const
{
  return address;
}

void print(Person &p)
{
  cout << "..............................................\n";
  cout << "Name : "<<p.name << " Address: "<<p.address << endl;
  cout << "..............................................\n";
}
void read(istream &is, Person &p)
{
  cout << "Read Person details\n";
  is >> p.name;
  is.ignore();
  getline(cin, p.address);
}

int main()
{
  Person p1;
  string name = "Constructor_2";
  string address = "Initializer list!";
  Person p2(name, address);
  Person p3(cin);
  Person p4;
  read(cin, p4);

  print(p1);
  print(p2);
  print(p3);
  print(p4);

  return 0;
}
