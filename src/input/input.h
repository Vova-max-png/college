#include "../provider/provider.h"

class Input {
    private:
        Provider provider;
        bool is_active = true;

        Transaction generate_transaction();

        void print_help();

    public:
        Input();
        void handle_input();
};