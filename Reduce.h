#include "ReduceInterface.h"

class Reduce : public ReduceInterface
{
    public:
        Reduce();
        virtual std::vector<std::pair<std::string,std::vector<int>>> reduce(std::string key, std::vector<int> values) override;
    
    private:
        void clearBuffer();
        void fileExport(std::string key, int value);

        std::vector<std::pair<std::string,std::vector<int>>> reduceBuffer;
};
