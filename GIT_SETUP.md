# Git Repository Setup

This project follows proper Git version control practices as required by the assessment.

## Initial Setup

If starting fresh, initialize the repository:

```bash
git init
git add .
git commit -m "Initial project setup: Android app structure, Gradle config, and basic files"
```

## Recommended Commit Structure

The project should be committed in logical, modular chunks:

```bash
# 1. Project structure
git add build.gradle settings.gradle .gitignore .gitattributes
git commit -m "Add Android project structure and build configuration"

# 2. Android app code
git add app/src/main/java/ app/src/main/res/
git commit -m "Implement camera capture with Camera2 API and UI components"

# 3. JNI and native code
git add app/src/main/cpp/
git commit -m "Add JNI bridge and C++ OpenCV processing (Canny edge detection)"

# 4. OpenGL rendering
git add app/src/main/java/com/edgedetection/viewer/GLSurfaceViewRenderer.java
git commit -m "Implement OpenGL ES 2.0 renderer for processed frames"

# 5. Web viewer
git add web/
git commit -m "Add TypeScript web viewer with frame display and statistics"

# 6. Documentation
git add README.md SETUP.md
git commit -m "Add comprehensive documentation and setup instructions"

# 7. OpenCV module
git add opencv/
git commit -m "Add OpenCV module configuration"
```

## Push to Remote

```bash
git remote add origin <your-repository-url>
git branch -M main
git push -u origin main
```

## Commit Message Guidelines

- Use clear, descriptive messages
- One logical change per commit
- Reference what was added/changed
- Follow conventional commit format when possible

Example good commits:
- "Add camera permission handling in MainActivity"
- "Implement Canny edge detection in edge_processor.cpp"
- "Fix OpenGL texture binding issue"
- "Update README with OpenCV setup instructions"

