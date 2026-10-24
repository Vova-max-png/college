#include "input.h"

Input::Input() {
    this->provider = Provider();
}

void Input::print_help() {
    std::cout << "1. Add a new record" << '\n'
        << "2. Show all records" << '\n'
        << "3. Filters" << '\n'
        << "4. Statistics" << '\n'
        << "5. Remove a record" << '\n'
        << "6. Visualize expenses" << '\n'
        << "7. Save data" << '\n'
        << "8. Load data" << '\n'
        << "0. Exit" << "\n\n";
}

// Generate transaction, protects each field from being set unproperly
Transaction Input::generate_transaction() {
    short day = -1;
    short month = -1;
    short year= -1;

    double amount = -1;
    bool isIncome;

    TransactionCategory category;
    std::string comment;

    this->ask_user_double<short>(&day, "day", 1, 31);

    this->ask_user_double<short>(&month, "month", 1, 12);

    this->ask_user_double<short>(&year, "year", 1, 99);

    this->ask_user_double<double>(&amount, "amount", 1, std::numeric_limits<double>::max());
    
    char input;
    isIncome = this->handle_input_acception("Is income(Y/n): ");

    std::string categoryHandler;
    categoryHandler = this->handle_input_data("Category: ");
    category = this->provider.string_to_category(categoryHandler);

    comment = this->handle_input_data("Comment: ");

    Transaction newT(day, month, year, amount, isIncome, category, comment);
    return newT;
};

ushort Input::request_choice() {
    ushort choice;

    bool running = true;

    while(running) {
        print_help();

        std::cout << "Your choice: ";
        std::cin >> choice;
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
        std::cout << std::endl;

        if(!std::cin >> choice) {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            std::cout << "You must enter a number!" << std::endl;
            continue;
        }

        running = false;
    }

    return choice;
}

// Handle user's choice
void Input::handle_input() {
    ushort choice;

    while(this->is_active) {
        choice = this->request_choice();

        switch(choice) {
            case 1: {
                Transaction t = generate_transaction();
                this->provider.add_record(t);
                break;
            }
            case 2:
                if(this->provider.print_records() == -1) {
                    std::cout << "No records were found corresponding to the filter type to be printed!\n\n";
                }
                break;
            case 3: 
                std::cout << "Choose filtering type(1. By expenses; 2. By income; 3. By category; 4. By month; 0. No filtering): ";
                int choice;
                std::cin >> choice;

                FilterBy filterType;
                switch(choice) {
                    case 1:
                        filterType = Expenses;
                        break;
                    case 2:
                        filterType = Income;
                        break;
                    case 3:
                        filterType = Category;
                        break;
                    case 4:
                        filterType = Month;
                        break;
                    default:
                        filterType = None;
                }

                this->provider.set_filter_by(filterType);
                break;
            case 4: 
                this->provider.print_statistics();
                break;
            case 5: 
                if(this->provider.print_records() == -1) {
                    std::cout << "No records were found corresponding to the filter type to be printed!\n\n";
                    continue;
                }

                std::cout << "Index to remove: ";
                ushort index;
                std::cin >> index;

                this->provider.remove_record(index);
                break;
            case 6: 
                this->provider.visualize_expenses();
                break;
            case 7: {
                int result = this->provider.save_file_data();
                if(result != 0) std::cout << "Couldn't save the data into file!\n\n";
                break;
            }
            case 8:
                this->provider.load_file_data();
                break;
            case 0:
                exit(0);
        }
    }
}

// Handle std::string input using getline
std::string Input::handle_input_data(std::string prompt) {
    std::cout << prompt << std::flush;
    std::string result;

    std::getline(std::cin, result);
    std::cout << std::endl;
    
    return result;
}

// Handle y/n acception with character check
bool Input::handle_input_acception(std::string prompt) {
    std::string result;

    do {
        std::cout << prompt << std::flush;
        std::getline(std::cin, result);
    } while(std::tolower(static_cast<unsigned char>(result[0])) != 'y' && std::tolower(static_cast<unsigned char>(result[0])) != 'n');

    std::cout << std::endl;

    return result[0] == 'y' ? true : false;
}

// Transform std::string into double with range check, returns -1 when out of range
double Input::string_to_double(std::string data, double min, double max) {
    double result = std::strtoul(data.c_str(), NULL, 10);

    if(result == 0 || result < min || result > max) return -1;

    return result;
}
