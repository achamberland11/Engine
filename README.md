# C++ Game Engine

A custom-built C++ game engine featuring a subsystem-based architecture, integrated debugging tools with ImGui, and a custom memory management system.

## Overview

This repository contains a modular C++ game engine designed for educational or prototyping purposes. It leverages SDL3 for windowing/input and OpenGL for rendering, with a focus on a clean separation of concerns through its subsystem architecture.

### Key Features
- **Subsystem Architecture**: Modular design with dedicated systems for Rendering, Input, and Game logic.
- **Custom Memory Management**: High-performance `CPageAllocator` for efficient object allocation and deallocation.
- **Integrated Debugger**: Real-time inspection and manipulation of game entities and engine state using Dear ImGui.
- **Entity-Component System (ECS) Lite**: Flexible object model with support for components like Transform and Colliders.

## Requirements

- **Operating System**: Windows 10/11 (Primary development environment).
- **Compiler**: MSVC (Visual Studio 2022 recommended) or a C++20 compatible compiler.
- **SDKs**: 
  - Windows SDK 10.0.
  - OpenGL 3.3+.
- **Dependencies** (Included in `external/`):
  - [SDL3](https://github.com/libsdl-org/SDL)
  - [Dear ImGui](https://github.com/ocornut/imgui)

## Project Structure

```text
Engine/
├── Engine/              # Main engine project
│   ├── src/             # Source code
│   │   ├── Core/        # Engine core, GameLoop, Class system
│   │   ├── Factories/   # Object/Component factories
│   │   ├── Game/        # ECS: Entity, Component, and Object logic
│   │   ├── Memory/      # Memory management (PageAllocator)
│   │   ├── Subsystems/  # Subsystems (Renderer, Input, Game)
│   │   └── Utils/       # Math and general utilities
│   └── main.cpp         # Application entry point
├── external/            # Third-party libraries (SDL3, ImGui)
└── Engine.sln           # Visual Studio Solution
```

## Setup & Run

### 1. Clone the repository
```bash
git clone <repository-url>
cd Engine
```

### 2. Build and Run
- Open `Engine.sln` in **Visual Studio** or **JetBrains Rider**.
- Set `Engine` as the StartUp project.
- Select `Debug` or `Release` configuration and `x64` platform.
- Build and run (`F5`).

## Scripts & Entry Points

- **Entry Point**: `Engine/main.cpp`
- **Main Engine Logic**: `Engine/src/Core/GameEngine.cpp`
- **Building**: Managed through Visual Studio project files (`.vcxproj`). There are no separate build scripts (e.g., CMake/Make) currently configured.

## Environment Variables

- None currently required. TODO: Add support for asset path overrides or logging levels via environment variables.

## Tests

- TODO: Implement a testing framework (e.g., GoogleTest or Catch2).
- Currently, verification is done manually through the ImGui debug windows.

## License

- TODO: Specify license (e.g., MIT). External libraries in `external/` are subject to their own respective licenses (SDL3: Zlib, ImGui: MIT).

