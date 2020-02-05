#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Block
{
public:
	unsigned int VBO, VAO, EBO;
	float vertices[180] = {
		//Object Cords			//Texture Cords
		-0.25f, -0.25f, -0.25f,  1.0f, 1.0f,
		 0.25f, -0.25f, -0.25f,  0.0f, 1.0f,
		 0.25f,  0.25f, -0.25f,  0.0f, 0.0f,			//hinten
		 0.25f,  0.25f, -0.25f,  0.0f, 0.0f,
		-0.25f,  0.25f, -0.25f,  1.0f, 0.0f,
		-0.25f, -0.25f, -0.25f,  1.0f, 1.0f,

		-0.25f, -0.25f,  0.25f,  1.0f, 1.0f,
		 0.25f, -0.25f,  0.25f,  0.0f, 1.0f,
		 0.25f,  0.25f,  0.25f,  0.0f, 0.0f,			//vorne
		 0.25f,  0.25f,  0.25f,  0.0f, 0.0f,
		-0.25f,  0.25f,  0.25f,  1.0f, 0.0f,
		-0.25f, -0.25f,  0.25f,  1.0f, 1.0f,

		-0.25f,  0.25f,  0.25f,  0.0f, 0.0f,
		-0.25f,  0.25f, -0.25f,  1.0f, 0.0f,
		-0.25f, -0.25f, -0.25f,  1.0f, 1.0f,			//links
		-0.25f, -0.25f, -0.25f,  1.0f, 1.0f,
		-0.25f, -0.25f,  0.25f,  0.0f, 1.0f,
		-0.25f,  0.25f,  0.25f,  0.0f, 0.0f,

		 0.25f,  0.25f,  0.25f,  0.0f, 0.0f,
		 0.25f,  0.25f, -0.25f,  1.0f, 0.0f,
		 0.25f, -0.25f, -0.25f,  1.0f, 1.0f,			//rechts
		 0.25f, -0.25f, -0.25f,  1.0f, 1.0f,
		 0.25f, -0.25f,  0.25f,  0.0f, 1.0f,
		 0.25f,  0.25f,  0.25f,  0.0f, 0.0f,

		-0.25f, -0.25f, -0.25f,  0.0f, 0.0f,
		 0.25f, -0.25f, -0.25f,  0.0f, 0.0f,
		 0.25f, -0.25f,  0.25f,  0.0f, 0.0f,			//unten
		 0.25f, -0.25f,  0.25f,  0.0f, 0.0f,
		-0.25f, -0.25f,  0.25f,  0.0f, 0.0f,
		-0.25f, -0.25f, -0.25f,  0.0f, 0.0f,

		-0.25f,  0.25f, -0.25f,  0.0f, 0.0f,
		 0.25f,  0.25f, -0.25f,  0.0f, 0.0f,
		 0.25f,  0.25f,  0.25f,  0.0f, 0.0f,			//oben
		 0.25f,  0.25f,  0.25f,  0.0f, 0.0f,
		-0.25f,  0.25f,  0.25f,  0.0f, 0.0f,
		-0.25f,  0.25f, -0.25f,  0.0f, 0.0f
	};

	void genBuffer()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		bindBuffer();
	};

	void attribute()
	{
		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	};

	void delBuffer()
	{
		// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

private:

	void bindBuffer() //no need to call
	{
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	};
};

#endif