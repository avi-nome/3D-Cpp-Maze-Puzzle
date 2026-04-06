# 3D C++ Maze Puzzle (Raycasting Engine)

A pseudo-3D puzzle game built from scratch using **C++** and **SDL3**. This project implements a raycasting engine similar to the one used in *Wolfenstein 3D* (1992).

## 🚀 Features
- **Custom 3D Engine**: Built using the DDA (Digital Differential Analyzer) algorithm for fast ray-wall intersections.
- **Puzzle Logic**: Navigate from the **Green Start Room** to the **Golden Exit Wall**.
- **Dynamic Shading**: Walls get darker as they move further away to create a sense of depth.
- **Collision Detection**: Solid walls prevent the player from walking out of bounds.

## 🕹️ Controls
- **W / S**: Move Forward / Backward
- **A / D**: Rotate View (Left / Right)

## 🛠️ Technical Setup
- **Language**: C++
- **Graphics Library**: SDL3 (32-bit)
- **Compiler**: MinGW (i686-w64-mingw32)

### How to Compile and Run
Ensure you have SDL3 installed in `C:\SDL3`. Use the following command in your terminal:

```powershell
g++ main.cpp -o main -I"C:\SDL3\include" -L"C:\SDL3\lib" -lSDL3 -lmingw32
.\main
