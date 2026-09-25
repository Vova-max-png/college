#include "../include.h"

// Transaction category enum describes what
// category the transactions belongs to
enum TransactionCategory {
    Food = 0,
    Transport = 0,
    Education = 0,
    Entertainment = 0,
    Health = 0,
    Other = 1 | 0,
    Scholarship = 1,
    PartTimeJob = 1,
    Gift = 1
};

struct Transaction {
    ushort day;
    ushort month;
    double amount;
    bool isIncome;
    TransactionCategory category;
    std::string comment;

    Transaction(ushort day, ushort month, double amount, bool isIncome, TransactionCategory category, std::string comment);
};

// Filter enum that is used to describe 
// a filterting way
enum FilterBy {
    Expenses,
    Income,
    Category,
    Month,
    None
};

class Provider {
    private:
        std::vector<Transaction> journal;

        FilterBy filter_config = None;

        int general_income();
        int general_expenses();
        int avg_expenses();

    public:
        void add_record(Transaction t);
        int remove_record(int index);
        void print_records();
        void print_statistics();
        void set_filter_by(FilterBy filterOption);
};