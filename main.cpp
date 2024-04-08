#include "Models/Model3D.h"
#include "Models/GameObjects/Player.h"
#include "Models/GameObjects/Enemy.h"
#include "Models/Camera/PerspectiveCamera.h"
#include "Models/Camera/OrthoCamera.h"
#include "Models/Light/Directional.h"
#include "Models/Light/Point.h"
#include "Models/Shader.h"

bool is1stPerson = false;
bool is3rdPerson = false;
bool isPerspective = true;
bool isPlayer = true;
double tLastUpdate = 0.0;
float tTimePerFrame = 1.0 / 60.0;
const double keyPressDelay = 0.2; 
double lastKeyPressTime = 0.0;
PerspectiveCamera* perspectiveCamera = new PerspectiveCamera();
OrthoCamera* orthoCamera = new OrthoCamera();

static void initWindow(GLFWwindow*& window, float window_width, float window_height) {
	/* Initialize the library */
	if (!glfwInit())
		return;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(window_width, window_height, "Ramirez, Catrina Mikaela & Jacinto, Gracielle Ann", NULL, NULL);
    if (!window) {
		glfwTerminate();
		return;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	gladLoadGL();
}


int main(void) {
    GLFWwindow* window;

    float window_width = 600;
    float window_height = 600;

    initWindow(window, window_width, window_height);

    //Player
    Player* pPlayer = new Player("3D/0submarine.obj", 
                                "Shaders/sample.vert", 
                                "Shaders/samplePlayer.frag", 
                                "3D/0submarine.jpg", 
                                glm::vec3(0.f, 0.f, 0.f), 1.f, false);
    //Pirate
    Enemy* pEnemy = new Enemy("3D/1pirate.obj", 
                               "Shaders/sample.vert", 
                               "Shaders/sample.frag", 
                               "3D/1pirate.jpg", 
                                glm::vec3(20.f, -5.f, -20.f), 2.0f, false);                         

    //Turtle Monster
    Enemy* pEnemy2 = new Enemy("3D/2turtle.obj", 
                                "Shaders/sample.vert", 
                                "Shaders/sample.frag", 
                                "3D/2turtle.jpg", 
                                glm::vec3(-30.f, -11.f, -30.f),15.0f, false);
    
    //Octopus
    Enemy* pEnemy3 = new Enemy("3D/3octopus.obj", 
                                "Shaders/sample.vert", 
                                "Shaders/sample.frag", 
                                "3D/3octopus.jpg", 
                                glm::vec3(5.f, -10.f, -40.f), 5.0f, false);

    //Angler Fish
    Enemy* pEnemy4 = new Enemy("3D/4angler.obj", 
                                "Shaders/sample.vert", 
                                "Shaders/sample.frag", 
                                "3D/4angler.png", 
                                glm::vec3(0.f, -30.f, -70.f), 5.0f, false);

    //Carp Fish
    Enemy* pEnemy5 = new Enemy("3D/5carp.obj", 
                                "Shaders/sample.vert", 
                                "Shaders/sample.frag", 
                                "3D/5carp.png", 
                                glm::vec3(40.f, -40.f, -60.f), 50.0f, false);

    //Tuna Fish
    Enemy* pEnemy6 = new Enemy("3D/6tuna.obj", 
                                "Shaders/sample.vert", 
                                "Shaders/sample.frag", 
                                "3D/6tuna.png", 
                                glm::vec3(-40.f, -30.f, -70.f), 5.0f, false);

    Point* pointLightSrc = new Point("3D/0submarine.obj", 
        "Shaders/lightShader.vert", 
        "Shaders/lightShader.frag", 
        "3D/0submarine.png", 
        glm::vec3(0.f, 7.f, -4.f), 10.f,
        glm::vec3(1.f, 0.f, 0.f),
        glm::vec3(0.f, 1.f, 0.f),
        10.f, 0.5f, 16.0f);

    Directional* directionalLightSrc = new Directional("3d/0submarine.obj", 
        "shaders/lightshader.vert", 
        "shaders/lightshader.frag", 
        "3d/0submarine.jpg",
        glm::vec3(0.f, 0.f, 0.f), 10.f,
        glm::vec3(0.36f, 0.89f, 0.96f),
        glm::vec3(0.36f, 0.89f, 0.96f),
        1.f, 0.5f, 16.0f);

    directionalLightSrc->setDirection(glm::vec3(0.0f, -1.0f, 0.f));

    //skybox start
    Shader* skyBoxShader = new Shader("Shaders/skyboxvert.vert", "Shaders/skyboxfrag.frag");

    GLuint skyboxShaderProg = skyBoxShader->getShaderProg();
    glEnable(GL_DEPTH_TEST);

    float skyboxVertices[] {
    -1.f, -1.f, 1.f, //0
    1.f, -1.f, 1.f,  //1
    1.f, -1.f, -1.f, //2
    -1.f, -1.f, -1.f,//3
    -1.f, 1.f, 1.f,  //4
    1.f, 1.f, 1.f,   //5
    1.f, 1.f, -1.f,  //6
    -1.f, 1.f, -1.f  //7
    };

    unsigned int skyboxIndices[] {
    1,2,6,
    6,5,1,

    0,4,7,
    7,3,0,

    4,5,6,
    6,7,4,

    0,3,2,
    2,1,0,

    0,1,5,
    5,4,0,

    3,7,6,
    6,2,3
    };

    unsigned int skyboxVAO, skyboxVBO, skyboxEBO;

    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glGenBuffers(1, &skyboxEBO);

    glBindVertexArray(skyboxVAO);

    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GL_INT) * 36, &skyboxIndices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    std::string facesSkybox[] {
        
        "skybox/left.png",
        "skybox/right.png",
        "skybox/up.png",
        "skybox/down.png",
        "skybox/forward.png",
        "skybox/back.png"
        
    };

    GLuint skyboxTex;

    glGenTextures(1, &skyboxTex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    

    for (unsigned int i = 0; i < 6; i++) {
        int w, h, skyColorChannel;

        stbi_set_flip_vertically_on_load(false);

        unsigned char* data = stbi_load(facesSkybox[i].c_str(), &w, &h, &skyColorChannel, 0);   

        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
    }

    stbi_set_flip_vertically_on_load(true);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //initiate matrices
        glm::mat4 identity_matrix = glm::mat4(1.0f);
        glm::mat4 projectionMatrix = glm::mat4();
        glm::mat4 viewMatrix = glm::mat4();
        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);

        double currentTime = glfwGetTime();
        lastKeyPressTime += currentTime;

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && (lastKeyPressTime >= keyPressDelay)) {
			lastKeyPressTime = currentTime;
            isPlayer = !isPlayer;
            std::cout << "perspective" << std::endl;
		}

        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && (lastKeyPressTime >= keyPressDelay)) {
			lastKeyPressTime = currentTime;
            pointLightSrc->cycleLightIntensity();
        }

        if (isPerspective) {
            projectionMatrix = perspectiveCamera->getProjectionMatrix(window_width / window_height);
            viewMatrix = perspectiveCamera->getViewMatrix();
            cameraPos = perspectiveCamera->getCameraPosition();
            if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && (lastKeyPressTime >= keyPressDelay)) {
                lastKeyPressTime = currentTime;
                is3rdPerson = true;
                std::cout << "Switched to third-person perspective" << std::endl;
            }
            else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && (lastKeyPressTime >= keyPressDelay)) {
                lastKeyPressTime = currentTime;
                is1stPerson = true;
                std::cout << "Switched to first-person perspective" << std::endl;
            }
        }
        else {
            projectionMatrix = orthoCamera->getProjectionMatrix(window_width / window_height);
            viewMatrix = orthoCamera->getViewMatrix();
            cameraPos = orthoCamera->getCameraPosition();
        }
        
        if (is1stPerson) {
            perspectiveCamera->FOV(is1stPerson, is3rdPerson, pPlayer->getPosition());
            is1stPerson = false;
        }

        if (is3rdPerson) {
            perspectiveCamera->FOV(is1stPerson, is3rdPerson, pPlayer->getPosition());
            is3rdPerson = false;
        }

        tLastUpdate += glfwGetTime();
        glfwSetTime(0.0f);

        while (tLastUpdate > tTimePerFrame) {
           tLastUpdate -= tTimePerFrame;
           perspectiveCamera->updateCamera(window, tTimePerFrame);
           pPlayer->update(window, tTimePerFrame);
           directionalLightSrc->update(window, tTimePerFrame);
           perspectiveCamera->update(window, tTimePerFrame);
           glm::vec3 playerPosition = pPlayer->getPosition();
           glm::vec3 frontPosition = playerPosition + glm::vec3(0.0f, 7, -4);
           pointLightSrc->setPosition(frontPosition);
        }

        glDepthMask(GL_FALSE);
        glDepthFunc(GL_LEQUAL);
        glUseProgram(skyboxShaderProg);
        glm::mat4 sky_view = glm::mat4(1.f);
        sky_view = glm::mat4(glm::mat3(viewMatrix));
        unsigned int skyboxViewLoc = glGetUniformLocation(skyboxShaderProg, "view");
        glUniformMatrix4fv(skyboxViewLoc,
            1,
            GL_FALSE,
            glm::value_ptr(sky_view));

        unsigned int skyboxProjLoc = glGetUniformLocation(skyboxShaderProg, "projection");
        glUniformMatrix4fv(skyboxProjLoc,
            1,
            GL_FALSE,
            glm::value_ptr(projectionMatrix));

        glBindVertexArray(skyboxVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);

        pPlayer->drawPlayer(viewMatrix, projectionMatrix, pointLightSrc->getPosition(), pointLightSrc->getLightColor(isPlayer),
            pointLightSrc->getAmbientStr(), pointLightSrc->getAmbientColor(isPlayer), pointLightSrc->getSpecStr(), pointLightSrc->getSpecPhong(),
            pointLightSrc->getIntensity(), directionalLightSrc->getPosition(), directionalLightSrc->getLightColor(isPlayer), directionalLightSrc->getAmbientStr(),
            directionalLightSrc->getAmbientColor(isPlayer), directionalLightSrc->getSpecStr(), directionalLightSrc->getSpecPhong(), directionalLightSrc->getIntensity(),
            cameraPos);

       
        pEnemy->draw(viewMatrix, projectionMatrix, pointLightSrc->getPosition(), pointLightSrc->getLightColor(isPlayer),
            pointLightSrc->getAmbientStr(), pointLightSrc->getAmbientColor(isPlayer), pointLightSrc->getSpecStr(), pointLightSrc->getSpecPhong(),
            pointLightSrc->getIntensity(), directionalLightSrc->getPosition(), directionalLightSrc->getLightColor(isPlayer), directionalLightSrc->getAmbientStr(),
            directionalLightSrc->getAmbientColor(isPlayer), directionalLightSrc->getSpecStr(), directionalLightSrc->getSpecPhong(), directionalLightSrc->getIntensity(),
            cameraPos);

        pEnemy2->draw(viewMatrix, projectionMatrix, pointLightSrc->getPosition(), pointLightSrc->getLightColor(isPlayer),
            pointLightSrc->getAmbientStr(), pointLightSrc->getAmbientColor(isPlayer), pointLightSrc->getSpecStr(), pointLightSrc->getSpecPhong(),
            pointLightSrc->getIntensity(), directionalLightSrc->getPosition(), directionalLightSrc->getLightColor(isPlayer), directionalLightSrc->getAmbientStr(),
            directionalLightSrc->getAmbientColor(isPlayer), directionalLightSrc->getSpecStr(), directionalLightSrc->getSpecPhong(), directionalLightSrc->getIntensity(),
            cameraPos);

        pEnemy3->draw(viewMatrix, projectionMatrix, pointLightSrc->getPosition(), pointLightSrc->getLightColor(isPlayer),
            pointLightSrc->getAmbientStr(), pointLightSrc->getAmbientColor(isPlayer), pointLightSrc->getSpecStr(), pointLightSrc->getSpecPhong(),
            pointLightSrc->getIntensity(), directionalLightSrc->getPosition(), directionalLightSrc->getLightColor(isPlayer), directionalLightSrc->getAmbientStr(),
            directionalLightSrc->getAmbientColor(isPlayer), directionalLightSrc->getSpecStr(), directionalLightSrc->getSpecPhong(), directionalLightSrc->getIntensity(),
            cameraPos);

        pEnemy4->draw(viewMatrix, projectionMatrix, pointLightSrc->getPosition(), pointLightSrc->getLightColor(isPlayer),
            pointLightSrc->getAmbientStr(), pointLightSrc->getAmbientColor(isPlayer), pointLightSrc->getSpecStr(), pointLightSrc->getSpecPhong(),
            pointLightSrc->getIntensity(), directionalLightSrc->getPosition(), directionalLightSrc->getLightColor(isPlayer), directionalLightSrc->getAmbientStr(),
            directionalLightSrc->getAmbientColor(isPlayer), directionalLightSrc->getSpecStr(), directionalLightSrc->getSpecPhong(), directionalLightSrc->getIntensity(),
            cameraPos);

        pEnemy5->draw(viewMatrix, projectionMatrix, pointLightSrc->getPosition(), pointLightSrc->getLightColor(isPlayer),
            pointLightSrc->getAmbientStr(), pointLightSrc->getAmbientColor(isPlayer), pointLightSrc->getSpecStr(), pointLightSrc->getSpecPhong(),
            pointLightSrc->getIntensity(), directionalLightSrc->getPosition(), directionalLightSrc->getLightColor(isPlayer), directionalLightSrc->getAmbientStr(),
            directionalLightSrc->getAmbientColor(isPlayer), directionalLightSrc->getSpecStr(), directionalLightSrc->getSpecPhong(), directionalLightSrc->getIntensity(),
            cameraPos);

        pEnemy6->draw(viewMatrix, projectionMatrix, pointLightSrc->getPosition(), pointLightSrc->getLightColor(isPlayer),
            pointLightSrc->getAmbientStr(), pointLightSrc->getAmbientColor(isPlayer), pointLightSrc->getSpecStr(), pointLightSrc->getSpecPhong(),
            pointLightSrc->getIntensity(), directionalLightSrc->getPosition(), directionalLightSrc->getLightColor(isPlayer), directionalLightSrc->getAmbientStr(),
            directionalLightSrc->getAmbientColor(isPlayer), directionalLightSrc->getSpecStr(), directionalLightSrc->getSpecPhong(), directionalLightSrc->getIntensity(),
            cameraPos);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}