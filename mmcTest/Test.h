#ifndef __TEST_H_
#define __TEST_H_
#include "resource.h"
#include <atlsnap.h>

class CTestData : public CSnapInItemImpl<CTestData>
{
public:
	static const GUID* m_NODETYPE;
	static const OLECHAR* m_SZNODETYPE;
	static const OLECHAR* m_SZDISPLAY_NAME;
	static const CLSID* m_SNAPIN_CLASSID;

	CComPtr<IControlbar> m_spControlBar;

	CTestData()
	{
		// イメージ インデックスは snapin に対する固有のイメージ
		// によって、変更を必要とする場合があります。
		memset(&m_scopeDataItem, 0, sizeof(SCOPEDATAITEM));
		m_scopeDataItem.mask = SDI_STR | SDI_IMAGE | SDI_OPENIMAGE | SDI_PARAM;
		m_scopeDataItem.displayname = MMC_CALLBACK;
		m_scopeDataItem.nImage = 0;			// 変更を必要とする可能性があります
		m_scopeDataItem.nOpenImage = 0;		// 変更を必要とする可能性があります
		m_scopeDataItem.lParam = (LPARAM) this;
		memset(&m_resultDataItem, 0, sizeof(RESULTDATAITEM));
		m_resultDataItem.mask = RDI_STR | RDI_IMAGE | RDI_PARAM;
		m_resultDataItem.str = MMC_CALLBACK;
		m_resultDataItem.nImage = 0;		// 変更を必要とする可能性があります
		m_resultDataItem.lParam = (LPARAM) this;
	}

	~CTestData()
	{
	}

    STDMETHOD(GetScopePaneInfo)(SCOPEDATAITEM *pScopeDataItem);

    STDMETHOD(GetResultPaneInfo)(RESULTDATAITEM *pResultDataItem);

    STDMETHOD(Notify)( MMC_NOTIFY_TYPE event,
        long arg,
        long param,
		IComponentData* pComponentData,
		IComponent* pComponent,
		DATA_OBJECT_TYPES type);

	LPOLESTR GetResultPaneColInfo(int nCol);
};

class CTest;

class CTestComponent : public CComObjectRootEx<CComSingleThreadModel>,
	public CSnapInObjectRoot<2, CTest >,
	public IPersistStreamInit,
	public IComponentImpl<CTestComponent>
{
public:
BEGIN_COM_MAP(CTestComponent)
	COM_INTERFACE_ENTRY(IComponent)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
END_COM_MAP()

public:
	CTestComponent()
	{
	}

	STDMETHOD(Notify)(LPDATAOBJECT lpDataObject, MMC_NOTIFY_TYPE event, long arg, long param)
	{
		if (lpDataObject != NULL)
			return IComponentImpl<CTestComponent>::Notify(lpDataObject, event, arg, param);
		// TODO : lpDataObject == NULL に設定する通知をハンドルするためのコードを追加してください
		return E_NOTIMPL;
	}

    STDMETHOD(GetClassID)(CLSID *pClassID)
	{
		ATLTRACENOTIMPL(_T("CTestComponent::GetClassID"));
	}	

	STDMETHOD(IsDirty)()
	{
		ATLTRACENOTIMPL(_T("CTestComponent::IsDirty"));
	}

	STDMETHOD(Load)(IStream *pStm)
	{
		ATLTRACENOTIMPL(_T("CTestComponent::Load"));
	}

    STDMETHOD(Save)(IStream *pStm, BOOL fClearDirty)
	{
		ATLTRACENOTIMPL(_T("CTestComponent::Save"));
	}

    STDMETHOD(GetSizeMax)(ULARGE_INTEGER *pcbSize)
	{
		ATLTRACENOTIMPL(_T("CTestComponent::GetSizeMax"));
	}

    STDMETHOD(InitNew)()
	{
		ATLTRACE(_T("CTestComponent::InitNew\n"));
		return S_OK;
	}

};

