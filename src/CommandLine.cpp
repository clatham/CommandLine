#include <cstdio>
#include "CommandLine.h"


//
//  Constructs a CommandLine object with the provided description.
//

CommandLine::CommandLine(const std::string& programDescription) :
    m_programDescription(programDescription)
{
}


//
//  Destructs a CommandLine object.
//

CommandLine::~CommandLine()
{
}


//
//  Adds a boolean option with the provided flags and description.
//

void CommandLine::addOption(const std::vector<std::string>& flags, bool *variable, const std::string& description)
{
    Option option { flags, (void *) variable, Type_Bool, description };
    m_options.push_back(option);
}


//
//  Adds an integer option with the provided flags and description.
//

void CommandLine::addOption(const std::vector<std::string>& flags, int *variable, const std::string& description)
{
    Option option { flags, (void *) variable, Type_Integer, description };
    m_options.push_back(option);
}


//
//  Adds an unsigned integer option with the provided flags and description.
//

void CommandLine::addOption(const std::vector<std::string>& flags, unsigned *variable, const std::string& description)
{
    Option option { flags, (void *) variable, Type_UInteger, description };
    m_options.push_back(option);
}


//
//  Adds a single-precision floating-point option with the provided flags and description.
//

void CommandLine::addOption(const std::vector<std::string>& flags, float *variable, const std::string& description)
{
    Option option { flags, (void *) variable, Type_Float, description };
    m_options.push_back(option);
}


//
//  Adds a double-precision floating-point option with the provided flags and description.
//

void CommandLine::addOption(const std::vector<std::string>& flags, double *variable, const std::string& description)
{
    Option option { flags, (void *) variable, Type_Double, description };
    m_options.push_back(option);
}


//
//  Adds a std::string option with the provided flags and description.
//

void CommandLine::addOption(const std::vector<std::string>& flags, std::string *variable, const std::string& description)
{
    Option option { flags, (void *) variable, Type_String, description };
    m_options.push_back(option);
}


//
//  Parses the provided arguments to see if any of the defined options are
//  present.  Returns false if an unknown argument is found; otherwise,
//  returns true.
//

bool CommandLine::parse(int argc, char *argv[]) const
{
    // for each argument, skipping the program name
    for(int index = 1; index < argc; ++index)
    {
        std::string arg(argv[index]);
        std::string value;
        bool valueIsSeparate = false;
        
        
        // if arg contains an equal, then we need to split the value from the arg
        std::size_t pos = arg.find("=");
        
        if(pos != std::string::npos)
        {
            value = arg.substr(pos + 1);
            arg.resize(pos);
        }

        // otherwise, if there's a next arg, let's assume that's the value
        else if(index + 1 < argc)
        {
            value = argv[index + 1];
            valueIsSeparate = true;
        }
        
        
        bool foundArgument = false;
        
        for(Option option : m_options)
        {
            for(std::string flag : option.flags)
            {
                if(arg.compare(flag) == 0)
                {
                    foundArgument = true;

                    switch(option.type)
                    {
                        case Type_Bool:
                            if(value.compare("true") != 0  &&  value.compare("false") != 0)
                            {
                                valueIsSeparate = false;
                            }

                            *((bool *) option.pointer) = (bool)(value.compare("false") != 0);
                            break;
                        
                        case Type_Integer:
                            *((int *) option.pointer) = std::atoi(value.c_str());
                            break;
                        
                        case Type_UInteger:
                            *((unsigned *) option.pointer) = (unsigned) std::atoi(value.c_str());
                            break;
                        
                        case Type_Float:
                            *((float *) option.pointer) = (float) std::atof(value.c_str());
                            break;
                        
                        case Type_Double:
                            *((double *) option.pointer) = std::atof(value.c_str());
                            break;
                        
                        case Type_String:
                            *((std::string *) option.pointer) = value;
                            break;
                    }
                }
            }
        }

        if(!foundArgument)
        {
            fprintf(stderr, "error unknown argument \"%s\"\n", arg.c_str());
            return false;
        }

        if(foundArgument  &&  valueIsSeparate)
        {
            ++index;
        }
    }

    return true;
}


//
//  Prints the program description and argument usage to stdout using the
//  provided width as the maximum number of columns.
//

void CommandLine::printUsage(int maxWidth) const
{
    // TODO:  pre-calculate the flag width so that all flags and comments
    // align.

    // TODO:  obey the max width.
    
    printf(
        "\n"
        "%s\n",
        m_programDescription.c_str());
    
    for(Option option : m_options)
    {
        for(int flagIndex = 0; flagIndex < option.flags.size(); ++flagIndex)
        {
            if(flagIndex == 0)
            {
                printf("    ");
            }

            printf("%s", option.flags[flagIndex].c_str());
            
            if(option.flags.size() > flagIndex + 1)
            {
                printf(", ");
            }
        }
        
        printf(":    %s\n", option.description.c_str());
    }
}
