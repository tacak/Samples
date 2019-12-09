#include "stdafx.h"
#include "MmcTest.h"
#include "Test.h"

/////////////////////////////////////////////////////////////////////////////
// CTestComponentData
static const GUID CTestGUID_NODETYPE = 
{ 0xdc1c5cda, 0x887, 0x4584, { 0xb7, 0xae, 0x38, 0x16, 0xef, 0x17, 0x5c, 0x6d } };
const GUID*  CTestData::m_NODETYPE = &CTestGUID_NODETYPE;
const OLECHAR* CTestData::m_SZNODETYPE = OLESTR("DC1C5CDA-0887-4584-B7AE-3816EF175C6D");
const OLECHAR* CTestData::m_SZDISPLAY_NAME = OLESTR("Test");
const CLSID* CTestData::m_SNAPIN_CLASSID = &CLSID_Test;

HRESULT CTestData::GetScopePaneInfo(SCOPEDATAITEM *pScopeDataItem)
{
	if (pScopeDataItem->mask & SDI_STR)
		pScopeDataItem->displayname = m_bstrDisplayName;
	if (pScopeDataItem->mask & SDI_IMAGE)
		pScopeDataItem->nImage = m_scopeDataItem.nImage;
	if (pScopeDataItem->mask & SDI_OPENIMAGE)
		pScopeDataItem->nOpenImage = m_scopeDataItem.nOpenImage;
	if (pScopeDataItem->mask & SDI_PARAM)
		pScopeDataItem->lParam = m_scopeDataItem.lParam;
	if (pScopeDataItem->mask & SDI_STATE )
		pScopeDataItem->nState = m_scopeDataItem.nState;

	// TODO : SDI_CHILDREN 用のコードを追加してください 
	return S_OK;
}

HRESULT CTestData::GetResultPaneInfo(RESULTDATAITEM *pResultDataItem)
{
	if (pResultDataItem->bScopeItem)
	{
		if (pResultDataItem->mask & RDI_STR)
		{
			pResultDataItem->str = GetResultPaneColInfo(pResultDataItem->nCol);
		}
		if (pResultDataItem->mask & RDI_IMAGE)
		{
			pResultDataItem->nImage = m_scopeDataItem.nImage;
		}
		if (pResultDataItem->mask & RDI_PARAM)
		{
			pResultDataItem->lParam = m_scopeDataItem.lParam;
		}

		return S_OK;
	}

	if (pResultDataItem->mask & RDI_STR)
	{
		pResultDataItem->str = GetResultPaneColInfo(pResultDataItem->nCol);
	}
	if (pResultDataItem->mask & RDI_IMAGE)
	{
		pResultDataItem->nImage = m_resultDataItem.nImage;
	}
	if (pResultDataItem->mask & RDI_PARAM)
	{
		pResultDataItem->lParam = m_resultDataItem.lParam;
	}
	if (pResultDataItem->mask & RDI_INDEX)
	{
		pResultDataItem->nIndex = m_resultDataItem.nIndex;
	}

	return S_OK;
}

HRESULT CTestData::Notify( MMC_NOTIFY_TYPE event,
    long arg,
    long param,
	IComponentData* pComponentData,
	IComponent* pComponent,
	DATA_OBJECT_TYPES type)
{
	// 異なる通知を処理するためのコードを追加してください。
	// ハンドル MMCN_SHOW および MMCN_EXPAND は子アイテムの列挙用です。
	// MMCN_SHOW への応答内ではスコープおよび結果ペイン アイテムを列挙
	// する必要があります。
	// MMCN_EXPAND に対してはスコープ アイテムのみを列挙する必要があります。
	// スコープ ペイン アイテムの挿入には IConsoleNameSpace::InsertItem を使用してください。
	// 結果ペイン アイテムの挿入には IResultData::InsertItem を使用してください。
	HRESULT hr = E_NOTIMPL;

	
	_ASSERTE(pComponentData != NULL || pComponent != NULL);

	CComPtr<IConsole> spConsole;
	CComQIPtr<IHeaderCtrl, &IID_IHeaderCtrl> spHeader;
	if (pComponentData != NULL)
		spConsole = ((CTest*)pComponentData)->m_spConsole;
	else
	{
		spConsole = ((CTestComponent*)pComponent)->m_spConsole;
		spHeader = spConsole;
	}

	switch (event)
	{
	case MMCN_SHOW:
		{
			CComQIPtr<IResultData, &IID_IResultData> spResultData(spConsole);
			// TODO : 結果ペイン アイテムを列挙してください
			hr = S_OK;
			break;
		}
	case MMCN_EXPAND:
		{
			CComQIPtr<IConsoleNameSpace, &IID_IConsoleNameSpace> spConsoleNameSpace(spConsole);
			// TODO : スコープ ペイン アイテムを列挙してください
			hr = S_OK;
			break;
		}
	case MMCN_ADD_IMAGES:
		{
			// イメージの追加
			IImageList* pImageList = (IImageList*) arg;
			hr = E_FAIL;
			// スコープ ペインに関連付けられたビットマップを読み込み
			// それらをイメージ リストに追加してください。
			// ウィザードによって作成された既定のビットマップを読み込み
			// 必要に応じて変更してください。
			HBITMAP hBitmap16 = LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_TEST_16));
			if (hBitmap16 != NULL)
			{
				HBITMAP hBitmap32 = LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_TEST_32));
				if (hBitmap32 != NULL)
				{
					hr = pImageList->ImageListSetStrip((long*)hBitmap16, 
					(long*)hBitmap32, 0, RGB(0, 128, 128));
					if (FAILED(hr))
						ATLTRACE(_T("IImageList::ImageListSetStrip failed\n"));
				}
			}
			break;
		}
	}
	return hr;
}

LPOLESTR CTestData::GetResultPaneColInfo(int nCol)
{
	if (nCol == 0)
		return m_bstrDisplayName;
	// TODO : 他の列に対して文字を返します
	return OLESTR("Override GetResultPaneColInfo");
}

HRESULT CTest::Initialize(LPUNKNOWN pUnknown)
{
	HRESULT hr = IComponentDataImpl<CTest, CTestComponent >::Initialize(pUnknown);
	if (FAILED(hr))
		return hr;

	CComPtr<IImageList> spImageList;

	if (m_spConsole->QueryScopeImageList(&spImageList) != S_OK)
	{
		ATLTRACE(_T("IConsole::QueryScopeImageList failed\n"));
		return E_UNEXPECTED;
	}

	// スコープ ペインに関連付けられたビットマップを読み込み
	// それらをイメージ リストに追加してください。
	// ウィザードによって作成された既定のビットマップを読み込み
	// 必要に応じて変更してください。
	HBITMAP hBitmap16 = LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_TEST_16));
	if (hBitmap16 == NULL)
		return S_OK;

	HBITMAP hBitmap32 = LoadBitmap(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDB_TEST_32));
	if (hBitmap32 == NULL)
		return S_OK;

	if (spImageList->ImageListSetStrip((long*)hBitmap16, 
		(long*)hBitmap32, 0, RGB(0, 128, 128)) != S_OK)
	{
		ATLTRACE(_T("IImageList::ImageListSetStrip failed\n"));
		return E_UNEXPECTED;
	}
	return S_OK;
}
