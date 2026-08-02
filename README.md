# Cub3D 🔫

This project has been created as part of the 42 curriculum by **aelbouaz** and **lpieck**.

## 📖 Description

Cub3D is a 42 School project focused on the topic of **raycasting**, where you play as a character that moves in a 3D-lookalike simulation (thus the "3D" in Cub3D).

The goal is simple: collect all the coins scattered across the map (if available) before making your way to the exit. The exit door isn't a normal door — it stays locked until every collectible has been picked up, so there's no rushing to the end.

Along the way, enemies will notice you and give chase if you get within their detection range, following you for up to 5 meters before giving up the pursuit. Combat works both ways: your gun damages enemies caught in its vicinity, but enemies deal damage back to you, and how much damage you take scales with how close they are to you — the nearer they are, the more it hurts.

Grab every coin, watch your back, and make it to the exit alive.

## ⚙️ Instructions

### Prerequisites

Make sure you have `make` and a compatible compiler installed on your system.

### Step 1 — Compile

In your terminal, navigate to the project directory and run:

```bash
make
```

This will compile the source files and produce the `cub3D` executable.

### Step 2 — Run

Once compiled, run the program by passing a `.cub` map file as an argument:

```bash
./cub3D your_map.cub
```

Replace `your_map.cub` with the path to your actual map file. For example:

```bash
./cub3D /Resources/maps/simple.cub
```

The program will exit cleanly if the map provided has flaws, like disordered map components, an open map, and many more error preventions. Examples of invalid maps can be found in the `/Resources/maps/invalid` folder.

## 🎮 Controls

| Key | Action |
|-----|--------|
| `W` | Walk forward |
| `S` | Walk backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `E` | Interact |
| `Space` / `LMB` | Attack |
| `Shift` | Sprint |
| `←` | Rotate camera left |
| `→` | Rotate camera right |
| Mouse move | Look left/right |
| `Esc` | Quit the game |
| `1` | Equip Katana |
| `2` | Equip Shotgun |

## 🥚 Easter Egg

Feeling goofy? Add the word `goofy` at the end of your command when launching the game and the guns will swap to a goofier set of textures:

```bash
./cub3D your_map.cub goofy
```

## 📚 Resources

- [Sin/Cos/Tan Formulas](https://www.cuemath.com/sin-cos-tan-formula/)
- [Gun Textures](https://sketchfab.com/)

---
*Part of the 42 School common core curriculum.*
