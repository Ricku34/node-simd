#ifndef FLOAT32x4_H
#define FLOAT32x4_H

#include <nan.h>
#include <mmintrin.h>

class Float32x4 : public Nan::ObjectWrap {
	public:
		unsigned char getType() { return FLOAT32x4; }
		static const unsigned char FLOAT32x4=0x01;
		static void Init(v8::Local<v8::Object> exports);

	private:
		explicit Float32x4(float x= NAN, float y = NAN, float z = NAN,float w = NAN);

		~Float32x4();

		static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);

		static NAN_INDEX_GETTER(PropertyGetter);
		static NAN_INDEX_SETTER(PropertySetter);
		static NAN_INDEX_ENUMERATOR(PropertyEnumerator);
		static NAN_INDEX_DELETER(PropertyDeleter);
		static NAN_INDEX_QUERY(PropertyQuery);

		static Float32x4 *cast(v8::Local<v8::Object> object);

		static void Add(const Nan::FunctionCallbackInfo<v8::Value>& info);
		static void Abs(const Nan::FunctionCallbackInfo<v8::Value>& info);
		static void Check(const Nan::FunctionCallbackInfo<v8::Value>& info);
		static void Div(const Nan::FunctionCallbackInfo<v8::Value>& info);
		static void ExtractLane(const Nan::FunctionCallbackInfo<v8::Value>& info);

		static Nan::Persistent<v8::Function> constructor;
		__m128 vec;
};

#endif
