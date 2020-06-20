#include <iostream>
#include <string> 
using namespace std;

struct Sales_data;
void print(ostream &os, Sales_data const &item);
Sales_data add(Sales_data &lhs, Sales_data &rhs);
istream& read(istream &is, Sales_data &item);

struct Sales_data
{
    //  Constructors
    // Constructor 1
    Sales_data() = default; // forced compiler generated default constructor (c+11 syntax)
    // Constructor 2
    Sales_data(string &book):bookNo(book){}; // 1. Constructor initilizer list
                                             // 2. In-class initilizers
    // Constructor 3
    Sales_data(string &book, unsigned uSold, double price):
     bookNo(book), unitsSold(uSold), revenue(uSold*price){};    // Constructor initilizer list
    // Constructor 4
    Sales_data(istream &is){ read(is, *this); };
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
    cout << "Enter transaction\n";
    double price;
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
    Sales_data newBook(cin);
    while(cin)
    {
        bool bookFoundInInventory = false;
        unsigned int i;
        for(i = 0; (i < Sales_data::numOfBooksInInventory) && (bookFoundInInventory == false); i++)
        {
            if(newBook.isbn() == inventory[i].isbn())
            {
                bookFoundInInventory = true;
                inventory[i].combine(newBook);
                break;
            }
        }

        if((bookFoundInInventory == false) && (Sales_data::numOfBooksInInventory < MAX_BOOKS))
        {
            inventory[i].combine(newBook);
            Sales_data::numOfBooksInInventory = i + 1;
        }
        Sales_data temp(cin);
        newBook = temp;
    }

    cout << "Read transaction using constructor 1\n";
    Sales_data ctor1Obj;

    cout << "Read transaction using constructor 2\n";
    string book2 = "constructor 2";
    Sales_data ctor2Obj(book2);

    cout << "Read transaction using constructor 3\n";
    string book3 = "constructor 3";
    Sales_data ctor3Obj(book3, 10, 10.0);

    cout << "Read transaction using constructor 4\n";
    // TODO: how to handle cin here, because from above while loop,
    // cin now contains EOF character which is not allowing to enter e
    // new transaction here!
    Sales_data ctor4Obj(cin);

    cout << "show ctor3Obj + ctor1Obj\n";
    print(cout, add(ctor3Obj, ctor1Obj));
    cout << "show ctor4Obj + ctor2Obj\n";
    print(cout, add(ctor4Obj, ctor2Obj));
    
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