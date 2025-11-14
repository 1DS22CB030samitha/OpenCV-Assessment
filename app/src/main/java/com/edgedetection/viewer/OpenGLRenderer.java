package com.edgedetection.viewer;

import android.graphics.SurfaceTexture;
import android.util.Log;

public class OpenGLRenderer {
    private static final String TAG = "OpenGLRenderer";
    
    // Native methods
    static {
        System.loadLibrary("edge-detection");
    }
    
    public native void nativeInit();
    public native void nativeResize(int width, int height);
    public native void nativeProcessFrame(int textureId, int width, int height);
    public native void nativeRender();
    public native void nativeRelease();
    
    private boolean initialized = false;
    
    public OpenGLRenderer(android.content.Context context) {
        // Constructor - initialization happens when surface is available
    }
    
    public void onSurfaceCreated(SurfaceTexture surface) {
        if (!initialized) {
            nativeInit();
            initialized = true;
        }
    }
    
    public void onSurfaceChanged(int width, int height) {
        nativeResize(width, height);
    }
    
    public void processFrame(SurfaceTexture surface, int width, int height) {
        if (surface != null && initialized) {
            // Get texture ID from SurfaceTexture
            // Note: In a real implementation, we'd need to extract the texture ID
            // For now, we'll process when the texture is available
            int textureId = getTextureIdFromSurface(surface);
            if (textureId > 0 && width > 0 && height > 0) {
                nativeProcessFrame(textureId, width, height);
                nativeRender();
            }
        }
    }
    
    private int getTextureIdFromSurface(SurfaceTexture surface) {
        // This is a placeholder - in practice, TextureView provides the texture ID
        // For this implementation, we'll use a workaround
        try {
            // TextureView automatically manages the texture, so we process via native
            // The actual texture ID will be handled in native code
            return 1; // Placeholder - actual implementation would extract from TextureView
        } catch (Exception e) {
            Log.e(TAG, "Error getting texture ID", e);
            return 0;
        }
    }
    
    public void release() {
        if (initialized) {
            nativeRelease();
            initialized = false;
        }
    }
}

