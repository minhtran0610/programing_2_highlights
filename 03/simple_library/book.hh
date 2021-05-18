#ifndef BOOK_HH
#define BOOK_HH

#include <string>
#include "date.hh"


class Book
{
public:
    // Constructor
    Book(const std::string& author, const std::string& title);

    // Destructor
    ~Book();

    // Print the information of the book
    void print();

    // Loan the book
    void loan(Date& loan_date);

    // Renew the book
    void renew();

    // Return the book
    void give_back();

private:
    const std::string author_;
    const std::string title_;
    bool available_;
    Date loan_start_;
    Date loan_end_;
};

#endif // BOOK_HH
