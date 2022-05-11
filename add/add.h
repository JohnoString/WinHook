// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 ADD_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// ADD_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef ADD_EXPORTS
#define ADD_API __declspec(dllexport)
#else
#define ADD_API __declspec(dllimport)
#endif

#ifdef __cplusplus //如果是c++文件，就将endif内的代码用c编译器编译
extern "C" {
#endif
    __declspec(dllexport) int WINAPI add(int a, int b) //__declspec(dllexport)  声明此函数为导出函数
    {
        return a + b;
    }
#ifdef __cplusplus
}
#endif


