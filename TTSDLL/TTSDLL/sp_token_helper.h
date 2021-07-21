#pragma once

#ifndef __sapi_h__
#include <sapi.h>
#endif


#ifndef __ATLBASE_H__
#include <atlbase.h>
#endif

//=== Token helpers

inline HRESULT SpGetTokenFromId(
	const WCHAR* pszTokenId,
	ISpObjectToken** ppToken,
	BOOL fCreateIfNotExist = FALSE)
{
	HRESULT hr;

	CComPtr<ISpObjectToken> cpToken;
	hr = cpToken.CoCreateInstance(CLSID_SpObjectToken);

	if (SUCCEEDED(hr))
	{
		hr = cpToken->SetId(NULL, pszTokenId, fCreateIfNotExist);
	}

	if (SUCCEEDED(hr))
	{
		*ppToken = cpToken.Detach();
	}

	return hr;
}

inline HRESULT SpGetCategoryFromId(
	const WCHAR* pszCategoryId,
	ISpObjectTokenCategory** ppCategory,
	BOOL fCreateIfNotExist = FALSE)
{
	HRESULT hr;

	CComPtr<ISpObjectTokenCategory> cpTokenCategory;
	hr = cpTokenCategory.CoCreateInstance(CLSID_SpObjectTokenCategory);

	if (SUCCEEDED(hr))
	{
		hr = cpTokenCategory->SetId(pszCategoryId, fCreateIfNotExist);
	}

	if (SUCCEEDED(hr))
	{
		*ppCategory = cpTokenCategory.Detach();
	}

	return hr;
}

inline HRESULT SpGetDefaultTokenIdFromCategoryId(
	const WCHAR* pszCategoryId,
	_Outptr_ WCHAR** ppszTokenId)
{
	HRESULT hr;

	CComPtr<ISpObjectTokenCategory> cpCategory;
	hr = SpGetCategoryFromId(pszCategoryId, &cpCategory);

	if (SUCCEEDED(hr))
	{
		hr = cpCategory->GetDefaultTokenId(ppszTokenId);
	}

	return hr;
}

inline HRESULT SpSetDefaultTokenIdForCategoryId(
	const WCHAR* pszCategoryId,
	const WCHAR* pszTokenId)
{
	HRESULT hr;

	CComPtr<ISpObjectTokenCategory> cpCategory;
	hr = SpGetCategoryFromId(pszCategoryId, &cpCategory);

	if (SUCCEEDED(hr))
	{
		hr = cpCategory->SetDefaultTokenId(pszTokenId);
	}

	return hr;
}

inline HRESULT SpGetDefaultTokenFromCategoryId(
	const WCHAR* pszCategoryId,
	ISpObjectToken** ppToken,
	BOOL fCreateCategoryIfNotExist = TRUE)
{
	HRESULT hr;

	CComPtr<ISpObjectTokenCategory> cpCategory;
	hr = SpGetCategoryFromId(pszCategoryId, &cpCategory, fCreateCategoryIfNotExist);

	if (SUCCEEDED(hr))
	{
		WCHAR* pszTokenId;
		hr = cpCategory->GetDefaultTokenId(&pszTokenId);
		if (SUCCEEDED(hr))
		{
			hr = SpGetTokenFromId(pszTokenId, ppToken);
			::CoTaskMemFree(pszTokenId);
		}
	}

	return hr;
}

inline HRESULT SpSetDefaultTokenForCategoryId(
	const WCHAR* pszCategoryId,
	ISpObjectToken* pToken)
{
	HRESULT hr;

	WCHAR* pszTokenId;
	hr = pToken->GetId(&pszTokenId);

	if (SUCCEEDED(hr))
	{
		hr = SpSetDefaultTokenIdForCategoryId(pszCategoryId, pszTokenId);
		::CoTaskMemFree(pszTokenId);
	}

	return hr;
}

inline HRESULT SpEnumTokens(
	const WCHAR* pszCategoryId,
	const WCHAR* pszReqAttribs,
	const WCHAR* pszOptAttribs,
	IEnumSpObjectTokens** ppEnum)
{
	HRESULT hr = S_OK;

	CComPtr<ISpObjectTokenCategory> cpCategory;
	hr = SpGetCategoryFromId(pszCategoryId, &cpCategory);

	if (SUCCEEDED(hr))
	{
		hr = cpCategory->EnumTokens(
			pszReqAttribs,
			pszOptAttribs,
			ppEnum);
	}

	return hr;
}