#ifndef FLOAT32x4_H
#define FLOAT32x4_H

#include <nan.h>
#include <mmintrin.h>

class Float32x4 : public Nan::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit Float32x4();
  explicit Float32x4(float x, float y = 0.f, float z = 0.f,float w = 0.f);

  ~Float32x4();

  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);

  static void Add(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void Abs(const Nan::FunctionCallbackInfo<v8::Value>& info);

  static Nan::Persistent<v8::Function> constructor;
  __m128 vec;
};

#endif
