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

# sfml header files location
/opt/homebrew/Cellar/sfml/2.6.1

# compile src use make
# reference: https://github.com/Beatzoid/sfml-macos.git
make

# run app
./bin/app

# to compile and run in one command
make run

```

# config
**Window**
- width
- height
- frameLimit
- fullScreen(bool)

**Font**
- fontPath(string)
- fontSize(int)
- R(int)
- G(int)
- B(int)

**Player**
- shapeRadius(int)
- collisionRadius(int)
- speed(float)
- fillColor(int,int,int)
- outlineColor(int,int,int)
- outlineThickness(int)
- shapeVertices(int)

**Enemy**
- shapeRadius(int)
- collisionRadius(int)
- speedMin(int)
- speedMax(int)
- outlineColor(int,int,int)
- outlineThickness(int)
- minVertices(int)
- maxVertices(int)
- smallLifespan(int)
- spawnInterval(int)

**Bullet**
- shapeRadius(int)
- collisionRadius(int)
- speed(int)
- fillColor(int)
- outlineColor(int,int,int)
- outlineThickness(int)
- shapeVertices(int)
- lifeSpan(int)