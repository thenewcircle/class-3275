#include <jni.h>

namespace com_intel_fib {

// Plain C code
long fib(long n) {
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	return fib(n - 1) + fib(n - 2);
}

// JNI Wrapper
jlong fibN(JNIEnv *env, jclass clazz, jlong n) {
	return (jlong) fib((long) n);
}

static JNINativeMethod method_table[] {
		{ "fibN", "(J)J", (void *) fibN }
};

}

using namespace com_intel_fib;

extern "C" jint JNI_OnLoad(JavaVM* vm, void* reserved) {
	JNIEnv* env;
	if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
		return JNI_ERR;
	} else {
		jclass clazz = env->FindClass(
				"com/intel/fib/FibLib");
		if (clazz) {
			jint ret = env->RegisterNatives(clazz, method_table,
					sizeof(method_table) / sizeof(method_table[0]));
			env->DeleteLocalRef(clazz);
			return ret == 0 ? JNI_VERSION_1_6 : JNI_ERR;
		} else {
			return JNI_ERR;
		}
	}
}


