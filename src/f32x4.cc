#include "f32x4.h"

Nan::Persistent<v8::Function> Float32x4::constructor;

Float32x4::Float32x4(float x, float y, float z,float w) {
	vec = _mm_set_ps( w, z, y , x );
}

Float32x4::Float32x4() {
}


Float32x4::~Float32x4() {
}

void Float32x4::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Float32x4").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  v8::Local<v8::Function> cst = tpl->GetFunction();
  constructor.Reset(cst);
  exports->Set(Nan::New("Float32x4").ToLocalChecked(), cst);
  cst->Set(Nan::New("add").ToLocalChecked(),Nan::New<v8::FunctionTemplate>(Add)->GetFunction());
  cst->Set(Nan::New("abs").ToLocalChecked(),Nan::New<v8::FunctionTemplate>(Abs)->GetFunction());
}

void Float32x4::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new Float32x4(...)`

    Float32x4* obj;
    if(info.Length()==0) {
     	obj = new Float32x4();
    } else {
    	double r0 = (info.Length() >= 1 && info[0]->IsNumber())? info[0]->NumberValue() : 0;
    	double r1 = (info.Length() >= 2 && info[1]->IsNumber())? info[1]->NumberValue() : 0;
    	double r2 = (info.Length() >= 3 && info[2]->IsNumber())? info[2]->NumberValue() : 0;
    	double r3 = (info.Length() == 4 && info[3]->IsNumber())? info[3]->NumberValue() : 0;
    	obj = new Float32x4(r0,r1,r2,r3);
    }

    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `Float32x4(...)`, turn into construct call.
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = { info[0] };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

void Float32x4::Add(const Nan::FunctionCallbackInfo<v8::Value>& info) {

	if (info.Length() < 2) {
		Nan::ThrowTypeError("Wrong number of arguments");
		return;
	}
    Float32x4* a = ObjectWrap::Unwrap<Float32x4>(info[0]->ToObject());
    Float32x4* b = ObjectWrap::Unwrap<Float32x4>(info[1]->ToObject());
    const int argc = 0;
    v8::Local<v8::Value> argv[argc] = { };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    v8::Local<v8::Object> res = cons->NewInstance(argc, argv);
	Float32x4* r = ObjectWrap::Unwrap<Float32x4>(res);
	r->vec = _mm_add_ps(a->vec,b->vec);
	info.GetReturnValue().Set(res);
}

void Float32x4::Abs(const Nan::FunctionCallbackInfo<v8::Value>& info) {

	if (info.Length() < 1) {
		Nan::ThrowTypeError("Wrong number of arguments");
		return;
	}
    Float32x4* a = ObjectWrap::Unwrap<Float32x4>(info[0]->ToObject());
    const int argc = 0;
    v8::Local<v8::Value> argv[argc] = { };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    v8::Local<v8::Object> res = cons->NewInstance(argc, argv);
	Float32x4* r = ObjectWrap::Unwrap<Float32x4>(res);
	r->vec = _mm_max_ps(_mm_sub_ps(_mm_setzero_ps(), a->vec), a->vec);
	info.GetReturnValue().Set(res);
}
