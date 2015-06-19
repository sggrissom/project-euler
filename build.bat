@echo off

set ignoredWarnings= -wd4505 -wd4201 -wd4100
set commonCompilerFlags= -MTd -nologo -GR- -EHa- -Od -Oi -WX -W4 %ignoredWarnings% -FC -Z7

IF NOT EXIST bin mkdir bin
pushd bin

del *.pdb > NUL 2> NUL
cl %commonCompilerFlags% ../problem.c /link -incremental:no

popd
