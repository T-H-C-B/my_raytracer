# RayTracer

## Implementing a New Plugin for Ray Tracer

This document explains how to create a new plugin for the ray tracer program. The plugin system allows you to extend the ray tracer with new features or custom code without modifying the core program. You can create various types of plugins such as primitives, lights, graphical modules, decorators, and cameras.

### Prerequisites

Before you start, make sure you have:

1. Familiarity with C++ and object-oriented programming.
2. A development environment set up for C++ development.
3. The ray tracer source code or a plugin template for the desired plugin type.

### Steps to create a new plugin

1. **Create a new C++ project**

Create a new C++ project with your desired development environment. Add the necessary dependencies and include the required header files, such as the ray tracer's core and shared libraries, to the project.

2. **Implement the plugin class**

Create a new class that inherits from the appropriate interface for the plugin type you are creating. Implement the necessary methods for the plugin as required by the interface. For example, if you are creating a new primitive, inherit from `RayTracer::Core::IEntity` and implement the required methods.

```cpp
class MyCustomPrimitive : public RayTracer::Core::IEntity {
    // Implement required IEntity methods
};
```

3. **Implement the plugin entry points**

The entry points are C-style functions that are used by the ray tracer to interact with the plugin. You will need to implement the following entry points:

- `create`: Creates an instance of the plugin class using the provided settings.
- `destroy`: Destroys an instance of the plugin class.
- `getName`: Returns the name of the plugin.
- `getType`: Returns the plugin type.

Here's an example of implementing the entry points for a custom primitive:

```cpp
extern "C" {
    RayTracer::Core::IEntity* create(const RayTracer::Shared::SettingWrapper &setting) {
        // Parse settings and create an instance of MyCustomPrimitive
        return new MyCustomPrimitive(/* constructor arguments */);
    }

    void destroy(RayTracer::Core::IEntity* entity) {
        delete entity;
    }

    const char* getName() {
        return "MyCustomPrimitive";
    }

    RayTracer::Plugins::PluginType getType() {
        return RayTracer::Plugins::PluginType::Entity;
    }
}
```

4. **Configure and build the plugin**

Set up the build system to compile the plugin as a shared library (e.g., .so, .dll, or .dylib, depending on your platform). Ensure the compiled library is placed in a directory where the ray tracer can find it.

5. **Test the plugin**

To test your new plugin, create a configuration file for the ray tracer that includes your plugin and its settings. Run the ray tracer with this configuration file and verify that your plugin is loaded and functions as expected.

## Plugin Types

In order to provide an easy-to-follow guide, I will create separate sections for each type of plugin and briefly describe their purpose and usage.

### Camera Plugin

The camera plugin defines a camera in the ray tracer. In this example, we have a `BasicCamera` class. The camera plugin allows users to control the position and rotation of the camera.

#### BasicCamera

```cpp
#include "BasicCamera.hpp"

BasicCamera::BasicCamera(const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &rotation) {
    // Initialize camera position and rotation
}

void BasicCamera::rotate(const RayTracer::Shared::Vec3 &rotation) {
    // Rotate the camera
}

BasicCamera::~BasicCamera() {
    // Clean up resources
}

std::vector<std::vector<RayTracer::Shared::Ray>> BasicCamera::calculateRays() {
    // Calculate rays for the camera
}
```

### Decorator Plugin

The decorator plugin is used to apply specific effects or modifications to the final image, such as adding a flat color. In this example, we have a `FlatColor` class.

#### FlatColor

```cpp
#include "FlatColor.hpp"

FlatColor::FlatColor(const Shared::Vec3 &color) {
    // Initialize color
}

void FlatColor::computeColor(RayTracer::Shared::Intersection &intersection,
                             const RayTracer::Shared::Ray &ray,
                             RayTracer::Shared::Vec3 &baseColor,
                             std::unordered_map<RayTracer::Core::EntityType, std::vector<RayTracer::Core::IEntity *>>,
                             RayTracer::Plugins::Skyboxes::ISkyBox *SkyBox) {
    // Compute color for the intersection
}
```

### Graphics Module Plugin

The graphics module plugin is responsible for managing the rendering window and updating the final image. In this example, we have an `SFMLGraphModule` class.

#### SFMLGraphModule

```cpp
#include "SFMLGraphModule.hpp"

SFMLGraphModule::SFMLGraphModule() {
    // Initialize window and resources
}

SFMLGraphModule::~SFMLGraphModule() {
    // Clean up resources
}

void SFMLGraphModule::update(RayTracer::Core::EventManager &eventManager) {
    // Update window events
}

void SFMLGraphModule::draw(RayTracer::Core::Image &image) {
    // Draw the image to the window
}
```

### Light Plugin

The light plugin defines various types of light sources for the ray tracer. In this example, we have an `AmbientLight` class.

