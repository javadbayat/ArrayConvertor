#define _CRT_SECURE_NO_WARNINGS

#include "ArrayConvertor.h"
#include <stdlib.h>

//Helper functions

#define PVE_HELPER(d) SafeArrayPutElement(psa, pIndices, (PVOID) (d))
#define GVE_HELPER(d) SafeArrayGetElement(psa, pIndices, (PVOID) (&(d)))

HRESULT SafeArrayPutVarElement(SAFEARRAY *psa, LONG *pIndices, VARIANT *pVarElem)
{
	HRESULT hr = S_OK;

	switch (pVarElem->vt)
	{
	case VT_I1 :
		{
			hr = PVE_HELPER(&(pVarElem->cVal));
			break;
		}
	case VT_I2 :
		{
			hr = PVE_HELPER(&(pVarElem->iVal));
			break;
		}
	case VT_I4 :
		{
			hr = PVE_HELPER(&(pVarElem->lVal));
			break;
		}
	case VT_I8 :
		{
			hr = PVE_HELPER(&(pVarElem->llVal));
			break;
		}
	case VT_R4 :
		{
			hr = PVE_HELPER(&(pVarElem->fltVal));
			break;
		}
	case VT_R8 :
		{
			hr = PVE_HELPER(&(pVarElem->dblVal));
			break;
		}
	case VT_CY :
		{
			hr = PVE_HELPER(&(pVarElem->cyVal));
			break;
		}
	case VT_DATE :
		{
			hr = PVE_HELPER(&(pVarElem->date));
			break;
		}
	case VT_BSTR :
		{
			//According to the documentation:
			//The variant types VT_DISPATCH, VT_UNKNOWN, and VT_BSTR are
			//pointers, and do not require another level of indirection.
			hr = PVE_HELPER(pVarElem->bstrVal);
			//NOT hr = PVE_HELPER(&(pVarElem->bstrVal));
			break;
		}
	case VT_DISPATCH :
		{
			hr = PVE_HELPER(pVarElem->pdispVal);
			break;
		}
	case VT_UNKNOWN :
		{
			hr = PVE_HELPER(pVarElem->punkVal);
			break;
		}
	case VT_BOOL :
		{
			hr = PVE_HELPER(&(pVarElem->boolVal));
			break;
		}
	case VT_DECIMAL :
		{
			hr = PVE_HELPER(&(pVarElem->decVal));
			break;
		}
	case VT_UI1 :
		{
			hr = PVE_HELPER(&(pVarElem->bVal));
			break;
		}
	case VT_UI2 :
		{
			hr = PVE_HELPER(&(pVarElem->puiVal));
			break;
		}
	case VT_UI4 :
		{
			hr = PVE_HELPER(&(pVarElem->ulVal));
			break;
		}
	case VT_UI8 :
		{
			hr = PVE_HELPER(&(pVarElem->ullVal));
			break;
		}
	case VT_INT :
		{
			hr = PVE_HELPER(&(pVarElem->intVal));
			break;
		}
	case VT_UINT :
		{
			hr = PVE_HELPER(&(pVarElem->uintVal));
			break;
		}
	default:
		{
			hr = DISP_E_TYPEMISMATCH;
			break;
		}
	}

	return hr;
}

HRESULT SafeArrayGetVarElement(SAFEARRAY *psa, LONG *pIndices, VARIANT *pVarElem)
{
	HRESULT hr = S_OK;

	switch (pVarElem->vt)
	{
	case VT_I1 :
		{
			hr = GVE_HELPER(pVarElem->cVal);
			break;
		}
	case VT_I2 :
		{
			hr = GVE_HELPER(pVarElem->iVal);
			break;
		}
	case VT_I4 :
		{
			hr = GVE_HELPER(pVarElem->lVal);
			break;
		}
	case VT_I8 :
		{
			hr = GVE_HELPER(pVarElem->llVal);
			break;
		}
	case VT_R4 :
		{
			hr = GVE_HELPER(pVarElem->fltVal);
			break;
		}
	case VT_R8 :
		{
			hr = GVE_HELPER(pVarElem->dblVal);
			break;
		}
	case VT_CY :
		{
			hr = GVE_HELPER(pVarElem->cyVal);
			break;
		}
	case VT_DATE :
		{
			hr = GVE_HELPER(pVarElem->date);
			break;
		}
	case VT_BSTR :
		{
			hr = GVE_HELPER(pVarElem->bstrVal);
			break;
		}
	case VT_DISPATCH :
		{
			hr = GVE_HELPER(pVarElem->pdispVal);
			break;
		}
	case VT_UNKNOWN :
		{
			hr = GVE_HELPER(pVarElem->punkVal);
			break;
		}
	case VT_BOOL :
		{
			hr = GVE_HELPER(pVarElem->boolVal);
			break;
		}
	case VT_DECIMAL :
		{
			hr = GVE_HELPER(pVarElem->decVal);
			break;
		}
	case VT_UI1 :
		{
			hr = GVE_HELPER(pVarElem->bVal);
			break;
		}
	case VT_UI2 :
		{
			hr = GVE_HELPER(pVarElem->puiVal);
			break;
		}
	case VT_UI4 :
		{
			hr = GVE_HELPER(pVarElem->ulVal);
			break;
		}
	case VT_UI8 :
		{
			hr = GVE_HELPER(pVarElem->ullVal);
			break;
		}
	case VT_INT :
		{
			hr = GVE_HELPER(pVarElem->intVal);
			break;
		}
	case VT_UINT :
		{
			hr = GVE_HELPER(pVarElem->uintVal);
			break;
		}
	default :
		{
			hr = DISP_E_TYPEMISMATCH;
			break;
		}
	}

	if (FAILED(hr))
		pVarElem->vt = VT_EMPTY;

	return hr;
}

