#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int main() {
	glfwInit();

	//Diz qual versao do OpenGL o GLFW vai usar
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Diz qual perfil o GLFW vai usar
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Criar a janela com tamanho 800 por 800
	GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL Test", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Diz que vamos usar a janela e introduz ela no contexto atual
	glfwMakeContextCurrent(window);

	//Diz pro glad carregar as configuracoes do opengl e da janela
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	//Diz pro opengl preparar para trocar a cor do buffer
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Troca o back buffer (onde a cor foi criada) pelo front buffer
	glfwSwapBuffers(window);

	//While usado pra manter a janela aberta
	while (!glfwWindowShouldClose(window)) {
		//Diz pro glfw pra processar todos os eventos (como redimensionar a janela e mexer nela)
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}