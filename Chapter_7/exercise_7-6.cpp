#include <iostream>
#include <string> 
using namespace std;

struct Sales_data
{
    string bookName;
    double revenue = 0.0;
    unsigned numOfBooksSold = 0;
    static unsigned int numOfBooksInInventory;
    void combine(Sales_data trans);
    string isbn() const;
};

unsigned int Sales_data::numOfBooksInInventory = 0;

void Sales_data::combine(Sales_data trans)
{
    bookName = trans.bookName;
    numOfBooksSold += trans.numOfBooksSold;
    revenue += trans.revenue;
}

string Sales_data::isbn() const
{
    return bookName;
}

const unsigned int MAX_BOOKS = 100; 
istream& read(istream &is, Sales_data &item);
void print(ostream &os, Sales_data &item);
Sales_data add(Sales_data &lhs, Sales_data &rhs);

istream& read(istream &is, Sales_data &item)
{
    double price;
    is >> item.bookName >> item.numOfBooksSold >> price;
    item.revenue = item.numOfBooksSold * price;
    return is;
}

void print(ostream &os, Sales_data &item)
{
    os << item.bookName << "  "
    << item.numOfBooksSold << "  "
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
    while(cin >> newBook.bookName >> newBook.numOfBooksSold >> pricePerBook)
    {
        newBook.revenue = pricePerBook * newBook.numOfBooksSold;
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
    }

    if(Sales_data::numOfBooksInInventory > 0)
    {
        for(int i = 0; i < Sales_data::numOfBooksInInventory; i++)
        {
            cout << i+1 << ". ";
        }
    }
    else
    {
        cerr << "No Data?!" << endl;
    }

    return 0;
}