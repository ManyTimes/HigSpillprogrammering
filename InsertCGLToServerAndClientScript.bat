@rem BATCH FILE
@rem COPYING DLL FILES TO CLIENT
copy Build\CustomGameLibrary\CustomGameLibrary.dll Client\Debug\CustomGameLibrary.dll /D /Y 
@rem COPYING DLL FILES TO SERVER
copy Build\CustomGameLibrary\CustomGameLibrary.dll Server\Debug\CustomGameLibrary.dll /D /Y 
@rem COPYING DLL FILES TO BIRCHES
copy Build\CustomGameLibrary\CustomGameLibrary.dll BirchesServer\Debug\CustomGameLibrary.dll /D /Y 
@rem COPYING DLL FILES TO BIRCHES
copy Build\CustomGameLibrary\CustomGameLibrary.dll BirchesClient\Debug\CustomGameLibrary.dll /D /Y 
echo Copy Success