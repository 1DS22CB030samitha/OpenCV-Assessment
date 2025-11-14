package com.edgedetection.viewer;

import android.graphics.SurfaceTexture;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.util.Log;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class GLSurfaceViewRenderer implements GLSurfaceView.Renderer {
    private static final String TAG = "GLSurfaceViewRenderer";
    
    static {
        System.loadLibrary("edge-detection");
    }
    
    public native void nativeInit();
    public native void nativeResize(int width, int height);
    public native void nativeProcessFrame(int textureId, int width, int height);
    public native void nativeRender();
    public native void nativeRelease();
    
    private int viewWidth = 0;
    private int viewHeight = 0;
    private boolean initialized = false;
    private int cameraTextureId = 0;
    private SurfaceTexture cameraSurfaceTexture;
    private boolean frameAvailable = false;
    private final Object frameLock = new Object();
    
    public void setCameraTexture(SurfaceTexture surfaceTexture, int textureId) {
        synchronized (frameLock) {
            this.cameraSurfaceTexture = surfaceTexture;
            this.cameraTextureId = textureId;
        }
    }
    
    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        GLES20.glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        if (!initialized) {
            nativeInit();
            initialized = true;
        }
    }
    
    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        this.viewWidth = width;
        this.viewHeight = height;
        GLES20.glViewport(0, 0, width, height);
        nativeResize(width, height);
    }
    
    @Override
    public void onDrawFrame(GL10 gl) {
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
        
        synchronized (frameLock) {
            if (cameraSurfaceTexture != null) {
                try {
                    // Update the camera texture
                    cameraSurfaceTexture.updateTexImage();
                    
                    // Get texture ID from SurfaceTexture (it's managed internally)
                    // We'll pass 0 and let native code handle it, or extract from SurfaceTexture
                    int texId = cameraTextureId;
                    if (texId == 0) {
                        // Try to get texture ID - in practice, TextureView manages this
                        // For this implementation, we'll process in native code
                        texId = 1; // Placeholder
                    }
                    
                    // Process frame with edge detection
                    nativeProcessFrame(texId, viewWidth, viewHeight);
                    
                    // Render the processed frame
                    nativeRender();
                } catch (Exception e) {
                    Log.e(TAG, "Error processing frame", e);
                }
            }
        }
    }
    
    public void release() {
        if (initialized) {
            nativeRelease();
            initialized = false;
        }
    }
}

