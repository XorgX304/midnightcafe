
/*

+--------------------+
|   *  _.._          |
|    .' .-'` *       |
|   /  /  *          |
|  |  |              | Developed by: TRAGENALPHA (@tragenalpha)
|  \  '.__ .;        | //beartrap Software (c)
| * '._  _.'         |
|      ``   *        |
|     MidnightCafe   |
+--------------------+

 Notes:
 * The inclusion of the header "thread" requires the ISO C++ 11 Library Standard
 * This program uses the Boost C++ Library
 * Compiled using MinGW
 * Compilation Flags: -std=c++11 -fomit-frame-pointer -Os -s
*/

#define DEBUG
#define _WIN32_WINNT 0x600
#define VER "0.0.2"
#include <iostream>
#include <windows.h>
#include <string>
#include <thread>
#include <shellapi.h>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

//Stores the process id as a DWORD
DWORD pid_c = 0, pid_g = 0;
//Stores the image names as a string
string pim_c = "", pim_g = "";

//Stores the delay amount between checks in force terminate
DWORD ft_checkDelay = 2000;
//Tells if the force terminate thread should terminate
bool ft_threadterminate = false;

//Stores the boolean value for the suspend through debugger, wether this method is running / used
bool util_s_dbg = false;
//Stores the last PID that was used by the suspend through debugger command
DWORD util_s_dbg_pid = 0;

void ft_thread();

