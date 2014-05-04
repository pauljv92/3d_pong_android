#!/bin/bash

ndk-build -C jni &&
ant debug &&
adb install -d bin/honorsgame-debug.apk