HRESULT JsArrayGetElement(IDispatch *pJsArray, long elemIndex, VARIANT *pVarValue)
{
	HRESULT hr = S_OK;
	WCHAR wszElemIndex[16];
	PWSTR pwszElemIndex = wszElemIndex;
	DISPID diElemIndex = 0;
	DISPPARAMS dpNoArgs = { NULL };

	if (elemIndex == -1)
		wcscpy(wszElemIndex, L"length");
	else
		_ltow(elemIndex, wszElemIndex, 10);

	hr = pJsArray->GetIDsOfNames( IID_NULL, &pwszElemIndex, 1, LOCALE_USER_DEFAULT, &diElemIndex );
	if (SUCCEEDED(hr))
		hr = pJsArray->Invoke( diElemIndex, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_PROPERTYGET, &dpNoArgs, pVarValue, NULL, NULL );

	if (SUCCEEDED(hr) && (elemIndex == -1))
		hr = VariantChangeType( pVarValue, pVarValue, 0, VT_I4 );

	return hr;
}

VARTYPE VarTypeFromString(BSTR bsVarType)
{
	if (!_wcsicmp(bsVarType, L"VT_I1"))
		return VT_I1;
	else if (!_wcsicmp(bsVarType, L"VT_I2"))
		return VT_I2;
	else if (!_wcsicmp(bsVarType, L"VT_I4"))
		return VT_I4;
	else if (!_wcsicmp(bsVarType, L"VT_I8"))
		return VT_I8;
	else if (!_wcsicmp(bsVarType, L"VT_UI1"))
		return VT_UI1;
	else if (!_wcsicmp(bsVarType, L"VT_UI2"))
		return VT_UI2;
	else if (!_wcsicmp(bsVarType, L"VT_UI4"))
		return VT_UI4;
	else if (!_wcsicmp(bsVarType, L"VT_UI8"))
		return VT_UI8;
	else if (!_wcsicmp(bsVarType, L"VT_R4"))
		return VT_R4;
	else if (!_wcsicmp(bsVarType, L"VT_R8"))
		return VT_R8;
	else if (!_wcsicmp(bsVarType, L"VT_INT"))
		return VT_INT;
	else if (!_wcsicmp(bsVarType, L"VT_UINT"))
		return VT_UINT;
	else if (!_wcsicmp(bsVarType, L"VT_BSTR"))
		return VT_BSTR;
	else if (!_wcsicmp(bsVarType, L"VT_BOOL"))
		return VT_BOOL;
	else if (!_wcsicmp(bsVarType, L"VT_DATE"))
		return VT_DATE;
	else if (!_wcsicmp(bsVarType, L"VT_DISPATCH"))
		return VT_DISPATCH;
	else if (!_wcsicmp(bsVarType, L"VT_UNKNOWN"))
		return VT_UNKNOWN;
	else if (!_wcsicmp(bsVarType, L"VT_VARIANT"))
		return VT_VARIANT;
	else if (!_wcsicmp(bsVarType, L"VT_RECORD"))
		return VT_RECORD;
	else if (!_wcsicmp(bsVarType, L"VT_ERROR"))
		return VT_ERROR;
	else if (!_wcsicmp(bsVarType, L"VT_DECIMAL"))
		return VT_DECIMAL;
	else if (!_wcsicmp(bsVarType, L"VT_CY"))
		return VT_CY;
	else
		return VT_ILLEGAL;
}

// Constructor and Destructor

CArrayConvertor::CArrayConvertor(void)
	: m_cRef( 0 )
{

}

CArrayConvertor::~CArrayConvertor(void)
{

}

// IUnknown Members

