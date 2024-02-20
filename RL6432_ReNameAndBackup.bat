@echo off

::删除旧的文件，并且从复制编译生成路径的hex文件到OutHexBin文件夹
cd OutHexBin
del *.H*
del *.bin
del *.h

cd ..

set profile=RL6432_BEACON
set pro=RL6432

copy "Output\%profile%\%pro%*.H*" "OutHexBin\"
copy "Output\%profile%\%pro%*.bin" "OutHexBin\"
copy "Panel\RTDColorDefaultTable\Gamma\GammaBeaconUse.h" "OutHexBin\"

::获得完整名字，包含机型，软件版本，Git/SVN版本，系统日期和时间
for /f "tokens=3" %%a in ('findstr /c:"#define _USER_PROJECT_TYPE" "Project\Header\Project_User_Beacon_List.h"') do (
set "fn0=%%~a"
)

echo %fn0% 

if exist "Project\Header\Info\INFO_%fn0%.h" (
for /f "tokens=3" %%a in ('findstr /c:"#define _VERSION_STR" "Project\Header\Info\INFO_%fn0%.h"') do (
set "fn1=%%~a"
)
) else  (
set "fn1=VX.XX.XX"
)

echo %fn1%

for /f "tokens=3" %%a in ('findstr /c:"#define _SVN_VERSION" "Project\Header\Svn_Version.h"') do (
set "SvnVer=%%~a"
)
set SvnVer=SVN%SvnVer:~0,4%

echo %SvnVer%

::for /f "tokens=3" %%a in ('findstr /c:"#define _TEST_VERSION_STR" "Project\Header\Project_User_Beacon_List.h"') do (
::set "fn1=%%~a"
::)

::echo %fn1%

::for /f "tokens=3" %%a in ('findstr /c:"#define _MAIN_VERSION_STR" "Project\Header\Project_User_Beacon_List.h"') do (
::set "fn2=%%~a"
::)

::echo %fn2%

::git log -1
::for /f "tokens=2" %%a in ('findstr /c:"commit" "log.txt"') do (
::set "GitVer=%%~a"
::)
::set GitVer=%GitVer:~0,4%

::set hh=%time:~0,2%
::if /i %hh% LSS 10 (set hh=0%time:~1,1%)

::set "name=%pro%_%fn0%_%fn1%%fn2%_Git_%GitVer%_%date:~0,4%%date:~5,2%%date:~8,2%_%hh%%time:~3,2%
set "name=%fn0%_%fn1%_%SvnVer%_%date:~0,4%%date:~5,2%%date:~8,2%"

::改名

cd OutHexBin

ren %pro%*.bin "%name%.bin"

if exist "%pro%*.H00" (
ren %pro%*.H00 "%name%.H00"
)

if exist "%pro%*.H01" (
ren %pro%*.H01 "%name%.H01"
)

if exist "%pro%*.H02" (
ren %pro%*.H02 "%name%.H02"
)

if exist "%pro%*.H03" (
ren %pro%*.H03 "%name%.H03"
)

if exist "%pro%*.H04" (
ren %pro%*.H04 "%name%.H04"
)

if exist "%pro%*.H05" (
ren %pro%*.H05 "%name%.H05"
)

if exist "%pro%*.H06" (
ren %pro%*.H06 "%name%.H06"
)

if exist "%pro%*.H07" (
ren %pro%*.H07 "%name%.H07"
)




