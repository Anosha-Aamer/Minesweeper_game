#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

class Minesweeper {
public:
    const int HIDDEN = 0;
    const int VISIBLE = 1;
    const int FLAGGED = 2;

    const int ONGOING = 0;
    const int WIN = 1;
    const int LOSE = 2;

    struct Cell {
        bool isMine;
        int count;
        int status;

        Cell() : isMine(false), count(0), status(0) {}
    };
    Cell** board;
    int rows;
    int cols;
    int numMines;
    int numRemaining;
    int numFlags;
    int status;
    clock_t startTime;
    Minesweeper() {}
    virtual ~Minesweeper() {
        for (int i = 0; i < rows; ++i) {
            delete[] board[i];
        }
        delete[] board;
    }
    virtual void initializeBoard() = 0;

    virtual void updateNeighborCounts(int row, int col) = 0;

    virtual void displayBoard() = 0;

    virtual void startGame() = 0;

    virtual void revealCell(int row, int col) = 0;

    virtual void flagCell(int row, int col) = 0;

    virtual void revealMines() = 0;

    virtual void checkGameStatus() = 0;

    virtual void recordTime(double timeTaken) = 0;
};


class Easy_level :public Minesweeper {
public:
    Easy_level(int difficulty) {
        rows = 8;
        cols = 8;
        numMines = 10;
        numRemaining = rows * cols - numMines;
        numFlags = 0;
        status = ONGOING;
        board = new Cell * [rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new Cell[cols];
        }
        initializeBoard();
    }
    virtual ~Easy_level() {
        for (int i = 0; i < rows; ++i) {
            delete[] board[i];
        }
        delete[] board;
    }
    void initializeBoard() {
        // Initialize the board with empty cells
        int minesPlaced = 0;
        while (minesPlaced < numMines) {
            int r = rand() % rows;
            int c = rand() % cols;
            if (!board[r][c].isMine) {
                board[r][c].isMine = true;
                updateNeighborCounts(r, c);
                minesPlaced++;
            }
        }
    }

