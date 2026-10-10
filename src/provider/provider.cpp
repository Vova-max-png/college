#include "provider.h"

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

    std::cout << "A new record has been added successfully!" << "\n\n";
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
int Provider::print_records() {
    int index = 0;
    std::vector<Transaction> trans;
    FilterBy filter_conf = this->filter_config;

    for(Transaction t : this->journal) {
        if(filter_conf == None || filter_conf == t.isIncome) trans.push_back(t);
    }

    if(trans.empty()) return -1;

    print_statistics_header();

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

    return 0;
}

void Provider::print_statistics_header() {
    std::cout << std::left << std::setw(4) << "№"
        << std::setw(9) << "Date"
        << std::setw(20) << "Category"
        << std::setw(16) << "Comment"
        << std::right << std::setw(12) << "Sum" << std::endl;

}

void Provider::print_statistics() {
    if(this->journal.empty()) {
        std::cout << "There are no elements in the journal yet!" << "\n\n";
        return;
    }

    MostExpensiveCategory mostExpensive = this->most_expensive_category();

    std::cout << "Records amount: " << this->journal.size() << std::endl;
    std::cout << "Income: " << this->general_income() << '\n';
    std::cout << "Expenses: " << this->general_expenses() << '\n';
    std::cout << "Balance: " << this->general_income() - this->general_expenses() << '\n';
    std::cout << "Average expenses: " << this->avg_expenses() << '\n';
    std::cout << "The most expensive: " << this->category_to_string(mostExpensive.category) << " (" << mostExpensive.amount << ")" << "\n\n";
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

std::map<TransactionCategory, std::vector<Transaction>> Provider::sort_categories() {
    std::vector<std::vector<Transaction>> sortedByCategory;

    std::vector<Transaction> journalCopy = this->journal;

    std::sort(journalCopy.begin(), 
        journalCopy.end(),
        [](const Transaction& a, const Transaction& b) {
            return a.category < b.category;
        }
    );

    std::map<TransactionCategory, std::vector<Transaction>> groups;

    for(const Transaction& transaction : journalCopy) {
        if(transaction.isIncome) continue;
        
        groups[transaction.category].push_back(transaction);
    }

    return groups;
}

MostExpensiveCategory Provider::most_expensive_category() {
    int result = 0;
    TransactionCategory resultCategory;

    std::map<TransactionCategory, std::vector<Transaction>> groups = this->sort_categories();

    for(std::pair<const TransactionCategory, std::vector<Transaction>> pair : groups) {
        int groupAmount = 0;

        TransactionCategory cuurentCategory = pair.first;
        std::vector<Transaction> transactions = pair.second;

        for(Transaction transaction : transactions) {
            groupAmount += transaction.amount;
        }

        if(groupAmount > result) {
            result = groupAmount;
            resultCategory = cuurentCategory;
        }
    }

    return MostExpensiveCategory {
        resultCategory,
        result
    };
}

Provider::Provider() {}