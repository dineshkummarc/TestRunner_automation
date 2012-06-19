
Test1ps.dll: dlldata.obj Test1_p.obj Test1_i.obj
	link /dll /out:Test1ps.dll /def:Test1ps.def /entry:DllMain dlldata.obj Test1_p.obj Test1_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del Test1ps.dll
	@del Test1ps.lib
	@del Test1ps.exp
	@del dlldata.obj
	@del Test1_p.obj
	@del Test1_i.obj
