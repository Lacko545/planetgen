#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

int main(int argc, char ** argv)
{
	//initialize glfw
	glfwInit();
	//configure glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//uncomment for OSX
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	

	GLFWwindow* window = glfwCreateWindow(800,600,"Main Window",NULL,NULL);
	if(window == NULL)
	{
		printf("Couldn't create window.\n");
		glfwTerminate();
		return -1;
	}	

	glfwMakeContextCurrent(window);


	//GLAD loads all OpenGL functions
	//--OS dependent
	//--queries OS for function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
		return -1;
	}

	//Give OpenGLthe size of screen for rendering
	glViewport(0,0,800,600);
	//set up callback for dynamic window resize
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	

	
	//triangle
	//opengl expects every coordinate in range <-1;1>
		//usually scaled down by shaders
	/*float vertices[] = {
		 0.5f,  0.5f, 0.0f, // top right
		 0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f // top left
	};*/
	float vertices[] = {
		// positions
		// colors
		// texture coords
		0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
		0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f
		// top left
	};

	unsigned int indices[] = {
		0,1,3, // first triangle
		1,2,3
	};
	
	//ID of Vertex Buffer Object
	unsigned int VBO, VAO;
	unsigned int EBO;
	//create memory on GPU
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(1,&VBO);
	glGenBuffers(1,&EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	//bind buffer type to our buffer
	//VBO has GL_ARRAY_BUFFER type
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//send vertex data to the buffer
	//slow, don't do often, send a lot at once instead
	//GL_STATIC_DRAW -- object won't change, or will change rarelyyy
	//GL_DYNAMIC_DRAW -- object will change often
	//GL_STREAM_DRAW -- object will change on every draw
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE, 8*sizeof(float),(void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);
	Shader my_shader("shaders/vshader1.glsl", "shaders/fshader1.glsl");


	unsigned int texture;
	glGenTextures(1,&texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int width, height,n_chan;
	unsigned char *data = stbi_load("aa.jpg",&width, &height, &n_chan, 0);
	if(data){
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, 
				GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(texture);
	}
	else {
		printf("Error loading texture.\n");
	}

	stbi_image_free(data);

	//game loop
	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f,0.3f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//		glUseProgram(shaderProgram);
		
		my_shader.use();
//		float timeValue = glfwGetTime();
//		float greenValue = sin(timeValue) / 2.0f + 0.5f;
//		int vertexColorLocation = glGetUniformLocation(my_shader.ID, "ourColor");
//		glUniform4f(vertexColorLocation,0.0f,greenValue,0.0f,1.0f);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
//		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
//		glBindVertexArray(0);
		//2 buffers
		//render in invisible background buffer
		//then swap with foreground buffer at once
		//prevents flickers from slow rendering
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();
	return 0;
}
