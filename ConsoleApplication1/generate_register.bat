@echo off

echo ���� ���: %cd%
where python

echo [Python] �ڵ� �׼� ��� ����...

cd /d %~dp0  REM �� �� �� �� �ʿ�: bat�� ���� ��ġ�� �̵�

python generate_action_register.py

IF %ERRORLEVEL% NEQ 0 (
    echo [Python] ����!
    pause
    exit /b 1
)

echo [Python] ���������� �ڵ� ��� �Ϸ�!
