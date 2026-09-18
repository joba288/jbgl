# jbgl

A lightweight C rendering library built on OpenGL.

## Features

- 2D batch rendering
- Texture rendering
- Text rendering with FreeType
- Shader management

## Dependencies

- OpenGL
- FreeType
- cglm
- stb_image
- GLAD
  
## Example
```c
#include "jbgl.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

int main(void)
{
    int screen_w = 1080;
    int screen_h = 768;

    glfwInit();

    GLFWwindow* window = glfwCreateWindow(screen_w, screen_h, "jbgl Example", NULL, NULL);

    glfwMakeContextCurrent(window);
    jbgl_gladLoadGL(glfwGetProcAddress);

    JbglState* state = jbgl_init(screen_w, screen_h);

    JbglFont* font = jbgl_load_font(state, "resources/fonts/Matcha Mint.ttf",36);

    JbglTexture tex = jbgl_load_texture("resources/textures/southey.jpg");

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.071f, 0.165f, 0.263f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        jbgl_begin_batch(state);



		jbgl_draw_texture(state, tex, (vec3) { 0.0f, 0.0f, 0.0f }, 200, 200, (vec4) { 1.0f, 1.0f, 1.0f, 1.0f });
		jbgl_draw_text(state, "Hello World", (vec2) { 0.0f, 110.0f }, font, false, (vec4) { 255.0f, 255.0f, 255.0f, 255.0f }, false, false, true, false);
		

        jbgl_end_batch(state);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    jbgl_destroy_texture(&tex);
    jbgl_free_font(font);
    jbgl_batch_cleanup(state);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
```
## Building

#### Windows

```bash
cmake -S . -B build
cmake --build build
