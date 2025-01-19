Title: Rat In A Maze

Objective: Develop a game where the player navigates a rat (R) through a maze to reach the exit (E).
Key Features:
Dynamic maze display.
Movement controls using W, A, S, D.
Auto-solving functionality with shortest path visualization.
Move and time limits for added challenge.

Maze Generation:
Static 2D array used to represent the maze.
Symbols:

for walls.
R for the rat (player).
E for the exit.
Player Movement:
Controls: W, A, S, D.
Valid moves are within maze boundaries and avoid walls.

Global Constants:
Maze dimensions, move and time limits.
Functions:
generateMaze(): Initializes the maze.
displayMaze(): Displays the maze with colors for walls, the rat, and the exit.
processInput(): Handles player input and moves the rat.
findShortestPath(): Implements BFS for pathfinding.
Game Loop:
Runs until the player reaches the exit or limits are exceeded.

Static Representation:
plaintext
Copy code

#R #

##
E#
Dynamic Display:
Uses escape sequences for colored output.
Rat: Blue (R), Walls: Yellow (#), Exit: Green (E).

Key Bindings:

W: Move Up
A: Move Left
S: Move Down
D: Move Right
P: Auto-solve
Q: Quit Game
Gameplay Enhancements:

Beep sounds for moves and events.
Visual feedback during auto-solve.

Algorithm Steps:
Start at the rat's position.
Explore neighbors in all four directions.
Track the parent of each cell to reconstruct the path.
Stop when the exit (E) is reached.
Visualization:
Path cells marked with . during auto-solve.

Move Limit: Maximum 120 moves allowed.
Time Limit: Complete within 120 seconds.
End Conditions:
Game Over on exceeding limits.
Success on reaching the exit.

Real-Time Updates:
Dynamic maze rendering.
Move and time counter.
Audio Feedback:
Beep sounds for moves, pathfinding, and game states.
Game Over Options:
Retry (R) or Quit (Q).

Highlight important sections:
Maze generation.
Player input handling.
BFS implementation for auto-solve.
