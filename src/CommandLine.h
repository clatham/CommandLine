#pragma once
#include <string>
#include <vector>


class CommandLine
{
    public:
        CommandLine(const std::string& programDescription);
        ~CommandLine();
        
        void addOption(const std::vector<std::string>& flags, bool *variable, const std::string& description);
        void addOption(const std::vector<std::string>& flags, int *variable, const std::string& description);
        void addOption(const std::vector<std::string>& flags, unsigned *variable, const std::string& description);
        void addOption(const std::vector<std::string>& flags, float *variable, const std::string& description);
        void addOption(const std::vector<std::string>& flags, double *variable, const std::string& description);
        void addOption(const std::vector<std::string>& flags, std::string *variable, const std::string& description);
        
        bool parse(int argc, char *argv[]) const;
        
        void printUsage(int maxWidth = 80) const;
        
    private:
        enum TypeEnum
        {
            Type_Bool,
            Type_Integer,
            Type_UInteger,
            Type_Float,
            Type_Double,
            Type_String
        };
        
        struct Option
        {
            std::vector<std::string> flags;
            void *pointer;
            TypeEnum type;
            std::string description;
        };
        
        std::string m_programDescription;
        std::vector<Option> m_options;
};
