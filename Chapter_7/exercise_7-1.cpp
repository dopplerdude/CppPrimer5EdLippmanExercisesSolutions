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
};

unsigned int Sales_data::numOfBooksInInventory = 0;

void Sales_data::combine(Sales_data trans)
{
    this->bookName = trans.bookName;
    this->numOfBooksSold += trans.numOfBooksSold;
    this->revenue += trans.revenue;
}

const unsigned int MAX_BOOKS = 100; 

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
            if(newBook.bookName == inventory[i].bookName)
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
            cout << i+1 << ". "
            << inventory[i].bookName << "  "
            << inventory[i].numOfBooksSold << "  "
            << inventory[i].revenue << endl;
        }
    }
    else
    {
        cerr << "No Data?!" << endl;
    }

    return 0;
}