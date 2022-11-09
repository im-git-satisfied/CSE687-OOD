#include "MapInterface.h"

class Map : public MapInterface
{
    public:
        Map();
        virtual void tokenMap(std::string key, std::string value) override;
        virtual std::vector<std::pair<std::string,std::vector<int>>> getWordBuffer() override;
        virtual bool checkIsFull() override;
        virtual void clearBuffer() override;
    
    private:
        std::string tokenize(std::string word);
        void fileExport(std::string key, int value);

        std::vector<std::pair<std::string,std::vector<int>>> wordBuffer;
        bool isFull;

};