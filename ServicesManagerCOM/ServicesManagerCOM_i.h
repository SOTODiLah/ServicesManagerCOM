

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 06:14:07 2038
 */
/* Compiler settings for ServicesManagerCOM.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __ServicesManagerCOM_i_h__
#define __ServicesManagerCOM_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IServiceManager_FWD_DEFINED__
#define __IServiceManager_FWD_DEFINED__
typedef interface IServiceManager IServiceManager;

#endif 	/* __IServiceManager_FWD_DEFINED__ */


#ifndef __ServiceManager_FWD_DEFINED__
#define __ServiceManager_FWD_DEFINED__

#ifdef __cplusplus
typedef class ServiceManager ServiceManager;
#else
typedef struct ServiceManager ServiceManager;
#endif /* __cplusplus */

#endif 	/* __ServiceManager_FWD_DEFINED__ */


#ifndef __IFactoryServiceManager_FWD_DEFINED__
#define __IFactoryServiceManager_FWD_DEFINED__
typedef interface IFactoryServiceManager IFactoryServiceManager;

#endif 	/* __IFactoryServiceManager_FWD_DEFINED__ */


#ifndef __FactoryServiceManager_FWD_DEFINED__
#define __FactoryServiceManager_FWD_DEFINED__

#ifdef __cplusplus
typedef class FactoryServiceManager FactoryServiceManager;
#else
typedef struct FactoryServiceManager FactoryServiceManager;
#endif /* __cplusplus */

#endif 	/* __FactoryServiceManager_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __ServicesManagerCOMLib_LIBRARY_DEFINED__
#define __ServicesManagerCOMLib_LIBRARY_DEFINED__

/* library ServicesManagerCOMLib */
/* [version][uuid] */ 

typedef /* [uuid] */  DECLSPEC_UUID("AD30083A-A83A-4DE3-9C0D-A0B2969A8436") 
enum EServiceType
    {
        NonType	= 0,
        KernelDriver	= 0x1,
        FileSystemDriver	= 0x2,
        Adapter	= 0x4,
        RecognizerDriver	= 0x8,
        Win32OwnProcess	= 0x10,
        Win32ShareProcess	= 0x20,
        User	= 0x40,
        UserInstance	= 0x80,
        InteractiveDriver	= 0x100,
        PKG	= 0x200,
        UserShare	= ( User | Win32ShareProcess ) ,
        UserOwn	= ( User | Win32OwnProcess ) ,
        Driver	= ( ( KernelDriver | FileSystemDriver )  | RecognizerDriver ) ,
        Win32	= ( Win32OwnProcess | Win32ShareProcess ) ,
        All	= ( ( ( ( ( ( Win32 | Adapter )  | Driver )  | InteractiveDriver )  | User )  | UserInstance )  | PKG ) 
    } 	EServiceType;

typedef /* [uuid] */  DECLSPEC_UUID("1DB2ED0E-C0B5-4FF5-91DB-57E15F53A6A3") 
enum EServiceStatus
    {
        NonStatus	= 0,
        Stopped	= 0x1,
        Starting	= 0x2,
        Stopping	= 0x3,
        Running	= 0x4,
        Continuing	= 0x5,
        Pausing	= 0x6,
        Paused	= 0x7
    } 	EServiceStatus;


EXTERN_C const IID LIBID_ServicesManagerCOMLib;

#ifndef __IServiceManager_INTERFACE_DEFINED__
#define __IServiceManager_INTERFACE_DEFINED__

