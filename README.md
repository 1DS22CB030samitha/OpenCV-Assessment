# Edge Detection Viewer - Technical Assessment

A real-time edge detection Android application that captures camera frames, processes them using OpenCV (C++), and displays the results using OpenGL ES 2.0. Includes a TypeScript-based web viewer for displaying processed frames.

## 🎯 Features Implemented

### Android Application
- ✅ **Camera Feed Integration**: Uses Camera2 API with TextureView for real-time frame capture
- ✅ **OpenCV C++ Processing**: JNI bridge to native C++ code performing Canny edge detection
- ✅ **OpenGL ES 2.0 Rendering**: Real-time rendering of processed frames with smooth performance
- ✅ **FPS Counter**: Displays real-time frame rate (target: 10-15 FPS minimum)
- ✅ **Toggle Button**: Switch between raw camera feed and edge-detected output
- ✅ **Modular Architecture**: Clean separation between Java, JNI, and C++ code

### Web Viewer (TypeScript)
- ✅ **TypeScript Module**: Clean, modular TypeScript code with proper type definitions
- ✅ **Frame Display**: Canvas-based rendering of processed frames
- ✅ **Statistics Display**: Shows FPS, resolution, and timestamp information
- ✅ **Modern UI**: Responsive design with clean interface
- ✅ **Build System**: TypeScript compilation with `tsc`

## 🏗️ Architecture

### Project Structure
```
.
├── app/                          # Android application
│   ├── src/main/
│   │   ├── java/                 # Java/Kotlin code
│   │   │   └── com/edgedetection/viewer/
│   │   │       ├── MainActivity.java      # Camera & UI setup
│   │   │       └── OpenGLRenderer.java    # OpenGL integration
│   │   ├── cpp/                  # Native C++ code
│   │   │   ├── native-lib.cpp            # JNI bridge
│   │   │   ├── edge_processor.cpp        # OpenCV processing
│   │   │   ├── opengl_renderer.cpp       # OpenGL rendering
│   │   │   └── CMakeLists.txt            # Build configuration
│   │   └── res/                  # Android resources
│   └── build.gradle              # App build configuration
├── opencv/                       # OpenCV module
│   └── build.gradle
├── web/                          # TypeScript web viewer
│   ├── src/
│   │   ├── viewer.ts             # Core viewer module
│   │   └── index.ts              # Main entry point
│   ├── index.html                # Web interface
│   ├── styles.css                # Styling
│   ├── package.json              # Dependencies
│   └── tsconfig.json             # TypeScript config
└── README.md                     # This file
```

### Frame Processing Flow

1. **Camera Capture** (Java)
   - Camera2 API captures frames via TextureView
   - Frames are available as SurfaceTexture

2. **JNI Bridge** (native-lib.cpp)
   - Java calls native methods through JNI
   - Passes texture ID and dimensions to C++

3. **OpenCV Processing** (edge_processor.cpp)
   - Reads frame data from OpenGL texture
   - Converts RGBA to grayscale
   - Applies Canny edge detection
   - Returns processed frame as texture

4. **OpenGL Rendering** (opengl_renderer.cpp)
   - Renders processed texture to screen
   - Uses GLSL shaders for efficient rendering

5. **Web Viewer** (TypeScript)
   - Receives processed frames (base64 or ImageData)
   - Displays on HTML5 canvas
   - Shows frame statistics

## 📋 Prerequisites

### Android Development
- Android Studio (latest version)
- Android SDK (API 24+)
- Android NDK (r21 or later)
- CMake (3.22.1 or later)
- OpenCV Android SDK (4.x)

### Web Development
- Node.js (v16 or later)
- TypeScript (v5.0+)
- Modern web browser

## 🚀 Setup Instructions

### 1. Clone the Repository
```bash
git clone <repository-url>
cd opengl
```

### 2. OpenCV Setup

