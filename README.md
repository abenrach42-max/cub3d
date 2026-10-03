*This project has been created as part of the 42 curriculum by abenrach and hcissoko.*

# cub3D

## Description

cub3D is a first-person renderer inspired by Wolfenstein 3D, the first FPS in video game history. The program reads a scene description file (`.cub`), builds a maze from it, and displays a "realistic" 3D view of the inside of that maze from the player's point of view.

The rendering is done with **ray-casting**: for every vertical column of the window, a ray is cast from the player's position and advanced through the grid with a DDA algorithm until it hits a wall. The distance to that wall gives the height of the column to draw, and the exact hit point gives the texture column to sample. A different texture is drawn depending on the face of the wall that was hit (North, South, East, West), while the floor and the ceiling are filled with two colors read from the scene file.

Everything is drawn into a single MiniLibX image that is pushed to the window once per frame, which keeps the display smooth while moving.

## Instructions

### Requirements

- Linux
- `cc`, `make`, `git`
- X11 development headers (`libx11-dev`, `libxext-dev`) and the math library

### Compilation

```bash
make
```

The Makefile clones the MiniLibX from its official repository on the first build, compiles it together with the libft, then builds the `cub3D` binary.

Available rules:

| Rule | Effect |
| --- | --- |
| `all` | builds `cub3D` (default rule) |
| `clean` | removes the object files |
| `fclean` | removes the object files, the binary and the cloned MiniLibX |
| `re` | `fclean` then `all` |

### Execution

```bash
./cub3D maps/map1.cub
```

The program takes exactly one argument: a scene description file with the `.cub` extension.

### Controls

| Key | Action |
| --- | --- |
| `W` / `S` | move forward / backward |
| `A` / `D` | strafe left / right |
| `←` / `→` | turn the point of view left / right |
| `ESC` | close the window and quit |
| red cross | close the window and quit |

## Scene file format

A `.cub` file contains six configuration elements, then the map. The elements can be written in any order, separated by one or more spaces or empty lines, but the map always comes last.

| Identifier | Meaning |
| --- | --- |
| `NO` | path to the north texture |
| `SO` | path to the south texture |
| `WE` | path to the west texture |
| `EA` | path to the east texture |
| `F` | floor color, `R,G,B` in range [0,255] |
| `C` | ceiling color, `R,G,B` in range [0,255] |

The map itself uses six characters only: `0` for an empty space, `1` for a wall, `N`, `S`, `E` or `W` for the starting position and orientation of the player, and the space character, which is a valid part of the map.

Example:

```
NO textures/trueadam.xpm
SO textures/tungtung.xpm
WE textures/mumur.xpm
EA textures/laglu.xpm
F 160,82,45
C 100,149,254

1111111
1000001
10N0001
1111111
```

## Error handling

When anything is wrong in the scene file, the program exits cleanly and prints `Error` followed by an explicit message. The cases that are detected include:

- wrong number of arguments, or a file that is not a readable `.cub` file
- a missing, duplicated or malformed element
- a color outside [0,255], with a missing component or with too many digits
- a texture that cannot be loaded
- a character that is not allowed in the map
- an empty line inside the map
- no player, or more than one player
- a map that is not closed by walls, which is checked with a flood fill starting from the player

All heap memory is freed on every exit path, including the ones triggered by `ESC` and by the window's red cross.

## Technical choices

- **DDA ray-casting**: the ray is advanced from grid line to grid line instead of step by step, which avoids both missed walls and useless iterations.
- **Camera plane**: the direction vector and a perpendicular camera plane vector are stored for the player. Rotation is a single 2D rotation applied to both, and the field of view comes from the length of the plane vector.
- **Perpendicular distance**: the distance used for the wall height is the one projected on the camera plane, not the euclidean distance, which removes the fisheye effect.
- **Single image buffer**: the frame is written into one MiniLibX image with a direct write into its buffer, then displayed once, instead of calling `mlx_pixel_put` for every pixel.
- **Parsing in two passes**: the file is read once for the configuration elements, then a second time for the map, which keeps each function short and makes error reporting explicit.
- **Collision detection**: each axis is tested separately before the position is updated, so the player slides along a wall instead of being blocked.

## Resources

- [Lode Vandevenne's ray-casting tutorial](https://lodev.org/cgtutor/raycasting.html) — the reference for the DDA algorithm, the camera plane and textured walls
- [MiniLibX documentation (42 Docs)](https://harm-smits.github.io/42docs/libs/minilibx) — images, hooks and event handling
- [MiniLibX repository](https://github.com/42paris/minilibx-linux)

### Use of AI

AI (Claude) was used as a review and testing assistant, never as a code generator for the core of the project. Concretely, it was used to:

- review the parser and the map validation, which revealed an out-of-bounds read in the flood fill on maps with lines of different lengths, an integer overflow on color values, a memory leak when an identifier was duplicated, and a map split by an empty line being accepted
- explain the reasoning behind each of these bugs, so the fixes could be written and understood by us
- review the Makefile rules, in particular the ordering problem between cloning the MiniLibX and compiling the object files
- help write this README

The ray-casting, the parsing and the rendering were designed and written by us. Every suggestion was tested, checked with Valgrind and the Norminette, and reviewed with peers before being kept.
