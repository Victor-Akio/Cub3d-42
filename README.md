# Cub3d - 42SP

A Wolfeinstein-like renderer made in C using minilibX-Linux, with textures, sprites and basic map files.

## Compiling
Run `make` and you're set. Runs on Mac OS X and Linux (with XServer).
By default, the program will run with Linux framework, if you intend to use this aplication in a MAC OS,
please exchange the framework used in the `Makefile` document. 

## Running
Run `./cub3D [map_file]`, a window should appear. You can navigate through the
map using the arrow keys. Exit by closing the window or pressing ESC.
You may also, use `./cub3D --save [map_file]` to take a screenshot of the first rendered image of the
game in bmp format.

## Map file format
It's a very simple format. Open a file in your favorite text editor, make sure
you have a grid of integers (each one being it's block ID), and it should work
right out of the box. Spawn position is the first empty space available from the
top left.

```
1 1 1 1 1
1 0 2 0 1
1 0 0 0 1
1 1 1 1 1
```

Have fun!
This project was built for educational purpose.