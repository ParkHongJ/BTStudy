@echo off

echo 현재 경로: %cd%
where python

echo [Python] 자동 액션 등록 시작...

cd /d %~dp0  REM ★ 이 줄 꼭 필요: bat의 실제 위치로 이동

python generate_action_register.py

IF %ERRORLEVEL% NEQ 0 (
    echo [Python] 실패!
    pause
    exit /b 1
)

echo [Python] 성공적으로 자동 등록 완료!
