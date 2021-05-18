#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner), has_credit_(has_credit) {
    generate_iban();    
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::print() const {
    std::cout << owner_ << " : " << iban_ << " : " << balance_ << " euros" << std::endl;
}

void Account::save_money(int sum) {
    balance_ += sum;
}

void Account::set_credit_limit(int sum) {
    if (has_credit_) {
        credit_limit_ = sum;
    }
}

bool Account::take_money(int sum) {
    bool success = true;

    if (has_credit_) {
        if (sum >= credit_limit_ + balance_) {
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
            success = false;
        } else if (balance_ <= sum and sum < credit_limit_) {
            balance_ -= sum;
            credit_limit_ += balance_;
        } else {
            balance_ -= sum;
        }
    } else {
        if (sum >= balance_) {
            std::cout << "Cannot take money: balance underflow" << std::endl;
            success = false;
        } else {
            balance_ -= sum;
            success = true;
        }
    }

    if (success) {
        std::cout << sum << " euros taken: new balance of " << iban_ << " is "  << balance_ << " euros" << std::endl;
    }
    return success;
}

int Account::get_balance() {
    return balance_;
}

void Account::transfer_to(Account& acc, int sum) {
    bool transfer_success = take_money(sum);
    std::cout << transfer_success << std::endl;
    if (transfer_success) {
        acc.save_money(sum);
    } else {
        std::cout << "Transfer from " << iban_ << " failed" << std::endl;
    }
}
