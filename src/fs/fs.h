#include "../input/input.h"

class FileSystem {
    static int count_sections();
    static int parse_double(std::ifstream *stream, std::string string, std::string error_message, std::pair<double, double> limits);

    public:
        static int save_into_file(std::vector<Transaction>);
        static std::vector<Transaction> load_from_file();
};