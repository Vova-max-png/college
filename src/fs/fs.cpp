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
        if(day.empty()) continue;

        double parsed_day = parse_double(&file, day, "day", std::make_pair(1, 31));

        std::getline(file, month);

        double parsed_month = parse_double(&file, month, "month", std::make_pair(1, 12));

        std::getline(file, year);

        double parsed_year = parse_double(&file, year, "year", std::make_pair(1, 99));

        std::getline(file, amount);

        double parsed_amount = parse_double(&file, amount, "amount", std::make_pair(1, std::numeric_limits<double>::max()));

        std::getline(file, isIncome);

        int parsed_choice = std::strtoul(isIncome.c_str(), NULL, 10);
        if(isIncome != "0" && isIncome != "1") {
            std::cout << "Invalid y/n choice value found in journal file!" << "\n\n";
            parsed_choice = -1;
        }

        if(parsed_day == -1 || parsed_month == -1 || parsed_year == -1 || parsed_amount == -1 || parsed_choice == -1) {
            std::cout << "Make sure the journal file is formatted well\n\n";
            return std::vector<Transaction>();
        }

        std::getline(file, TransactionCategory);
        std::getline(file, comment);

        Transaction t(
            parsed_day,
            parsed_month,
            parsed_year,
            parsed_amount,
            parsed_choice,
            Provider::string_to_category(TransactionCategory),
            comment
        );

        transactions.push_back(t);
    }

    return transactions;
}

int FileSystem::parse_double(std::ifstream *stream, std::string string, std::string var_name, std::pair<double, double> limits) {
    double parsed_amount = Input::string_to_double(string, limits.first, limits.second);

    if(parsed_amount == -1) {
        std::cout << "Invalid " << var_name << " value in journal file!" << "\n\n";
        return -1;
    }

    return parsed_amount;
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