    void updateNeighborCounts(int row, int col) {
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                int nr = row + dr;
                int nc = col + dc;
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !(dr == 0 && dc == 0)) {
                    board[nr][nc].count++;
                }
            }
        }
    }

    void displayBoard() {
        cout << "  ";
        for (int c = 0; c < cols; c++) {
            cout << c << " ";
        }
        cout << endl;
        for (int r = 0; r < rows; r++) {
            cout << r << " ";
            for (int c = 0; c < cols; c++) {
                if (board[r][c].status == VISIBLE) {
                    if (board[r][c].isMine) {
                        cout << "* ";
                    }
                    else if (board[r][c].count > 0) {
                        cout << board[r][c].count << " ";
                    }
                    else {
                        cout << ". ";
                    }
                }
                else if (board[r][c].status == FLAGGED) {
                    cout << "F ";
                }
                else {
                    cout << "X ";
                }
            }
            cout << endl;
        }
    }

    void startGame() {
        displayBoard();
        startTime = clock();
        while (status == ONGOING) {
            int r, c;
            char m;
            cout << "\n-------------------------------------------------\n" << endl;
            cout << "Enter the row:" << endl;
            cin >> r;
            cout << "Enter the column:" << endl;
            cin >> c;
            cout << "Enter action (L/R): " << endl;
            cin >> m;
            cout << "\n-------------------------------------------------\n" << endl;
            if (r < 0 || r >= rows || c < 0 || c >= cols) {
                cout << "Invalid cell coordinates. Please try again." << endl;
                continue;
            }

            if (m == 'L') {
                revealCell(r, c);
            }
            else if (m == 'R') {
                flagCell(r, c);
            }

            displayBoard();
            checkGameStatus();
        }
        if (status == WIN) {
            double timeTaken = (clock() - startTime) / (double)CLOCKS_PER_SEC;
            cout << "Congratulations! You won in " << timeTaken << " seconds." << endl;
            recordTime(timeTaken);
        }
        else {
            cout << "Game over! You lose." << endl;
        }
    }

    void revealCell(int row, int col) {
        if (board[row][col].status == FLAGGED) {
            cout << "This cell is flagged. You can't reveal it." << endl;
            return;
        }

        if (board[row][col].isMine) {
            revealMines();
            status = LOSE;
            return;
        }

        numRemaining--;
        board[row][col].status = VISIBLE;

        if (board[row][col].count == 0) {
            // If the cell has no adjacent mines, recursively reveal its neighbors
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    int nr = row + dr;
                    int nc = col + dc;
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !(dr == 0 && dc == 0) && board[nr][nc].status != VISIBLE) {
                        revealCell(nr, nc);
                    }
                }
            }
        }
    }

    void flagCell(int row, int col) {
        if (board[row][col].status == VISIBLE) {
            cout << "This cell is already revealed. You can't flag it." << endl;
            return;
        }

        if (board[row][col].status == FLAGGED) {
            board[row][col].status = HIDDEN;
            numFlags--;
        }
        else {
            board[row][col].status = FLAGGED;
            numFlags++;
        }
    }

    void revealMines() {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (board[r][c].isMine) {
                    board[r][c].status = VISIBLE;
                }
            }
        }
    }

    void checkGameStatus() {
        if (numRemaining == 0 && numFlags == numMines) {
            status = WIN;
        }
    }

    void recordTime(double timeTaken) {
        ofstream file("top_times.txt", ios::app);
        if (file.is_open()) {
            string name;
            cout << "Enter your name: ";
            cin >> name;
            file << name << " " << timeTaken << endl;
            file.close();
        }
    }
};
class Intermediate_level :public Minesweeper {
public:
    Intermediate_level(int difficulty) {
        rows = 16;
        cols = 16;
        numMines = 40;
        numRemaining = rows * cols - numMines;
        numFlags = 0;
        status = ONGOING;
        board = new Cell * [rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new Cell[cols];
        }
        initializeBoard();
    }
    virtual ~Intermediate_level() {
        for (int i = 0; i < rows; ++i) {
            delete[] board[i];
        }
        delete[] board;
    }
    void initializeBoard() {
        // Initialize the board with empty cells
        int minesPlaced = 0;
        while (minesPlaced < numMines) {
            int r = rand() % rows;
            int c = rand() % cols;
            if (!board[r][c].isMine) {
                board[r][c].isMine = true;
                updateNeighborCounts(r, c);
                minesPlaced++;
            }
        }
    }

