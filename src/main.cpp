#include <cstdio>
#include <string>
#include "CommandLine.h"


bool g_debug = false;
std::string g_filename;
int g_count = 0;

int main(int argc, char *argv[])
{
    CommandLine commandLine("Command-line argument test program.");
    commandLine.addOption({ "--debug", "-d" }, &g_debug, "Enables debug output.");
    commandLine.addOption({ "--filename", "-f" }, &g_filename, "Specify the filename.");
    commandLine.addOption({ "--count", "-c" }, &g_count, "Specify iteration count.");
    
    if(!commandLine.parse(argc, argv))
    {
        commandLine.printUsage();
        return 1;
    }
    
    printf("g_debug = %s\n", g_debug ? "true" : "false");
    printf("g_filename = %s\n", g_filename.c_str());
    printf("g_count = %d\n", g_count);
    return 0;
}
