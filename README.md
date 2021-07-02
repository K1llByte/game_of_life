# Game of Life

Basic SDL2 implementation of John Conway's Game of Life

## Compiling & Running

```sh
# Just compile
make

# Compile and run
make run

# Clear compilation results
make clean
```

TODO:
- [ ] Save and load (only a bit for a cell, and position version)
- [ ] Logger
- [ ] Stop game
- [ ] Next iteration
- [ ] Edit cells



<!--

# Byte version
16*N = w*h
N = (w*h)/16

# Bit version
16*N = (w*h)/8
N = (w*h)/128

-->


<!--
Serialization of a game of life
2 bytes para versão

N - number of cells alive
w - width
h - height

if(N < (1/64)*w*h):

    version 1:
    save: every bit w*h (1 bit each cell)

else:
    version 2:
    save: positions (2*4 bytes for each position)
-->