    void updateNeighborCounts(int row, int col) {
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                int nr = row + dr;
                int nc = col + dc;
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !(dr == 0 && dc == 0)) {
                    board[nr][nc].count++;
                }
            }
        }
    }

    void displayBoard() {
        cout << "  ";
        for (int c = 0; c < cols; c++) {
            cout << c << " ";
        }
        cout << endl;
        for (int r = 0; r < rows; r++) {
            cout << r << " ";
            for (int c = 0; c < cols; c++) {
                if (board[r][c].status == VISIBLE) {
                    if (board[r][c].isMine) {
                        cout << "* ";
                    }
                    else if (board[r][c].count > 0) {
                        cout << board[r][c].count << " ";
                    }
                    else {
                        cout << ". ";
                    }
                }
                else if (board[r][c].status == FLAGGED) {
                    cout << "F ";
                }
                else {
                    cout << "X ";
                }
            }
            cout << endl;
        }
    }

    void startGame() {
        displayBoard();
        startTime = clock();
        while (status == ONGOING) {
            int r, c;
            char m;
            cout << "\n-------------------------------------------------\n" << endl;
            cout << "Enter the row:" << endl;
            cin >> r;
            cout << "Enter the column:" << endl;
            cin >> c;
            cout << "Enter action (L/R): " << endl;
            cin >> m;
            cout << "\n-------------------------------------------------\n" << endl;

            if (r < 0 || r >= rows || c < 0 || c >= cols) {
                cout << "Invalid cell coordinates. Please try again." << endl;
                continue;
            }

            if (m == 'L') {
                revealCell(r, c);
            }
            else if (m == 'R') {
                flagCell(r, c);
            }

            displayBoard();
            checkGameStatus();
        }
        if (status == WIN) {
            double timeTaken = (clock() - startTime) / (double)CLOCKS_PER_SEC;
            cout << "Congratulations! You won in " << timeTaken << " seconds." << endl;
            recordTime(timeTaken);
        }
        else {
            cout << "Game over! You lose." << endl;
        }
    }

    void revealCell(int row, int col) {
        if (board[row][col].status == FLAGGED) {
            cout << "This cell is flagged. You can't reveal it." << endl;
            return;
        }

        if (board[row][col].isMine) {
            revealMines();
            status = LOSE;
            return;
        }

        numRemaining--;
        board[row][col].status = VISIBLE;

        if (board[row][col].count == 0) {
            // If the cell has no adjacent mines, recursively reveal its neighbors
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    int nr = row + dr;
                    int nc = col + dc;
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !(dr == 0 && dc == 0) && board[nr][nc].status != VISIBLE) {
                        revealCell(nr, nc);
                    }
                }
            }
        }
    }

    void flagCell(int row, int col) {
        if (board[row][col].status == VISIBLE) {
            cout << "This cell is already revealed. You can't flag it." << endl;
            return;
        }

        if (board[row][col].status == FLAGGED) {
            board[row][col].status = HIDDEN;
            numFlags--;
        }
        else {
            board[row][col].status = FLAGGED;
            numFlags++;
        }
    }

    void revealMines() {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (board[r][c].isMine) {
                    board[r][c].status = VISIBLE;
                }
            }
        }
    }

    void checkGameStatus() {
        if (numRemaining == 0 && numFlags == numMines) {
            status = WIN;
        }
    }

    void recordTime(double timeTaken) {
        ofstream file("top_times.txt", ios::app);
        if (file.is_open()) {
            string name;
            cout << "Enter your name: ";
            cin >> name;
            file << name << " " << timeTaken << endl;
            file.close();
        }
    }
};
class Advance_level :public Minesweeper {
public:
    Advance_level(int difficulty) {
        rows = 30;
        cols = 30;
        numMines = 99;
        numRemaining = rows * cols - numMines;
        numFlags = 0;
        status = ONGOING;
        board = new Cell * [rows];
        for (int i = 0; i < rows; ++i) {
            board[i] = new Cell[cols];
        }
        initializeBoard();
    }
    virtual ~Advance_level() {
        for (int i = 0; i < rows; ++i) {
            delete[] board[i];
        }
        delete[] board;
    }
    void initializeBoard() {
        // Initialize the board with empty cells
        int minesPlaced = 0;
        while (minesPlaced < numMines) {
            int r = rand() % rows;
            int c = rand() % cols;
            if (!board[r][c].isMine) {
                board[r][c].isMine = true;
                updateNeighborCounts(r, c);
                minesPlaced++;
            }
        }
    }