class CTest : public CComObjectRootEx<CComSingleThreadModel>,
public CSnapInObjectRoot<1, CTest>,
	public IComponentDataImpl<CTest, CTestComponent>,
	public IPersistStreamInit,
    public CComCoClass<CTest, &CLSID_Test>
{
public:
	CTest()
	{
		m_pNode = new CTestData;
		_ASSERTE(m_pNode != NULL);
		m_pComponentData = this;
	}

	~CTest()
	{
		delete m_pNode;
		m_pNode = NULL;
	}

BEGIN_COM_MAP(CTest)
    COM_INTERFACE_ENTRY(IComponentData)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
END_COM_MAP()

DECLARE_REGISTRY_RESOURCEID(IDR_TEST)

DECLARE_NOT_AGGREGATABLE(CTest)

    STDMETHOD(GetClassID)(CLSID *pClassID)
	{
		ATLTRACENOTIMPL(_T("CTest::GetClassID"));
	}	

	STDMETHOD(IsDirty)()
	{
		ATLTRACENOTIMPL(_T("CTest::IsDirty"));
	}

	STDMETHOD(Load)(IStream *pStm)
	{
		ATLTRACENOTIMPL(_T("CTest::Load"));
	}

    STDMETHOD(Save)(IStream *pStm, BOOL fClearDirty)
	{
		ATLTRACENOTIMPL(_T("CTest::Save"));
	}

    STDMETHOD(GetSizeMax)(ULARGE_INTEGER *pcbSize)
	{
		ATLTRACENOTIMPL(_T("CTest::GetSizeMax"));
	}

    STDMETHOD(InitNew)()
	{
		ATLTRACE(_T("CTest::InitNew\n"));
		return S_OK;
	}

    STDMETHOD(Initialize)(LPUNKNOWN pUnknown);

	static void WINAPI ObjectMain(bool bStarting)
	{
		if (bStarting)
			CSnapInItem::Init();
	}
};

class ATL_NO_VTABLE CTestAbout : public ISnapinAbout,
	public CComObjectRoot,
	public CComCoClass< CTestAbout, &CLSID_TestAbout>
{
public:
	DECLARE_REGISTRY(CTestAbout, _T("TestAbout.1"), _T("TestAbout.1"), IDS_TEST_DESC, THREADFLAGS_BOTH);

	BEGIN_COM_MAP(CTestAbout)
		COM_INTERFACE_ENTRY(ISnapinAbout)
	END_COM_MAP()

	STDMETHOD(GetSnapinDescription)(LPOLESTR *lpDescription)
	{
		USES_CONVERSION;
		TCHAR szBuf[256];
		if (::LoadString(_Module.GetResourceInstance(), IDS_TEST_DESC, szBuf, 256) == 0)
			return E_FAIL;

		*lpDescription = (LPOLESTR)CoTaskMemAlloc((lstrlen(szBuf) + 1) * sizeof(OLECHAR));
		if (*lpDescription == NULL)
			return E_OUTOFMEMORY;

		ocscpy(*lpDescription, T2OLE(szBuf));

		return S_OK;
	}

    STDMETHOD(GetProvider)(LPOLESTR *lpName)
	{
		USES_CONVERSION;
		TCHAR szBuf[256];
		if (::LoadString(_Module.GetResourceInstance(), IDS_TEST_PROVIDER, szBuf, 256) == 0)
			return E_FAIL;

		*lpName = (LPOLESTR)CoTaskMemAlloc((lstrlen(szBuf) + 1) * sizeof(OLECHAR));
		if (*lpName == NULL)
			return E_OUTOFMEMORY;

		ocscpy(*lpName, T2OLE(szBuf));

		return S_OK;
	}

    STDMETHOD(GetSnapinVersion)(LPOLESTR *lpVersion)
	{
		USES_CONVERSION;
		TCHAR szBuf[256];
		if (::LoadString(_Module.GetResourceInstance(), IDS_TEST_VERSION, szBuf, 256) == 0)
			return E_FAIL;

		*lpVersion = (LPOLESTR)CoTaskMemAlloc((lstrlen(szBuf) + 1) * sizeof(OLECHAR));
		if (*lpVersion == NULL)
			return E_OUTOFMEMORY;

		ocscpy(*lpVersion, T2OLE(szBuf));

		return S_OK;
	}

    STDMETHOD(GetSnapinImage)(HICON *hAppIcon)
	{
		*hAppIcon = NULL;
		return S_OK;
	}

    STDMETHOD(GetStaticFolderImage)(HBITMAP *hSmallImage,
        HBITMAP *hSmallImageOpen,
        HBITMAP *hLargeImage,
        COLORREF *cMask)
	{
		*hSmallImageOpen = *hLargeImage = *hLargeImage = 0;
		return S_OK;
	}
};

#endif
