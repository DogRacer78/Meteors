@echo on
rmdir /s /Q Release
mkdir Release
cd build
make no_console
cd ..
echo d | xcopy /s res Release\res
echo d | xcopy /s build Release\bin
cd Release
cd bin
del /Q Makefile
jar -cfM Release.zip Release