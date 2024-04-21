pushd ..
tools\BuildMaster\bin\Release\net8.0\BuildMaster.exe build\config.bm builddata
..\..\..\sgdk200\bin\make -f build\makefile.gen TARGET="RadRuby"
popd