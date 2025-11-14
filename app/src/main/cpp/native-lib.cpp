#include <jni.h>
#include <string>
#include <android/log.h>
#include "edge_processor.h"
#include "opengl_renderer.h"

#define LOG_TAG "EdgeDetection"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

static EdgeProcessor* edgeProcessor = nullptr;
static OpenGLRenderer* glRenderer = nullptr;

extern "C" JNIEXPORT void JNICALL
Java_com_edgedetection_viewer_OpenGLRenderer_nativeInit(JNIEnv *env, jobject thiz) {
    LOGI("Native init called");
    if (edgeProcessor == nullptr) {
        edgeProcessor = new EdgeProcessor();
    }
    if (glRenderer == nullptr) {
        glRenderer = new OpenGLRenderer();
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_edgedetection_viewer_OpenGLRenderer_nativeResize(JNIEnv *env, jobject thiz, jint width, jint height) {
    LOGI("Native resize: %d x %d", width, height);
    if (glRenderer != nullptr) {
        glRenderer->resize(width, height);
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_edgedetection_viewer_OpenGLRenderer_nativeProcessFrame(JNIEnv *env, jobject thiz, jint textureId, jint width, jint height) {
    if (edgeProcessor == nullptr || glRenderer == nullptr) {
        LOGE("Processor or renderer not initialized");
        return;
    }
    
    // Process frame with edge detection
    edgeProcessor->processFrame(textureId, width, height);
    
    // Render the processed frame
    glRenderer->render(edgeProcessor->getOutputTexture());
}

extern "C" JNIEXPORT void JNICALL
Java_com_edgedetection_viewer_OpenGLRenderer_nativeRender(JNIEnv *env, jobject thiz) {
    if (glRenderer != nullptr) {
        glRenderer->render();
    }
}

extern "C" JNIEXPORT void JNICALL
Java_com_edgedetection_viewer_OpenGLRenderer_nativeRelease(JNIEnv *env, jobject thiz) {
    LOGI("Native release called");
    if (edgeProcessor != nullptr) {
        delete edgeProcessor;
        edgeProcessor = nullptr;
    }
    if (glRenderer != nullptr) {
        delete glRenderer;
        glRenderer = nullptr;
    }
}

