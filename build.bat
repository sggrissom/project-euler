@echo off

if not exist bin mkdir bin
pushd bin

//4505: unreference function
set IgnoredWarnings= -wd4505
set Defines= -DSLOW -DWIN32 -DDEBUG
set CompilerFlags= -MT -Zi -nologo -GR- -EHa- -Od -Oi -WX -W4 -FC %IgnoredWarnings% %Defines%

cl %CompilerFlags% ../problem.c /link -incremental:no

popd

rem set ignoredWarnings= -wd4505 -wd4201 -wd4100 -wd4101
