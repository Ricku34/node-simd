#include <nan.h>
#include "f32x4.h"


void Init(v8::Local<v8::Object> exports) {
   Float32x4::Init(exports);
}

NODE_MODULE(simd, Init)
