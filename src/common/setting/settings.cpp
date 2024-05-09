#include "common/setting/settings.hpp"
#include "common/log/log.hpp"
#include <cstdlib>
#include <unistd.h>
#include <cstring>

namespace common {

static Settings g_settings;

Settings &Settings::get_instance()
{
    return g_settings;
}

void Settings::parse_args(int argc, char *argv[])
{
    int opt;
    while((opt = getopt(argc,argv,"d:i:o:h:j:O")) != -1)
    {
        switch(opt)
        {
            case 'd':
                log_level = (atoi(optarg) > 4 || atoi(optarg) < 0) ? 0 : atoi(optarg);
                break;
            case 'i':
                input_file = optarg;
                break;
            case 'o':
                output_file = optarg;
                break;
            case 'h':
                say_help();
                exit(0);
                break;
            case 'j'
                thread_num = atoi(optarg);
                break;
            case 'O':
                opt_level = 1;
                break;
            default:
                LOG_FATAL("Unknown option: %c", opt);
                say_help();
                break;
        }
    }
}

void Settings::say_help()
{
    LOG_INFO("Usage: ./pascc [options]");
    LOG_INFO("Options:");
    LOG_INFO("  -d <level>  Set log level(0-4: MIN-MAX)");
    LOG_INFO("  -i <file>   Set input file");
    LOG_INFO("  -o <file>   Set output file");
    LOG_INFO("  -h          Show this help message");
    LOG_INFO("  -O          Enable optimization");
}

} // namespace common