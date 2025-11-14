@echo off
echo Building Edge Detection Viewer APK...
echo.

REM Set Android SDK path (update this to your SDK location)
if "%ANDROID_HOME%"=="" (
    set ANDROID_HOME=C:\Android\sdk
    echo Setting ANDROID_HOME to %ANDROID_HOME%
)

REM Set Java home if not set
if "%JAVA_HOME%"=="" (
    echo Warning: JAVA_HOME not set. Please set it to your JDK installation.
    echo Example: set JAVA_HOME=C:\Program Files\Java\jdk-17
    pause
    exit /b 1
)

echo.
echo Building debug APK...
call gradlew.bat assembleDebug

if %ERRORLEVEL% EQU 0 (
    echo.
    echo ========================================
    echo Build successful!
    echo APK location: app\build\outputs\apk\debug\app-debug.apk
    echo ========================================
    echo.
    echo To install on device:
    echo   adb install app\build\outputs\apk\debug\app-debug.apk
    echo.
) else (
    echo.
    echo ========================================
    echo Build failed! Check errors above.
    echo ========================================
    echo.
)

pause

