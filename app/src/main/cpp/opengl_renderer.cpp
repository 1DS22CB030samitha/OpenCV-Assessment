#include "opengl_renderer.h"
#include <android/log.h>
#include <string>

#define LOG_TAG "OpenGLRenderer"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static const char* vertexShaderSource = R"(
attribute vec4 aPosition;
attribute vec2 aTexCoord;
varying vec2 vTexCoord;
uniform mat4 uMVPMatrix;
void main() {
    gl_Position = uMVPMatrix * aPosition;
    vTexCoord = aTexCoord;
}
)";

static const char* fragmentShaderSource = R"(
precision mediump float;
varying vec2 vTexCoord;
uniform sampler2D uTexture;
void main() {
    gl_FragColor = texture2D(uTexture, vTexCoord);
}
)";

static const float vertices[] = {
    -1.0f, -1.0f, 0.0f,
     1.0f, -1.0f, 0.0f,
    -1.0f,  1.0f, 0.0f,
     1.0f,  1.0f, 0.0f
};

static const float textureCoords[] = {
    0.0f, 1.0f,
    1.0f, 1.0f,
    0.0f, 0.0f,
    1.0f, 0.0f
};

OpenGLRenderer::OpenGLRenderer() 
    : viewWidth(0), viewHeight(0), shaderProgram(0), 
      vertexShader(0), fragmentShader(0) {
    initShaders();
}

OpenGLRenderer::~OpenGLRenderer() {
    cleanup();
}

void OpenGLRenderer::initShaders() {
    vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderSource);
    fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    
    if (vertexShader == 0 || fragmentShader == 0) {
        LOGE("Failed to load shaders");
        return;
    }
    
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    GLint linkStatus;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);
    if (linkStatus == 0) {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        LOGE("Shader program linking failed: %s", infoLog);
        return;
    }
    
    positionHandle = glGetAttribLocation(shaderProgram, "aPosition");
    textureCoordHandle = glGetAttribLocation(shaderProgram, "aTexCoord");
    textureHandle = glGetUniformLocation(shaderProgram, "uTexture");
    mvpMatrixHandle = glGetUniformLocation(shaderProgram, "uMVPMatrix");
    
    LOGI("Shaders initialized successfully");
}

GLuint OpenGLRenderer::loadShader(GLenum type, const char* source) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    
    GLint compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled == 0) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        LOGE("Shader compilation failed: %s", infoLog);
        glDeleteShader(shader);
        return 0;
    }
    
    return shader;
}

void OpenGLRenderer::resize(int width, int height) {
    viewWidth = width;
    viewHeight = height;
    glViewport(0, 0, width, height);
}

void OpenGLRenderer::render(GLuint texture) {
    if (shaderProgram == 0) {
        return;
    }
    
    glUseProgram(shaderProgram);
    
    // Set up identity matrix
    float mvpMatrix[16] = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
    
    glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, mvpMatrix);
    
    // Enable vertex attributes
    glEnableVertexAttribArray(positionHandle);
    glVertexAttribPointer(positionHandle, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    
    glEnableVertexAttribArray(textureCoordHandle);
    glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, textureCoords);
    
    // Bind texture
    if (texture != 0) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(textureHandle, 0);
    }
    
    // Draw
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    // Cleanup
    glDisableVertexAttribArray(positionHandle);
    glDisableVertexAttribArray(textureCoordHandle);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void OpenGLRenderer::cleanup() {
    if (shaderProgram != 0) {
        glDeleteProgram(shaderProgram);
        shaderProgram = 0;
    }
    if (vertexShader != 0) {
        glDeleteShader(vertexShader);
        vertexShader = 0;
    }
    if (fragmentShader != 0) {
        glDeleteShader(fragmentShader);
        fragmentShader = 0;
    }
}

