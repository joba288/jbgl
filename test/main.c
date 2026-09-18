#include "jbgl.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>


int screen_w, screen_h;
JbglShader shader;
JbglState* state;
JbglFont* font;

JbglTexture tex;


int main(void)
{
	screen_w = 1080; screen_h = 768;

	glfwInit();
	GLFWwindow* window = glfwCreateWindow(screen_w, screen_h, "jobanote", NULL, NULL);
	glfwMakeContextCurrent(window);
	jbgl_gladLoadGL(glfwGetProcAddress);

	state = jbgl_init(screen_w, screen_h);
	font = jbgl_load_font(state, "resources/fonts/Matcha Mint.ttf", 36);
	tex = jbgl_load_texture("resources/textures/southey.jpg");


	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.071f, 0.165f, 0.263, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// --- Update ---
	
	
		// --- Render ---
		jbgl_begin_batch(state);

		jbgl_draw_texture(state, tex, (vec3) { 0.0f, 0.0f, 0.0f }, 200, 200, (vec4) { 1.0f, 1.0f, 1.0f, 1.0f });
		jbgl_draw_text(state, "Hello World", (vec2) { 0.0f, 110.0f }, font, false, (vec4) { 255.0f, 255.0f, 255.0f, 255.0f }, false, false, true, false);
		


		jbgl_end_batch(state);

		// --
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
