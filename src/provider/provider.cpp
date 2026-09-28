#include "provider.h"
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <string>

Transaction::Transaction(ushort day, ushort month, ushort year, double amount, bool isIncome, TransactionCategory category, std::string comment) {
    if(month > 12) month = month % 12;
    if(day > 31) std::cout << "There can't be more that 31 days in a month!";

    this->day = day;
    this->month = month;
    this->year = year;
    this->amount = amount;
    this->isIncome = isIncome;
    this->category = category;
    this->comment = comment;
}

// Adds a new record into journal
void Provider::add_record(Transaction t) {
    this->journal.push_back(t);
}

// Removes record from journal
int Provider::remove_record(int removeIndex) {
    if(removeIndex < 0 || removeIndex > this->journal.size()) return -1;

    this->journal.erase(this->journal.begin() + removeIndex);

    return 0;
}

bool Provider::is_income(TransactionCategory category) {
    switch(category) {
        case Scholarship:
        case PartTimeJob:
        case Gift:
        case Other: return false;
        default: return true;
    }
}

// Converts TransactionCategory type into string
// Used to output the category of the transaction
std::string Provider::category_to_string(TransactionCategory category) {
    switch(category) {
        case Food: return "Food";
        case Transport: return "Transport";
        case Education: return "Education";
        case Entertainment: return "Entertainment";
        case Health: return "Health";
        case Other: return "Other";
        case Scholarship: return "Scholarship";
        case PartTimeJob: return "Path-time job";
        case Gift: return "Gift";
    }
}

// Transforms string to TransactionCategory type
// Used to covert user's input into category
TransactionCategory Provider::string_to_category(std::string category) {
    std::transform(category.begin(), category.end(), category.begin(),
        [](unsigned char c) {return std::tolower(c);});
    if(category == "food") return Food;
    else if(category == "transport") return Transport;
    else if(category == "education") return Education;
    else if(category == "entertainment") return Entertainment;
    else if(category == "health") return Health;
    else if(category == "scholarship") return Scholarship;
    else if(category == "part-time job") return PartTimeJob;
    else if(category == "gift") return Gift;
    else return Other;
}

// Print all saved records in the journal
// Automatically applies filters of FilterBy enum set in the Provider class
void Provider::print_records() {
    print_statistics_header();
    int index = 0;
    std::vector<Transaction> trans;
    FilterBy filter_conf = this->filter_config;
    for(Transaction t : this->journal) {
        if(filter_conf == None || filter_conf == t.isIncome) trans.push_back(t);
    }
    std::sort(trans.begin(), trans.end(), [filter_conf](Transaction t1, Transaction t2) {
        switch(filter_conf) {
            case Expenses:
                return t1.amount > t2.amount;
            case Income:
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
        std::string date = std::to_string(t.day) + "." + std::to_string(t.month) + "." + std::to_string(t.year);
        std::cout << std::left << std::setw(2) << index
            << std::setw(9) << date
            << std::setw(20) << category_to_string(t.category)
            << std::setw(16) << t.comment
            << std::right << std::setw(12) << t.amount << std::endl;
        index += 1;
    }
    std::cout << std::endl;
}

void Provider::print_statistics_header() {
    std::cout << std::left << std::setw(4) << "№"
        << std::setw(9) << "Date"
        << std::setw(20) << "Category"
        << std::setw(16) << "Comment"
        << std::right << std::setw(12) << "Sum" << std::endl;

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

Provider::Provider() {}