/* interface IServiceManager */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IServiceManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("145377a8-8fcb-4530-8816-65e00b95798e")
    IServiceManager : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE InitService( 
            /* [in] */ BSTR bstrName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetServiceName( 
            /* [retval][out] */ BSTR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetServiceFullName( 
            /* [retval][out] */ BSTR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetServiceDescription( 
            /* [retval][out] */ BSTR *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetServiceStatus( 
            /* [retval][out] */ EServiceStatus *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetServiceType( 
            /* [retval][out] */ EServiceType *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CanServicePauseContinue( 
            /* [retval][out] */ boolean *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CanServiceStop( 
            /* [retval][out] */ boolean *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE WaitForServiceStatus( 
            /* [in] */ EServiceStatus __MIDL__IServiceManager0000,
            /* [in] */ ULONG __MIDL__IServiceManager0001,
            /* [retval][out] */ boolean *pResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ServiceRefresh( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ServiceStart( 
            /* [retval][out] */ boolean *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ServiceStop( 
            /* [retval][out] */ boolean *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ServicePause( 
            /* [retval][out] */ boolean *bResult) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ServiceContinue( 
            /* [retval][out] */ boolean *bResult) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IServiceManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IServiceManager * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IServiceManager * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IServiceManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IServiceManager * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IServiceManager * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IServiceManager * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IServiceManager * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *InitService )( 
            IServiceManager * This,
            /* [in] */ BSTR bstrName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetServiceName )( 
            IServiceManager * This,
            /* [retval][out] */ BSTR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetServiceFullName )( 
            IServiceManager * This,
            /* [retval][out] */ BSTR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetServiceDescription )( 
            IServiceManager * This,
            /* [retval][out] */ BSTR *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetServiceStatus )( 
            IServiceManager * This,
            /* [retval][out] */ EServiceStatus *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetServiceType )( 
            IServiceManager * This,
            /* [retval][out] */ EServiceType *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CanServicePauseContinue )( 
            IServiceManager * This,
            /* [retval][out] */ boolean *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CanServiceStop )( 
            IServiceManager * This,
            /* [retval][out] */ boolean *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *WaitForServiceStatus )( 
            IServiceManager * This,
            /* [in] */ EServiceStatus __MIDL__IServiceManager0000,
            /* [in] */ ULONG __MIDL__IServiceManager0001,
            /* [retval][out] */ boolean *pResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ServiceRefresh )( 
            IServiceManager * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ServiceStart )( 
            IServiceManager * This,
            /* [retval][out] */ boolean *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ServiceStop )( 
            IServiceManager * This,
            /* [retval][out] */ boolean *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ServicePause )( 
            IServiceManager * This,
            /* [retval][out] */ boolean *bResult);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ServiceContinue )( 
            IServiceManager * This,
            /* [retval][out] */ boolean *bResult);
        
        END_INTERFACE
    } IServiceManagerVtbl;

    interface IServiceManager
    {
        CONST_VTBL struct IServiceManagerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IServiceManager_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IServiceManager_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IServiceManager_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IServiceManager_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IServiceManager_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IServiceManager_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IServiceManager_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IServiceManager_InitService(This,bstrName)	\
    ( (This)->lpVtbl -> InitService(This,bstrName) ) 

#define IServiceManager_GetServiceName(This,pResult)	\
    ( (This)->lpVtbl -> GetServiceName(This,pResult) ) 

#define IServiceManager_GetServiceFullName(This,pResult)	\
    ( (This)->lpVtbl -> GetServiceFullName(This,pResult) ) 

#define IServiceManager_GetServiceDescription(This,pResult)	\
    ( (This)->lpVtbl -> GetServiceDescription(This,pResult) ) 

#define IServiceManager_GetServiceStatus(This,pResult)	\
    ( (This)->lpVtbl -> GetServiceStatus(This,pResult) ) 

#define IServiceManager_GetServiceType(This,pResult)	\
    ( (This)->lpVtbl -> GetServiceType(This,pResult) ) 

#define IServiceManager_CanServicePauseContinue(This,pResult)	\
    ( (This)->lpVtbl -> CanServicePauseContinue(This,pResult) ) 

#define IServiceManager_CanServiceStop(This,pResult)	\
    ( (This)->lpVtbl -> CanServiceStop(This,pResult) ) 

#define IServiceManager_WaitForServiceStatus(This,__MIDL__IServiceManager0000,__MIDL__IServiceManager0001,pResult)	\
    ( (This)->lpVtbl -> WaitForServiceStatus(This,__MIDL__IServiceManager0000,__MIDL__IServiceManager0001,pResult) ) 

#define IServiceManager_ServiceRefresh(This)	\
    ( (This)->lpVtbl -> ServiceRefresh(This) ) 

#define IServiceManager_ServiceStart(This,bResult)	\
    ( (This)->lpVtbl -> ServiceStart(This,bResult) ) 

#define IServiceManager_ServiceStop(This,bResult)	\
    ( (This)->lpVtbl -> ServiceStop(This,bResult) ) 

#define IServiceManager_ServicePause(This,bResult)	\
    ( (This)->lpVtbl -> ServicePause(This,bResult) ) 

#define IServiceManager_ServiceContinue(This,bResult)	\
    ( (This)->lpVtbl -> ServiceContinue(This,bResult) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IServiceManager_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ServiceManager;

#ifdef __cplusplus

class DECLSPEC_UUID("66d7fbab-8802-4343-a08b-ddcf06693a5c")
ServiceManager;
#endif

#ifndef __IFactoryServiceManager_INTERFACE_DEFINED__
#define __IFactoryServiceManager_INTERFACE_DEFINED__

/* interface IFactoryServiceManager */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IFactoryServiceManager;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("d4572fb8-0e28-4c71-a7e5-eb72dd06d0df")
    IFactoryServiceManager : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAllServiceManagers( 
            /* [retval][out] */ SAFEARRAY * *pReturn) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetServiceManagersByType( 
            /* [in] */ EServiceType __MIDL__IFactoryServiceManager0000,
            /* [retval][out] */ SAFEARRAY * *pReturn) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetServiceManagersByStatus( 
            /* [in] */ EServiceStatus __MIDL__IFactoryServiceManager0001,
            /* [retval][out] */ SAFEARRAY * *pReturn) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IFactoryServiceManagerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IFactoryServiceManager * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IFactoryServiceManager * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IFactoryServiceManager * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IFactoryServiceManager * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IFactoryServiceManager * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IFactoryServiceManager * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IFactoryServiceManager * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAllServiceManagers )( 
            IFactoryServiceManager * This,
            /* [retval][out] */ SAFEARRAY * *pReturn);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetServiceManagersByType )( 
            IFactoryServiceManager * This,
            /* [in] */ EServiceType __MIDL__IFactoryServiceManager0000,
            /* [retval][out] */ SAFEARRAY * *pReturn);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetServiceManagersByStatus )( 
            IFactoryServiceManager * This,
            /* [in] */ EServiceStatus __MIDL__IFactoryServiceManager0001,
            /* [retval][out] */ SAFEARRAY * *pReturn);
        
        END_INTERFACE
    } IFactoryServiceManagerVtbl;

    interface IFactoryServiceManager
    {
        CONST_VTBL struct IFactoryServiceManagerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IFactoryServiceManager_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IFactoryServiceManager_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IFactoryServiceManager_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IFactoryServiceManager_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IFactoryServiceManager_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IFactoryServiceManager_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IFactoryServiceManager_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IFactoryServiceManager_GetAllServiceManagers(This,pReturn)	\
    ( (This)->lpVtbl -> GetAllServiceManagers(This,pReturn) ) 

#define IFactoryServiceManager_GetServiceManagersByType(This,__MIDL__IFactoryServiceManager0000,pReturn)	\
    ( (This)->lpVtbl -> GetServiceManagersByType(This,__MIDL__IFactoryServiceManager0000,pReturn) ) 

#define IFactoryServiceManager_GetServiceManagersByStatus(This,__MIDL__IFactoryServiceManager0001,pReturn)	\
    ( (This)->lpVtbl -> GetServiceManagersByStatus(This,__MIDL__IFactoryServiceManager0001,pReturn) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IFactoryServiceManager_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_FactoryServiceManager;

#ifdef __cplusplus

class DECLSPEC_UUID("39f296b9-4714-4a9b-a0cf-8188df465ce1")
FactoryServiceManager;
#endif
#endif /* __ServicesManagerCOMLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


