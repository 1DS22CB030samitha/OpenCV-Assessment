#include "edge_processor.h"
#include <android/log.h>

#define LOG_TAG "EdgeProcessor"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

EdgeProcessor::EdgeProcessor() 
    : inputTexture(0), outputTexture(0), framebuffer(0), currentWidth(0), currentHeight(0) {
    LOGI("EdgeProcessor created");
}

EdgeProcessor::~EdgeProcessor() {
    cleanupTextures();
    LOGI("EdgeProcessor destroyed");
}

void EdgeProcessor::initializeTextures(int width, int height) {
    if (currentWidth == width && currentHeight == height) {
        return; // Already initialized
    }
    
    cleanupTextures();
    
    currentWidth = width;
    currentHeight = height;
    
    // Create framebuffer
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    
    // Create output texture
    glGenTextures(1, &outputTexture);
    glBindTexture(GL_TEXTURE_2D, outputTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, outputTexture, 0);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LOGE("Framebuffer not complete!");
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    LOGI("Textures initialized: %d x %d", width, height);
}

void EdgeProcessor::cleanupTextures() {
    if (outputTexture != 0) {
        glDeleteTextures(1, &outputTexture);
        outputTexture = 0;
    }
    if (framebuffer != 0) {
        glDeleteFramebuffers(1, &framebuffer);
        framebuffer = 0;
    }
    currentWidth = 0;
    currentHeight = 0;
}

void EdgeProcessor::processFrame(GLuint inputTexture, int width, int height) {
    if (width <= 0 || height <= 0) {
        LOGE("Invalid dimensions: %d x %d", width, height);
        return;
    }
    
    initializeTextures(width, height);
    
    // Read pixels from input texture
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glViewport(0, 0, width, height);
    
    // Read texture data
    cv::Mat inputMat(height, width, CV_8UC4);
    glBindTexture(GL_TEXTURE_2D, inputTexture);
    glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, inputMat.data);
    
    // Process with OpenCV
    cv::Mat processed = processWithOpenCV(inputMat);
    
    // Write processed data back to output texture
    glBindTexture(GL_TEXTURE_2D, outputTexture);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, processed.data);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

cv::Mat EdgeProcessor::processWithOpenCV(const cv::Mat& input) {
    if (input.empty()) {
        LOGE("Input Mat is empty");
        return input;
    }
    
    cv::Mat gray, edges;
    
    // Convert RGBA to Grayscale
    cv::cvtColor(input, gray, cv::COLOR_RGBA2GRAY);
    
    // Apply Canny Edge Detection
    cv::Canny(gray, edges, 50, 150);
    
    // Convert back to RGBA for display
    cv::Mat output;
    cv::cvtColor(edges, output, cv::COLOR_GRAY2RGBA);
    
    return output;
}

