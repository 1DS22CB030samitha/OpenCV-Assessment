#!/bin/bash

echo "Building Edge Detection Viewer APK..."
echo ""

# Set Android SDK path if not set
if [ -z "$ANDROID_HOME" ]; then
    export ANDROID_HOME=~/Android/sdk
    echo "Setting ANDROID_HOME to $ANDROID_HOME"
fi

# Set Java home if not set
if [ -z "$JAVA_HOME" ]; then
    echo "Warning: JAVA_HOME not set. Please set it to your JDK installation."
    echo "Example: export JAVA_HOME=/usr/lib/jvm/java-17-openjdk"
    exit 1
fi

echo ""
echo "Building debug APK..."
./gradlew assembleDebug

if [ $? -eq 0 ]; then
    echo ""
    echo "========================================"
    echo "Build successful!"
    echo "APK location: app/build/outputs/apk/debug/app-debug.apk"
    echo "========================================"
    echo ""
    echo "To install on device:"
    echo "  adb install app/build/outputs/apk/debug/app-debug.apk"
    echo ""
else
    echo ""
    echo "========================================"
    echo "Build failed! Check errors above."
    echo "========================================"
    echo ""
    exit 1
fi