#### AmbientLight

```cpp
#include "AmbientLight.hpp"

AmbientLight::AmbientLight(const RayTracer::Shared::Vec3 &position, const RayTracer::Shared::Vec3 &rotation, float intensity, const RayTracer::Shared::Vec3 &color) {
    // Initialize light position, rotation, intensity, and color
}

bool AmbientLight::inView(const RayTracer::Shared::Vec3 &point) const {
    // Check if the point is in view of the light source
}
```

### Primitive Plugin

The primitive plugin defines various types of geometric primitives for the ray tracer. In this example, we have a `Sphere` class.

#### Sphere

```cpp
#include "Sphere.hpp"

Sphere::Sphere(const RayTracer::Shared::Vec3& center, float radius) {
    // Initialize sphere center and radius
}

void Sphere::scale(float scale) {
    // Scale the sphere
}

std::optional<std::unique_ptr<RayTracer::Shared::Intersection>> Sphere::intersect(const RayTracer::Shared::Ray&ray, float& t) const {
    // Check for intersection between the sphere and the ray
}

```

### Skybox Plugin

The skybox plugin defines various types of skyboxes for the ray tracer. In this example, we have a `PNGSkyBox` class.

#### PNGSkyBox

```cpp
#include "PNGSkyBox.hpp"

PNGSkyBox::PNGSkyBox(const std::string& filePath) {
    // Load PNG file and initialize skybox
}

PNGSkyBox::~PNGSkyBox() {
    // Clean up resources
}

void PNGSkyBox::rotate(const RayTracer::Shared::Vec3 &rotation) {
    // Rotate the skybox
}

RayTracer::Shared::Vec3 PNGSkyBox::getColor(const RayTracer::Shared::Ray &ray) const {
    // Get the color of the skybox at the given ray direction
}

void PNGSkyBox::read_png_file(const std::string& filePath) {
    // Read the PNG file and store its data
}

RayTracer::Shared::Vec3 PNGSkyBox::sample_color(const RayTracer::Shared::Vec3& direction) const {
    // Sample the color from the PNG file based on the given direction
}

RayTracer::Shared::Vec3 PNGSkyBox::apply_rotation(const RayTracer::Shared::Vec3& direction) const {
    // Apply rotation to the given direction
}

RayTracer::Shared::Vec3 PNGSkyBox::rotate_x(const RayTracer::Shared::Vec3& v, float angle) const {
    // Rotate the vector around the X-axis by the given angle
}

RayTracer::Shared::Vec3 PNGSkyBox::rotate_y(const RayTracer::Shared::Vec3& v, float angle) const {
    // Rotate the vector around the Y-axis by the given angle
}

RayTracer::Shared::Vec3 PNGSkyBox::rotate_z(const RayTracer::Shared::Vec3& v, float angle) const {
    // Rotate the vector around the Z-axis by the given angle
}

```

With these implementations, users can create and customize each type of plugin to suit their needs in the ray tracer. Each plugin can be utilized to enhance the functionality and appearance of the rendered images.

### Conclusion

You have now successfully created a new plugin for the ray tracer. To add more plugins, repeat these steps for each desired plugin type. Remember to keep the plugin interfaces and entry points consistent with the ray tracer's expectations to ensure compatibility.

## Scenes

A scene config file is a way to define a scene in a ray tracer by specifying the settings for different plugins such as cameras, lights, primitives, and decorators. The file typically contains settings for various plugins like `Sphere`, `Plane`, `BasicCamera`, `AmbientLight`, and `PNGSkyBox`. Here is a guide on how to create a scene config file and the required settings for each plugin.

### Obligatory settings

These settings are required for the basic setup of a scene:

- Camera: At least one camera should be defined in the scene.
- Primitives: At least one primitive (Sphere, Plane, etc.) should be present in the scene.
- Light: At least one light source should be defined in the scene.

### Base Plugins settings

#### Sphere

A sphere is defined by its position, radius, and an optional decorator.

```
Sphere = {
    position = {
        x = 10;
        y = 0;
        z = 0;
        r = 2;
    };
    Decorator = {
        FlatColor = {
            Color = {
                r = 255;
                g = 64;
                b = 64;
            };
        };
    };
}
```

#### Plane

A plane is defined by its position, normal (orientation), and an optional decorator.

```
Plane = {
    position = {
        x = 0;
        y = 0;
        z = -10;
    };
    normal = {
        x = 0;
        y = 0;
        z = 1;
    };
    Decorator = {
        PlaneColor = {
            Color1 = {
                r = 255;
                g = 64;
                b = 64;
            };
            Color2 = {
                r = 64;
                g = 64;
                b = 64;
            };
        };
    };
}
```

#### BasicCamera

A basic camera is defined by its field of view, position, rotation, and resolution.

