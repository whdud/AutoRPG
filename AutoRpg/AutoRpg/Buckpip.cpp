#include "Buckpip.h"


Buckpip::Buckpip(int level)
    : Monster(level, "Buckpip",
        R"(
"                                                     ",
"                  █  ██                              ",      
"               ▒▓▓▓▓▓▓▓▓░░                           ",    
"             ▓██▓▓▓▓▓▓▓▓░░                           ",  
"           ▓▓▓▓▓▓▓██  ▓▓▓▓▓▓▓▓                       ",
"        ▓▓▓▓▓▓▓▓▓▓  ██  ██▓▓▓▓                       ",
"     ▒▓▓ ░░░░░███░██  █ ██▓▓▓▓                       ",
"     ▓ ░░░░░░░░░██      ██▓▓▓▓                       ",
"     ░░░░░░░░░░░▓▓██▒▒██▓▓▓▓██                       ",
"   █░░░░░░░░░░░░██▓▓▓▓▓▓▓▓▓▓█                        ",
"  ░░░░░░░░░░░░▓  ░▒▒▓▓▓▓████                         ",
"  ░░░░░░░░░░▒▒   ░░░████▓▓██                         ",
"  ░░░░░░░▒▒    ░░██▓▓▓▓▓▓▓▓██                        ",
"   ░░ █▓▓   █▓▓▒▒██▓▓▓▓▓▓▓▓▓▓██           ███░░      ",
"       ▓██▒▒████ ██▓▓▓▓▓▓▓▓▓▓▓▓▒▒      ██▓▓▓▓██▒▒    ",
"       ░▓▓▓▓▓▓▓▓▓▓▓▓ ▓▓▓▓▓▓▓▓▓▓▓▓▓██  ██▓▓▓▓▒▒▒▒     ",
"        ██████▓▓▓▓▓ ▓ ▓▓▓▓▓▓▓▓▓▓▓▓████▓▓▓▓██▓▓▓▓▓    ",
"        ▓▓▓▓████▓▓▓▓ ▓▓▓▓▓▓▓██▓▓▓▓▓▓▓▓▓▓▓▓▓▓██▓▓▓▓▓  ",
"        ██████████▓▓▓▓▓▓██▓▓██▓▓████▓▓▓▓▓▓▓▓██     ▓ ",
"          ██████  ▓▓▓▓▓▓▓▓████████▓▓▓▓░░▓▓▓▓▓▓██     ",
"                    ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓██  ██   ▓▓      ",
"                      ▓▓▓▓▓▓▓▓▓▓▓▓██          ▓▓     ",
"                        ████▓▓████             █     ",
"                        ▒▒  ░░                       ",
"                       ░     ░                       ",
"                    ░░▒▒    ░░░▓                     ",
"                                                     "
        )") {
}
