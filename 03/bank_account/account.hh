#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>

class Account
{
public:
    // Constructor
    Account(const std::string& owner, bool has_credit = false);

    // More methods
    void print() const;
    void save_money(int sum);
    void set_credit_limit(int sum);
    bool take_money(int sum);
    void transfer_to(Account& acc,int sum);
    int get_balance();

private:
    // Generates IBAN (based on running_number_ below).
    // Allows no more than 99 accounts.
    void generate_iban();

    // Used for generating IBAN.
    // Static keyword means that the value of running_number_ is the same for
    // all Account objects.
    // In other words, running_number_ is a class-wide attribute, there is
    // no own copies of it for each object of the class.
    static int running_number_;

    // More attributes/methods
    const std::string owner_;
    bool has_credit_ = false;
    std::string iban_;
    int balance_ = 0;
    int credit_limit_ = 0;
};

#endif // ACCOUNT_HH