STDMETHODIMP CArrayConvertor::QueryInterface(REFIID riid, void **ppv)
{
    HRESULT hr = S_OK;
    if (ppv)
    {
        *ppv = NULL;

        if (IsEqualIID( riid, IID_IDispatch ) || IsEqualIID( riid, IID_IUnknown ))
            *ppv = (IDispatch *) (this);
        else
            hr = E_NOINTERFACE;

        if (*ppv)
            AddRef();
    }
    else
        hr = E_INVALIDARG;

    return hr;
}

STDMETHODIMP_(ULONG) CArrayConvertor::AddRef(void)
{
    return((ULONG) (InterlockedIncrement((long *) &m_cRef)));
}

STDMETHODIMP_(ULONG) CArrayConvertor::Release(void)
{
    ULONG cRef = (ULONG) (InterlockedDecrement((long *) &m_cRef));
    if (!cRef)
        delete this;

    return cRef;
}

// IDispatch Members

STDMETHODIMP CArrayConvertor::GetTypeInfoCount(UINT FAR* pctInfo)
{
    if (!pctInfo)
        return E_INVALIDARG;

    *pctInfo = 0;
    return S_OK;
}

STDMETHODIMP CArrayConvertor::GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo FAR* FAR* ppTInfo)
{
    return E_NOTIMPL;
}

STDMETHODIMP CArrayConvertor::GetIDsOfNames(REFIID riid, OLECHAR FAR* FAR* rgszNames, UINT cNames, LCID lcid, DISPID FAR* rgDispId)
{
	return E_NOTIMPL;
}

STDMETHODIMP CArrayConvertor::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, UINT FAR* puArgErr)
{
	if (!pDispParams)
		return E_INVALIDARG;

	if (!IsEqualIID( riid, IID_NULL ))	
		return DISP_E_UNKNOWNINTERFACE;

	if (dispIdMember != DISPID_VALUE)
		return DISP_E_MEMBERNOTFOUND;

	if (!(wFlags & DISPATCH_METHOD))
		return DISP_E_MEMBERNOTFOUND;

	HRESULT hr = S_OK;
	VARIANT varTempResult;

	VariantInit(&varTempResult);

	m_pExcepStation = pExcepInfo;

	if (pDispParams->cArgs == 1)
	{
		VARIANT varTemp;
		VariantInit(&varTemp);
		varTemp.vt = VT_UI2;
		varTemp.uiVal = 12;

		hr = ConvertArray( pDispParams->rgvarg, &varTemp, &varTempResult );

		VariantClear(&varTemp);
	}
	else if (pDispParams->cArgs == 2)
		hr = ConvertArray( pDispParams->rgvarg + 1, pDispParams->rgvarg, &varTempResult );
	else
		hr = DISP_E_BADPARAMCOUNT;

	m_pExcepStation = NULL;

	if (SUCCEEDED(hr) && pVarResult)
		hr = VariantCopy(pVarResult, &varTempResult );

	VariantClear(&varTempResult);

	return hr;
}

// ArrayConvertor Members

