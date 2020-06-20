#include <iostream>
#include <string> 
using namespace std;

struct Sales_data
{
    //  Constructors
    // Constructor 1
    Sales_data();
    // Constructor 2
    Sales_data(string &book):bookNo(book){}; // 1. Constructor initilizer list
                                             // 2. In-class initilizers
    // Constructor 3
    Sales_data(string &book, unsigned uSold, double price):
     bookNo(book), unitsSold(uSold), revenue(uSold*price){};    // Constructor initilizer list
    // Constructor 4
    Sales_data(istream &is);
//  Member variables
    string bookNo;
    double revenue = 0.0;
    unsigned unitsSold = 0;
    static unsigned int numOfBooksInInventory;
//  Member functions
    void combine(Sales_data &trans);
    string isbn() const;
    double avgPrice() const;
};

void print(ostream &os, Sales_data const &item);
Sales_data add(Sales_data &lhs, Sales_data &rhs);
istream& read(istream &is, Sales_data &item);

Sales_data::Sales_data()
{
    unitsSold = 0;
    revenue = 0.0;
}

Sales_data::Sales_data(istream &is)
{
    read(is, *this);
}
unsigned int Sales_data::numOfBooksInInventory = 0;

void Sales_data::combine(Sales_data &trans)
{
    bookNo = trans.bookNo;
    unitsSold += trans.unitsSold;
    revenue += trans.revenue;
}

string Sales_data::isbn() const
{
    return bookNo;
}

const unsigned int MAX_BOOKS = 100; 

istream& read(istream &is, Sales_data &item)
{
    double price;
    cout << "Enter new transaction\n";
    is >> item.bookNo >> item.unitsSold >> price;
    item.revenue = item.unitsSold * price;
    return is;
}

void print(ostream &os, Sales_data const &item)
{
    os << item.bookNo << "  "
    << item.unitsSold << "  "
    << item.revenue << endl;
}

Sales_data add(Sales_data &lhs, Sales_data &rhs)
{
    Sales_data sum = lhs;
    sum.combine(rhs);
    return sum;
}

int main()
{
    Sales_data inventory[MAX_BOOKS];    //  With vectors we won't need static array
    double pricePerBook;
    Sales_data newBook;
    while(Sales_data::numOfBooksInInventory < MAX_BOOKS)
    {
    cout << "Read transaction using constructor 1\n";
    Sales_data ctor1Obj;
    inventory[Sales_data::numOfBooksInInventory++] = ctor1Obj;

    cout << "Read transaction using constructor 2\n";
    string book2 = "constructor 2";
    Sales_data ctor2Obj(book2);
    inventory[Sales_data::numOfBooksInInventory++] = ctor2Obj;

    cout << "Read transaction using constructor 3\n";
    string book3 = "constructor 3";
    Sales_data ctor3Obj(book3, 10, 10.0);
    inventory[Sales_data::numOfBooksInInventory++] = ctor3Obj;

    cout << "Read transaction using constructor 4\n";
    Sales_data ctor4Obj(cin);
    inventory[Sales_data::numOfBooksInInventory++] = ctor4Obj;

    cout << "show ctor3Obj + ctor1Obj\n";
    print(cout, add(ctor3Obj, ctor1Obj));
    cout << "show ctor4Obj + ctor2Obj\n";
    print(cout, add(ctor4Obj, ctor2Obj));
    
    break;
    }
    cout << "Inventory Details: " << Sales_data::numOfBooksInInventory << " transactions in inventory\n";
    if(Sales_data::numOfBooksInInventory > 0)
    {
        for(int i = 0; i < Sales_data::numOfBooksInInventory; i++)
        {
            print(cout, inventory[i]);
        }
    }
    else
    {
        cerr << "No Data?!" << endl;
    }

    return 0;
}