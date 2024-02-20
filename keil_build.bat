@echo off
echo build_code start.

del build_log.txt
set UV_project_name=STD_FW_1P_BEACON.Uv2

set UV=C:\Keil\UV3\Uv3.exe
set UV_PRO_PATH=%UV_project_name%
echo Init building ...
echo .>build_log.txt
%UV% -j0 -r %UV_PRO_PATH% -o %cd%\build_log.txt
type build_log.txt

echo Done.
