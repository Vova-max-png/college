#include "../provider/provider.h"

class FileSystem {
    static int count_sections();

    public:
        static int save_into_file(std::vector<Transaction>);
        static std::vector<Transaction> load_from_file();
};