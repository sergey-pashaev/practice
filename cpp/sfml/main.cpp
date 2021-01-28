#include <cstdint>
#include <iostream>
#include <chrono>
#include <cmath>
#include <cassert>
#include <algorithm>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Vertex shader source.
const char* gVertexSource = R"glsl(
#version 150 core

in vec3 position;
in vec3 color;
in vec2 texcoord;

out vec3 Color;
out vec2 Texcoord;

uniform float time;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    Texcoord = texcoord;
    Color = color;
    gl_Position = proj * view * model * vec4(position, 1.0);
}
)glsl";

// Fragment shader source.
const char* gFragmentSource = R"glsl(
#version 150 core

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;

uniform sampler2D tex1;
uniform sampler2D tex2;
uniform float time;

void main() {
    vec2 dist;
    dist.x = Texcoord.x * 1.0;
    dist.y = Texcoord.y * 1.0;
    vec4 col1 = texture(tex1, dist);
    vec4 col2 = texture(tex2, dist);
    outColor = vec4(Color, 1.0) * mix(col1, col2, sin(time));
}
)glsl";

GLuint MakeShader(const char* source, GLenum type) {
    // Create shader.
    GLuint shader = glCreateShader(type);

    // Load vertex shader sources.
    glShaderSource(shader, 1, &source, NULL /* use null terminated strings */);

    // Compile shader.
    glCompileShader(shader);

    return shader;
}

GLuint MakeVertexShader(const char* source) {
    return MakeShader(source, GL_VERTEX_SHADER);
}

GLuint MakeFragmentShader(const char* source) {
    return MakeShader(source, GL_FRAGMENT_SHADER);
}

// Check shader compilation went ok.
bool IsShaderCompilationOk(GLuint shader) {
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    return status == GL_TRUE;
}

// Make, Activate & Load Texture object.
GLuint MakeAndLoadTex(const char* path, GLenum n, const char* name) {
    // Create texture object.
    GLuint tex;
    glGenTextures(1, &tex);

    // Make it active.
    glActiveTexture(n);
    glBindTexture(GL_TEXTURE_2D, tex);

    sf::Image img;
    assert(img.loadFromFile(path));
    auto size = img.getSize();
    auto pixels = img.getPixelsPtr();

    if (pixels) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, pixels);
    }

    return tex;
}

void SetupTexture(GLuint tex) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    // // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // float color[] = {0.0f, 0.0f, 0.0f, 1.0f};
    // glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
}

// Make, Activate & Load Vertex Buffer Object.
GLuint MakeAndLoadVBO(float* vertices, std::size_t size) {
    // Create vertex buffer object.
    GLuint vbo;
    glGenBuffers(1, &vbo);

    // Make it active.
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    // Copy data to active vertex buffer object.
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size, vertices,
                 GL_STATIC_DRAW);

    return vbo;
}

// Make, Activate & Load Elements Buffer Object.
GLuint MakeAndLoadEBO(GLuint* elements, std::size_t size) {
    // Create elemebt buffer object.
    GLuint ebo;
    glGenBuffers(1, &ebo);

    // Make it active.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    // Copy data to active elements buffer object.
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * size, elements,
                 GL_STATIC_DRAW);

    return ebo;
}

void PrintShaderCompilationLog(GLuint shader) {
    // Get compilation log.
    char buffer[512];
    glGetShaderInfoLog(shader, 512, NULL, buffer);
    std::cout << buffer << '\n';
}

