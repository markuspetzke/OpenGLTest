#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <SFML/System/Clock.hpp>

#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

#include "VertexArray.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Fenster1", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glClearColor(0.25f, 0.75f, 1.0f, 1.0f);
	glfwSwapInterval(1);

	if (glewInit() != GLEW_OK)
		std::cout << "Error" << std::endl;

	{
		float positions[] = {	//Hinten
		-0.5f,   -0.5f,  // 0
		 0.5f,   -0.5f,  // 1
		 0.5f,    0.5f,  // 2
		-0.5f,	  0.5f  // 3
		};

		/*
		float positions[] = {	//Vorne
		-0.5f,   -0.5f, 0.5f, // 0
		 0.5f,   -0.5f, 0.5f, // 1
		 0.5f,    0.5f, 0.5f, // 2
		-0.5f,	  0.5f, 0.5f  // 3
		};
		float positions[] = {	//Links
		-0.5f,   -0.5f, 0.5f, // 0
		-0.5f,    0.5f, 0.5f, // 1
		-0.5f,    0.5f, 0.5f, // 2
		-0.5f,	 -0.5f, 0.5f // 3
		};
		float positions[] = {	//Rechts
		 0.5f,   -0.5f, -0.5f, // 0
		 0.5f,    0.5f, -0.5f, // 1
		 0.5f,    0.5f,  0.5f, // 2
		 0.5f,	 -0.5f,  0.5f// 3
		};
		*/

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		unsigned int vao;
		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));

		VertexArray va;
		VertexBuffer vb(positions, 4 * 2 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		Shader shader("Res/Shaders/Basic.shader");
		shader.Bind();

		shader.SetUniform4f("u_Color", 1.0f, 0.3f, 0.8f, 1.0f);

		va.Unbind();
		vb.Unbind();
		ib.Unbind();
		shader.Unbind();

		Renderer renderer;

		float r = 0.0f;
		float increament = 0.5f;
		//Keyboard keyboard;
		sf::Clock frameTimer;
		int frameCount = 0;
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Wireframe Mode

		while (!glfwWindowShouldClose(window))
		{
			//status = handleWindowEvents(window, keyboard);
			renderer.Clear();

			shader.Bind();
			shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
			glLoadIdentity();
			glTranslatef(0.4f, 0.5f, 1.0f);
			r = +0.05f;

			renderer.Draw(va, ib, shader);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();

			//stats
			frameCount++;
			if (frameTimer.getElapsedTime().asSeconds() > 2) {
				float ms = frameTimer.getElapsedTime().asMilliseconds();
				int secs = frameTimer.getElapsedTime().asSeconds();
				std::cout << "Average Frame Time: " << ms / frameCount
					<< "Average FPS: " << frameCount / secs << "\n\n";
				frameCount = 0;
				frameTimer.restart();
			}
		}
	}

	glfwTerminate();
	return 0;
}