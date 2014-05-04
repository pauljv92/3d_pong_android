#!/bin/bash

ndk-build -C jni &&
ant debug &&
adb install -d -r bin/honorsgame-debug.apk
