@echo off
msbuild /p:Configuration=Test tests.vcxproj

set only_arg=
IF not "%~1"=="" (
  set only_arg=--only=%1
)

.\test\tests.exe --reporter=singleline --no-color %only_arg%
