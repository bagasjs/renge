# Renge Game Engine
This is just my hobby game engine written from ground up in C. I have a plan to make this
engine to use multi graphic library such as OpenGL4.x and Vulkan. But I will start the engine 
by using OpenGL4.x first since it's the most efficient one to start game engine. Also I want
the engine core to be modular which mean it should be usable outside the editor.

## Feature Lists
### Implemented
- Logging (Naive)
- Event System (Naive)
- Memory Management (Naive)
- Display System (Naive)
- OpenGL Context Creation (GLX Only, EGL & WGL in the future)

### Not Implemented
- 2D Rendering
- Multi-threading
- File System
- Audio System
- Scripting (C#)
- Editor
- Vulkan???
- etc...

## Toolchain
- Clang
The compiler that you should use to compile this project
- Premake5 & Makefile (Linux/Windows)
The build system that I choose, It's just simpler than CMake.
- Visual Studio (Windows)
Primary usage is just for the Windows headers, i.e. **windows.h**. You could also use MSYS2, as long 
as we can access the Windows headers I think it will be okay, since the library will use the standard
library at the most minimum level. The only real dependencies might be the **stdarg.h** for logging.

