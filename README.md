# 🧟 Zombiecide

> A terminal-based zombie survival strategy game. Eliminate every zombie on the board to advance levels — before the outbreak consumes the world.

---

## Table of Contents

- [Overview](#overview)
- [Requirements](#requirements)
- [Installation](#installation)
- [How to Play](#how-to-play)
  - [Starting the Game](#starting-the-game)
  - [Board & Levels](#board--levels)
  - [Weapons](#weapons)
  - [Zombie Behavior](#zombie-behavior)
  - [Scoring](#scoring)
  - [Exiting the Game](#exiting-the-game)
- [Sound Effects](#sound-effects)
- [FAQ](#faq)

---

## Overview

**Zombiecide** is a console-based strategy game for Windows, compiled for x86-64 architecture. The player must clear a grid-based board of zombies using a selection of weapons. The board grows in size as the player progresses through levels, and the game ends when the board reaches its maximum size of **9×9**.

---

## Requirements

| Requirement | Details |
|-------------|---------|
| OS | Windows (64-bit) |
| Runtime | No additional runtime required |
| Terminal | Windows Command Prompt or Windows Terminal (ANSI color support recommended) |
| Audio files | Must be present in the same directory as the executable (see [Sound Effects](#sound-effects)) |

---

## Installation

1. Download or clone this repository.
2. Place `zombiecide.exe` in a folder of your choice.
3. Ensure all `.wav` audio files are in the **same directory** as the executable.
4. Open a terminal in that directory and run:

```cmd
zombiecide.exe
```

---

## How to Play

### Starting the Game

Upon launch, the game will play a welcome sound and ask:

```
Do you want instructions on how to play the game? [Y/N]
```

Type `Y` to read the in-game FAQ or `N` to start immediately.

You will then be prompted to choose how many different **types of zombies** you want on the board, and whether you want **extra resources**.

---

### Board & Levels

The game is played on a **grid (table)** that grows with each completed level. The number of levels depends on your **starting board size**:

| Starting Board Size | Levels to Complete |
|---------------------|--------------------|
| 2×2 | 7 levels |
| 7×8 | 2 levels |
| 9×9 | Final level (game complete) |

> The game is completed when the player clears the **9×9 board**.

---

### Weapons

Each turn, you are prompted to select a weapon. Three weapons are available:

#### 🔵 Plasmagun — `P` / `p`
Fires along an entire **row or column** from a chosen side.

1. Press `P` when prompted for a weapon.
2. Choose the **side** from which the plasma blast will originate.
3. Enter the **coordinates** for the shot.

#### 💣 Bomb — `B` / `b`
Drops a bomb at a **specific coordinate**, affecting an area around the target.

1. Press `B` when prompted for a weapon.
2. Enter the **coordinates** where the bomb should be dropped.
3. Coordinates must be within the board boundaries.

#### 🧠 Neurogun — `N` / `n`
A high-power weapon that affects **multiple zombies** simultaneously.

1. Press `N` when prompted for a weapon.
2. Enter the **coordinates** for the neurogun.

> ⚠️ The Neurogun **cannot** be used when only a single zombie remains.

#### ❌ Exit — `X` / `x`
Press `X` at the weapon selection prompt to **quit the game** immediately.

---

### Zombie Behavior

Zombies are **sound-reactive** — they move in the direction from which sound originates. For example:

- Sound from **above** → zombies move **up**
- Plan your weapon usage accordingly to group and eliminate zombies efficiently

---

### Scoring

The score is calculated using the following formula:

```
score = (zombies_killed × points_per_zombie) + zombies_killed²
```

The game tracks and displays:

- **Points** per action: `[POINTS]: Your points are X`
- **Total score**: `[TOTAL POINTS]: X`
- **Total zombies killed**: `[TOTAL ZOMBIES KILL]: X`
- **Playtime**: `[PLAYTIME]: X minutes X seconds`
- **Courses (turns)**: `[COURSES]: X`

---

### Exiting the Game

To exit at any time, press `X` or `x` when prompted to select a weapon. The game will log your session with a logout timestamp.

---

## Sound Effects

The following `.wav` files must be present in the same directory as `zombiecide.exe`:

| File | Trigger |
|------|---------|
| `welcome.wav` | Game startup |
| `soundtrack1.wav` | Background music loop |
| `zombie.wav` | Zombie placement / encounter |
| `plasmagun.wav` | Plasmagun fired |
| `bomb.wav` | Bomb dropped |
| `neurogun.wav` | Neurogun used |
| `nothing.wav` | No effect / missed shot |

> Missing audio files will not crash the game but may result in silent actions.

---

## FAQ

The game includes an in-game FAQ accessible at startup. Topics covered:

1. What is the purpose of the game?
2. How many courses are there?
3. How to use the Plasmagun
4. How to use Bombing
5. How to use the Neurogun
6. How is the score calculated?
7. What do zombies do?
8. How to quit the game

---

## Build Info

| Property | Value |
|----------|-------|
| Architecture | x86-64 |
| Platform | Windows (PE32+) |
| Compiler | GCC 15.2.0 (MinGW-Builds, win32-seh) |
| Subsystem | Console |

---

> *"The game's purpose is to eliminate all the zombies on the board to get to the next level until the zombie outbreak ends and Earth returns back to normal..."*