@echo off

set ignoredWarnings= -wd4505 -wd4201 -wd4100 -wd4101
set debugCompilerFlags= -MTd -nologo -GR- -EHa- -Od -Oi -WX -W4 %ignoredWarnings% -FC -Z7 -DWIN32=1 -DDEGUG=1
set releaseCompilerFlags= -MTd -nologo -GR- -EHa- -O2 -Oi -WX -W4 %ignoredWarnings% -FC -DWIN32=1

IF NOT EXIST bin mkdir bin
pushd bin

del *.pdb > NUL 2> NUL
cl %debugCompilerFlags% ../problem.c /link -incremental:no /OUT:debug.exe
cl %releaseCompilerFlags% ../problem.c /link -incremental:no /OUT:release.exe

popd
