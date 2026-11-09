#ifndef ARRAY_CONVERTOR_HEADER
#define ARRAY_CONVERTOR_HEADER

#include <Windows.h>

//The Object's Exception Codes

#define EXC_NOT_ONE_DIM					1001

//The Object's Exception Descriptions

#define EXCDES_NOT_ONE_DIM L"Unfortunately, only one-dimensional safearrays are currently supported for conversion."

class CArrayConvertor : public IDispatch
{
private:
	ULONG m_cRef;
	EXCEPINFO *m_pExcepStation;
public:
	CArrayConvertor(void);
	~CArrayConvertor(void);

    // IUnknown Members
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void **ppv);
    ULONG STDMETHODCALLTYPE AddRef(void);
    ULONG STDMETHODCALLTYPE Release(void);

    // IDispatch Members
    HRESULT STDMETHODCALLTYPE GetTypeInfoCount(UINT FAR* pctInfo);
    HRESULT STDMETHODCALLTYPE GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo FAR* FAR* ppTInfo);
    HRESULT STDMETHODCALLTYPE GetIDsOfNames(REFIID riid, OLECHAR FAR* FAR* rgszNames, UINT cNames, LCID lcid, DISPID FAR* rgDispId);
	HRESULT STDMETHODCALLTYPE Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS FAR* pDispParams, VARIANT FAR* pVarResult, EXCEPINFO FAR* pExcepInfo, UINT FAR* puArgErr);

	// ArrayConvertor Members
	HRESULT STDMETHODCALLTYPE ConvertArray(const VARIANT *pvarArg1, const VARIANT *pvarArg2, VARIANT *pvarRetVal);
};

#endif