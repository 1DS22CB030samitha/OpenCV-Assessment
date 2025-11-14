#ifndef EDGE_DETECTION_OPENGL_RENDERER_H
#define EDGE_DETECTION_OPENGL_RENDERER_H

#include <GLES2/gl2.h>

class OpenGLRenderer {
public:
    OpenGLRenderer();
    ~OpenGLRenderer();
    
    void resize(int width, int height);
    void render(GLuint texture = 0);
    
private:
    int viewWidth;
    int viewHeight;
    
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;
    
    GLint positionHandle;
    GLint textureCoordHandle;
    GLint textureHandle;
    GLint mvpMatrixHandle;
    
    void initShaders();
    GLuint loadShader(GLenum type, const char* source);
    void cleanup();
};

#endif //EDGE_DETECTION_OPENGL_RENDERER_H

