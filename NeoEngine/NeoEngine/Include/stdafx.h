// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once


#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
#include <windows.h>



// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <cassert>
#include <fstream>

//STL
#include <string>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <memory>
#include <limits>

// OIS
#include <OIS.h>

//D3D
#include <d3d11.h>
#include <d3dx11.h>

//XNAMATH
#include <xnamath.h>

//SSE
#include <xmmintrin.h>
#include <emmintrin.h>

//tinyxml
#include <tinyxml/tinystr.h>
#include <tinyxml/tinyxml.h>

#ifdef _DEBUG
	#define _AST(a)		if(!(a)) { __debugbreak(); }
#else
	#define _AST(a)		(a)
#endif

struct handle_closer { void operator()(HANDLE h) { if (h) CloseHandle(h); } };

typedef std::unique_ptr<void, handle_closer> ScopedHandle;

inline HANDLE safe_handle(HANDLE h) { return (h == INVALID_HANDLE_VALUE) ? 0 : h; }

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif


