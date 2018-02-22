// This is the main DLL file.

#include "stdafx.h"

#include "MapIterator.h"

#include <iostream>

JNIEXPORT void JNICALL Java_MapIterator_nativeIterateMap
  (JNIEnv *env, jclass clazz, jobject map) {

	  jclass c_map = env->GetObjectClass(map);
	  jmethodID id_entrySet = env->GetMethodID(c_map, "entrySet", "()Ljava/util/Set;");
	  
	  jclass c_entryset = env->FindClass("java/util/Set");
	  jmethodID id_iterator = env->GetMethodID(c_entryset, "iterator", "()Ljava/util/Iterator;");
	  
	  jclass c_iterator = env->FindClass("java/util/Iterator");
	  jmethodID id_hasNext = env->GetMethodID(c_iterator, "hasNext", "()Z");
	  jmethodID id_next = env->GetMethodID(c_iterator, "next", "()Ljava/lang/Object;");

	  jclass c_entry = env->FindClass("java/util/Map$Entry");
	  jmethodID id_getKey = env->GetMethodID(c_entry, "getKey", "()Ljava/lang/Object;");
	  jmethodID id_getValue = env->GetMethodID(c_entry, "getValue", "()Ljava/lang/Object;");
	  
	  jclass c_string = env->FindClass("java/lang/String");
	  jmethodID id_toString = env->GetMethodID(c_string, "toString", "()Ljava/lang/String;");

	  
	  jobject obj_entrySet = env->CallObjectMethod(map, id_entrySet);

	  jobject obj_iterator = env->CallObjectMethod(obj_entrySet, id_iterator);

	  bool hasNext = (bool) env->CallBooleanMethod(obj_iterator, id_hasNext);

	  while(hasNext) {
		  jobject entry = env->CallObjectMethod(obj_iterator, id_next);

		  jobject key = env->CallObjectMethod(entry, id_getKey);
		  jobject value = env->CallObjectMethod(entry, id_getValue);

		  jstring jstrKey = (jstring) env->CallObjectMethod(key, id_toString);
		  jstring jstrValue = (jstring) env->CallObjectMethod(value, id_toString);

		  const char *strKey = env->GetStringUTFChars(jstrKey, 0);
		  const char *strValue = env->GetStringUTFChars(jstrValue, 0);

		  std::cout << strKey << " " << strValue << std::endl;

		  hasNext = (bool) env->CallBooleanMethod(obj_iterator, id_hasNext);
	  }

}