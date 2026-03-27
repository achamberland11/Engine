# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [0.1.4] - 27-03-2026

### Added
- **Entity Registry**: New `CEntityRegistry` class for managing all entities in the engine
- **Entity Factory**: New `CEntityFactory` class for entity creation with registration system
- **Entity Type Popup**: Added popup menu in Hierarchy window to select entity type when creating new entities
- **Game Project**: Added separate Game project for game-specific code

### Fixed
- **Pause Mode Bug**: Fixed issue where editor would immediately pause when entering play mode

## [0.1.3] - 26-03-2026

### Added
- **Scene Management**: New `CScene` class for managing entities and scene lifecycle
- **Editor Modes**: Added `EEditorMode` enum with Editor, Play, and Pause modes
- **Keyboard Shortcuts**: F5 enters play mode, ESC quits application
- **JSON Utilities**: Added `Json.cpp` and `Json.h` for JSON handling
- **Entity Factory Methods**: `CGameEngine::CreateEntity()` and `DestroyEntity()`
- **Input Helper Methods**: `GetKeyDown()`, `GetKeyUp()`, `GetKeyPressed()`, `GetKeyReleased()` static methods

### Changed
- **Engine Loop Order**: EditorSubsystem now updates before GameSubsystem
- **Input Processing**: Button state transitions now processed before event polling

## [0.1.2] - 25-03-2026

### Added
- **Doxygen Documentation**: Added comprehensive Doxygen-generated documentation in `docs/` folder

### Changed
- **Window Class Naming**: Renamed editor window classes from `C*` prefix to `E*` prefix (e.g., `CDebugWindow` → `EDebugWindow`)
- **Vector Types**: Moved vector/math types from `Math.h` to new `Vectors.h` file with `F` prefix (e.g., `Vector3` → `FVector3`)
- **Color Struct**: Merged `FColor` from `Color.h` into `Vectors.h`
- **TransformComponent**: Updated to use `FVector3` instead of `Vector3`
- **Include Cleanup**: Fixed vcxproj to remove erroneous `.cpp` include and add `Vectors.h`

### Removed
- **Color.h**: Deleted (merged into Vectors.h)
- **Legacy Vector Types**: Removed `Vector2`, `Vector3`, `Quaternion`, `Matrix4x4` from Math.h

## [0.1.1] - 24-03-2026

### Added
- **Property System**: Added `bRendered` flag to `FProperty` struct to control property visibility in editor
- **Property Rendering**: New `RenderProperty()` method in `FProperty` for inline property rendering
- **Macro Enhancement**: Added `REGISTER_PROPERTY_EX` macro for explicit `bRendered` control
- **Unique Entity Names**: Automatic unique name generation when creating entities with duplicate names
- **Component Context Menu**: Right-click popup menu for component delete/duplicate actions
- **Workspace Window**: Added workspace window

### Changed
- **Component Capabilities**: Moved `CanDuplicate`, `CanBeDisabled`, `CanBeDeleted` from virtual methods to `CClass` flags
- **Name Property**: `Name` property in components now marked as non-rendered (hidden in editor)
- **Inspector Window**: Restructured component list with context menus instead of inline buttons
- **Default Entity Name**: Changed from "New Entity" to "Entity" in hierarchy window
- **TODO Comments**: Removed numbered prefixes from TODO comments throughout codebase

### Fixed
- **Memory Leak**: `CGameSubsystem::DestroyEntity()` now properly calls `FreeObject()` to release memory
- **Singleton Components**: Added filtering to prevent duplicate singleton components (e.g., Transform)

### Removed
- **Virtual Methods**: Removed `CanDuplicate()`, `CanBeDisabled()`, `CanBeDeleted()` virtual methods from `GComponent`

## [0.1.0] - 23-03-2026

### Added
- Initial release
- Basic engine architecture with subsystems
- ImGui-based editor interface
- Entity-Component system
- Window management system
- Transform and Collider components
- Memory management with object allocation
