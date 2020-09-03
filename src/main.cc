#include <napi.h>
#include <iostream>

using namespace Napi;

std::string WcharToChar(const wchar_t *wp)
{
  std::string str;
  int len = wcslen(wp) * sizeof(wchar_t);
  char *m_char = new char[len];
  setlocale(LC_ALL, ""); // set system locale to show chinese string
  wcstombs(m_char, wp, len);
  str = m_char;
  delete[] m_char;
  return str;
}

Value Say(const CallbackInfo &info)
{
  auto env = info.Env();
  if (info.Length() == 0)
  {
    std::cout << "Hi，我是前端工程师，刘辉。" << std::endl;
    return env.Undefined();
  }
  if (info[0].IsString())
  {
    std::cout << info[0].As<String>().Utf8Value() << std::endl;
  }
  else if (info[0].IsFunction())
  {
    info[0].As<Function>().Call(env.Global(), {String::New(env, " HaHa, 荒川爆笑团！")});
  }
  else if (info[0].IsNumber())
  {
    auto deferred = Promise::Deferred::New(env);
    deferred.Resolve(String::New(env, "Done"));
    return deferred.Promise();
  }
  else
  {
    TypeError::New(env, std::string("invalid arguments ").append(info[0].ToString()))
        .ThrowAsJavaScriptException();
    return env.Undefined(); // generally return immediately after throw error
  }
}

Object Init(Env env, Object exports)
{
  exports.Set("age", 24);                 // int => number
  exports.Set("balance", 999.9999999999); // double => number

  exports.Set("name", "Sysiya");                       // char * => string (UTF-8)
  exports.Set("alias", u"刘辉");                       // char16_t * => string (UTF-16)
  exports.Set("position", WcharToChar(L"前端工程师")); // wchar_t * => char * => string（WCHAR）

  exports.Set("say", Function::New<Say>(env)); // function

  auto friends = Array::New(env);
  friends.Set(uint32_t(0), String::New(env, "Ada"));
  friends.Set(1, String::New(env, "Bob"));
  exports.Set("friends", friends);

  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
