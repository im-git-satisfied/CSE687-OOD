#include "Function.h"



class Map :
    public Function
{
    public:
        Map();
        virtual void clearBuffer() override;
        void tokenMap(std::string key, std::string value);

        virtual std::vector<std::pair<std::string,std::vector<int>>> getBuffer() override;

        bool isFull;
        std::vector<std::pair<std::string,std::vector<int>>> wordBuffer;
    
    private:
        std::string tokenize(std::string word);
        // void fileExport(std::string key, int value);
        virtual void fileExport(std::string key, int value) override;
};