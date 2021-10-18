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

bool playerFacingRight = true;
bool playerFacingLeft = true;
bool up = true;
bool down = true;
bool pause = false;


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

	// Background
	GLuint texID = loadTexture("./textures/2.png");

	vector <Object> objects;

	Object backgroud;
	backgroud.initialize();
	backgroud.setPosition(glm::vec3(400, 300, 0));
	backgroud.setDimensions(glm::vec3(800, 600, 1.0));
	backgroud.setTexture(texID);
	backgroud.setShader(shader);

	// Personagens

	GLuint img[28];
	Object player[28];

	int i = 0;
	int y = 1;

	while (i <= 28 || y <= 28) {

		int posX[28];
		int posY[28];

		img[i] = loadTexture("./textures/sh" + to_string(y) + ".png");
		player[i].initialize();
		player[i].setPosition(glm::vec3(posX[i + 1] = (rand() % 1000), posY[i + 1] = (rand() % 600), 0.0));
		player[i].setDimensions(glm::vec3(20.0, 20.0, 1.0));
		player[i].setTexture(img[i]);
		player[i].setShader(shader);
		i++;
		y++;
	}

	// Yoshi

	GLuint texID2 = loadTexture("./textures/yoshi.png");

	Sprite sprPlayer;
	sprPlayer.setSpritesheet(texID2, 2, 8);
	sprPlayer.setPosition(glm::vec3(20.0, 20.0, 0.0));
	sprPlayer.setDimensions(glm::vec3(30.0, 30.0, 1.0));
	sprPlayer.setShader(sprShader);
	sprPlayer.setAnimation(1);

	GLuint VAO = createSprite();



	//Ativando o shader que será usado
	shader->Use();

	GLint projLoc = glGetUniformLocation(shader->Program, "projection");
	assert(projLoc > -1);

	glUniform1i(glGetUniformLocation(shader->Program, "tex1"), 0);


	glm::mat4 ortho = glm::mat4(1); //inicializa com a matriz identidade

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


		//Chamar objects
		backgroud.update();
		backgroud.draw();

		int p = 0;

		while (p <= 28) {
			player[p].update();
			player[p].draw();
			p++;
		}

		// Para o Yoshi caminhar lentamente
		Sleep(200);


		sprShader->Use();
		sprShader->setMat4("projection", glm::value_ptr(ortho));


		// Yoshi caminhar
		if (playerFacingRight) {
			if (pause) {
				sprPlayer.setAnimation(1);
				sprPlayer.setPosition(glm::vec3(sprPlayer.getPosition().x + 10, sprPlayer.getPosition().y, 0));
			}
		}
		else if (playerFacingLeft) {
			if (pause) {
				sprPlayer.setAnimation(0);
				sprPlayer.setPosition(glm::vec3(sprPlayer.getPosition().x - 10, sprPlayer.getPosition().y, 0));
			}
		}	
		else if (up) {
			if (pause) {
				sprPlayer.setPosition(glm::vec3(sprPlayer.getPosition().x, sprPlayer.getPosition().y + 10, 0));
			}
		}
		else if (down) {
			if (pause) {
				sprPlayer.setPosition(glm::vec3(sprPlayer.getPosition().x, sprPlayer.getPosition().y - 10 , 0));
			}
		}


		//Colisão das bordas
		if (sprPlayer.getPosition().x == 1000) {
			sprPlayer.setPosition(glm::vec3(sprPlayer.getPosition().x - 10, sprPlayer.getPosition().y, 1));
			playerFacingLeft = true;
		}

		else if (sprPlayer.getPosition().x < 0) {
			sprPlayer.setPosition(glm::vec3(sprPlayer.getPosition().x + 10, sprPlayer.getPosition().y, 1));
			playerFacingRight = true;
		}

		else if (sprPlayer.getPosition().y == 800) {
			sprPlayer.setPosition(glm::vec3(sprPlayer.getPosition().x, sprPlayer.getPosition().y - 10, 1));
			down = true;
		}
		else if (sprPlayer.getPosition().y < 0) {
			sprPlayer.setPosition(glm::vec3(sprPlayer.getPosition().x, sprPlayer.getPosition().y + 10, 1));
			up = true;
		}

		
		//Chamar sprite
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

//Chamada de teclado
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
		
	if (key == GLFW_KEY_D && (action == GLFW_PRESS)) {
		playerFacingRight = true;
		playerFacingLeft = false;
		up = false;
		down = false;
		pause = true;
	}

	if (key == GLFW_KEY_A && (action == GLFW_PRESS)) {
		playerFacingRight = false;
		playerFacingLeft = true;
		up = false;
		down = false;
		pause = true;
	}

	if (key == GLFW_KEY_W && (action == GLFW_PRESS)) {
		playerFacingRight = false;
		playerFacingLeft = false;
		up = true;
		down = false;
		pause = true;
	}
	

	if (key == GLFW_KEY_S && (action == GLFW_PRESS)) {
		playerFacingRight = false;
		playerFacingLeft = false;
		up = false;
		down = true;
		pause = true;	
	}
		
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

