@echo off
chcp 65001 >nul
title 成都地铁查询系统 - 本地服务器

echo ============================
echo 成都地铁查询系统 - 网页版
echo ============================
echo.

REM 检查Python
echo [1/4] 检查Python环境...
python --version
if errorlevel 1 (
    echo.
    echo [X] 错误：未检测到Python
    echo.
    echo 请先安装Python 3.x
    echo 下载地址: https://www.python.org/downloads/
    echo.
    pause
    exit /b 1
)
echo [√] Python环境正常
echo.

REM 检查文件
echo [2/4] 检查必要文件...
if not exist "index.html" (
    echo [X] 错误：未找到 index.html
    echo 请确保在项目根目录运行此脚本
    pause
    exit /b 1
)
if not exist "metro_data.json" (
    echo [X] 错误：未找到 metro_data.json
    echo 请先运行: python convert_data.py
    pause
    exit /b 1
)
echo [√] 文件检查通过
echo.

REM 启动服务器
echo [3/4] 启动本地服务器...
echo 在 localhost:8000 上运行
echo.
echo 注意：请保持此窗口打开！
echo.
echo ============================
echo 服务器运行中...
echo ============================
echo.

REM 在新窗口中启动服务器
start "地铁服务器 - 请勿关闭" /MIN cmd /k "python -m http.server 8000"

REM 等待服务器启动
timeout /t 3 /nobreak >nul

REM 打开浏览器
echo [4/4] 打开浏览器...
start http://localhost:8000

echo.
echo ============================
echo 启动完成！
echo ============================
echo.
echo 浏览器已自动打开
echo 如果未打开，请手动访问: http://localhost:8000
echo.
echo 关闭此窗口将停止服务器
echo.

pause

