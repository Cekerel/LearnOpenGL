
#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Model.h"

#include <iostream>

float lastX = 800.0f / 2.0f;
float lastY = 600.0f / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);


// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));



const float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};

const unsigned int indices[] = {
    0, 1, 3, // first triangle
    1, 2, 3  // second triangle
};

// positions all containers
glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f),
    glm::vec3(2.0f,  5.0f, -15.0f),
    glm::vec3(-1.5f, -2.2f, -2.5f),
    glm::vec3(-3.8f, -2.0f, -12.3f),
    glm::vec3(2.4f, -0.4f, -3.5f),
    glm::vec3(-1.7f,  3.0f, -7.5f),
    glm::vec3(1.3f, -2.0f, -2.5f),
    glm::vec3(1.5f,  2.0f, -2.5f),
    glm::vec3(1.5f,  0.2f, -1.5f),
    glm::vec3(-1.3f,  1.0f, -1.5f)
};

// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(0.7f,  0.2f,  2.0f),
    glm::vec3(2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3(0.0f,  0.0f, -3.0f)
};

const static int SCR_WIDTH = 800;
const static int SCR_HEIGHT = 600;


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


//int main()
//{
//    // glfw: initialize and configure
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    // glfw window creation
//    // --------------------
//    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    // tell GLFW to capture our mouse
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//
//    // Init GLEW
//    glewExperimental = true;
//    if (glewInit() != GLEW_OK)
//    {
//        std::cout << "Init GLEW failed..." << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//
//    // configure global opengl state
//// -----------------------------
//    glEnable(GL_DEPTH_TEST);
//
//
//    // load textures (we now use a utility function to keep the code more organized)
//// -----------------------------------------------------------------------------
//    unsigned int diffuseMap = loadTexture("container2.png");
//    unsigned int specularMap = loadTexture("container2_specular.png");
//
//
//    unsigned int cubeVAO;
//    glGenVertexArrays(1, &cubeVAO);
//    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//    glBindVertexArray(cubeVAO);
//
//    // Create a VBO and bind the buffer, then input the data
//    unsigned int VBO;
//    glGenBuffers(1, &VBO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    //unsigned int EBO;
//    //glGenBuffers(1, &EBO);
//    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//
//    // Set the vertex configuration pointer
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    //glEnableVertexAttribArray(1);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//
//
//    unsigned int lightVAO;
//    glGenVertexArrays(1, &lightVAO);
//    glBindVertexArray(lightVAO);
//    
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//
//    // Create a cubeShader program
//    Shader cubeShader("cubeVertexSource.txt", "cubeFragmentSource.txt");
//
//
//    Shader lightingShader("lightVertexSource.txt", "lightFragmentSource.txt");
//
//
//    // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window))
//    {
//
//        // per-frame time logic
//        // --------------------
//        float currentFrame = static_cast<float>(glfwGetTime());
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        // input
//        // -----
//        processInput(window);
//
//        // render
//        // ------
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        //float timeValue = glfwGetTime();
//        //float colorValue = sin(timeValue) / 2.0f + 0.5f;
//        //int uniformLocation = glGetUniformLocation(cubeShader.getShaderProgram(), "myOwnColor");
//        //glUniform4f(uniformLocation, 0.0f, colorValue, 0.0f, 1.0f);
//
//        
//
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, diffuseMap);
//
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, specularMap);
//
//        cubeShader.use();
//        // create transformations
//        // camera/view transformation
//        //glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
//        //float radius = 10.0f;
//        //float camX = static_cast<float>(sin(glfwGetTime()) * radius);
//        //float camZ = static_cast<float>(cos(glfwGetTime()) * radius);
//        //view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); 
//        //cubeShader.setMat4("view", view);
//
//
//        glm::mat4 view = camera.GetViewMatrix();
//        cubeShader.setMat4("view", view);
//
//        
//        // pass transformation matrices to the cubeShader
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
//        cubeShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
//
//        // calculate the model matrix for each object and pass it to cubeShader before drawing
//        glm::mat4 model = glm::mat4(1.0f);
//        model = glm::translate(model, cubePositions[9]);
//        model = glm::scale(model, glm::vec3(0.2f));
//        cubeShader.setMat4("model", model);
//
//        glBindVertexArray(cubeVAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//
//
//
//        // be sure to activate shader when setting uniforms/drawing objects
//        lightingShader.use();
//
//        lightingShader.setInt("material.diffuse", 0);
//        lightingShader.setInt("material.specular", 1);
//        lightingShader.setVec3("viewPos", camera.Position);
//        lightingShader.setFloat("material.shininess", 32.0f);
//        /*
//           Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
//           the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
//           by defining light types as classes and set their values in there, or by using a more efficient uniform approach
//           by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
//        */
//        // directional light
//        lightingShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
//        lightingShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
//        lightingShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
//        lightingShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
//        // point light 1
//        lightingShader.setVec3("pointLights[0].position", pointLightPositions[0]);
//        lightingShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
//        lightingShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
//        lightingShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
//        lightingShader.setFloat("pointLights[0].constant", 1.0f);
//        lightingShader.setFloat("pointLights[0].linear", 0.09f);
//        lightingShader.setFloat("pointLights[0].quadratic", 0.032f);
//        // point light 2
//        lightingShader.setVec3("pointLights[1].position", pointLightPositions[1]);
//        lightingShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
//        lightingShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
//        lightingShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
//        lightingShader.setFloat("pointLights[1].constant", 1.0f);
//        lightingShader.setFloat("pointLights[1].linear", 0.09f);
//        lightingShader.setFloat("pointLights[1].quadratic", 0.032f);
//        // point light 3
//        lightingShader.setVec3("pointLights[2].position", pointLightPositions[2]);
//        lightingShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
//        lightingShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
//        lightingShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
//        lightingShader.setFloat("pointLights[2].constant", 1.0f);
//        lightingShader.setFloat("pointLights[2].linear", 0.09f);
//        lightingShader.setFloat("pointLights[2].quadratic", 0.032f);
//        // point light 4
//        lightingShader.setVec3("pointLights[3].position", pointLightPositions[3]);
//        lightingShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
//        lightingShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
//        lightingShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
//        lightingShader.setFloat("pointLights[3].constant", 1.0f);
//        lightingShader.setFloat("pointLights[3].linear", 0.09f);
//        lightingShader.setFloat("pointLights[3].quadratic", 0.032f);
//        // spotLight
//        lightingShader.setVec3("spotLight.position", camera.Position);
//        lightingShader.setVec3("spotLight.direction", camera.Front);
//        lightingShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
//        lightingShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
//        lightingShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
//        lightingShader.setFloat("spotLight.constant", 1.0f);
//        lightingShader.setFloat("spotLight.linear", 0.09f);
//        lightingShader.setFloat("spotLight.quadratic", 0.032f);
//        lightingShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
//        lightingShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
//
//
//        lightingShader.setMat4("view", view);
//        lightingShader.setMat4("projection", projection);
//
//        for (unsigned int i = 0; i < 1; i++)
//        {
//            // world transformation
//            glm::mat4 model = glm::mat4(1.0f);
//            model = glm::translate(model, cubePositions[i]);
//            float angle = 20.0f * i;
//            model = glm::rotate(model, glm::radians(angle + (float)glfwGetTime() * (20 + i)), glm::vec3(1.0f, 0.3f, 0.5f));
//            lightingShader.setMat4("model", model);
//
//
//            glBindVertexArray(lightVAO);
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//
//       
//        
//
//        // Draw the triangles
//        //glBindVertexArray(cubeVAO);
//        //for (unsigned int i = 0; i < 10; i++)
//        //{
//        //    // calculate the model matrix for each object and pass it to cubeShader before drawing
//        //    glm::mat4 model = glm::mat4(1.0f);
//        //    model = glm::translate(model, cubePositions[i]);
//        //    model = glm::rotate(model, (float)glfwGetTime() * (i + 5) * glm::radians(30.0f), glm::vec3(i / 10.0f, i / 10.0f, i / 10.0f));
//        //    cubeShader.setMat4("model", model);
//
//        //    glDrawArrays(GL_TRIANGLES, 0, 36);
//        //}
//        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    glDeleteVertexArrays(1, &cubeVAO);
//    glDeleteBuffers(1, &VBO);
//
//
//    // glfw: terminate, clearing all previously allocated GLFW resources.
//    // ------------------------------------------------------------------
//    glfwTerminate();
//    return 0;
//}


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    // Init GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Init GLEW failed..." << std::endl;
        glfwTerminate();
        return -1;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    Shader ourShader("modelVertexSource.txt", "modelFragmentSource.txt");

    // load models
    // -----------
    Model ourModel("nanosuit/nanosuit.obj");


    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        ourShader.use();

        //// view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
