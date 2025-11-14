#ifndef EDGE_DETECTION_EDGE_PROCESSOR_H
#define EDGE_DETECTION_EDGE_PROCESSOR_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <GLES2/gl2.h>

class EdgeProcessor {
public:
    EdgeProcessor();
    ~EdgeProcessor();
    
    void processFrame(GLuint inputTexture, int width, int height);
    GLuint getOutputTexture() const { return outputTexture; }
    
private:
    void initializeTextures(int width, int height);
    void cleanupTextures();
    
    GLuint inputTexture;
    GLuint outputTexture;
    GLuint framebuffer;
    
    int currentWidth;
    int currentHeight;
    
    cv::Mat processWithOpenCV(const cv::Mat& input);
};

#endif //EDGE_DETECTION_EDGE_PROCESSOR_H

