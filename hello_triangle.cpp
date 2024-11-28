#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "main_functions.h"

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

static void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

//Checa se a compilacao do glCompileShader teve sucesso
static void checkShaderErrors(unsigned int shader) {
	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::" << shader << "COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

//Checa se a linkagem do shaderProgram deu certo
static void checkShaderProgramErrors(unsigned int shaderProgram) {
	int success;
	char infoLog[512];
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::" << shaderProgram << "COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}

//Precisamos escrever o vertex shader na linguagem de shader GLSL. Embaixo esta o codigo fonte de um vertex shader basico em GLSL
//Especificamos a versao do OpenGL (3.3) e escolhemos o perfil core
static const char* vertexShaderSource = "#version 330 core\n"
//Atributo do vertice, recebe um vec3 pra sua posicao como entrada
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
//gl_Position e o output do vertex shader
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

static const char* fragmentShaderSource = "#version 330 core\n"
//Variavel de output que define a cor final
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int hello_triangle() {

	//Coordenadas 3D normalizadas (range de -1 a 1) dos vertices do triangulo
	float vertices[] = {
		//Como o Z de todos os pontos e 0 parece que a imagem e 2D
		-0.5f, -0.5f, 0.0f, //Ponta direita
		0.5f, -0.5f, 0.0f, //Ponta esquerda
		0.0f, 0.5f, 0.0f //Ponta de cima
	};

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
	void framebuffer_size_callback(GLFWwindow * window, int width, int height);

	//Precisamos dizer pro GLFW chamar essa funcao quando a janela for redimensionada
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);



	//Criando o vertex buffer object e o vertex array object
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	//Faz o VAO o Vertex Array Object atual bindando ele
	glBindVertexArray(VAO);

	//Bindamos o VBO no tipo de buffer object GL_ARRAY_BUFFER que e pro VBO, agora qualquer mudanca feita no GL_ARRAY_BUFFER vai ser feita no VBO conectado
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Copia o dado dos vertices pra memoria do buffer
	//1 arg: tipo de buffer que vamos copiar os dados para. 2 arg: tamanho dos dados que vai ser passado. 3 arg: dados. 4 arg: functions.md explica
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Dizemos pro OpenGL como ele deve interpretar os dados do vertice por vertice, mais explicacao no functions.md
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//Ligamos o vertex attribute na posicao 0, que foi onde criamos la no codigo fonte 
	glEnableVertexAttribArray(0);


	//Criando o vertex shader object
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Conectamos o codigo fonte do vertex shader no vertex shader object e compilamos o shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	checkShaderErrors(vertexShader);


	//Criando o fragment shader object
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Conectamos o codigo fonte do fragment shader no fragment shader object e compilamos o shader
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	checkShaderErrors(fragmentShader);



	//Precisamos criar o shader program que vai conectar todos os shaders que criamos, mais explicacao no functions.md
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	//Conectar os shaders criados no shader program e depois linka eles
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	checkShaderProgramErrors(shaderProgram);

	//Nao precisamos mais dos shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);



	//Nao queremos que a aplicacao rode a imagem e feche na hora, entao vamos criar um render loop, que roda ate que o GLFW seja dito pra parar
	while (!glfwWindowShouldClose(window)) {

		//INPUT
		//Se detectar a tecla ESC, fecha a janela
		processInput(window);

		//RENDERIZACAO
		//Limpa a tela com uma cor de nossa escolha
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Ativar o shader program
		glUseProgram(shaderProgram);

		//Conecta o VAO pro OpenGL saber como usar ele
		glBindVertexArray(VAO);

		//Desenha as primitivas com base no shader ativo
		glDrawArrays(GL_TRIANGLES, 0, 3);

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