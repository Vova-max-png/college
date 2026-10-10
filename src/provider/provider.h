#include "../include.h"

// Transaction category enum describes what
// category the transactions belongs to
enum TransactionCategory {
    Food,
    Transport,
    Education,
    Entertainment,
    Health,
    Other,
    Scholarship,
    PartTimeJob,
    Gift,
};

struct Transaction {
    ushort day;
    ushort month;
    ushort year;
    double amount;
    bool isIncome;
    TransactionCategory category;
    std::string comment;

    Transaction(ushort day, ushort month, ushort year, double amount, bool isIncome, TransactionCategory category, std::string comment);
};

struct MostExpensiveCategory {
    TransactionCategory category;
    int amount;
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

        MostExpensiveCategory most_expensive_category();
        std::map<TransactionCategory, std::vector<Transaction>> sort_categories();

        int category_expenses(TransactionCategory category);

        bool is_income(TransactionCategory category);

        std::string category_to_string(TransactionCategory category);

        void print_statistics_header();
        std::map<TransactionCategory, double> expenses_by_category();

    public:
        Provider();
        TransactionCategory string_to_category(std::string category);
        int remove_record(int index);

        void add_record(Transaction t);
        int print_records();
        void print_statistics();
        void visualize_expenses();
        void set_filter_by(FilterBy filterOption);
};