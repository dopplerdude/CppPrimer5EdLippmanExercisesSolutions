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
  Person newPerson1, newPerson2;
// Here innermost read() will read data from input stream in to newPerson1
// It will return reference to input stream which is again passed as an
// argument to outer read(), where it will read data from input stream in to
// newPerson2 object.
  if(read(read(cin, newPerson1),newPerson2))
  {
    print(cout, newPerson1);
    print(cout, newPerson2);
  }
  return 0;
}


