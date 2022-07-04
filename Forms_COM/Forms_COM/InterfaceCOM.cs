using System;
using System.Runtime.InteropServices;

namespace Forms_COM
{
    public static class GuidsCOM
    {
        public const string LIBID_ServicesManagerCOMLib = "a871ac02-f7c1-4a9e-b060-95645d1d5826";

        public const string IID_EServiceType = "AD30083A-A83A-4DE3-9C0D-A0B2969A8436";

        public const string IID_EServiceStatus = "1DB2ED0E-C0B5-4FF5-91DB-57E15F53A6A3";

        public const string IID_IServiceManager = "145377a8-8fcb-4530-8816-65e00b95798e";

        public const string CLSID_ServiceManager = "66d7fbab-8802-4343-a08b-ddcf06693a5c";

        public const string IID_IFactoryServiceManager = "d4572fb8-0e28-4c71-a7e5-eb72dd06d0df";

        public const string CLSID_FactoryServiceManager = "39f296b9-4714-4a9b-a0cf-8188df465ce1";
    }

    [Guid(GuidsCOM.IID_EServiceType)]
    public enum EServiceType
    {
        NonType = 0x0,
        KernelDriver = 0x00000001,
        FileSystemDriver = 0x00000002,
        Adapter = 0x00000004,
        RecognizerDriver = 0x00000008,
        Win32OwnProcess = 0x00000010,
        Win32ShareProcess = 0x00000020,
        User = 0x00000040,
        UserInstance = 0x00000080,
        InteractiveDriver = 0x00000100,
        PKG = 0x00000200,
        UserShare = User | Win32ShareProcess,
        UserOwn = User | Win32OwnProcess,
        Driver = KernelDriver | FileSystemDriver | RecognizerDriver,
        Win32 = Win32OwnProcess | Win32ShareProcess,
        All = Win32 | Adapter | Driver | InteractiveDriver | User | UserInstance | PKG
    };

    [Guid(GuidsCOM.IID_EServiceStatus)]
    public enum EServiceStatus
    {
        NonStatus = 0x00000000,
        Stopped = 0x00000001,
        Starting = 0x00000002,
        Stopping = 0x00000003,
        Running = 0x00000004,
        Continuing = 0x00000005,
        Pausing = 0x00000006,
        Paused = 0x00000007
    };

    [Guid(GuidsCOM.IID_IServiceManager),
    InterfaceType(ComInterfaceType.InterfaceIsIDispatch)]
    public interface IServiceManager
    {
        [DispId(0)]
        void InitService(string name);

        [DispId(1)]
        [return: MarshalAs(UnmanagedType.BStr)]
        string GetServiceName();

        [DispId(2)]
        [return: MarshalAs(UnmanagedType.BStr)]
        string GetServiceFullName();

        [DispId(3)]
        [return: MarshalAs(UnmanagedType.BStr)]
        string GetServiceDescription();

        [DispId(4)]
        [return: MarshalAs(UnmanagedType.SysInt)]
        EServiceStatus GetServiceStatus();

        [DispId(5)]
        [return: MarshalAs(UnmanagedType.SysInt)]
        EServiceType GetServiceType();

        [DispId(6)]
        [return: MarshalAs(UnmanagedType.U1)]
        bool CanServicePauseContinue();

        [DispId(7)]
        [return: MarshalAs(UnmanagedType.U1)]
        bool CanServiceStop();

        [DispId(8)]
        [return: MarshalAs(UnmanagedType.U1)]
        bool WaitForServiceStatus(EServiceStatus status, uint time);

        [DispId(9)]
        void ServiceRefresh();

        [DispId(10)]
        [return: MarshalAs(UnmanagedType.U1)]
        bool ServiceStart();

        [DispId(11)]
        [return: MarshalAs(UnmanagedType.U1)]
        bool ServiceStop();

        [DispId(12)]
        [return: MarshalAs(UnmanagedType.U1)]
        bool ServicePause();

        [DispId(13)]
        [return: MarshalAs(UnmanagedType.U1)]
        bool ServiceContinue();
    };

    [Guid(GuidsCOM.IID_IFactoryServiceManager),
    InterfaceType(ComInterfaceType.InterfaceIsIDispatch)]
    public interface IFactoryServiceManagers
    {
        [return: MarshalAs(UnmanagedType.SafeArray, SafeArraySubType = VarEnum.VT_UNKNOWN)]
        object[] GetAllServiceManagers();

        [return: MarshalAs(UnmanagedType.SafeArray, SafeArraySubType = VarEnum.VT_UNKNOWN)]
        object[] GetServiceManagersByType(EServiceType type);

        [return: MarshalAs(UnmanagedType.SafeArray, SafeArraySubType = VarEnum.VT_UNKNOWN)]
        object[] GetServiceManagersByStatus(EServiceStatus status);
    }

    

}