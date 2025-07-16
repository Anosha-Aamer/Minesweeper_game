# Minesweeper_game
A simple Minesweeper game implemented using Object-Oriented Programming in C++.


🧩 Minesweeper Game (OOP Project)
This is a console-based implementation of the classic Minesweeper game written in C++.
It is designed as an Object-Oriented Programming (OOP) semester project, demonstrating concepts like inheritance, abstraction, encapsulation, and polymorphism.

Players can choose between three difficulty levels:
Easy (8×8 grid, 10 mines)
Intermediate (16×16 grid, 40 mines)
Advance (30×30 grid, 99 mines)

✨ Features
✅ Fully playable Minesweeper game in the terminal
✅ Three difficulty levels
✅ Recursive revealing of empty cells
✅ Flagging and unflagging cells
✅ Win/Lose game status detection
✅ Time taken is recorded and saved to a file (top_times.txt)

📦 Project Structure
Minesweeper – Abstract base class defining common functionality
Easy_level, Intermediate_level, Advance_level – Derived classes implementing the game for different difficulty levels
top_times.txt – Stores records of player names and completion times

🎮 How to Play
At the start, choose your preferred difficulty level.
The board will be displayed with cells marked as X (hidden).
Enter the row and column to select a cell.
Enter:
  L → to reveal the cell
  R → to flag/unflag the cell
Win the game by revealing all non-mine cells and flagging all mines!

📌 Technologies Used
C++
Standard Library (iostream, fstream, ctime)

✏️ Author
Developed as an Object-Oriented Programming project by Anosha Aamer
