@echo on
rmdir /s /Q Release
mkdir Release
cd build
make no_console
cd ..
echo d | xcopy /s res Release\res
echo d | xcopy /s build Release\bin
jar -cfM Release.zip Release