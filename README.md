# Mnemos Evolved

This project exists because I wanted to learn how a modern game engine works behind the hood. I want to keep external dependencies at a minimum, no SDL/glfw-like libraries are used. Almost everything is done from scratch using C++ 20.

<img src="logo.png" width="200" height="200">

![LinuxBuild](https://github.com/OlivierGisselmann/mnemos-evolved/actions/workflows/build-linux.yml/badge.svg)
![WindowsBuild](https://github.com/OlivierGisselmann/mnemos-evolved/actions/workflows/build-windows.yml/badge.svg)
![Last Commit](https://img.shields.io/github/last-commit/OlivierGisselmann/mnemos-evolved)
![License](https://img.shields.io/github/license/OlivierGisselmann/mnemos-evolved)

## Features

- Minimal external dependencies — pure C++ and system APIs
- Cross-platform support: Windows, Linux
- Built with CMake using `CMakePresets.json`
- Low-level rendering (OpenGL, will add Vulkan/DX12 later)
- Modular design with extensibility in mind

### List of features (WIP)
- [x] CMake cross-platform project structure
- [x] Engine subsystems
    - [x] Logging
        - [x] Levels
        - [x] Channels
        - [x] Timestamp
    - [x] Game loop
        - [x] Fixed timestep update
        - [x] Variable timestep update
    - [x] Windowing
        - [x] Window abstraction
        - [x] Event handling
        - [x] OpenGL context
    - [x] Input
        - [x] Keycodes abstraction
        - [x] Key state
    - [ ] Events
        - [ ] Event creation
        - [ ] Event callback
    - [x] Renderer
        - [x] Renderer API abstraction
        - [x] Mesh rendering
        - [x] Material system
        - [ ] Camera (projection, orthogonal)
        - [ ] Lighting models
            - [ ] Phong
            - [ ] PBR
        - [ ] Deferred renderer
        - [ ] Post processing
    - [ ] ECS
        - [ ] Entity
        - [ ] Components
        - [ ] Scene system
        - [ ] Entity hierarchy
    - [x] Resource Manager
        - [x] File parsers
            - [x] BMP
            - [ ] JPG
            - [ ] PNG
            - [x] OBJ
            - [ ] FBX
            - [ ] GLTF
        - [ ] Asset caching
    - [ ] Editor
        - [ ] User Interface
        - [ ] Scene tree panel
        - [ ] Inspector (entities, components)
        - [ ] Asset browser
        - [ ] Profiler
    - [ ] Physics
        - [ ] Colliders
        - [ ] Rigidbodies
        - [ ] Raycasting
    - [ ] Audio
- [x] Application lifecycle management

## Build Instructions

### Clone the Repository

```bash
git clone git@github.com:OlivierGisselmann/mnemos-evolved
cd mnemos-evolved
```

### Build with CMake Presets

Make sure you have CMake ≥ 3.25:

```bash
cmake --list-presets
cmake --preset debug-linux     # or release-linux, debug-windows etc.
cmake --build --preset app-debug-linux
```

## Project Structure

```
MnemosEvolved/
├── application/         # Application source files
├── engine/              # Engine sources
├── include/             # Public headers
├── vendor/              # External dependencies
├── CMakeLists.txt       # Root CMake config
├── CMakePresets.json    # Build presets
└── README.md
```

## Running the Engine

After building, the engine executable will be in the preset-specific `out/{preset}` directory:

```bash
./out/debug-linux/Application
# OR
.\out\debug-windows\Application.exe
```

## Dependencies

I want to keep this project with minimal dependencies. For now, the only external libraries used are OS-specific APIs (e.g. window system).

## Contributing

Contributions are welcome! Open an issue for discussion before submitting large changes.

## License

GNU General Public License. See `LICENSE` for details.

## Credits

Here is a list of useful resources I used for this project:

- Effective C++ - Third Edition by Scott Meyers
- Game Engine Architecture - Third Edition by Jason Gregory
- Game Programming Patterns - Robert Nystrom
- Kohi Game Engine series by Travis Vroman