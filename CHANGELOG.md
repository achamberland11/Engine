# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- **Property System**: Added `bRendered` flag to `FProperty` struct to control property visibility in editor
- **Property Rendering**: New `RenderProperty()` method in `FProperty` for inline property rendering
- **Macro Enhancement**: Added `REGISTER_PROPERTY_EX` macro for explicit `bRendered` control
- **Unique Entity Names**: Automatic unique name generation when creating entities with duplicate names
- **Component Context Menu**: Right-click popup menu for component delete/duplicate actions

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

## [0.1.0] - 2026-03-23

### Added
- Initial release
- Basic engine architecture with subsystems
- ImGui-based editor interface
- Entity-Component system
- Window management system
- Transform and Collider components
- Memory management with object allocation