int main(int argc, char *argv[]) {
    #ifdef DEBUG
        cout << "!ALERT_@main: Program is running in debug mode";
    #endif
    #ifndef DEBUG
        //Check if running Windows XP or older.
        if ((DWORD)(LOBYTE(LOWORD(GetVersion()))) <= 5) {
            cout << "WARNING COMPABILITY ISSUE: You are running a windows version older than Vista (0x600) some features will not work.";
        }

        //Show Terms of Use
        if (MessageBox(0x00000000L, "DISCLAIMER:\n* The user of this software is fully responsible for the method of usage, The developer cannot be held liable for the consequences that the user ensues due to (but not limited to) mis-use, abuse, malicious intent(s), etc...\n\nTerms of Use:\n* By continuing the use of this software you agree that you will take full responsibility and liability to your actions through this software.\n\nNote:\n* This software is open source and licensed under the GNU v3 General Public License, a copy of the license is required to be distributed with this software.", "Midnight Cafe | Terms of Use", 0x00000001L | 0x00000020L | 0x00000100L) != 1) { return 0; }
    #endif

    //Displays the banner
    cout << "\n+--------------------------------------------------+"
            "\n|  *  _.._    +----------------------------------+ |"
            "\n|   .' .-'` * |     MidnightCafe                 | |"
            "\n|  /  /  *    |             version " VER "        | |"
            "\n|  |  |       +----------------------------------+ |"
            "\n|  \\  '.__ .; | TRAGENALPHA (@tragenalpha)       | |"
            "\n| * '._  _.'  | //beartrap Software Development  | |"
            "\n|      ``   * +----------------------------------+ |"
            "\n+--------------------------------------------------+"
            ;

    //Command interpreter
    while (true) {
        cout << "\n>";
        string opt;
        getline(cin, opt);
        vector<string> _o;
        algorithm::split(_o, opt, is_any_of(" "));

        if (_o.size() != 0) {
            //Store the size in a local variable rather than calling vector::size/end repeteadly
            int _os = _o.size() - 1;

            //Help
            if (_o[0] == "?" || _o[0] == "help") {
                cout <<
                        "\n\n* Available commands:"
                        "\n? / help                            -- Shows the help dialog and the available commands."
                        "\n\nabout                               -- Shows the About dialog."
                        "\n\nexit                                -- Exits the program."
                        "\n\nconfig.pid <client pid> <guard pid> -- Configure the PID values. <guard pid> is optional"
                        "\n\nconfig.pim <client pim> <guard pim> -- Configure the PIM values. <guard pim> is optional"
                        "\n\nconfig.pim.id <parameter>           -- Configure the PIM values by known ID's. use ? parameter for help"
                        "\n\nconfig.show                         -- Show the current configuration"
                        "\n\nutil.forceterminate <delay(ms)>     -- Forces the termination of the application"
                        "\n                                     - Arguments are taken from pim. Delay parameter is optional (default:2000)"
                        "\n\nutil.suspend.dbg <pid>              -- Suspends the process by debugging it"
                        "\n\ncmd <command>                       -- Allows you to run commands like in a normal command prompt"
                        ;
            }
            //About
            else if (_o[0] == "about") {
                cout << "\n+---[About]----------------------------------------------------------------->"
                        "\n|\n| MidnightCafe version " VER
                        "\n|"
                        "\n|\n| Moon ASCII Art by: jgs"
                        "\n| License: GNU General Public License v3.0"
                        "\n| Github: https://github.com/tragenalpha/midnightcafe"
                        "\n|\n| Developed by: TRAGENALPHA (@tragenalpha)"
                        "\n|               https://tragenalpha.github.io"
                        "\n|\n| //beartrap Software (c)"
                        "\n+--------------------------------------------------------------------------->";
            }
            //Exit
            else if (_o[0] == "exit") {
                return 0;
            }
            //Configure PID
            else if (_o[0] == "config.pid") {
                if (_os > 0 && _os <= 2) {
                    pid_c = strtol(_o[1].c_str(), 0, 0);
                    if (_os == 2) {
                        pid_g = strtol(_o[2].c_str(), 0, 0);
                    }
                    cout << "config.pid Configured.";
                }
                else {
                    cout << "!ERROR_@interpreter: Insufficient/Too much parameters!";
                }
            }
            //Configure IM
            else if (_o[0] == "config.pim") {
                if (_os > 0 && _os <= 2) {
                    pim_c = _o[1];
                    if (_os == 2) {
                        pim_g = _o[2];
                    }
                    cout << "config.pim Configured.";
                }
                else {
                    cout << "!ERROR_@interpreter: Insufficient/Too much parameters!";
                }
            }
            //Show Configuration Settings
            else if (_o[0] == "config.show") {
                cout << "pid_c: " << pid_c
                    << "\npid_g: " << pid_g
                    << "\npim_c: " << pim_c
                    << "\npim_g: " << pim_g;
            }
            //Force Terminate
            else if (_o[0] == "util.forceterminate") {
                if (_os > 0) {
                    ft_checkDelay = strtol(_o[1].c_str(), 0, 0);
                }
                if (pim_c == "" || pim_g == "") {
                    cout << "Force terminate started with " << ft_checkDelay << "ms of delay. Press enter to stop.\n";
                    ft_threadterminate = true;
                    thread ft_thread_h (ft_thread);
                    ft_thread_h.detach();
                    cin.get();
                    ft_threadterminate = false;
                }
                else {
                    cout << "!ERROR_@interpreter: config.pim Configuration error";
                }
            }
            //Run Commands
            else if (_o[0] == "cmd") {
                if (_os < 1) {
                    cout << "!ERROR_@interpreter: Parameter error";
                }
                else {
                    string fullcom = "";
                    for (int x = 1; x <= _os; x++) {
                        fullcom += " " + _o[x];
                    }
                    system(fullcom.c_str());
                }
            }
            //Suspend through Debugger
            else if (_o[0] == "util.suspend.dbg") {
                if (_os == 1 && !util_s_dbg) {
                    util_s_dbg_pid = strtol(_o[1].c_str(), 0, 0);
                    if (DebugActiveProcess(util_s_dbg_pid)) {
                        cout << "Debugger was successfuly attached to the process!\n\nNote: Terminating this application without deattaching the debugger will cause the debugged program to be terminated as well!\n* To deattach the debugger / disable this command, simply enter the command again without parameters.";
                        util_s_dbg = true;
                    }
                    else {
                        util_s_dbg_pid = 0;
                        cout << "!ERROR_@interpretter: Debugger can't be attached";
                    }
                }
                else if (util_s_dbg_pid != 0 && util_s_dbg && _os == 0) {
                    if (DebugActiveProcessStop(util_s_dbg_pid)) {
                        cout << "Debugger was successfuly deattached from the process!";
                        util_s_dbg = false;
                        util_s_dbg_pid = 0;
                    }
                    else {
                        cout << "!ERROR_@interpretter: Unable to deattach the debugger for the process.";
                    }
                }
                else {
                    //too lazy to make a bunch of if else statements just for the purpose of verbosity
                    cout << "!ERROR_@interpreter: Command cannot be executed due to varying reasons.";
                }
            }
            //Unknown Command
            else {
                cout << "!ERROR_@interpreter: Unknown Command. Enter ? or help to see the available commands";
            }
        }
        else {
            cout << "!ERROR_@interpreter: No user input.";
        }

    }

    return 0;
}

//The thread of force terminate that handles the counter and killings by spawning taskkill.exe
void ft_thread() {
    int _cc = 0;
    string _ftt;
    if (pim_c != "" && pim_g != "") {
        _ftt += "/c taskkill /f /im ";
        _ftt += pim_c;
        _ftt += "&taskkill /f /im ";
        _ftt += pim_g;
    }
    else if (pim_c != "" && pim_g == "") {
        _ftt += "/c taskkill /f /im ";
        _ftt += pim_c;
    }
    else if (pim_c == "" && pim_g != "") {
        _ftt += "/c taskkill /f /im ";
        _ftt += pim_g;
    }

    while (ft_threadterminate) {
        if (pim_c != "") {
            ShellExecute(NULL, "open", "cmd.exe", _ftt.c_str(), NULL, SW_HIDE);
            _cc++;
        }
        cout << "\rCycle count: " << _cc;
        Sleep(ft_checkDelay);
    }
}
