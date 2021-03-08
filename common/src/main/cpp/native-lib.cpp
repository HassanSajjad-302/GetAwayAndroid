#include <jni.h>
#include <string>
#include <iostream>
#include "resourceStrings.hpp"
#include "satiAndroid.hpp"
#include "androidMain.hpp"
#include "home.hpp"
namespace CacheIoContextThread{
    JNIEnv* envGlobal;
    jobject objGlobal;
}

namespace CacheMainThread{
    JNIEnv* envGlobal;
    jobject objGlobal;
}

asio::io_context io;
androidMain a{io};
extern "C"
JNIEXPORT void JNICALL
Java_com_example_myapplication_MainActivity_userTerminalInput(JNIEnv *env, jobject obj,
                                                              jstring user_input_string) {
    jboolean isCopy;
    const char * str = env->GetStringUTFChars(user_input_string, &isCopy);
    sati::getInstance()->operator()(str);
    env->ReleaseStringUTFChars(user_input_string, str);
}


JavaVM * g_vm;
jobject g_obj;
jmethodID g_mid;
jmethodID g_mid2;
jmethodID  g_mid3;
jmethodID g_mid4;
extern "C"
JNIEXPORT void JNICALL
Java_com_example_myapplication_MainActivity_register(JNIEnv *env, jobject obj) {
    // convert local to global reference
    // (local will die after this method call)
    g_obj = env->NewGlobalRef(obj);

    // save refs for callback
    jclass g_clazz = env->GetObjectClass(g_obj);
    if (g_clazz == nullptr) {
        std::cout << "Failed to find class" << std::endl;
    }

    g_mid = env->GetMethodID(g_clazz, "clearAndPrint", "(Ljava/lang/String;)V");
    if (g_mid == nullptr) {
        std::cout << "Unable to get method ref" << std::endl;
    }

    g_mid2 = env->GetMethodID(g_clazz, "print", "(Ljava/lang/String;)V");
    if (g_mid2 == NULL) {
        std::cout << "Unable to get method ref" << std::endl;
    }

    g_mid3 = env->GetMethodID(g_clazz, "setKeyBoard", "(Z)V");
    if(g_mid3 == NULL){
        std::cout << "Unable to get method ref" << std::endl;
    }

    g_mid4 = env->GetMethodID(g_clazz, "exitApp", "()V");
    if(g_mid4 == NULL){
        std::cout << "Unable to get method ref" << std::endl;
    }
}

void resourceStrings::clearAndPrint(const std::string &toPrint) {
    JNIEnv * g_env;
    // double check it's all ok
    int getEnvStat = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        std::cout << "GetEnv: not attached" << std::endl;
        if (g_vm->AttachCurrentThread( &g_env, nullptr) != 0) {
            std::cout << "Failed to attach" << std::endl;
        }
    } else if (getEnvStat == JNI_OK) {
        //
    } else if (getEnvStat == JNI_EVERSION) {
        std::cout << "GetEnv: version not supported" << std::endl;
    }

    g_env->CallVoidMethod(g_obj, g_mid, g_env->NewStringUTF(toPrint.c_str()));

    if (g_env->ExceptionCheck()) {
        g_env->ExceptionDescribe();
    }

    if(getEnvStat == JNI_EDETACHED){
        g_vm->DetachCurrentThread();
    }
    if (getEnvStat == JNI_EDETACHED) {
        std::cout << "GetEnv: not attached" << std::endl;
        g_vm->DetachCurrentThread();
    }
}

void resourceStrings::print(const std::string &toPrint) {
    JNIEnv * g_env;
    // double check it's all ok
    int getEnvStat = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        std::cout << "GetEnv: not attached" << std::endl;
        if (g_vm->AttachCurrentThread( &g_env, nullptr) != 0) {
            std::cout << "Failed to attach" << std::endl;
        }
    } else if (getEnvStat == JNI_OK) {
        //
    } else if (getEnvStat == JNI_EVERSION) {
        std::cout << "GetEnv: version not supported" << std::endl;
    }

    g_env->CallVoidMethod(g_obj, g_mid2, g_env->NewStringUTF(toPrint.c_str()));

    if (g_env->ExceptionCheck()) {
        g_env->ExceptionDescribe();
    }

    getEnvStat = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        std::cout << "GetEnv: not attached" << std::endl;
        g_vm->DetachCurrentThread();
    }
}

void sati::setInputType(inputType nextReceiveInputType) {
    JNIEnv * g_env;
    // double check it's all ok
    int getEnvStat = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        std::cout << "GetEnv: not attached" << std::endl;
        if (g_vm->AttachCurrentThread( &g_env, nullptr) != 0) {
            std::cout << "Failed to attach" << std::endl;
        }
    } else if (getEnvStat == JNI_OK) {
        //
    } else if (getEnvStat == JNI_EVERSION) {
        std::cout << "GetEnv: version not supported" << std::endl;
    }

    receiveInputType = nextReceiveInputType;
    handlerAssigned = true;

    jboolean numberKeyBoard;
    if(nextReceiveInputType == inputType::MESSAGESTRING ||
       nextReceiveInputType == inputType::HOMEIPADDRESS ||
       nextReceiveInputType == inputType::HOMEASSIGNSERVERNAME ||
       nextReceiveInputType == inputType::HOMESTARTSERVER ||
       nextReceiveInputType == inputType::HOMECLIENTNAMEJOININGSERVER ||
       nextReceiveInputType == inputType::HOMECLIENTNAMESTARTINGSERVER){
        numberKeyBoard = false;
        g_env->CallVoidMethod(g_obj, g_mid3, JNI_FALSE);

    }else{
        numberKeyBoard = true;
        g_env->CallVoidMethod(g_obj, g_mid3, JNI_TRUE);
    }

    if (g_env->ExceptionCheck()) {
        g_env->ExceptionDescribe();
    }

    getEnvStat = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        std::cout << "GetEnv: not attached" << std::endl;
        g_vm->DetachCurrentThread();
    }

}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_myapplication_MainActivity_startGame(JNIEnv *env, jobject obj) {
    // TODO: implement startGame()
    env->GetJavaVM(&g_vm);
    CacheIoContextThread::envGlobal = env;
    CacheIoContextThread::objGlobal = obj;
    a.run();
}

namespace Cat{
    void exitGame(){
        JNIEnv * g_env;
        // double check it's all ok
        int getEnvStat = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_6);
        if (getEnvStat == JNI_EDETACHED) {
            std::cout << "GetEnv: not attached" << std::endl;
            if (g_vm->AttachCurrentThread( &g_env, nullptr) != 0) {
                std::cout << "Failed to attach" << std::endl;
            }
        } else if (getEnvStat == JNI_OK) {
            //
        } else if (getEnvStat == JNI_EVERSION) {
            std::cout << "GetEnv: version not supported" << std::endl;
        }

        g_env->CallVoidMethod(g_obj, g_mid4);

        if (g_env->ExceptionCheck()) {
            g_env->ExceptionDescribe();
        }

        getEnvStat = g_vm->GetEnv((void **)&g_env, JNI_VERSION_1_6);
        if (getEnvStat == JNI_EDETACHED) {
            std::cout << "GetEnv: not attached" << std::endl;
            g_vm->DetachCurrentThread();
        }
    }
}

void androidMain::run() {
    thr = std::thread([s = std::ref(io)](){
        sati::getInstanceFirstTime(s.get());

        std::make_shared<home>(home(s.get()))->run();

        s.get().run();
        Cat::exitGame();
        //End Game Here Below This;
    });
}
