# Tic-Tac-Toe (C, Minimax AI)

This project is a **command-line Tic-Tac-Toe game written in C**, featuring a computer opponent with **three difficulty levels** implemented using the **Minimax algorithm**.

The game runs entirely in the terminal and supports **Player vs Computer** gameplay.  
A precompiled Windows executable (`.exe`) is provided so users can play without compiling the source code.

---

## Controls (How to Play)

The board positions are numbered as follows:

|1 | 2 | 3 |
|--|--|--|
|4 | 5 | 6 |
|7 | 8 | 9 |


- You play as **X**
- The computer plays as **O**
- Enter a number **1–9** to place your move
- You cannot place a move on an occupied spot

---

## How to Download and Play (No Compilation Required)

### Requirements
- Windows OS

### Steps

1. Download or clone this repository
2. Locate the `.exe` file in the **root directory**
3. Double-click the `.exe` to launch the game
4. Follow the on-screen prompts:
   - A coin flip decides who goes first
   - Select a difficulty level (1–3)
   - Enter numbers **1–9** to make your moves

---

## Features

- Classic 3×3 Tic-Tac-Toe
- Player vs Computer
- Terminal-based board rendering
- Win and draw detection
- Randomized coin flip for first turn

---

## Difficulty Levels Explained

| Difficulty | Description |
|----------|------------|
| Easy | Introduces intentional mistakes and random decisions |
| Medium | Limited-depth (imperfect) minimax |
| Impossible | Full minimax search (optimal play, cannot be beaten) |

---

## Game Rules

- Players take turns placing one mark per turn
- A player wins by placing **three marks in a row**:
  - Horizontally
  - Vertically
  - Diagonally
- If all spots are filled and no one wins, the game ends in a draw

---

## Source Code Overview

- Written in **standard C**
- Uses arrays to track:
  - Board availability
  - Player moves
  - Winning combinations
- AI implemented using a recursive **Minimax algorithm**
- No external dependencies beyond the C standard library

---

## Build From Source (Optional)

If you want to compile the program yourself:

```bash
gcc main.c -o tictactoe