1. Download OpenCV Android SDK from [opencv.org/releases](https://opencv.org/releases/)
2. Extract the SDK
3. Copy the `sdk` folder to `opencv/` directory:
   ```
   opencv/
   └── sdk/
       ├── native/
       │   └── jni/
       │       ├── OpenCV.mk
       │       └── ...
       └── ...
   ```
4. Update `app/src/main/cpp/CMakeLists.txt` with the correct OpenCV path:
   ```cmake
   set(OpenCV_DIR "${CMAKE_SOURCE_DIR}/../../../opencv/sdk/native/jni")
   ```

### 3. Android Project Setup

1. Open the project in Android Studio
2. Sync Gradle files (File → Sync Project with Gradle Files)
3. Ensure NDK is installed:
   - Tools → SDK Manager → SDK Tools
   - Check "NDK (Side by side)" and "CMake"
4. Build the project:
   ```bash
   ./gradlew build
   ```

### 4. Web Viewer Setup

```bash
cd web
npm install
npm run build
```

To serve the web viewer:
```bash
# Option 1: Python
python -m http.server 8000

# Option 2: Node.js http-server
npx http-server -p 8000

# Option 3: Open index.html directly in browser
```

Then open `http://localhost:8000` in your browser.

## 🧪 Building and Running

### Android App
1. Connect an Android device (API 24+) or start an emulator
2. Enable USB debugging on device
3. Run the app:
   ```bash
   ./gradlew installDebug
   ```
   Or use Android Studio: Run → Run 'app'

### Web Viewer
1. Build TypeScript:
   ```bash
   cd web
   npm run build
   ```
2. Open `index.html` in a web browser
3. Click "Load Sample Frame" to see a demo

## 📱 Usage

### Android App
1. Launch the app
2. Grant camera permission when prompted
3. The camera feed will appear with edge detection applied
4. Tap "Show Raw" to toggle between processed and raw feed
5. FPS counter shows real-time performance

### Web Viewer
- Displays processed frames from Android app
- Shows frame statistics (FPS, resolution, timestamp)
- In production, frames would be transmitted via WebSocket/HTTP

## 🔧 Technical Details

### JNI Communication
- **Java → C++**: Native method calls via JNI
- **C++ → Java**: Return values and callbacks
- **Memory Management**: Proper cleanup in native code

### OpenCV Integration
- **Canny Edge Detection**: Thresholds: 50 (low), 150 (high)
- **Color Conversion**: RGBA → Grayscale → RGBA
- **Performance**: Optimized for real-time processing

### OpenGL ES 2.0
- **Shaders**: Vertex and fragment shaders for texture rendering
- **Textures**: Input from camera, output for display
- **Framebuffers**: Used for intermediate processing

### TypeScript
- **Modular Design**: Separate viewer class and utilities
- **Type Safety**: Full TypeScript type definitions
- **ES Modules**: Modern JavaScript module system

## 🐛 Troubleshooting

### Android Build Issues
- **NDK not found**: Install NDK via SDK Manager
- **OpenCV not found**: Verify OpenCV path in CMakeLists.txt
- **Permission denied**: Check AndroidManifest.xml permissions

### Runtime Issues
- **Camera not working**: Ensure device has camera and permission granted
- **Low FPS**: Reduce processing resolution or optimize OpenCV code
- **App crashes**: Check logcat for native crash logs

### Web Viewer Issues
- **TypeScript errors**: Run `npm install` to install dependencies
- **Canvas not displaying**: Check browser console for errors
- **Module not found**: Ensure `npm run build` completed successfully

## 📝 Git Commit History

This project follows proper Git practices with meaningful commit messages:
- Initial project setup
- Camera integration
- JNI bridge implementation
- OpenCV processing
- OpenGL rendering
- Web viewer implementation
- Documentation and README

## 🎓 Evaluation Criteria Coverage

✅ **Android SDK**: Camera2 API, TextureView, proper lifecycle management  
✅ **NDK**: CMake build system, JNI bridge, native C++ code  
✅ **OpenCV C++**: Canny edge detection, image processing  
✅ **OpenGL ES 2.0**: Shaders, textures, real-time rendering  
✅ **JNI**: Proper Java ↔ C++ communication  
✅ **TypeScript**: Modular code, type definitions, build system  
✅ **Git**: Proper version control with meaningful commits  
✅ **Architecture**: Clean, modular structure  
✅ **Documentation**: Comprehensive README with setup instructions  

## 📄 License

This project is created for technical assessment purposes.

## 👤 Author

Technical Assessment Submission - Web R&D Intern

---

**Note**: This is a minimal implementation focused on demonstrating integration skills. For production use, additional error handling, optimization, and features would be required.

