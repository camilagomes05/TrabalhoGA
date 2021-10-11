/* Hello Triangle - c�digo adaptado de https://learnopengl.com/#!Getting-started/Hello-Triangle
 *
 * Adaptado por Rossana Baptista Queiroz
 * para a disciplina de Processamento Gr�fico - Jogos Digitais - Unisinos
 * Vers�o inicial: 7/4/2017
 * �ltima atualiza��o em 09/08/2021
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

// Prot�tipo da fun��o de callback de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// Prot�tipos das fun��es
//int setupGeometry();
int loadTexture(string path);
GLuint createSprite();

// Dimens�es da janela (pode ser alterado em tempo de execu��o)
const GLuint WIDTH = 800, HEIGHT = 600;

// Fun��o MAIN
int main()
{
	// Inicializa��o da GLFW
	glfwInit();

	//Muita aten��o aqui: alguns ambientes n�o aceitam essas configura��es
	//Voc� deve adaptar para a vers�o do OpenGL suportada por sua placa
	//Sugest�o: comente essas linhas de c�digo para desobrir a vers�o e
	//depois atualize (por exemplo: 4.5 com 4 e 5)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Essencial para computadores da Apple
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Cria��o da janela GLFW
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Encontre os Easter Eggs!", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	// Fazendo o registro da fun��o de callback para a janela GLFW
	//glfwSetKeyCallback(window, key_callback);
	glfwSetKeyCallback(window, key_callback);


	// GLAD: carrega todos os ponteiros d fun��es da OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	// Obtendo as informa��es de vers�o
	const GLubyte* renderer = glGetString(GL_RENDERER); /* get renderer string */
	const GLubyte* version = glGetString(GL_VERSION); /* version as a string */
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	//glEnable(GL_DEPTH_TEST);

	
	 glEnable(GL_BLEND);
	 glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Compilando e buildando o programa de shader
	Shader* shader = new Shader("./shaders/sprite.vs", "./shaders/sprite.fs");
	Shader* sprShader = new Shader("./shaders/animatedsprites.vs", "./shaders/animatedsprites.fs");

	GLuint texID = loadTexture("./textures/mario.png");
	GLuint texID2 = loadTexture("./textures/cenario.png");
	GLuint texID3 = loadTexture("./textures/City1.png");
	GLuint texID4 = loadTexture("./textures/player.png");
	GLuint texID5 = loadTexture("./textures/characterRun.png");
	GLuint texID6 = loadTexture("./textures/yoshi.png");


	//Sorteio de posi��es dos objetos e Sprite

	float posX = 0.0, posY = 0.0;
	srand(time(NULL)); //� para gerar um numero aleatorio todas as vezes que abrir o programa

	do
	{
		posX = rand() % 800; // Vai gerar o numero entre 0 e 799
		posY = rand() % 600; // Vai gerar o numero entre 0 e 599
	} while (posX == 0.0 || posY == 0.0); //Vai sorteando at� que o "a" n�o seja um n�mero que eu defini


	Object backgroud;
	backgroud.initialize();
	backgroud.setPosition(glm::vec3(400, 300, 0));
	backgroud.setDimensions(glm::vec3(800, 600, 1.0));
	backgroud.setTexture(texID3);
	backgroud.setShader(shader);
	//obj.update();

	Object player;
	player.initialize();
	player.setPosition(glm::vec3(posX, posY, 0.0));
	player.setDimensions(glm::vec3(128.0, 128.0, 1.0));
	player.setTexture(texID4);
	player.setShader(shader);

	vector <Object> objects;

	float xini = 100;
	float yini = 100;

	float objW = 100;
	float objH = 120;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {

			Object obj;
			obj.initialize();
			obj.setPosition(glm::vec3(xini + j* objW, yini + i* objH, 0.0));
			obj.setDimensions(glm::vec3(objW, objH, 1.0));
			obj.setTexture(texID);
			obj.setShader(shader);
			objects.push_back(obj);
		}
	}

	Sprite sprPlayer;
	sprPlayer.initialize();
	sprPlayer.setSpriteSheet(texID5, 1, 2);
	sprPlayer.setPosition(glm::vec3(posX, posY, 0));
	sprPlayer.setDimensions(glm::vec3(40.0, 40.0, 1.0));
	sprPlayer.setShader(sprShader);
	sprPlayer.setAnimation(1);

	Sprite sprPlayer2;
	sprPlayer2.initialize();
	sprPlayer2.setSpriteSheet(texID6, 2, 8);
	sprPlayer2.setPosition(glm::vec3(posX, posY, 0.0));
	sprPlayer2.setDimensions(glm::vec3(100.0, 100.0, 1.0));
	sprPlayer2.setShader(sprShader);
	sprPlayer2.setAnimation(1);

	// Gerando um buffer simples, com a geometria de um tri�ngulo
	//GLuint VAO = setupGeometry();
	GLuint VAO = createSprite();

	//Ativando o shader que ser� usado
	shader->Use();

	// Enviando a cor desejada (vec4) para o fragment shader
	// Utilizamos a vari�veis do tipo uniform em GLSL para armazenar esse tipo de info
	// que n�o est� nos buffers

	GLint projLoc = glGetUniformLocation(shader->Program, "projection");
	assert(projLoc > -1);

	GLint modelLoc = glGetUniformLocation(shader->Program, "model");
	assert(modelLoc > -1);

	glUniform1i(glGetUniformLocation(shader->Program, "tex1"), 0);
		
	glm::mat4 ortho = glm::mat4(1); //inicializa com a matriz identidade

	glm::mat4 model = glm::mat4(1);


	double xmin = 0.0, xmax = 800.0, ymin = 0.0, ymax = 600.0;

	// Loop da aplica��o - "game loop"
	while (!glfwWindowShouldClose(window))
	{
		// Checa se houveram eventos de input (key pressed, mouse moved etc.) e chama as fun��es de callback correspondentes
		glfwPollEvents();

		// Definindo as dimens�es da viewport com as mesmas dimens�es da janela da aplica��o
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height);

		ortho = glm::ortho(xmin, xmax, ymin, ymax, -1.0, 1.0);

		model = glm::mat4(1); //matriz identidade para "limpar a matriz"

		model = glm::translate(model, glm::vec3(400.0f, 300.0f, 0.0f));
		model = glm::scale(model, glm::vec3(302.0f, 402.f, 1.0));

		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//Enviar a matriz de proje��o ortogr�fica para o shader
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(ortho));

		//Chamar sprints
		float newRot = (float)glfwGetTime();
		objects[0].setAngle(newRot);

		backgroud.update();
		backgroud.draw();

		player.update();
		player.draw();

		sprPlayer.update();
		sprPlayer.draw();

		sprPlayer2.update();
		sprPlayer2.draw();


		// Troca os buffers da tela
		glfwSwapBuffers(window);
	}

	// Pede pra OpenGL desalocar os buffers
	glDeleteVertexArrays(1, &VAO);
	// Finaliza a execu��o da GLFW, limpando os recursos alocados por ela
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

	// Gera o identificador da textura na mem�ria 
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	//Ajusta os par�metros de wrapping e filtering
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

