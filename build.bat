@echo off

if not exist bin mkdir bin
pushd bin

set IgnoredWarnings= -wd4505 -wd4189
set Defines= -DSLOW -DWIN32 -DDEBUG
set CompilerFlags= -O2 -MT -Zi -nologo -GR- -EHa- -Oi -WX -W4 -FC %IgnoredWarnings% %Defines%

cl %CompilerFlags% ../problem.cpp /link -incremental:no

popd
