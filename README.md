# AntichessAI

AI to play forced capture chess, but we still want to win

Created for CO 456 project

## To Run normally

from root folder  
`cmake . -DDEBUG=OFF -DCLI_MODE=OFF -DLICHESS_MODE=OFF`  
`make`  
`./AntichessAI`

(Or optionally for CLI: `cmake . -DCLI_MODE=ON`)  
(Or optionally for Debugging: `cmake . -DDEBUG=OFF`)  
commands above can also be combined using multiple flags similar to line 10  
`make`  
`./AntichessAI`

## References

src/cpp-chess sourced from https://github.com/pjpuzzler/cpp-chess
