/**
 * Main entry point for Edge Detection Viewer web application
 */

import { EdgeDetectionViewer, loadSampleFrame } from './viewer';

// Initialize viewer when DOM is ready
document.addEventListener('DOMContentLoaded', () => {
    const viewer = new EdgeDetectionViewer('frameCanvas', 'statsContainer');
    
    // Load sample frame if available
    const sampleFrameButton = document.getElementById('loadSampleBtn');
    if (sampleFrameButton) {
        sampleFrameButton.addEventListener('click', async () => {
            try {
                // Try to load a sample frame (placeholder - in real app, this would come from Android)
                const sampleData = 'data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAEAAAABCAYAAAAfFcSJAAAADUlEQVR42mNk+M9QDwADhgGAWjR9awAAAABJRU5ErkJggg==';
                viewer.displayFrame(sampleData, {
                    fps: 15.0,
                    resolution: '640x480'
                });
            } catch (error) {
                console.error('Failed to load sample frame:', error);
                alert('Failed to load sample frame. Please ensure you have a processed frame from the Android app.');
            }
        });
    }
    
    // Clear canvas
    const clearButton = document.getElementById('clearBtn');
    if (clearButton) {
        clearButton.addEventListener('click', () => {
            viewer.clear();
            // Reset stats
            const fpsElement = document.getElementById('fpsValue');
            const resolutionElement = document.getElementById('resolutionValue');
            const timestampElement = document.getElementById('timestampValue');
            if (fpsElement) fpsElement.textContent = '0.0';
            if (resolutionElement) resolutionElement.textContent = '0x0';
            if (timestampElement) timestampElement.textContent = '--';
        });
    }
    
    // Simulate frame updates (for demo purposes)
    let frameCounter = 0;
    setInterval(() => {
        frameCounter++;
        const stats = viewer.getStats();
        if (stats.fps > 0) {
            // Update FPS display periodically
            console.log(`Frame ${frameCounter} - FPS: ${stats.fps}, Resolution: ${stats.resolution}`);
        }
    }, 1000);
    
    console.log('Edge Detection Viewer initialized');
});

// Export for potential module usage
export { EdgeDetectionViewer, loadSampleFrame };

