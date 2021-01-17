@echo off
MSbuild Workspace\DullEngine.sln /nologo /verbosity:m /ds /nr:true /p:Configuration=Debug

call .\Build\Debug\Sandbox.exe
