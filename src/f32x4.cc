#include "f32x4.h"

Nan::Persistent<v8::Function> Float32x4::constructor;

Float32x4::Float32x4(float x, float y, float z,float w) {
	vec = _mm_set_ps( w, z, y , x );
}


Float32x4::~Float32x4() {
}

void Float32x4::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Float32x4").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);
  Nan::SetIndexedPropertyHandler(
  	tpl->InstanceTemplate(),
  	Float32x4::PropertyGetter,
    Float32x4::PropertySetter,
    Float32x4::PropertyQuery,
    Float32x4::PropertyDeleter,
    Float32x4::PropertyEnumerator
  );

  v8::Local<v8::Function> cst = tpl->GetFunction();
  constructor.Reset(cst);
  exports->Set(Nan::New("Float32x4").ToLocalChecked(), cst);
  cst->Set(Nan::New("add").ToLocalChecked(),Nan::New<v8::FunctionTemplate>(Add)->GetFunction());
  cst->Set(Nan::New("abs").ToLocalChecked(),Nan::New<v8::FunctionTemplate>(Abs)->GetFunction());
  cst->Set(Nan::New("check").ToLocalChecked(),Nan::New<v8::FunctionTemplate>(Check)->GetFunction());
  cst->Set(Nan::New("div").ToLocalChecked(),Nan::New<v8::FunctionTemplate>(Div)->GetFunction());
  cst->Set(Nan::New("extractLane").ToLocalChecked(),Nan::New<v8::FunctionTemplate>(ExtractLane)->GetFunction());
  cst->Set(Nan::New("load").ToLocalChecked(),Nan::New<v8::FunctionTemplate>(Load)->GetFunction());
}

