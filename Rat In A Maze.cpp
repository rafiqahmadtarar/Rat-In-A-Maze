#include <iostream>
#include <queue>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>
#include <conio.h>  // For _getch()
#include <windows.h>  // For Beep()

using namespace std;

const int WIDTH = 40;
const int HEIGHT = 20;
char maze[HEIGHT][WIDTH];
int ratX = 1, ratY = 1;
int moveCount = 0;
bool gameRunning = true;
auto gameStart = chrono::steady_clock::now();

const int MAX_MOVES = 120;
const int MAX_TIME = 120;  // Time limit in seconds

int dx[] = {0, 0, -1, 1};  // Left, Right, Up, Down
int dy[] = {-1, 1, 0, 0};

bool firstMove = false; 

void generateMaze() {
    char staticMaze[HEIGHT][WIDTH] = {
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#','#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#',' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', ' ', '#', ' ', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#',' ', ' ', '#', ' ', '#', ' ', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ',' ', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#', ' ', '#'},
        {'#', ' ', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', ' ', '#', '#', '#', '#', ' ', ' ',' ', ' ', '#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', ' ', '#', '#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', ' ','#', '#', '#', '#', ' ', '#', ' ', '#', '#', '#', '#', ' ', '#', ' ', '#', ' ', '#', '#', '#', '#'},
        {'#', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ','#', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#', ' ', ' ', '#'},
        {'#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', ' ', ' ','#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', ' ', ' ', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ','#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', '#'},
        {'#', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', ' ','#', '#', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#'},
        {'#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ','#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', ' ', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', ' ','#', ' ', '#', ' ', '#', '#', '#', ' ', '#', '#', '#', '#', '#', '#', '#', ' ', '#', '#', '#', '#'},
        {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ','#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#'},
        {'#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ','#', ' ', '#', ' ', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', '#'},
        {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#','#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', ' ','#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', ' ', ' ', 'E'},
        {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#','#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
    };


    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            maze[i][j] = staticMaze[i][j];
        }
    }
}

void beepSound(int frequency, int duration) {
    Beep(frequency, duration);  // Generate a beep sound with given frequency and duration
}

void displayMaze() {
    cout << "\033[H\033[J";  // Clear screen
    auto now = chrono::steady_clock::now();
    auto elapsed = chrono::duration_cast<chrono::seconds>(now - gameStart).count();
    int timeLeft = MAX_TIME - elapsed;  // Calculate remaining time
    if (timeLeft < 0) {
        timeLeft = 0;  // Prevent negative time display
    }
    
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||\n";
    cout << "|||||||||||||||                   ||||||||||||||\n";
    
    cout << "|||||||||||||||Welcome To The Maze||||||||||||||\n";
    
    cout << "|||||||||||||||                   ||||||||||||||\n";
    cout << "||||||||||||||||||||||||||||||||||||||||||||||||\n";
    cout<<endl;
    
    

    
    cout << "Navigate the rat (R) to the exit (E).\n";
    
    cout << "Moves Left: " << MAX_MOVES - moveCount << " | Time Left: " << timeLeft << "s\n";
    cout << "Use w,a,s,d keys to move, 'p' to auto-solve, and 'q' to quit.\n\n";

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == ratY && j == ratX)
                cout << "\033[1;34mR\033[0m";  // Blue Rat
            else if (maze[i][j] == '#')
                cout << "\033[1;33m#\033[0m";  // Yellow Wall
            else if (maze[i][j] == 'E')
                cout << "\033[1;32mE\033[0m";  // Green Exit
            else
                cout << maze[i][j];
        }
        cout << endl;
    }
}

bool findShortestPath() {
    queue<pair<int, int>> q;
    bool visited[HEIGHT][WIDTH] = {false};
    pair<int, int> parent[HEIGHT][WIDTH];

    q.push({ratY, ratX});
    visited[ratY][ratX] = true;

    while (!q.empty()) {
        auto [currentY, currentX] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++) {
            int newY = currentY + dy[i];
            int newX = currentX + dx[i];

            if (newY >= 0 && newY < HEIGHT && newX >= 0 && newX < WIDTH &&
                (maze[newY][newX] == ' ' || maze[newY][newX] == 'E') &&
                !visited[newY][newX]) {

                visited[newY][newX] = true;
                parent[newY][newX] = {currentY, currentX};
                q.push({newY, newX});

                if (maze[newY][newX] == 'E') {
                    int pathY = newY, pathX = newX;
                    while (!(pathY == ratY && pathX == ratX)) {
                        maze[pathY][pathX] = '.';
                        auto [prevY, prevX] = parent[pathY][pathX];
                        pathY = prevY;
                        pathX = prevX;
                        displayMaze();
                        this_thread::sleep_for(chrono::milliseconds(100));
                    }
                    beepSound(1000, 300);  // Beep sound when path is found
                    return true;
                }
            }
        }
    }
    beepSound(500, 300);  // Beep sound when no path is found
    return false;
}

void displayGameOver() {
    cout << "|||||||||||||||||||||||||||||||||||||||\n";
    cout << "|||||||||||||||         |||||||||||||||\n";
    
    cout << "|||||||||||||||GAME OVER|||||||||||||||\n";
    
    cout << "|||||||||||||||         |||||||||||||||\n";
    cout << "|||||||||||||||||||||||||||||||||||||||\n";
    
   
    cout << "Try Again? Press (r)' to restart, or (q) to quit.\n";
    beepSound(400, 400);  // Beep sound for game over
}

void processInput(char input) {
    int newX = ratX;
    int newY = ratY;

    switch (tolower(input)) {
        case 'w': // Up
            newY--;
            beepSound(500, 100);  // Beep sound for movement
            break;
        case 's': // Down
            newY++;
            beepSound(500, 100);  // Beep sound for movement
            break;
        case 'a': // Left
            newX--;
            beepSound(500, 100);  // Beep sound for movement
            break;
        case 'd': // Right
            newX++;
            beepSound(500, 100);  // Beep sound for movement
            break;
        case 'p':
            if (findShortestPath()) {
                displayMaze();
                cout << "Path found!.\n";
                beepSound(1500, 500);  // Beep sound when the solution is found
        gameRunning = false; 
                displayGameOver();
                char retryInput = _getch();
                if (retryInput == 'r') {
                    gameRunning = true;
                    moveCount = 0;
                    ratX = 1;
                    ratY = 1;
                    firstMove = false;  // Reset first move for the new game
                    generateMaze();
                    gameStart = chrono::steady_clock::now();
                } else if (retryInput == 'q') {
                    gameRunning = false;
                }
            } else {
                cout << "No path found." << endl;
            }
            return;
        case 'q':
            gameRunning = false;
            return;
        default:
            return;
    }

    // Start the timer on the first move
    if (!firstMove) {
        gameStart = chrono::steady_clock::now();  // Start the timer
        firstMove = true;  // Mark that the first move has been made
    }

    if (maze[newY][newX] == ' ' || maze[newY][newX] == 'E') {
        ratX = newX;
        ratY = newY;
        moveCount++;

        auto now = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::seconds>(now - gameStart).count();

        // Check for move and time limits
        if (moveCount >= MAX_MOVES || elapsed >= MAX_TIME) {
            displayMaze();
            cout << "Game Over: ";
            if (moveCount >= MAX_MOVES) cout << "Move limit reached.\n";
            if (elapsed >= MAX_TIME) cout << "Time limit reached.\n";
            displayGameOver();
            char retryInput = _getch();
            if (retryInput == 'r') {
                gameRunning = true;
                moveCount = 0;
                ratX = 1;
                ratY = 1;
                firstMove = false;  // Reset first move for the new game
                generateMaze();
                gameStart = chrono::steady_clock::now();
            } else if (retryInput == 'q') {
                gameRunning = false;
            }
            return;
        }

        if (maze[ratY][ratX] == 'E') {
            displayMaze();
            cout << "Congratulations! You reached the exit in " << moveCount << " moves!" << endl;
            cout << endl;
            beepSound(1500, 500);  // Beep sound when exit is reached
            displayGameOver();
			    gameRunning = false;  // Display game over options
            char retryInput = _getch();
            if (retryInput == 'r') {
                gameRunning = true;
                moveCount = 0;
                ratX = 1;
                ratY = 1;
                firstMove = false;  // Reset first move for the new game
                generateMaze();
                gameStart = chrono::steady_clock::now();
            } else if (retryInput == 'q') {
                gameRunning = false;
            }
            return;
        }
    }
}
int main() {
    srand(time(0));
    generateMaze();

    while (gameRunning) {
        auto now = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::seconds>(now - gameStart).count();

        // Check for time or move limits before accepting any more input
        if (moveCount >= MAX_MOVES || elapsed >= MAX_TIME) {
            displayMaze();
            if (moveCount >= MAX_MOVES) cout << "Move limit reached.\n";
            if (elapsed >= MAX_TIME) cout << "Time limit reached.\n";
            displayGameOver();
            char retryInput = _getch();
            if (retryInput == 'r') {
                gameRunning = true;
                moveCount = 0;
                ratX = 1;
                ratY = 1;
                generateMaze();
                gameStart = chrono::steady_clock::now();
            } else if (retryInput == 'q') {
                gameRunning = false;
            }
            continue;  // Skip further iterations and recheck the game state
        }

        displayMaze();
        char input = _getch();
        processInput(input);
    }

    cout << "Game Over." << endl;
    return 0;
}