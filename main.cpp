#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

int main() {
	//Inicializa GLFW
	glfwInit();
	//Configura o GLFW, primeiro argumento diz qual opcao pra configurar, segundo argumento e um INT que representa o valor da config
	//Usamos pra definir a versao usada do OpenGL
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Usar o core profile diz pro GLFW que vamos acessar apenas features atuais do OpenGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//Cria a janela com width e height colocados nos primeiros 2 args, com titulo no 3 arg
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);

	//Retorna se a janela nao foi criada
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Diz pro GLFW fazer com que a janela seja o contexto principal na thread atual
	glfwMakeContextCurrent(window);


	//Precisamos inicializar o GLAD antes de chamar qualquer funcao OpenGL
	//Pega as funcoes especificas do OS pra serem carregadas
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	//Precisamos dizer pro OpenGL o tamanho da janela de renderizacao pra ele mostrar os dados e coordenadas em relacao a janela
	//Note that processed coordinates in OpenGL are between -1 and 1 so we effectively map from the range(-1 to 1) to (0, 800) and (0, 800).
	glViewport(0, 0, 800, 800);

	//Toda vez que o usuario redimensionar a tela o viewport tambem vai ser ajustado por essa funcao
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	//Precisamos dizer pro GLFW chamar essa funcao quando a janela for redimensionada
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	
	//Nao queremos que a aplicacao rode a imagem e feche na hora, entao vamos criar um render loop, que roda ate que o GLFW seja dito pra parar
	while (!glfwWindowShouldClose(window)) {

		//INPUT
		//Se detectar a tecla ESC, fecha a janela
		processInput(window);

		//RENDERIZACAO
		//Limpa a tela com uma cor de nossa escolha
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//EVENTOS
		//Mais explicacao no functions.md
		//Troca o back buffer pelo front buffer
		glfwSwapBuffers(window);

		//Checa se eventos foram acionados (input de teclado ou mouse) e atualiza a janela
		glfwPollEvents();
	}

	//Ao sair do render loop precisamos limpar todos os recursos GLFW que foram alocados
	glfwTerminate();
	return 0;
}