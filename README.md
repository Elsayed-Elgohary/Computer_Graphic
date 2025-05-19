## Tic Tac Toe Game (OpenGL Version with AI)

This is a graphical implementation of the classic **Tic Tac Toe** game using **OpenGL** in C++. The game supports two modes: 
- **Player vs Player**
- **Player vs AI (Smart Opponent)**

###  Features:
- Graphical user interface built with OpenGL.
- Smooth animations for drawing X and O.
- Smart AI that makes intelligent moves based on game state.
- Score counter for both players.
- User-friendly and intuitive gameplay.
- Reset option to start a new round easily.

###  AI Logic:
The AI uses a simple decision-making strategy:
- Checks for winning moves first.
- Blocks opponent from winning if possible.
- Prioritizes center, corners, then sides for optimal play.

###  Technical Concepts Used:
- **OpenGL Functions**: `glBegin`, `glVertex`, `glEnd`, `glClear`, `glFlush`, etc.
- **Mouse Input Handling**: Detecting player clicks and responding accordingly.
- **Game State Management**: Managing turns, checking win conditions.
- **Basic AI Logic**: Conditional checks for smart decision-making.
- **Graphics Drawing**: Drawing the grid, X and O using OpenGL primitives.
- **Timers and Animations**: To animate moves and improve UX.

###  Files:
- `main.cpp`: The main game logic and rendering code.
- `AI.cpp / AI.h`: (if separated) Logic for the AI opponent.
- `graphics_utils.h`: (optional) Helper functions for drawing shapes.

---

###  How to Run:
1. Make sure OpenGL is installed and configured in your IDE (like Code::Blocks).
2. Compile the project using your compiler.
3. Run the executable and enjoy!

