# AntichessAI

AI to play forced capture chess, but we still want to win

Created for CO 456 project

## Build and run

To compile for the CO 456 tournament, navigate to the root folder and run:  
`cmake . -DDEBUG=OFF -DCLI_MODE=OFF -DLICHESS_MODE=OFF`  
`make`  
`./AntichessAI`

Options explanation:

- `-DCLI_MODE=ON` enables CLI mode (prompts, etc.)
- `-DDEBUG=ON` enables debug output (lines, evaluation, search depth, etc.)
- `-DLICHESS_MODE=ON` enables lichess (colour passed in as stdin)

## References

Niklas Fiekas, python-chess, (2022), GitHub repository,  
https://github.com/niklasf/python-chess
