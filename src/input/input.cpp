#include "input.h"
#include <ios>
#include <iostream>
#include <limits>
#include <string>

Input::Input() {
    this->provider = Provider();
}

void Input::print_help() {
    std::cout << "1. Add a new record" << std::endl
        << "2. Show all records" << std::endl
        << "3. Filters" << std::endl
        << "4. Statistics" << std::endl
        << "5. Remove a record" << std::endl
        << "0. Exit" << std::endl;
}

Transaction Input::generate_transaction() {
    ushort day;
    ushort month;
    ushort year;

    double amount;
    bool isIncome;

    TransactionCategory category;
    std::string comment;

    std::cout << "Day: ";
    std::cin >> day;
    std::cout << std::endl;

    std::cout << "Month: ";
    std::cin >> month;
    std::cout << std::endl;
                
    std::cout << "Year: ";
    std::cin >> year;
    std::cout << std::endl;

    std::cout << "Amount: ";
    std::cin >> amount;
    std::cout << std::endl;

    std::cout << "Is income(1/0): ";
    std::cin >> isIncome;
    std::cout << std::endl;

    std::cin.ignore();

    std::string tempCategory;
    std::cout << "Category: ";
    std::getline(std::cin, tempCategory);
    std::cout << std::endl;
    category = this->provider.string_to_category(tempCategory);

    std::cout << "Comment: ";
    std::getline(std::cin, comment);
    std::cout << std::endl;

    Transaction newT(day, month, year, amount, isIncome, category, comment);
    return newT;
};

void Input::handle_input() {
    while(this->is_active) {
        ushort choise;

        print_help();
        std::cout << "Your choice: ";
        std::cin.clear();
        std::cin >> choise;
        std::cout << std::endl;
        if(!std::cin >> choise) {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );
            std::cout << "You must enter a number!" << std::endl;
            continue;
        }

        switch(choise) {
            case 1: {
                Transaction t = generate_transaction();
                this->provider.add_record(t);
                break;
            }
            case 2: {
                this->provider.print_records();
                break;
            }
            case 4: {
                this->provider.print_statistics();
                break;
            }
            case 5: {
                this->provider.print_records();
                std::cout << "index to remove: ";
                ushort index;
                std::cin >> index;
                this->provider.remove_record(index);
                break;
            }
        }
    }
}