int main(int argc, char *argv[]) {
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 2;
    settings.majorVersion = 3;
    settings.minorVersion = 2;
    settings.attributeFlags = sf::ContextSettings::Core;

    sf::Window win(sf::VideoMode(900, 900, 32), "OpenGL", sf::Style::Close, settings);

    // Enusre we are using modern OpenGL.
    glewExperimental = GL_TRUE;
    glewInit();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    // Make vertex array object (which stores all links between attributes &
    // vbo's).
    GLuint vao;
    glGenVertexArrays(1, &vao);

    // Bind it to current vbo.
    glBindVertexArray(vao);

    GLfloat vertices[] = {
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

    -1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
     1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
     1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
     1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    -1.0f,  1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
};
    GLuint vbo = MakeAndLoadVBO(vertices, sizeof(vertices));

    GLuint elements[] = { 0, 1, 2, 2, 3, 0 };
    GLuint ebo = MakeAndLoadEBO(elements, sizeof(elements));

    GLuint vertexShader = MakeVertexShader(gVertexSource);
    if (!IsShaderCompilationOk(vertexShader)) {
        PrintShaderCompilationLog(vertexShader);
        return 1;
    }

    GLuint fragmentShader = MakeFragmentShader(gFragmentSource);
    if (!IsShaderCompilationOk(fragmentShader)) {
        PrintShaderCompilationLog(fragmentShader);
        return 1;
    }

    // Make shader program.
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glBindFragDataLocation(shaderProgram, 0, "outColor");

    // Link shader program.
    glLinkProgram(shaderProgram);

    // Use it.
    glUseProgram(shaderProgram);

    GLuint tex1 = MakeAndLoadTex("img.png", GL_TEXTURE0, "tex1");
    glUniform1i(glGetUniformLocation(shaderProgram, "tex1"), 0);
    SetupTexture(tex1);

    GLuint tex2 = MakeAndLoadTex("img2.png", GL_TEXTURE1, "tex2");
    glUniform1i(glGetUniformLocation(shaderProgram, "tex2"), 1);
    SetupTexture(tex2);

    // Specify how to read vertex data.
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 3 /* x, y */, GL_FLOAT,
                          GL_FALSE /* don't normalize */,
                          8 * sizeof(float) /* stride */, 0 /* offset */);

    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(
        colAttrib, 3 /* r, g, b */, GL_FLOAT, GL_FALSE /* don't normalize */,
        8 * sizeof(float) /* stride */, (void*)(3 * sizeof(float)) /* offset */);

    GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
    glEnableVertexAttribArray(texAttrib);
    glVertexAttribPointer(texAttrib, 2 /* x, y */, GL_FLOAT,
                          GL_FALSE /* don't normalize */,
                          8 * sizeof(float) /* stride */,
                          (void*)(6 * sizeof(float)) /* offset */);

    GLint timeAttrib = glGetUniformLocation(shaderProgram, "time");

    // Rotation.
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    GLint uniModel = glGetUniformLocation(shaderProgram, "model");
    glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

    glm::mat4 view =
        glm::lookAt(glm::vec3(1.2f, 1.2f, 1.2f),  // Camera position.
                    glm::vec3(0.0f, 0.0f, 0.0f),  // Center point on screen.
                    glm::vec3(0.0f, 0.0f, 1.0f)   // Up axis = Z
        );
    GLint uniView = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));

    auto fov = glm::radians(30.0f);
    auto aspectRatio = 1.0f;
    // Clipping planes.
    auto near = 1.0f;
    auto far = 10.f;
    glm::mat4 proj =
        glm::perspective(fov, aspectRatio, near, far);
    GLint uniProj = glGetUniformLocation(shaderProgram, "proj");
    glUniformMatrix4fv(uniProj, 1, GL_FALSE, glm::value_ptr(proj));

    auto timeStart = std::chrono::high_resolution_clock::now();

    bool running = true;
    while (running) {
        sf::Event e;
        while (win.pollEvent(e)) {
            switch (e.type) {
                case sf::Event::EventType::Closed:
                    running = false;
                    break;
                case sf::Event::KeyPressed:
                    if (e.key.code == sf::Keyboard::Escape) {
                        running = false;
                    }
            }
        }

        auto timeNow = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration_cast<std::chrono::duration<float>>(timeNow - timeStart).count();
        // time = std::sin(time);
        model = glm::rotate(model, std::sin(time) * glm::radians(0.3f), glm::vec3(0.0f, 0.0f, 1.0f));

        {
            glm::mat4 view = glm::lookAt(
                glm::vec3(5.0f * std::sin(time), std::cos(time) * 5.0f, (std::abs(std::sin(time) * 5.0f + 1.0f))),  // Camera position.
                glm::vec3(0.0f, 0.0f, 0.0f),  // Center point on screen.
                glm::vec3(0.0f, 0.0f, 1.0f)   // Up axis = Z
            );
            GLint uniView = glGetUniformLocation(shaderProgram, "view");
            glUniformMatrix4fv(uniView, 1, GL_FALSE, glm::value_ptr(view));
        }

        glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1f(timeAttrib, time);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        const GLfloat bcolor[] = {
            std::sin(time) * 0.5f  + 0.5f,
            std::cos(time) * 0.5f  + 0.5f,
            0.0f, 1.0f,
        };
        glClearBufferfv(GL_COLOR, 0, bcolor);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // glEnable(GL_STENCIL_TEST);
        // // floor
        // glStencilFunc(GL_ALWAYS, 1, 0xFF);
        // glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
        // glStencilMask(0xFF);
        // glDepthMask(GL_FALSE);
        // glClear(GL_STENCIL_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 36, 6);

        // // // reflection
        // model = glm::scale(glm::translate(model, glm::vec3(0, 0, -1)),
        //                    glm::vec3(1, 1, -1));
        // glUniformMatrix4fv(uniModel, 1, GL_FALSE, glm::value_ptr(model));

        // glStencilFunc(GL_EQUAL, 1, 0xFF);
        // glStencilMask(0x00);
        // glDepthMask(GL_TRUE);

        // glDrawArrays(GL_TRIANGLES, 0, 36);

        // glDisable(GL_STENCIL_TEST);
        win.display();
    }
}