    void updateNeighborCounts(int row, int col) {
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                int nr = row + dr;
                int nc = col + dc;
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !(dr == 0 && dc == 0)) {
                    board[nr][nc].count++;
                }
            }
        }
    }

    void displayBoard() {
        cout << "  ";
        for (int c = 0; c < cols; c++) {
            cout << c << " ";
        }
        cout << endl;
        for (int r = 0; r < rows; r++) {
            cout << r << " ";
            for (int c = 0; c < cols; c++) {
                if (board[r][c].status == VISIBLE) {
                    if (board[r][c].isMine) {
                        cout << "* ";
                    }
                    else if (board[r][c].count > 0) {
                        cout << board[r][c].count << " ";
                    }
                    else {
                        cout << ". ";
                    }
                }
                else if (board[r][c].status == FLAGGED) {
                    cout << "F ";
                }
                else {
                    cout << "X ";
                }
            }
            cout << endl;
        }
    }

    void startGame() {
        displayBoard();
        startTime = clock();
        while (status == ONGOING) {
            int r, c;
            char m;
            cout << "\n-------------------------------------------------\n" << endl;
            cout << "Enter the row:" << endl;
            cin >> r;
            cout << "Enter the column:" << endl;
            cin >> c;
            cout << "Enter action (L/R): " << endl;
            cin >> m;
            cout << "\n-------------------------------------------------\n" << endl;

            if (r < 0 || r >= rows || c < 0 || c >= cols) {
                cout << "Invalid cell coordinates. Please try again." << endl;
                continue;
            }

            if (m == 'L') {
                revealCell(r, c);
            }
            else if (m == 'R') {
                flagCell(r, c);
            }

            displayBoard();
            checkGameStatus();
        }
        if (status == WIN) {
            double timeTaken = (clock() - startTime) / (double)CLOCKS_PER_SEC;
            cout << "Congratulations! You won in " << timeTaken << " seconds." << endl;
            recordTime(timeTaken);
        }
        else {
            cout << "Game over! You lose." << endl;
        }
    }

    void revealCell(int row, int col) {
        if (board[row][col].status == FLAGGED) {
            cout << "This cell is flagged. You can't reveal it." << endl;
            return;
        }

        if (board[row][col].isMine) {
            revealMines();
            status = LOSE;
            return;
        }

        numRemaining--;
        board[row][col].status = VISIBLE;

        if (board[row][col].count == 0) {
            // If the cell has no adjacent mines, recursively reveal its neighbors
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    int nr = row + dr;
                    int nc = col + dc;
                    if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && !(dr == 0 && dc == 0) && board[nr][nc].status != VISIBLE) {
                        revealCell(nr, nc);
                    }
                }
            }
        }
    }

    void flagCell(int row, int col) {
        if (board[row][col].status == VISIBLE) {
            cout << "This cell is already revealed. You can't flag it." << endl;
            return;
        }

        if (board[row][col].status == FLAGGED) {
            board[row][col].status = HIDDEN;
            numFlags--;
        }
        else {
            board[row][col].status = FLAGGED;
            numFlags++;
        }
    }

    void revealMines() {
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (board[r][c].isMine) {
                    board[r][c].status = VISIBLE;
                }
            }
        }
    }

    void checkGameStatus() {
        if (numRemaining == 0 && numFlags == numMines) {
            status = WIN;
        }
    }

    void recordTime(double timeTaken) {
        ofstream file("top_times.txt", ios::app);
        if (file.is_open()) {
            string name;
            cout << "Enter your name: ";
            cin >> name;
            file << name << " " << timeTaken << endl;
            file.close();
        }
    }
};

int main() {
    cout << "-------------------WELCOME TO MINESWEEPER GAME-----------------------" << endl;
    int difficulty;
    cout << "Choose the difficulty level from the following list:" << endl;
    cout << "1.\tEasy Level\n2.\tIntermediate Level\n3.\tAdvance Level" << endl << endl;
    cin >> difficulty;
    cout << "\n-------------------------------------------------------------------------\n" << endl;
    cout << "\n--------------------You are entering in the game--------------------------\n" << endl;
    cout << "\nWISH YOU GOOD LUCK!!!!!!!!!!!!!\n" << endl;
    cout << "\n============================================================================\n" << endl;
    Minesweeper* game = nullptr;
    if (difficulty == 1) {
        game = new Easy_level(difficulty);
        game->startGame();
    }
    else if (difficulty == 2) {
        game = new Intermediate_level(difficulty);
        game->startGame();
    }
    else if (difficulty == 3) {
        game = new Advance_level(difficulty);
        game->startGame();
    }
    else {
        cout << "Invalid Number is entered:(" << endl;
    }
    
    delete[] game;
    cout << "\n-------------------------HOPE YOU ENJOY THIS GAME---------------------------\n" << endl;

    return 0;
}
