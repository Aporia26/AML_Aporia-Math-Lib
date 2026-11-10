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


## Installation

AML is header-only. You can either clone the repository or add it as a Git submodule.

**Option 1: Clone the repository**

```bash
git clone https://github.com/Aporia26/AML_Aporia-Math-Lib.git
```

Add the repository's root directory to your project's include directories.

**Option 2: Add as a Git submodule**

From your project's root directory:

```bash
git submodule add https://github.com/Aporia26/AML_Aporia-Math-Lib.git external/AML
```

If you're using CMake, add AML's repository root to your target's include directories:

```cmake
target_include_directories(YourTarget PRIVATE
    "${CMAKE_SOURCE_DIR}/external/AML"
)
```

### Including AML

Use the master header to include the complete library:

```cpp
#include "AML/AML.hpp"
```

You can also include individual headers when you only need specific functionality:

```cpp
#include "AML/Vector.hpp"
#include "AML/Matrix.hpp"
#include "AML/Geometry.hpp"
#include "AML/Intersection.hpp"
#include "AML/Math.hpp"
```

## Usage Examples

### 1. Vector Mathematics

```cpp
#include <iostream>
#include "AML/AML.hpp"

int main()
{
    AML::vec3 position(1.0f, 2.0f, 3.0f);
    AML::vec3 velocity(0.5f, 0.0f, -1.0f);

    AML::vec3 newPosition = position + velocity;

    float magnitude = AML::length(velocity);

    AML::vec3 direction = AML::normalize(velocity);

    float alignment = AML::dot(position, velocity);

    std::cout << "New Position: " << newPosition << '\n';
    std::cout << "Velocity Magnitude: " << magnitude << '\n';
    std::cout << "Direction: " << direction << '\n';
    std::cout << "Dot Product: " << alignment << '\n';

    return 0;
}
```

### 2. 3D Transformations and Camera

```cpp
#include <iostream>
#include <numbers>
#include "AML/AML.hpp"

int main()
{
    // Model transformation
    AML::vec3 modelPosition(0.0f, 0.0f, 0.0f);
    float modelRotationY = std::numbers::pi_v<float> / 4.0f;

    AML::mat4 model =
        AML::translate(modelPosition) *
        AML::rotateY(modelRotationY);

    // Camera configuration
    AML::vec3 cameraPosition(0.0f, 0.0f, 5.0f);
    AML::vec3 lookTarget(0.0f, 0.0f, 0.0f);
    AML::vec3 worldUp(0.0f, 1.0f, 0.0f);

    AML::mat4 view =
        AML::look_at(cameraPosition, lookTarget, worldUp);

    // Perspective projection
    AML::mat4 projection =
        AML::perspective(
            std::numbers::pi_v<float> / 4.0f,
            16.0f / 9.0f,
            0.1f,
            100.0f
        );

    // Model-View-Projection matrix
    AML::mat4 mvp = projection * view * model;

    // Transform a local-space position
    AML::vec4 localPosition(1.0f, 0.0f, 0.0f, 1.0f);
    AML::vec4 clipPosition = mvp * localPosition;

    std::cout << "Clip-space Position: "
              << clipPosition << '\n';

    return 0;
}
```

**Note:** Transformation angles are expressed in radians. The resulting MVP matrix follows the multiplication order `projection * view * model`.

### 3. 2D Geometry and Collision Detection

```cpp
#include <iostream>
#include "AML/AML.hpp"

int main()
{
    // Create two circles
    AML::circle circleA(
        AML::vec2(100.0f, 100.0f),
        20.0f
    );

    AML::circle circleB(
        AML::vec2(125.0f, 100.0f),
        15.0f
    );

    // Circle-circle intersection
    if (AML::overlap_circle(circleA, circleB))
    {
        AML::vec2 delta = circleB.center - circleA.center;

        float distance = AML::length(delta);
        float penetration =
            circleA.radius + circleB.radius - distance;

        AML::vec2 normal =
            (distance > 0.0f)
            ? AML::normalize(delta)
            : AML::vec2(0.0f, -1.0f);

        std::cout << "Collision detected!\n";
        std::cout << "Normal: " << normal << '\n';
        std::cout << "Penetration: " << penetration << '\n';
    }

    // Circle-AABB intersection
   AML::AABB2D box(
    AML::vec2(115.0f, 80.0f),
    AML::vec2(220.0f, 140.0f)
    );

    bool intersects =
        AML::overlap_circle_vs_aabb(circleA, box);

    std::cout << "Circle overlaps box: "
              << intersects << '\n';

    return 0;
}
```

These examples demonstrate how AML's mathematical and geometric operations can be combined to build higher-level systems such as rendering pipelines and physics simulations.


## Repository Structure

* `AML/` - The core folder containing all high-performance header files.
* `Old_shit/` - Legacy code and archive files.

## License

This project is licensed under [License](https://github.com/Aporia26/AML_Aporia-Math-Lib/blob/main/LICENSE)

## Upcoming Next
* Will be adding Quaternions and BHV 
* And, other 3D stuff later
* SIMD, benchmarking optimizations ig idk
