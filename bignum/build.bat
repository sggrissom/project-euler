@echo off

if not exist bin mkdir bin
pushd bin

//4505: unused function
//4189: unused variable
set IgnoredWarnings= -wd4505 -wd4189
set Defines= -DSLOW -DWIN32 -DDEBUG
set CompilerFlags= -MT -Zi -nologo -GR- -EHa- -Od -Oi -WX -W4 -FC %IgnoredWarnings% %Defines%

cl %CompilerFlags% ../bignum_test.cpp /link -incremental:no

popd
