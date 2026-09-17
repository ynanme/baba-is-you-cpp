# Baba Is You — C++ Recreation

A C++ recreation of **Baba Is You**, developed as a two-person academic project at Université Paris Cité.

The project focuses on dynamic rule management, object-oriented design and memory management in C++, with a graphical interface built using SFML.

## Features

- Dynamic creation and removal of game rules
- PUSH and PULL mechanics
- Undo and redo
- Object interactions such as WIN, DEFEAT, SINK, HOT/MELT and OPEN/SHUT
- Object transformations such as `WALL IS BABA`
- 11 playable levels
- Normal progression mode
- Explorer mode with unrestricted level selection
- Text-based level loading

## Architecture

The project separates the game logic from rendering and user interaction.

The main components are:

- **Game** — core game engine and rule application
- **Board** — stores the characters currently present on the board
- **Ruler** — detects dynamic rule changes
- **Loader** — creates levels from text configuration files
- **View** — SFML-based graphical interface
- **Observer system** — propagates board and rule-change events

The `Ruler` avoids rescanning the whole board after every move and instead inspects configurations around moved word tiles that may have created or destroyed a rule.

Undo/redo is implemented using reversible actions rather than full copies of the game state.

For a detailed explanation of the architecture, game engine and memory-management choices, see the original project report:

[`doc/rapport.pdf`](doc/rapport.pdf)

The original presentation is also available here:

[`doc/presentation.pdf`](doc/presentation.pdf)

## Requirements

- C++11-compatible compiler
- GNU Make
- SFML

On Ubuntu/Debian:

```bash
sudo apt install g++ make libsfml-dev
```

## Build

```bash
git clone https://github.com/ynanme/baba-is-you-cpp.git
cd baba-is-you-cpp
make
```

## Run

```bash
make run
```

`make run` will build the executable first if necessary.

## Clean

```bash
make clean
```

## Controls

| Key | Action |
| --- | --- |
| Arrow keys | Move |
| Ctrl + Arrow keys | Move while pulling |
| Ctrl + Z | Undo |
| Ctrl + Y | Redo |

## Levels

Levels are stored as text files in:

```text
res/levels/
```

The loader makes it possible to create additional levels without modifying the game engine.

## Authors

Developed by [**Badr MOTAIM**](https://github.com/Badr04-dev) and [**Yendoumban NANMEDIGOU**](https://github.com/ynanme) as an academic project at **Université Paris Cité**.

## Third-party assets

This is a free, non-commercial academic project inspired by **Baba Is You**.

Some graphical assets and the bundled font are third-party works and are not covered by any license that may apply to the source code.

See [`THIRD_PARTY_ASSETS.md`](THIRD_PARTY_ASSETS.md) for attribution and licensing information.

This project is not affiliated with or endorsed by the creators of **Baba Is You**.
