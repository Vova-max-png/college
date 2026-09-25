#include "./provider/provider.h"

int main(int argc, char* argv[]) {
    Provider provider;

    provider.add_record(Transaction(14, 3, 350., true, TransactionCategory::Other, "Salary"));
    provider.add_record(Transaction(14, 8, 499, false, TransactionCategory::Entertainment, "Yandex plus"));
    provider.add_record(Transaction(2, 5, 2760, false, TransactionCategory::Entertainment, "Arc Raiders purchase"));
    
    provider.print_records();
    provider.print_statistics();

    provider.set_filter_by(FilterBy::Expenses);
    provider.print_records();

    provider.remove_record(0);
    provider.print_records();
}