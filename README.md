# Raylib Pong Game

A classic Pong game implementation using the Raylib graphics library in C++.

## Features

- **Single Player vs AI** - Play against a computer opponent
- **Score Tracking** - Keep track of wins for both player and AI
- **Smooth Ball Physics** - Realistic ball bouncing with angle variation
- **Responsive Controls** - Smooth paddle movement
- **FPS Display** - Optional frame rate monitoring

## Controls

| Key | Action |
|-----|--------|
| `UP Arrow` | Move paddle up |
| `DOWN Arrow` | Move paddle down |
| `F` | Toggle FPS display |
| `R` | Reset game and scores |

## Gameplay

- Use the UP and DOWN arrow keys to control your paddle (left side)
- The AI controls the right paddle and will follow the ball
- Score points by getting the ball past your opponent's paddle
- The ball will bounce off the top and bottom walls
- Ball angle changes based on where it hits your paddle (hit near edges for sharper angles)
- First to score the most points wins!

## AI Behavior

The AI opponent:
- Follows the ball's Y position consistently
- Moves at 2.2 speed units (player moves at 4.0 for advantage)
- Provides a fair but beatable challenge
- No complex prediction or cheating - just simple ball tracking

## Requirements

- **Raylib** - Graphics library for C++
- **C++ Compiler** - Supporting C++11 or later
- **Operating System** - Windows, macOS, or Linux

## Building

1. Install Raylib on your system
2. Compile the source file:
   ```bash
   g++ -o pong main.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
   ```
3. Run the executable:
   ```bash
   ./pong
   ```

## Game Structure

```
├── Player Paddle (Left) - User controlled
├── AI Paddle (Right) - Computer controlled  
├── Ball - Bounces between paddles
├── Score Display - Shows current points
└── Center Line - Visual court divider
```

## Tips for Winning

- **Use angles** - Hit the ball with the edges of your paddle for sharper bounces
- **Control the pace** - You move faster than the AI, use this to your advantage
- **Vary your shots** - Change between high and low returns to confuse the AI
- **Stay centered** - Position yourself well to return difficult shots

## Technical Details

- **Frame Rate** - Locked at 120 FPS for smooth gameplay
- **Ball Speed** - Starts at 3.0 horizontal, 2.0 vertical
- **Paddle Size** - 25x100 pixels
- **Ball Radius** - 10 pixels
- **Screen Resolution** - 800x450 pixels

## Customization

You can easily modify game parameters in the code:

- `aiSpeed` - AI paddle movement speed
- `ballDirectionX/Y` - Initial ball velocity
- `player.width/height` - Paddle dimensions
- `ballRadius` - Ball size
- `screenWidth/Height` - Game resolution

## License

This project is open source. Feel free to modify and distribute.

---

**Enjoy playing Pong!** 🏓
