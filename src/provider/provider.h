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
    Gift
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
// the way we filter the records output
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

        std::vector<std::pair<TransactionCategory, double>> most_expensive_categories();
        std::map<TransactionCategory, std::vector<Transaction>> group_categories();

        int category_expenses(TransactionCategory category);

        void print_statistics_header();
        std::map<TransactionCategory, double> expenses_by_category();

    public:
        Provider();

        static TransactionCategory string_to_category(std::string category);
        static std::string category_to_string(TransactionCategory category);

        int remove_record(int index);

        void load_file_data();
        int save_file_data();

        void add_record(Transaction t);
        int print_records();
        void print_statistics();
        void visualize_expenses();
        void set_filter_by(FilterBy filterOption);
};