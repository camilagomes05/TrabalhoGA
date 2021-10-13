/* Hello Triangle - código adaptado de https://learnopengl.com/#!Getting-started/Hello-Triangle
 *
 * Adaptado por Rossana Baptista Queiroz
 * para a disciplina de Processamento Gráfico - Jogos Digitais - Unisinos
 * Versão inicial: 7/4/2017
 * Última atualização em 09/08/2021
 *
 */

#include <iostream>
#include <string>
#include <assert.h>
#include <cmath>


using namespace std;

// GLAD
#include <glad/glad.h>

// GLFW
#include <GLFW/glfw3.h>

#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"

#include "Shader.h"

#include "Object.h"

#include "Sprite.h"

#include <vector>

using namespace std;

// Protótipo da função de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Protótipos das funções
//int setupGeometry();
int loadTexture(string path);
GLuint createSprite();

// Dimensões da janela (pode ser alterado em tempo de execução)
const GLuint WIDTH = 1000, HEIGHT = 600;

// Função MAIN
int main()
{
	// Inicialização da GLFW
	glfwInit();

	//Muita atenção aqui: alguns ambientes não aceitam essas configurações
	//Você deve adaptar para a versão do OpenGL suportada por sua placa
	//Sugestão: comente essas linhas de código para desobrir a versão e
	//depois atualize (por exemplo: 4.5 com 4 e 5)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Essencial para computadores da Apple
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Criação da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Encontre os Easter Eggs!", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da função de callback para a janela GLFW
	//glfwSetKeyCallback(window, key_callback);
	glfwSetKeyCallback(window, key_callback);


	// GLAD: carrega todos os ponteiros d funções da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Obtendo as informações de versão
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Compilando e buildando o programa de shader
	Shader* shader = new Shader("./shaders/sprite.vs", "./shaders/sprite.fs");
	Shader* sprShader = new Shader("./shaders/animatedsprites.vs", "./shaders/animatedsprites.fs");

	GLuint texID = loadTexture("./textures/2.png");
	GLuint texID1 = loadTexture("./textures/sh1.png");
	GLuint texID2 = loadTexture("./textures/sh2.png");
	GLuint texID3 = loadTexture("./textures/sh3.png");
	GLuint texID4 = loadTexture("./textures/sh4.png");
	GLuint texID5 = loadTexture("./textures/sh5.png");
	GLuint texID6 = loadTexture("./textures/sh6.png");
	GLuint texID7 = loadTexture("./textures/sh7.png");
	GLuint texID8 = loadTexture("./textures/sh8.png");
	GLuint texID9 = loadTexture("./textures/sh9.png");
	GLuint texID10 = loadTexture("./textures/sh10.png");
	GLuint texID11 = loadTexture("./textures/sh11.png");
	GLuint texID12 = loadTexture("./textures/sh12.png");
	GLuint texID13 = loadTexture("./textures/sh13.png");
	GLuint texID14 = loadTexture("./textures/sh14.png");
	GLuint texID15 = loadTexture("./textures/sh15.png");
	GLuint texID16 = loadTexture("./textures/sh16.png");
	GLuint texID17 = loadTexture("./textures/sh17.png");
	GLuint texID18 = loadTexture("./textures/sh18.png");
	GLuint texID19 = loadTexture("./textures/sh19.png");
	GLuint texID20 = loadTexture("./textures/sh20.png");
	GLuint texID21 = loadTexture("./textures/sh21.png");
	GLuint texID22 = loadTexture("./textures/sh22.png");
	GLuint texID23 = loadTexture("./textures/sh23.png");
	GLuint texID24 = loadTexture("./textures/sh24.png");
	GLuint texID25 = loadTexture("./textures/sh25.png");
	GLuint texID26 = loadTexture("./textures/sh26.png");
	GLuint texID27 = loadTexture("./textures/sh27.png");
	GLuint texID28 = loadTexture("./textures/sh28.png");
	GLuint texID29 = loadTexture("./textures/yoshi.png");


	Object backgroud;
	backgroud.initialize();
	backgroud.setPosition(glm::vec3(400, 300, 0));
	backgroud.setDimensions(glm::vec3(800, 600, 1.0));
	backgroud.setTexture(texID);
	backgroud.setShader(shader);

	Object player;
	player.initialize();
	player.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player.setTexture(texID1);
	player.setShader(shader);

	Object player2;
	player2.initialize();
	player2.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player2.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player2.setTexture(texID2);
	player2.setShader(shader);

	Object player3;
	player3.initialize();
	player3.setPosition(glm::vec3((rand() % 1000), (rand() % 60), 0.0));
	player3.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player3.setTexture(texID3);
	player3.setShader(shader);

	Object player4;
	player4.initialize();
	player4.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player4.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player4.setTexture(texID4);
	player4.setShader(shader);

	Object player5;
	player5.initialize();
	player5.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player5.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player5.setTexture(texID5);
	player5.setShader(shader);

	Object player6;
	player6.initialize();
	player6.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player6.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player6.setTexture(texID6);
	player6.setShader(shader);

	Object player7;
	player7.initialize();
	player7.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player7.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player7.setTexture(texID7);
	player7.setShader(shader);

	Object player8;
	player8.initialize();
	player8.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player8.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player8.setTexture(texID8);
	player8.setShader(shader);

	Object player9;
	player9.initialize();
	player9.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player9.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player9.setTexture(texID9);
	player9.setShader(shader);

	Object player10;
	player10.initialize();
	player10.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player10.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player10.setTexture(texID10);
	player10.setShader(shader);

	Object player11;
	player11.initialize();
	player11.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player11.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player11.setTexture(texID11);
	player11.setShader(shader);
		
	Object player12;
	player12.initialize();
	player12.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player12.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player12.setTexture(texID12);
	player12.setShader(shader);

	Object player13;
	player13.initialize();
	player13.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player13.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player13.setTexture(texID13);
	player13.setShader(shader);

	Object player14;
	player14.initialize();
	player14.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player14.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player14.setTexture(texID14);
	player14.setShader(shader);

	Object player15;
	player15.initialize();
	player15.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player15.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player15.setTexture(texID15);
	player15.setShader(shader);

	Object player16;
	player16.initialize();
	player16.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player16.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player16.setTexture(texID16);
	player16.setShader(shader);

	Object player17;
	player17.initialize();
	player17.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player17.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player17.setTexture(texID17);
	player17.setShader(shader);

	Object player18;
	player18.initialize();
	player18.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player18.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player18.setTexture(texID18);
	player18.setShader(shader);

	Object player19;
	player19.initialize();
	player19.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player19.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player19.setTexture(texID19);
	player19.setShader(shader);

	Object player20;
	player20.initialize();
	player20.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player20.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player20.setTexture(texID20);
	player20.setShader(shader);

	Object player21;
	player21.initialize();
	player21.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player21.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player21.setTexture(texID21);
	player21.setShader(shader);

	Object player22;
	player22.initialize();
	player22.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player22.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player22.setTexture(texID22);
	player22.setShader(shader);

	Object player23;
	player23.initialize();
	player23.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player23.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player23.setTexture(texID23);
	player23.setShader(shader);

	Object player24;
	player24.initialize();
	player24.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player24.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player24.setTexture(texID24);
	player24.setShader(shader);

	Object player25;
	player25.initialize();
	player25.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player25.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player25.setTexture(texID25);
	player25.setShader(shader);

	Object player26;
	player26.initialize();
	player26.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player26.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player26.setTexture(texID26);
	player26.setShader(shader);

	Object player27;
	player27.initialize();
	player27.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player27.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player27.setTexture(texID27);
	player27.setShader(shader);

	Object player28;
	player28.initialize();
	player28.setPosition(glm::vec3((rand() % 1000), (rand() % 600), 0.0));
	player28.setDimensions(glm::vec3(20.0, 20.0, 1.0));
	player28.setTexture(texID28);
	player28.setShader(shader);

	vector <Object> objects;

	Sprite sprPlayer;
	sprPlayer.setSpritesheet(texID, 2, 8);
	sprPlayer.setPosition(glm::vec3(200.0, 220.0, 0.0));
	sprPlayer.setDimensions(glm::vec3(200.0, 200.0, 1.0));
	sprPlayer.setShader(sprShader);

	GLuint VAO = createSprite();

	//Ativando o shader que será usado
	shader->Use();

	GLint projLoc = glGetUniformLocation(shader->Program, "projection");
	assert(projLoc > -1);

	GLint modelLoc = glGetUniformLocation(shader->Program, "model");
	assert(modelLoc > -1);

	glUniform1i(glGetUniformLocation(shader->Program, "tex1"), 0);
		
	glm::mat4 ortho = glm::mat4(1); //inicializa com a matriz identidade

	glm::mat4 model = glm::mat4(1);


	double xmin = 0.0, xmax = 800.0, ymin = 0.0, ymax = 600.0;

	// Loop da aplicação - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as funções de callback correspondentes
		glfwPollEvents();

		// Definindo as dimensões da viewport com as mesmas dimensões da janela da aplicação
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		ortho = glm::ortho(xmin, xmax, ymin, ymax, -1.0, 1.0);

		//Enviar a matriz de projeção ortográfica para o shader
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(ortho));

		//Chamar sprints

		backgroud.update();
		backgroud.draw();

		player.update();
		player.draw();

		player2.update();
		player2.draw();

		player3.update();
		player3.draw();

		player4.update();
		player4.draw();

		player5.update();
		player5.draw();

		player6.update();
		player6.draw();

		player7.update();
		player7.draw();

		player8.update();
		player8.draw();

		player9.update();
		player9.draw();

		player10.update();
		player10.draw();

		player11.update();
		player11.draw();

		player12.update();
		player12.draw();

		player13.update();
		player13.draw();

		player14.update();
		player14.draw();

		player15.update();
		player15.draw();

		player16.update();
		player16.draw();

		player17.update();
		player17.draw();

		player18.update();
		player18.draw();

		player19.update();
		player19.draw();

		player20.update();
		player20.draw();

		player21.update();
		player21.draw();

		player22.update();
		player22.draw();

		player23.update();
		player23.draw();

		player24.update();
		player24.draw();

		player25.update();
		player25.draw();

		player26.update();
		player26.draw();

		player27.update();
		player27.draw();

		player28.update();
		player28.draw();

		sprPlayer.update();
		sprPlayer.draw();

		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}

	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);
	// Finaliza a execução da GLFW, limpando os recursos alocados por ela
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int loadTexture(string path)
{
	GLuint texID;

	// Gera o identificador da textura na memória 
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	//Ajusta os parâmetros de wrapping e filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//Carregamento da imagem
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		if (nrChannels == 3) //jpg, bmp
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		}
		else //png
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);

	return texID;
}

GLuint createSprite()
{
	GLuint VAO;
	GLuint VBO, EBO;

	glGenVertexArrays(1, &VAO);

	return VAO;
}

