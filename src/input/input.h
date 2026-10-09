#include "../provider/provider.h"

class Input {
    private:
        Provider provider;
        bool is_active = true;

        Transaction generate_transaction();

        void print_help();

        std::string handle_input_data(std::string prompt);
        bool handle_input_acception(std::string prompt);

        double string_to_double(std::string, double min, double max);

        // TODO: try using double* instead of template to move the logic into cpp file
        template<typename T>
        void ask_user_double(T* var, std::string prompt, double min, double max) {
            std::string formattedPrompt = prompt;
            if(!formattedPrompt.empty()) {
                formattedPrompt[0] = static_cast<char>(
                    std::toupper(static_cast<unsigned char>(formattedPrompt[0]))
                );
            }

            while(*var == -1) {
                *var = this->string_to_double(this->handle_input_data(formattedPrompt + ": "), min, max);
                if(*var == -1) std::cout << "The value of " << prompt << " must be in range from " << min << " to " << max << "!" << std::endl;
            }
        }

    public:
        Input();
        void handle_input();
};