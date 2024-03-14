@if %1.==. (goto error) ELSE (goto restart)

:restart
@taskkill /f /im %1 >nul
@timeout /t 3 /nobreak >nul
@start %1 >nul
@echo restart complete
@goto exit

:error
@echo Please specify a program...
@goto exit


:exit