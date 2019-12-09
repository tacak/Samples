
mmcTestps.dll: dlldata.obj mmcTest_p.obj mmcTest_i.obj
	link /dll /out:mmcTestps.dll /def:mmcTestps.def /entry:DllMain dlldata.obj mmcTest_p.obj mmcTest_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del mmcTestps.dll
	@del mmcTestps.lib
	@del mmcTestps.exp
	@del dlldata.obj
	@del mmcTest_p.obj
	@del mmcTest_i.obj
