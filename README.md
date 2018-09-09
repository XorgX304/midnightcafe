# MidnightCafe (0.0.3-alpha)
```
+--------------------------------------------------+
|  *  _.._    +----------------------------------+ |
|   .' .-'` * |     MidnightCafe                 | |
|  /  /  *    |             version x.x.x        | |
|  |  |       +----------------------------------+ |
|  \  '.__ .; | TRAGENALPHA (@tragenalpha)       | |
| * '._  _.'  | //beartrap Software Development  | |
|      ``   * +----------------------------------+ |
+--------------------------------------------------+
```
<a href="https://github.com/tragenalpha/midnightcafe#overview">Overview</a> • <a href="https://github.com/tragenalpha/midnightcafe#features">Features</a> • <a href="https://github.com/tragenalpha/midnightcafe/updatelog.txt">Update Log</a> • <a href="https://github.com/tragenalpha/midnightcafe/releases">Release</a> • <a href="https://github.com/tragenalpha/midnightcafe#license">License(s)</a> • <a href="https://github.com/tragenalpha/midnightcafe#prerequisites">Prerequisites</a> • <a href="https://github.com/tragenalpha/midnightcafe#compiling-and-releasing">Compiling & Release</a>

## Overview
<b>Description</b><br>
- MidnightCafe is a multipurpose tool mostly centered around the idea of being utilized in an unit where most of the time the user's action is limited due to certain restriction in which includes time, allowed programs, extensibility, access, etc... MidnightCafe's feature allows the user of the software to breakout to some of the restriction or do things that aren't normally allowed. To be more specific (although not limited to) MidnightCafe is built in the idea of targeting certain Internet Cafe restrictions and such.
- If you are looking for commands and utility, this is provided by entering ? or help in the console

<br><b>Credits & Developers</b><br>
- Developed by: TRAGENALPHA <img src="https://raw.githubusercontent.com/tragenalpha/tragenalpha.github.io/master/flare002.png"/>• <a href="https://twitter.com/tragenalpha">@tragenalpha</a> • tragenalpha@protonmail.com
- Moon ASCII by: jgs

## Features
- Currently in development, features will be placed if MidnightCafe is atleast ready for beta release.

## License
- This software is licensed under the <a href="https://github.com/tragenalpha/midnightcafe/LICENSE">GNU General Public License v3</a>.
- This software uses Boost's C++ Library which is licensed under the <a href="https://github.com/tragenalpha/midnightcafe/boost_license.txt">BSL v1</a>.

## Prerequisites
- This software uses Boost C++ library. You can acquire Boost <a href="https://www.boost.org/users/download/">here</a>.

## Compiling and Releasing
- This software is compiled using MinGW64 GCC
- Before compiling undefine DEBUG
- This program follows the C++ 11 ISO Standard
- Compiler flags: <i>-std=c++11 -fomit-frame-pointer -Os -s</i>
- Use the <i>"_create_release.cmd"</i> batch script to automatically compress and copy the necessary files. This will create a <i>"Release\\"</i> Folder (which is excluded in the .gitignore) and if upx.exe is present in the current directory it will also compress it with <i>"-9 -q -f"</i> parameter. (UPX is not included)
