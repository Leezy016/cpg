# cpg
fire shadow and space

# course address
https://www.youtube.com/live/UARdwTLUH5U?si=55hEDyP8qkQeqTR2

# SFML Learn
https://www.sfml-dev.org/tutorials/2.6/

# build 

https://stackoverflow.com/questions/33071296/fatal-error-sfml-graphics-hpp-no-such-file-or-directory-exists

```bash

# install sfml
brew install sfml

# compile src
g++ src/*.cpp -I/opt/homebrew/Cellar/sfml/2.6.1/include/SFML -std=c++17 -o bin/sfmlgame -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

g++ -I/opt/homebrew/Cellar/sfml/2.6.1/include -L/opt/homebrew/Cellar/sfml/2.6.1/lib -lsfml-graphics -lsfml-window -lsfml-network src/main.cpp -o prog


# sfml header files location
/opt/homebrew/Cellar/sfml/2.6.1/include/SFML

```