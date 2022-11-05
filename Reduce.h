#include "BaseMapReduce.h"

class Reduce : public BaseMapReduce
{
    public:
        Reduce();
        virtual void clearBuffer() override;
        virtual std::vector<std::pair<std::string,std::vector<int>>> getBuffer() override;
        std::vector<std::pair<std::string,std::vector<int>>> reduce(std::string key, std::vector<int> values);
    
    private:
        void exportReduce(std::string key, int value);
        virtual void fileExport(std::string key, int value) override;
        std::vector<std::pair<std::string,std::vector<int>>> reduceBuffer;

};
