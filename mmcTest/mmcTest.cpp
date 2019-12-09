// mmcTest.cpp : DLL エクスポートのインプリメンテーション


// メモ: Proxy/Stub 情報
//  別々の proxy/stub DLL をビルドするためには、プロジェクトのディレクトリで 
//      nmake -f mmcTestps.mak を実行してください。

#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "mmcTest.h"

#include "mmcTest_i.c"
#include "Test.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_Test, CTest)
OBJECT_ENTRY(CLSID_TestAbout, CTestAbout)
END_OBJECT_MAP()

/////////////////////////////////////////////////////////////////////////////
// DLL エントリ ポイント

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_MMCTESTLib);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// DLL が OLE によってアンロード可能かどうかを調べるために使用されます

STDAPI DllCanUnloadNow(void)
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// 要求された型のオブジェクトを作成するためにクラス ファクトリを返します

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - システム レジストリへエントリを追加します

STDAPI DllRegisterServer(void)
{
    // オブジェクト、タイプライブラリおよびタイプライブラリ内の全てのインターフェイスを登録します
    return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - システム レジストリからエントリを削除します

STDAPI DllUnregisterServer(void)
{
    return _Module.UnregisterServer(TRUE);
}


