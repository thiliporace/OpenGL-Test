#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

//Codigo fonte Vertex Shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos; \n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n\0";

//Codigo fonte Fragment Shader
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor; \n"
"void main()\n"
"{\n"
"FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0);\n"
"}\n\0";

int main() {
	glfwInit();

	//Diz qual versao do OpenGL o GLFW vai usar
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//Diz qual perfil o GLFW vai usar
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Coordenadas dos vertices
	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //Esquerda baixo
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, //Direita baixo
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f //Meio em cima
	};

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

	//Cria Vertex Shader Object e pega sua referencia
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//Conecta o Vertex Shader source com o Vertex Shader Object
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	//Compila o Vertex Shader em codigo de maquina
	glCompileShader(vertexShader);

	//Cria Fragment Shader Object e pega sua referencia
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//Conecta Fragment Shader source no Fragment Shader Object
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//Compila o Fragment Shader em codigo de maquina
	glCompileShader(fragmentShader);

	//Cria Shader Program Object e pega sua referencia
	GLuint shaderProgram = glCreateProgram();
	//Conecta o Vertex e o Fragment shader no Shader Program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//Linka todos os shaders no Shader Program
	glLinkProgram(shaderProgram);

	//Deleta os shaders pois nao sao mais necessarios
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Cria referencia pro Vertex Array Object e Vertex Buffer Object
	GLuint VAO, VBO;

	//Gera o VAO e VBO com apenas um objeto cada
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Faz o VAO o Vertex Array Object atual bindando ele
	glBindVertexArray(VAO);

	//Binda o VBO especificando que e um GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Introduz os vertices no VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//Configura o Vertex Attribute para que o OpenGL saiba como ler o VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//Liga o Vertex Attribute pra que o OpenGL saiba como usar ele
	glEnableVertexAttribArray(0);

	//Binda o VBO e VAO pra 0 pra que a gente nao acidentalmente modifique eles
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	//Diz pro opengl preparar para trocar a cor do buffer
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Troca o back buffer (onde a cor foi criada) pelo front buffer
	glfwSwapBuffers(window);

	//While usado pra manter a janela aberta
	while (!glfwWindowShouldClose(window)) {

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//Diz pro OpenGL qual Shader Program queremos usar
		glUseProgram(shaderProgram);
		//Conecta o VAO pro OpenGL saber como usar ele
		glBindVertexArray(VAO);
		//Desenha o triangulo usando a primitiva GL_TRIANGLES 
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);

		//Diz pro glfw pra processar todos os eventos (como redimensionar a janela e mexer nela)
		glfwPollEvents();
	}

	//Deleta todos os objetos criados
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}