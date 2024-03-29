#include <jni.h>
#include <string>
#include "AudioEngine.h"

AudioEngine *ac = nullptr;
Loggable *logger = new Loggable("SJniBridge");

extern "C" JNIEXPORT void JNICALL
Java_com_sanascope_sanahackberdemo_MainActivity_initialize(JNIEnv *env, jobject obj /* this */,
                                                           jint deviceID) {
    logger->infoLog("Initializing...");
    if (!ac) {
        ac = new AudioEngine(deviceID);
        jint percentage = 50;
        jclass clazz = env->FindClass("com/sanascope/sanahackberdemo/MainActivity");
        jmethodID addColumn = env->GetMethodID(clazz, "addColumn", "(I)V");
//        for (int i = 0; i<100; i++) {
        env->CallObjectMethod(obj, addColumn, percentage);
//        }
    }
    logger->infoLog("Initialization finished.");
}

extern "C" JNIEXPORT void JNICALL
Java_com_sanascope_sanahackberdemo_MainActivity_startRecording__(JNIEnv *env, jobject /* this */) {
    logger->infoLog("Starting Recording...");
    if (!ac) {
        logger->errorLog("No AudioEngine object!");
    }
    ac->startRecording();
    logger->infoLog("Recording started.");
}
extern "C" JNIEXPORT void JNICALL
Java_com_sanascope_sanahackberdemo_MainActivity_stopRecording(JNIEnv *env, jobject /* this */) {
    logger->infoLog("Stopping Recording...");
    if (!ac) {
        logger->errorLog("No AudioEngine object!");
    }
    ac->stopRecording();
    logger->infoLog("Recording stopped.");
}
extern "C" JNIEXPORT void JNICALL
Java_com_sanascope_sanahackberdemo_MainActivity_startListening2(JNIEnv *env, jobject /* this */) {
    logger->infoLog("Starting Recording...");
    if (!ac) {
        logger->errorLog("No AudioEngine object!");
    }
    ac->startListening();
    logger->infoLog("Recording started.");
}
extern "C" JNIEXPORT void JNICALL
Java_com_sanascope_sanahackberdemo_MainActivity_stopListening(JNIEnv *env, jobject /* this */) {
    logger->infoLog("Stopping Recording...");
    if (!ac) {
        logger->errorLog("No AudioEngine object!");
    }
    ac->stopListening();
    logger->infoLog("Recording stopped.");
}
extern "C" JNIEXPORT void JNICALL
Java_com_sanascope_sanahackberdemo_MainActivity_startPlaying(JNIEnv *env, jobject /* this */) {
    logger->infoLog("Starting replay...");
    if (!ac) {
        logger->errorLog("No AudioEngine object!");
    }
    ac->startPlaying();
    logger->infoLog("Replay started.");
}
extern "C" JNIEXPORT void JNICALL
Java_com_sanascope_sanahackberdemo_MainActivity_stopPlaying(JNIEnv *env, jobject /* this */) {
    logger->infoLog("Stopping replay...");
    if (!ac) {
        logger->errorLog("No AudioEngine object!");
    }
    ac->stopPlaying();
    logger->infoLog("Replay stopped.");
}

extern "C" JNIEXPORT void JNICALL
Java_com_sanascope_sanahackberdemo_MainActivity_setAmplification(JNIEnv *env, jobject /* this */,
                                                                 jint newValue) {
    if (!ac) {
        logger->errorLog("No AudioEngine object.");
    }
    ac->setAmplificationFactor(newValue);
    logger->infoLog("Amplification factor changed.");
}

extern "C" JNIEXPORT jboolean JNICALL
Java_com_sanascope_sanahackberdemo_MainActivity_storeRecord(JNIEnv *env, jobject /* this */,
                                                            jstring jFilepath) {
    //path
    const char *path = env->GetStringUTFChars(jFilepath, 0);
    env->ReleaseStringUTFChars(jFilepath, path);
    std::string filepath = std::string(path);
    if (!ac) {
        logger->errorLog("No AudioEngine object.");
        return jboolean(false);
    }
    return jboolean(ac->storeRecord(filepath));
}