void Float32x4::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new Float32x4(...)`
	double r0 = (info.Length() >= 1 && info[0]->IsNumber())? info[0]->NumberValue() : NAN;
	double r1 = (info.Length() >= 2 && info[1]->IsNumber())? info[1]->NumberValue() : NAN;
	double r2 = (info.Length() >= 3 && info[2]->IsNumber())? info[2]->NumberValue() : NAN;
	double r3 = (info.Length() == 4 && info[3]->IsNumber())? info[3]->NumberValue() : NAN;
	Float32x4* obj = new Float32x4(r0,r1,r2,r3);

    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `Float32x4(...)`, turn into construct call.
    v8::Local<v8::Value>* argv= new v8::Local<v8::Value>[info.Length()];
    for(int i=0;i<info.Length();i++) {
    	argv[i]=info[i];
    }
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(info.Length(), argv));
  }
}

void Float32x4::Add(const Nan::FunctionCallbackInfo<v8::Value>& info) {

	if (info.Length() < 2) {
		Nan::ThrowTypeError("Wrong number of arguments");
		return;
	}
    Float32x4* a = cast(info[0]->ToObject());
    if(!a) {
		Nan::ThrowTypeError("1st argument isn't a Float32x4");
		return;
	}
    Float32x4* b = cast(info[1]->ToObject());
     if(!b) {
		Nan::ThrowTypeError("2sd argument isn't a Float32x4");
		return;
	}
    
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    v8::Local<v8::Object> res = cons->NewInstance(0, NULL);
	Float32x4* r = ObjectWrap::Unwrap<Float32x4>(res);
	r->vec = _mm_add_ps(a->vec,b->vec);
	info.GetReturnValue().Set(res);
}


void Float32x4::Div(const Nan::FunctionCallbackInfo<v8::Value>& info) {

	if (info.Length() < 2) {
		Nan::ThrowTypeError("Wrong number of arguments");
		return;
	}
    Float32x4* a = cast(info[0]->ToObject());
    if(!a) {
		Nan::ThrowTypeError("1st argument isn't a Float32x4");
		return;
	}
    Float32x4* b = cast(info[1]->ToObject());
     if(!b) {
		Nan::ThrowTypeError("2sd argument isn't a Float32x4");
		return;
	}
   v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    v8::Local<v8::Object> res = cons->NewInstance(0, NULL);
	Float32x4* r = ObjectWrap::Unwrap<Float32x4>(res);
	r->vec = _mm_div_ps(a->vec,b->vec);
	info.GetReturnValue().Set(res);
}

void Float32x4::Abs(const Nan::FunctionCallbackInfo<v8::Value>& info) {

	if (info.Length() < 1) {
		Nan::ThrowTypeError("Wrong number of arguments");
		return;
	}
	Float32x4* a = cast(info[0]->ToObject());
	if(!a) {
		Nan::ThrowTypeError("1st argument isn't a Float32x4");
		return;
	}

	v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
	v8::Local<v8::Object> res = cons->NewInstance(0, NULL);
	Float32x4* r = ObjectWrap::Unwrap<Float32x4>(res);
	r->vec = _mm_max_ps(_mm_sub_ps(_mm_setzero_ps(), a->vec), a->vec);
	info.GetReturnValue().Set(res);
}

void Float32x4::Check(const Nan::FunctionCallbackInfo<v8::Value>& info) {

	if (info.Length() < 1) {
		Nan::ThrowTypeError("Wrong number of arguments");
		return;
	}
    Float32x4* a = cast(info[0]->ToObject());
    if(!a) {
    	Nan::ThrowTypeError("1st argument isn't a Float32x4");
        return;
    }

	info.GetReturnValue().Set(info[0]->ToObject());
}

void Float32x4::ExtractLane(const Nan::FunctionCallbackInfo<v8::Value>& info) {

	if (info.Length() < 2) {
		Nan::ThrowTypeError("Wrong number of arguments");
		return;
	}
    Float32x4* a = cast(info[0]->ToObject());
    if(!a) {
		Nan::ThrowTypeError("1st argument isn't a Float32x4");
		return;
	}
	if(!info[1]->IsUint32()) {
		Nan::ThrowTypeError("2sd argument isn't a uint");
        return;
	}
    uint32_t idx = info[1]->Uint32Value();
     if(idx<0 || idx>=4) {
		Nan::ThrowRangeError("2sd argument isn't in [0 ... 3]");
		return;
	}
    float data[4];
    _mm_store_ps(data, a->vec );
	info.GetReturnValue().Set(data[idx]);
}


void Float32x4::Load(const Nan::FunctionCallbackInfo<v8::Value>& info) {

	if (info.Length() < 2) {
		Nan::ThrowTypeError("Wrong number of arguments");
		return;
	}
    Float32x4* a = cast(info[0]->ToObject());
    if(!a) {
		Nan::ThrowTypeError("1st argument isn't a Float32x4");
		return;
	}
	if(!info[1]->IsUint32()) {
		Nan::ThrowTypeError("2sd argument isn't a uint");
        return;
	}
    uint32_t idx = info[1]->Uint32Value();
     if(idx<0 || idx>=4) {
		Nan::ThrowRangeError("2sd argument isn't in [0 ... 3]");
		return;
	}
    float data[4];
    _mm_store_ps(data, a->vec );
	info.GetReturnValue().Set(data[idx]);
}


Float32x4* Float32x4::cast(v8::Local<v8::Object> object) {
  if(!object.IsEmpty() && object->InternalFieldCount() > 0) {
  	Float32x4* ptr = static_cast<Float32x4*>(Nan::GetInternalFieldPointer(object, 0));
	if(ptr && ptr->getType()==FLOAT32x4) {
		return ptr;
	}
  }
  return NULL;
}

NAN_INDEX_GETTER(Float32x4::PropertyGetter) {
	float data[4];
	Float32x4* r = ObjectWrap::Unwrap<Float32x4>(info.This());
	_mm_store_ps(data, r->vec );
    info.GetReturnValue().Set(Nan::New(data[index]));
}

NAN_INDEX_SETTER(Float32x4::PropertySetter) {
	float data[4];
	Float32x4* r = ObjectWrap::Unwrap<Float32x4>(info.This());
	_mm_store_ps(data, r->vec );
	data[index] = value->NumberValue();
	r->vec = _mm_load_ps(data);
	info.GetReturnValue().Set(info.This());
}

NAN_INDEX_ENUMERATOR(Float32x4::PropertyEnumerator) {

	v8::Local<v8::Array> arr = Nan::New<v8::Array>();
	Nan::Set(arr, 0, Nan::New(0));
	Nan::Set(arr, 1, Nan::New(1));
	Nan::Set(arr, 2, Nan::New(2));
	Nan::Set(arr, 3, Nan::New(3));
	info.GetReturnValue().Set(arr);
}

NAN_INDEX_DELETER(Float32x4::PropertyDeleter) {
  info.GetReturnValue().Set(Nan::True());
}

NAN_INDEX_QUERY(Float32x4::PropertyQuery) {

}