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

int main()
{
  Person p;
  cin >> p.name;
  cin.ignore();
  getline(cin, p.address);

  cout << p.name << endl;
  cout << p.address << endl;

  return 0;
}
