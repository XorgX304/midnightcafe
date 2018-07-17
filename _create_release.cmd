md Release
copy boost_license.txt, Release\boost_license.txt
copy license.txt, Release\license.txt
copy midnightcafe.exe, Release\MidnightCafe.exe
if exist upx.exe  upx.exe Release\MidnightCafe.exe -9 -q -f