STDMETHODIMP CArrayConvertor::ConvertArray(const VARIANT *pvarArg1, const VARIANT *pvarArg2, VARIANT *pvarRetVal)
{
	HRESULT hr = S_OK;
	VARIANT vArrType, vArrLength, vElem;
	IDispatch *pJsArray = NULL;
	long lb, ub, i;
	long &arrLength = ub;
	VARTYPE arrType, arrType2;
	SAFEARRAY *pSafeArray = NULL, *psaRes;
	PWSTR pwszPush = L"push";
	DISPID diPush = 0;
	DISPPARAMS argsForPush = {&vElem, NULL, 1, 0};

	if (pvarArg1 && pvarArg2 && pvarRetVal)
	{
		if (pvarArg1->vt == VT_DISPATCH)
		{
			VariantInit(&vArrType);
			hr = VariantChangeType(&vArrType, pvarArg2, 0, VT_UI2);
			arrType = (VARTYPE) (vArrType.uiVal);
			VariantClear(&vArrType);
			if (FAILED(hr) && (pvarArg2->vt == VT_BSTR))
			{
				arrType = VarTypeFromString(pvarArg2->bstrVal);
				hr = (arrType == VT_ILLEGAL) ? E_INVALIDARG : S_OK;
			}

			if (SUCCEEDED(hr))
			{
				pJsArray = pvarArg1->pdispVal;

				VariantInit(&vArrLength);
				hr = JsArrayGetElement(pJsArray, -1, &vArrLength);
				if (SUCCEEDED(hr))
				{
					arrLength = vArrLength.lVal;
					pSafeArray = SafeArrayCreateVector(arrType, 0, (ULONG) arrLength);
					if (pSafeArray)
					{
						for (i = 0; i < arrLength; i++)
						{
							VariantInit(&vElem);
							hr = JsArrayGetElement(pJsArray, i, &vElem);
							if (SUCCEEDED(hr))
							{
								if (arrType == VT_VARIANT)
									hr = SafeArrayPutElement(pSafeArray, &i, (PVOID) &vElem);
								else
								{
									hr = VariantChangeType(&vElem, &vElem, 0, arrType);
									if (SUCCEEDED(hr))
										hr = SafeArrayPutVarElement(pSafeArray, &i, &vElem);
								}
							}

							VariantClear(&vElem);

							if (FAILED(hr))
								break;
						}

						if (SUCCEEDED(hr))
						{
							pvarRetVal->vt = VT_ARRAY | arrType;
							pvarRetVal->parray = pSafeArray;
						}
					}
					else
						hr = E_FAIL;
				}
			}
		}
		else if (pvarArg1->vt & VT_ARRAY)
		{
			arrType = pvarArg1->vt - VT_ARRAY;
			pSafeArray = pvarArg1->parray;
			if (SafeArrayGetDim(pSafeArray) == 1)
			{
				if (pvarArg2->vt == VT_DISPATCH)
				{
					pJsArray = pvarArg2->pdispVal;
					hr = pJsArray->GetIDsOfNames( IID_NULL, &pwszPush, 1, LOCALE_USER_DEFAULT, &diPush );
					if (SUCCEEDED(hr))
					{
						hr = SafeArrayGetLBound(pSafeArray, 1, &lb);
						if (SUCCEEDED(hr))
						{
							hr = SafeArrayGetUBound(pSafeArray, 1, &ub);
							if (SUCCEEDED(hr))
							{
								for (i = lb; i <= ub; i++)
								{
									VariantInit(&vElem);

									if (arrType == VT_VARIANT)
										hr = SafeArrayGetElement(pSafeArray, &i, (PVOID) &vElem);
									else
									{
										vElem.vt = arrType;
										hr = SafeArrayGetVarElement(pSafeArray, &i, &vElem);
									}

									if (SUCCEEDED(hr))
										hr = pJsArray->Invoke( diPush, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &argsForPush, NULL, NULL, NULL );

									VariantClear(&vElem);

									if (FAILED(hr))
										break;
								}

								if (SUCCEEDED(hr))
									hr = VariantCopy(pvarRetVal, pvarArg2);
							}
						}
					}
				}
				else
				{
					VariantInit(&vArrType);
					hr = VariantChangeType(&vArrType, pvarArg2, 0, VT_UI2);
					arrType2 = (VARTYPE) (vArrType.uiVal);
					VariantClear(&vArrType);
					if (FAILED(hr) && (pvarArg2->vt == VT_BSTR))
					{
						arrType2 = VarTypeFromString(pvarArg2->bstrVal);
						hr = (arrType2 == VT_ILLEGAL) ? E_INVALIDARG : S_OK;
					}

					if (SUCCEEDED(hr))
					{
						hr = SafeArrayGetLBound(pSafeArray, 1, &lb);
						if (SUCCEEDED(hr))
						{
							hr = SafeArrayGetUBound(pSafeArray, 1, &ub);
							if (SUCCEEDED(hr))
							{
								psaRes = SafeArrayCreateVector(arrType2, lb, ub - lb + 1);
								if (psaRes)
								{
									for (i = lb; i <= ub; i++)
									{
										VariantInit(&vElem);

										if (arrType == VT_VARIANT)
											hr = SafeArrayGetElement(pSafeArray, &i, (PVOID) &vElem);
										else
										{
											vElem.vt = arrType;
											hr = SafeArrayGetVarElement(pSafeArray, &i, &vElem);
										}

										if (SUCCEEDED(hr))
										{
											if (arrType2 == VT_VARIANT)
												hr = SafeArrayPutElement(psaRes, &i, (PVOID) &vElem);
											else
											{
												hr = VariantChangeType(&vElem, &vElem, 0, arrType2);
												if (SUCCEEDED(hr))
													hr = SafeArrayPutVarElement(psaRes, &i, &vElem);
											}
										}

										VariantClear(&vElem);

										if (FAILED(hr))
											break;
									}

									if (SUCCEEDED(hr))
									{
										pvarRetVal->vt = VT_ARRAY | arrType2;
										pvarRetVal->parray = psaRes;
									}
								}
								else
									hr = E_FAIL;
							}
						}
					}
				}
			}
			else
				goto exc_NOD_stop;
		}
		else
			hr = DISP_E_TYPEMISMATCH;
	}
	else
		hr = E_INVALIDARG;

	return hr;

exc_NOD_stop:;
	if (m_pExcepStation)
	{
		m_pExcepStation->wCode = EXC_NOT_ONE_DIM;
		m_pExcepStation->bstrDescription = SysAllocString(EXCDES_NOT_ONE_DIM);
		m_pExcepStation->bstrSource = SysAllocString(L"ArrayConvertor");
		hr = DISP_E_EXCEPTION;
	}
	else
		hr = E_FAIL;

	return hr;
}