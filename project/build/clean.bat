pushd ..
tools\BuildMaster\bin\Release\net8.0\BuildMaster.exe build\config.bm clean
..\..\..\sgdk200\bin\make -f build\makefile.gen clean TARGET="RadRuby"
popd