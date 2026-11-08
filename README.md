# AML (Aporia Math Lib) | C++20, Header-Only, Git
---
• Designed and implemented a high-performance, header-only 3D-2D math library in C++ to eliminate function call overhead via compiler inlining.
## Features

* **Header-Only Architecture:** No compilation or complex building steps required. Just include the headers and start coding.
* **High Performance:** Functions are designed for optimal compiler inlining to minimize execution overhead.
* **Modern C++20:** Built using modern C++20 standards for clean type safety and optimizations.
* **Graphics Programmer's:** Focused implementation of vectors, matrices, and transformations required for 3D computational environments and ray tracers etc.

## Getting Started

### Prerequisites

* A compiler supporting **C++20** standard (e.g., GCC 10+, Clang 10+, or MSVC 2019+).

### Installation

Because AML is header-only, you can integrate it into your project either by downloading the source or adding it as a Git submodule.

To add it as a Git submodule in your existing repository:

```bash
git submodule add https://github.com external/AML
```

Then, include the `AML` folder path in your project's include directories.

## Usage Example

Here is a quick example demonstrating how to include and use the library in a C++ source file:

```cpp
#include <iostream>
#include "AML/Vector.hpp" // Replace with your exact header paths
#include "AML/Matrix.hpp"

int main() {
    // Example vector operation
    AML::vec3 position(1.0f, 2.0f, 3.0f);
    AML::vec3 velocity(0.5f, 0.0f, -1.0f);

    AML::mat4 model      = AML::translate(meshPos) * AML::rotateY(meshRot);
    AML::mat4 view       = AML::look_at(cameraPos, lookTarget, AML::vec3(0, 1, 0));
    AML::mat4 projection = AML::perspective(0.785f, 16.0f/9.0f, 0.1f, 100.0f);

    // Calculate the complete Model-View-Projection (MVP) matrix chain!
    AML::mat4 mvpMatrix = projection * view * model; 
    
    // Inlined vector addition
    AML::vec3 newPosition = position + velocity;
    
    std::cout << "New Position: (" 
              << newPosition.x << ", " 
              << newPosition.y << ", " 
              << newPosition.z << ")" << std::endl;
              
    return 0;
}
```

## Repository Structure

* `AML/` - The core folder containing all high-performance header files.
* `Old_shit/` - Legacy code and archive files.

## License

This project is licensed under [License](https://github.com/Aporia26/AML_Aporia-Math-Lib/blob/main/LICENSE)
