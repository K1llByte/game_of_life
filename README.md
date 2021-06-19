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


<!--
Serialization of a game of life
4 bytes para versão

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