```
BasicCamera = {
    fieldOfView = 60.0;
    position = { x = 30; y = 0; z = 0; };
    rotation = { x = 75; y = 0; z = 0; };
    resolution = { x = 1920; y = 1080; };
}
```

#### AmbientLight

Ambient light is defined by its position, color, and intensity.

```
AmbientLight = ({
    position = { x = 0; y = 0; z = 100; };
    color = { r = 100; g = 100; b = 100; };
    intensity = 0.6;
})
```

#### PNGSkyBox

A PNG skybox is defined by the path to the PNG image file.

```
PNGSkyBox = {
    path = "scenes/skybox.png";
}
```

### Defining plugin settings

To define the settings for each plugin, you can use the example syntax shown above, specifying the appropriate values for each attribute. For example, if you want to create a sphere with a reflective surface, you can use the following syntax:

```
Sphere = {
    position = {
        x = 0;
        y = 0;
        z = 8;
        r = 7;
    };
    Decorator = {
        ReflectionDecorator = {
            Color = {
                r = 255;
                g = 64;
                b = 64;
            };
            Reflectivity = 1.0;
        };
    };
}
```

By defining the settings in the scene config file, you can create a custom scene using different plugins and their respective attributes

### Advanced settings and customization

In addition to the basic settings for each plugin, you can further customize your scene by adding more primitives, lights, and decorators.

#### Multiple Primitives

You can add multiple instances of primitives in your scene. For example, you can have multiple spheres and planes by defining each of them with their respective settings.

```
Sphere = ({
    position = { x = 0; y = 0; z = 8; r = 7; };
    Decorator = {
        FlatColor = {
            Color = { r = 255; g = 64; b = 64; };
        };
    };
},
{
    position = { x = 30; y = 0; z = 10; r = 5; };
    Decorator = {
        FlatColor = {
            Color = { r = 64; g = 64; b = 255; };
        };
    };
})
```

#### Multiple Lights

You can also have multiple light sources in your scene to create complex lighting scenarios. Just define each light source with their respective settings.

```
AmbientLight = ({
    position = { x = -30; y = 70; z = 100; };
    color = { r = 100; g = 100; b = 100; };
    intensity = 0.5;
},
{
    position = { x = 30; y = 0; z = 20; };
    color = { r = 100; g = 100; b = 100; };
    intensity = 0.5;
},
{
    position = { x = 30; y = 0; z = 0; };
    color = { r = 100; g = 100; b = 100; };
    intensity = 0.5;
})
```

#### Custom Decorators

You can use custom decorators to enhance the appearance of your primitives. For example, you can use a `ReflectionDecorator` to create reflective surfaces or a `FlatColor` decorator to give a solid color to the primitive.

```
Sphere = {
    position = { x = 0; y = 0; z = 8; r = 7; };
    Decorator = {
        ReflectionDecorator = {
            Color = { r = 255; g = 64; b = 64; };
            Reflectivity = 1.0;
        };
    };
}
```

#### Custom Skyboxes

You can also use custom skyboxes to change the appearance of your scene's background. The `PNGSkyBox` plugin allows you to use a PNG image file as your skybox.

```
PNGSkyBox = {
    path = "scenes/skybox.png";
}
```

By combining different settings and customizations, you can create complex and visually stunning scenes in your ray tracer. Just remember to provide the appropriate settings for each plugin in the scene config file, and you'll be able to create a wide variety of scenes with different appearances and attributes.

## User Interaction

In this section, we explain how to control the camera, upscale the rendering, and change scenes and cameras using keyboard inputs in the Ray Tracer application.

### Camera Movement and Rotation

To control the camera position and direction, use the following keyboard keys:

- **Z**: Move the camera forward.
- **S**: Move the camera backward.
- **Q**: Move the camera to the left.
- **D**: Move the camera to the right.
- **Space**: Move the camera up.
- **Shift**: Move the camera down.
- **Left Arrow**: Rotate the camera to look left.
- **Right Arrow**: Rotate the camera to look right.
- **Up Arrow**: Rotate the camera to look up.
- **Down Arrow**: Rotate the camera to look down.

### Scene and Camera Navigation

To navigate between different scenes and cameras, use the following function keys:

- **F1**: Go to the next scene.
- **F2**: Go to the previous scene.
- **F3**: Go to the next camera.
- **F4**: Go to the previous camera.

### Rendering

To control the rendering percentage, use the following key:

- **P**: Adjust the rendering percentage.

Here is the mapping between the keyboard events and the corresponding functions in the `RayTracer::Core::Core` class:

```cpp
static const std::unordered_map<RayTracer::Core::EventType, void (RayTracer::Core::Core::*)()> METHOD_MAP = {
    // ... (existing mappings) ...
};
```

These mappings allow the Ray Tracer application to respond to user inputs by calling the appropriate methods in the `RayTracer::Core::Core` class.

