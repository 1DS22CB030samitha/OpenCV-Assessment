/**
 * Edge Detection Viewer - TypeScript Module
 * Displays processed frames from Android app
 */

export interface FrameStats {
    fps: number;
    resolution: string;
    timestamp: number;
}

export class EdgeDetectionViewer {
    private canvas: HTMLCanvasElement;
    private ctx: CanvasRenderingContext2D | null;
    private statsElement: HTMLElement | null;
    private currentStats: FrameStats = {
        fps: 0,
        resolution: '0x0',
        timestamp: Date.now()
    };

    constructor(canvasId: string, statsId?: string) {
        const canvas = document.getElementById(canvasId) as HTMLCanvasElement;
        if (!canvas) {
            throw new Error(`Canvas element with id '${canvasId}' not found`);
        }
        
        this.canvas = canvas;
        this.ctx = canvas.getContext('2d');
        
        if (statsId) {
            this.statsElement = document.getElementById(statsId);
        }
    }

    /**
     * Display a processed frame from base64 image data
     */
    displayFrame(base64Data: string, stats?: Partial<FrameStats>): void {
        if (!this.ctx) {
            console.error('Canvas context not available');
            return;
        }

        const img = new Image();
        img.onload = () => {
            // Update canvas size to match image
            this.canvas.width = img.width;
            this.canvas.height = img.height;
            
            // Draw image
            this.ctx!.drawImage(img, 0, 0);
            
            // Update stats
            if (stats) {
                this.updateStats({
                    ...this.currentStats,
                    ...stats,
                    timestamp: Date.now()
                });
            }
        };
        
        img.onerror = (error) => {
            console.error('Failed to load image:', error);
        };
        
        img.src = base64Data;
    }

    /**
     * Display a frame from ImageData
     */
    displayImageData(imageData: ImageData): void {
        if (!this.ctx) {
            console.error('Canvas context not available');
            return;
        }

        this.canvas.width = imageData.width;
        this.canvas.height = imageData.height;
        this.ctx.putImageData(imageData, 0, 0);
    }

    /**
     * Update frame statistics display
     */
    private updateStats(stats: FrameStats): void {
        this.currentStats = stats;
        
        // Update individual stat values
        const fpsElement = document.getElementById('fpsValue');
        const resolutionElement = document.getElementById('resolutionValue');
        const timestampElement = document.getElementById('timestampValue');
        
        if (fpsElement) {
            fpsElement.textContent = stats.fps.toFixed(1);
        }
        if (resolutionElement) {
            resolutionElement.textContent = stats.resolution;
        }
        if (timestampElement) {
            timestampElement.textContent = new Date(stats.timestamp).toLocaleTimeString();
        }
    }

    /**
     * Get current frame statistics
     */
    getStats(): FrameStats {
        return { ...this.currentStats };
    }

    /**
     * Clear the canvas
     */
    clear(): void {
        if (this.ctx) {
            this.ctx.clearRect(0, 0, this.canvas.width, this.canvas.height);
        }
    }

    /**
     * Get canvas element
     */
    getCanvas(): HTMLCanvasElement {
        return this.canvas;
    }
}

/**
 * Utility function to convert ArrayBuffer to base64
 */
export function arrayBufferToBase64(buffer: ArrayBuffer): string {
    const bytes = new Uint8Array(buffer);
    let binary = '';
    for (let i = 0; i < bytes.byteLength; i++) {
        binary += String.fromCharCode(bytes[i]);
    }
    return btoa(binary);
}

/**
 * Utility function to load a sample frame (for demo purposes)
 */
export async function loadSampleFrame(url: string): Promise<string> {
    try {
        const response = await fetch(url);
        const blob = await response.blob();
        return new Promise((resolve, reject) => {
            const reader = new FileReader();
            reader.onloadend = () => {
                if (typeof reader.result === 'string') {
                    resolve(reader.result);
                } else {
                    reject(new Error('Failed to read blob as data URL'));
                }
            };
            reader.onerror = reject;
            reader.readAsDataURL(blob);
        });
    } catch (error) {
        console.error('Failed to load sample frame:', error);
        throw error;
    }
}

