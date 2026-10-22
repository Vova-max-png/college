#include "fs.h"

int FileSystem::save_into_file(std::vector<Transaction> transactions) {
    std::ofstream file("journal", std::ios::app);

    if(!file.is_open()) return -1;

    for(Transaction t : transactions) {
        file << t.day << '\n'
            << t.month << '\n'
            << t.year << '\n'
            << t.amount << '\n'
            << t.isIncome << '\n'
            << Provider::category_to_string(t.category) << '\n'
            << t.comment << "\n\n";
    }

    return 0;
}

std::vector<Transaction> FileSystem::load_from_file() {
    std::ifstream file("journal");

    if(!file.is_open()) return std::vector<Transaction>();

    std::vector<Transaction> transactions;

    int sections = count_sections();
    std::cout << "Loading " << sections << " sections\n\n";

    for(int i = 0; i < sections; i++) {
        std::string day;
        std::string month;
        std::string year;
        std::string amount;
        std::string isIncome;
        std::string TransactionCategory;
        std::string comment;

        std::getline(file, day);
        std::getline(file, month);
        std::getline(file, year);
        std::getline(file, amount);
        std::getline(file, isIncome);
        std::getline(file, TransactionCategory);
        std::getline(file, comment);

        Transaction t(
            std::strtoul(day.c_str(), NULL, 10),
            std::strtoul(month.c_str(), NULL, 10),
            std::strtoul(year.c_str(), NULL, 10),
            std::strtoul(amount.c_str(), NULL, 10),
            std::strtoul(isIncome.c_str(), NULL, 10),
            Provider::string_to_category(TransactionCategory),
            comment
        );

        transactions.push_back(t);
    }

    return transactions;
}

int FileSystem::count_sections() {
    std::ifstream file("journal");

    if(!file.is_open()) return -1;

    std::string text{std::istreambuf_iterator<char>(file), {}};
    
    int count = 0;
    for(std::size_t i = 0; (i = text.find("\n\n", i)) != std::string::npos; i+=2)
        ++count;

    return count;
}