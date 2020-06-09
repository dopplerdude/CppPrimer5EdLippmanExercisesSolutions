#include <iostream>
#include <string>

using namespace std;

struct Person
{
  string name;
  string address;
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

istream& read(istream &is, Person &newPerson);
void print(ostream &os, Person const &newPerson);

istream& read(istream &is, Person &newPerson)
{
  is >> newPerson.name;
  is.ignore();
  getline(is, newPerson.address);
  return is;
}

void print(ostream &os, Person const &newPerson)
{
  os << "*************Person Information****************" << endl;
  os << "Name: "<< newPerson.getName() << endl;
  os << "Address: "<<newPerson.getAddress() <<endl;
}

int main()
{
  Person newPerson;
  while(read(cin, newPerson))
  {
    print(cout, newPerson);
  }
  return 0;
}
