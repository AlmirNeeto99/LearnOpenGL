# Learn OpenGL

This project is a keeper of LearnOpenGL course.

See here: https://learnopengl.com/Introduction

# Dependencies

- GLFW
- GLAD
- OpenGL

# Building

For building this project you will need Cmake.

This project uses separated build files for each Chapter.

- Create a directory called `build`
- Inside it, run: `cmake ../` and `make`

Each executable will be build inside its folder.

So `HelloTriangle` Chapter executable will be inside `Chapter-HelloTriangle`, you only need to run: `./Chapter-HelloTriangle/HelloTriangle`. You can also navigate to `Chapter-HelloTriangle` and run: `./HelloTriangle`

**This project was tested only on Ubuntu.**

# Path

- [x] Creating Window
- [x] Hello Window
- [x] Hello Triangle
- [x] Shaders
- [x] Textures
- [x] Transformations
- [x] Coordinate Systems
- [x] Camera
- [x] Colors
- [x] Lightning
- [x] Materials
- [x] Lighting maps

<div style="display: flex; justify-content: space-evenly">
    <div style="width: 40%">
        <img src="resources/images/1631401415.png" alt="Specular Map" />
    </div>
    <div style="width: 40%">
        <img src="resources/images/1631416736.png" alt="Emission Map" />
    </div>
</div>

- [ ] Light casters
- [ ] Multiple lights
- [ ] Assimp
- [ ] Mesh
- [ ] Model
- [ ] Depth
- [ ] Stencil
- [ ] Blending
- [ ] Face culling
- [ ] Framebuffers
- [ ] Cubemaps
- [ ] Advanced Data
- [ ] Advanced GLSL
- [ ] Geometry Shaders
- [ ] Anti aliasing
- [ ] Advanced Lightning
- [ ] Gamma Correction
- [ ] Shadows
- [ ] Point Shadows
- [ ] Normal Mapping
- [ ] Parallax Mapping
- [ ] HDR
- [ ] Bloom
- [ ] Deferred Shading
- [ ] SSAO
- [ ] PBR
- [ ] Text rendering

---

# Exercises

Every LearnOpenGL's sections come with some exercises. Each exercise will be done within a new branch prefixed with `exercise/`.