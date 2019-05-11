#pragma once

constexpr bool ArrayGuards = false;
#ifdef _DEBUG
constexpr bool DebugMode = true;
#else
constexpr bool DebugMode = false;
#endif

typedef long double vtype;
typedef unsigned long long ctype;