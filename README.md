# Minesweeper Game in C++

A console-based Minesweeper game implemented in C++ with three difficulty levels (Easy, Intermediate, and Advanced). This project demonstrates classical Minesweeper gameplay with dynamic board sizing, mine placement, user interaction, and timing functionality, all through a clean command-line interface.

---

## Features

- Three difficulty levels with adjustable board sizes and mine counts:
  - Easy: 8x8 grid with 10 mines
  - Intermediate: 16x16 grid with 40 mines
  - Advanced: 30x30 grid with 99 mines
- Classic Minesweeper gameplay:
  - Reveal cells
  - Flag suspected mines
  - Recursive reveal of adjacent empty cells
- Real-time board display with row and column indices
- Game status tracking: Ongoing, Win, Lose
- Score tracking via timing — records player's completion time
- Stores fastest times in a text file (`top_times.txt`)
- Input validation for coordinates and actions
- User-friendly console prompts and messages

---

## Follow on-screen instructions to:

- Choose difficulty level (1, 2, or 3)
- Enter cell coordinates to reveal or flag cells
- Try to clear the board without detonating any mines

---

## Controls

- **Input row and column:** Enter integers corresponding to the cell you want to interact with.
- **Action:**  
  - `L` — Left-click (reveal cell)  
  - `R` — Right-click (flag or unflag cell)  

---

## Gameplay Notes

- Revealing a cell with a mine ends the game with a loss, revealing all mines.
- Revealing a cell with zero neighboring mines will recursively reveal adjacent cells.
- Flagging can be toggled on hidden cells to mark suspected mines.
- Winning requires revealing all non-mine cells and flagging all mines correctly.
- Upon winning, you will be prompted to enter your name to record your completion time.
- Recorded times are saved in `top_times.txt` in the format `Name Time`.

---
## Project Structure Overview

- `Minesweeper` (abstract base class):
  - Defines the game board and core attributes.
  - Declares pure virtual methods for board initialization, display, and gameplay actions.

- `Easy_level`, `Intermediate_level`, `Advance_level` (derived classes):
  - Implement specific board sizes, mine counts, and gameplay logic.
  - Override abstract methods for initialization, display, interaction, and status checks.

- `main()`:
  - Prompts for difficulty level.
  - Instantiates the appropriate game class.
  - Starts the gameplay loop.

---


## Author

Developed by Anosha Aamer.

---

## Acknowledgments

Thanks to the classic Minesweeper game for inspiration and educational coding challenges.

---

**Enjoy playing Minesweeper!**


