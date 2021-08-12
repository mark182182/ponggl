#ifndef UTIL_H
#define UTIL_H

#pragma comment(lib, "rpcrt4.lib")
#include <iostream>
#include <windows.h>

std::string gen_uuid()
{
  UUID uuid;
  UuidCreate(&uuid);
  char *str;
  UuidToStringA(&uuid, (RPC_CSTR *)&str);
  std::string uuidStr = str;
  RpcStringFreeA((RPC_CSTR *)&str);
  return uuidStr;
};
#endif