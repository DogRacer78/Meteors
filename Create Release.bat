@echo on
rmdir /s /Q Release
mkdir Release
echo d | xcopy /s res Release\res
echo d | xcopy /s build Release\bin
jar -cfM Release.zip Release