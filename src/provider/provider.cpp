#include "provider.h"
#include <algorithm>
#include <vector>

Transaction::Transaction(ushort day, ushort month, double amount, bool isIncome, TransactionCategory category, std::string comment) {
    if(month > 12) month = month % 12;
    if(day > 31) std::cout << "There can't be more that 31 days in a month!";

    this->day = day;
    this->month = month;
    this->amount = amount;
    this->isIncome = isIncome;
    this->category = category;
    this->comment = comment;
}

void Provider::add_record(Transaction t) {
    this->journal.push_back(t);
}

int Provider::remove_record(int removeIndex) {
    if(removeIndex < 0 || removeIndex > this->journal.size()) return -1;

    this->journal.erase(this->journal.begin() + removeIndex);

    return 0;
}

void Provider::print_records() {
    int index = 0;
    std::vector<Transaction> trans;
    for(Transaction t : this->journal) {
        if(this->filter_config == None || this->filter_config == t.isIncome) trans.push_back(t);
    }
    FilterBy filter_conf = this->filter_config;
    std::sort(trans.begin(), trans.end(), [filter_conf](Transaction t1, Transaction t2) {
        switch(filter_conf) {
            case FilterBy::Expenses:
                return t1.amount > t2.amount;
            case FilterBy::Income:
                return t1.amount > t2.amount;
            case Category:
                return t1.category > t2.category;
            case Month:
                return t1.month < t2.month;
            case None:
                return false;
        }
    });
    for(Transaction t : trans) {
        std::cout << index << ") " <<  t.day << " day; " << t.month << " month; $" << t.amount << "; Category: " << t.category << "; Comment: " << t.comment << std::endl;
        index += 1;
    }
    std::cout << std::endl;
}

void Provider::print_statistics() {
    std::cout << "Records amount: " << this->journal.size() << std::endl;
    std::cout << "Income: " << this->general_income() << std::endl;
    std::cout << "Expenses: " << this->general_expenses() << std::endl;
    std::cout << "Balance: " << this->general_income() - this->general_expenses() << std::endl;
    std::cout << "Average expenses: " << this->avg_expenses() << std::endl << std::endl;
}

int Provider::avg_expenses() {
    int result = 0;
    int count = 0;

    for(Transaction t : this->journal) {
        if(t.isIncome) continue;

        result += t.amount;
        count += 1;
    }

    return result / count;
}

int Provider::general_income() {
    int result = 0;
    for(Transaction t : this->journal) {
        if(t.isIncome) result += t.amount;
    }
    return result;
}

int Provider::general_expenses() {
    int result = 0;
    for(Transaction t : this->journal) {
        if(!t.isIncome) result += t.amount;
    }
    return result;
}

void Provider::set_filter_by(FilterBy filterOption) {
    this->filter_config = filterOption;
}