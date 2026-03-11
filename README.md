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

# Review
## TP1
1. Chaque fois que vous allouez dynamiquement de la mémoire, assurez-vous qu’elle est également libérée. Chaque new ou 
new[] doit avoir un delete ou delete[] correspondant. Sinon, vous provoquez une fuite de mémoire. Il est aussi recommandé 
d’assigner nullptr au pointeur qui référençait l’objet alloué dynamiquement afin d’éviter tout accès accidentel après la 
suppression.
2. L’ordre d’initialisation des systèmes et leur arrêt doivent être inverses. Si vous initialisez le système A avant le 
système B, cela suggère que le système B a besoin de A pour fonctionner. Cela signifie que, potentiellement, B peut aussi 
avoir besoin que A fonctionne pour s’arrêter correctement. Pensez à la métaphore de la maison : on construit d’abord le 
rez-de-chaussée, puis le premier étage, puis le toit. Pour la démonter en toute sécurité, on enlève d’abord le toit, 
ensuite le premier étage, puis le rez-de-chaussée. Si vous retirez le rez-de-chaussée en premier, tout s’effondre (crash).
3. J’ai vu plusieurs personnes implémenter des fonctionnalités qui n’appartiennent pas au système correspondant. Par 
exemple, CInputSubsystem est censé traiter les entrées et permettre aux autres parties du code de vérifier l’état des 
entrées. Il ne devrait pas stocker une valeur de couleur pour l’arrière-plan, ni gérer spécifiquement la touche Espace. 
Dans notre exemple, la gestion de la couleur et la réaction à une touche précise relèvent de la logique de gameplay; 
elles devraient donc être implémentées dans CGameSubsystem.
4. Il n’est pas nécessaire que CInputSubsystem soit conservateur et n’initialise que les états des boutons au fur et à 
mesure. En général, on utilise un enum contenant toutes les touches existantes du clavier et un tableau de la taille de 
cet enum. Cela n’augmente pas beaucoup le coût mémoire du système, mais c’est bien plus performant, car au lieu de faire 
une recherche dans une map, on accède directement à un élément du tableau par index pour récupérer l’état d’une touche. 
De plus, de cette façon, il n’est pas nécessaire de réallouer de la mémoire chaque fois qu’on ajoute un nouveau bouton 
au système.
5. Il est important d’avoir un style de code et de s’y tenir. Définissez une manière précise de nommer les variables 
locales, statiques, globales, les macros, les types et les méthodes. N’importe quel style de code convient tant qu’il 
est cohérent. N’hésitez pas à consulter des styles de codage C++ populaires si vous ne souhaitez pas créer le vôtre.

## TP4
Changer l'allocateur de mémoire pour que celui-ci soit alligné. Allouer un gros bloc de mémoire et le diviser en plusieurs 
blocs plus petits (pages) à la place d'allouer chaque page indépendamment.