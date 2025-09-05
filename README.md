# CSC196_GameEngine

A lightweight C++ game engine built as part of the **CSC196** coursework.  
The goal of this project is to provide a simple but extendable framework for learning real-time rendering, input handling, and basic engine design patterns.

---

## ✨ Features
- **Core Engine Loop** – Runs update/render cycles with a clean structure.  
- **Graphics Module** – Rendering system (SDL2-based).  
- **Input Handling** – Keyboard/mouse input abstraction.  
- **Scene Management** – Organize objects and manage updates per frame.  
- **Educational Focus** – Designed to teach core engine architecture in C++.  

---

## 📂 Project Structure

Source/
├── main.cpp # Entry point for the engine
│
├── Engine/ # Core engine logic
│ ├── Engine.h
│ └── Engine.cpp
│
├── Graphics/ # Rendering system
│ ├── Renderer.h
│ └── Renderer.cpp
│
├── Input/ # Input system
│ ├── InputManager.h
│ └── InputManager.cpp
│
└── ... (other modules as added)

- **`Engine/`**: Implements the main loop, initialization, and shutdown logic.  
- **`Graphics/`**: Handles drawing to the screen (using SDL2).  
- **`Input/`**: Provides abstractions for handling keyboard/mouse events.  
- **`main.cpp`**: Demonstrates how to initialize and run the engine.  

---

## ⚙️ Getting Started

### Prerequisites
- C++17 or newer  
- [CMake](https://cmake.org/) (recommended)  
- SDL2 and OpenGL (if used in your engine — adjust as needed)  

### Build Instructions
# Clone the repository
git clone https://github.com/foxatschool/CSC196_GameEngine.git
cd CSC196_GameEngine

# Create a build directory
mkdir build && cd build

# Generate build files with CMake
cmake ..

# Compile
make
Usage
To run the demo:
From main.cpp, you can see a minimal setup:

cpp
Copy code
Engine engine;
engine.Initialize();
engine.Run();
engine.Shutdown();
This shows how a project can use the engine loop to create interactive applications.

Learning Goals
This project is designed to:

Teach modular game engine design.

Provide hands-on experience with rendering pipelines.

Introduce input handling and event-driven programming.

Serve as a foundation for more advanced features (physics, audio, networking).

🤝 Contributing
Contributions are welcome!

Open issues for bugs or feature requests.

Submit pull requests with clear commit history.

Keep code style consistent with existing files.

📜License
This project currently does not specify a license.

Author
Developed by foxatschool as part of the CSC196 course project.

---

This version is **specific to your repo’s structure** (engine, graphics, input, main).  
