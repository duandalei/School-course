// ===============================
// 🚇 成都地铁查询系统主脚本
// ===============================

// 常量定义
const CONFIG = {
    DATA_FILE: 'metro_data.json',
    LOAD_ERROR_MSG: '数据加载失败',
    SERVER_URL: 'http://localhost:8000'
};

const SELECTORS = {
    LINE_SELECT: '#line-select',
    STATION_INPUT: '#station-input',
    START_STATION: '#start-station',
    END_STATION: '#end-station',
    QUERY_LINE_BTN: '#query-line-btn',
    QUERY_STATION_BTN: '#query-station-btn',
    QUERY_PATH_BTN: '#query-path-btn',
    LINE_RESULT: '#line-result',
    STATION_RESULT: '#station-result',
    PATH_RESULT: '#path-result',
    TAB_BTNS: '.tab-btn',
    TAB_CONTENT: '.tab-content',
    CONTAINER: '.container'
};

// 全局数据
let metroData = {};

// ===============================
// 数据加载
// ===============================
async function loadMetroData() {
    try {
        const response = await fetch(CONFIG.DATA_FILE);
        if (response.ok) {
            metroData = await response.json();
            initializeApp();
            return;
        }
    } catch (error) {
        console.warn('fetch失败，尝试其他方法...', error);
    }
    
    try {
        if (typeof window.metroData !== 'undefined') {
            metroData = window.metroData;
            initializeApp();
            return;
        }
    } catch (error) {
        console.error('script标签加载失败', error);
    }
    
    showLoadError();
}

function showLoadError() {
    const container = document.querySelector(SELECTORS.CONTAINER);
    if (!container) return;
    
    container.innerHTML = `
        <div style="padding:40px;text-align:center;">
            <h2 style="color:#c33;">${CONFIG.LOAD_ERROR_MSG}</h2>
            <p style="margin:20px 0;">可能是浏览器安全限制，建议使用本地服务器：</p>
            <p style="background:#f0f0f0;padding:15px;border-radius:8px;">
                <strong>双击"启动网页.bat"文件</strong>，然后在浏览器访问 ${CONFIG.SERVER_URL}
            </p>
            <p style="margin-top:20px;color:#666;">
                或者直接访问已加载数据的版本：index.html（需要支持内嵌JSON）
            </p>
        </div>
    `;
}

// ===============================
// 初始化主界面
// ===============================
function initializeApp() {
    if (!metroData.lines || !metroData.stations) {
        console.error('数据格式错误');
        return;
    }

    initializeLineSelect();
    initializeAutocomplete();
    bindEvents();
}

function initializeLineSelect() {
    const lineSelect = document.querySelector(SELECTORS.LINE_SELECT);
    if (!lineSelect) return;

    const lines = Object.keys(metroData.lines).sort((a, b) => parseInt(a) - parseInt(b));
    
    lines.forEach(lineId => {
        const option = document.createElement('option');
        option.value = lineId;
        option.textContent = `线路${lineId}`;
        lineSelect.appendChild(option);
    });
}

function initializeAutocomplete() {
    if (!metroData.stations) return;
    
    initializeAutocompleteForInput('station-input', metroData.stations);
    initializeAutocompleteForInput('start-station', metroData.stations);
    initializeAutocompleteForInput('end-station', metroData.stations);
}

function bindEvents() {
    const queryLineBtn = document.querySelector(SELECTORS.QUERY_LINE_BTN);
    const queryStationBtn = document.querySelector(SELECTORS.QUERY_STATION_BTN);
    const queryPathBtn = document.querySelector(SELECTORS.QUERY_PATH_BTN);
    
    if (queryLineBtn) queryLineBtn.addEventListener('click', queryLine);
    if (queryStationBtn) queryStationBtn.addEventListener('click', queryStation);
    if (queryPathBtn) queryPathBtn.addEventListener('click', queryPath);

    document.querySelectorAll(SELECTORS.TAB_BTNS).forEach(btn => {
        btn.addEventListener('click', () => switchTab(btn.dataset.tab));
    });
}

// ===============================
// 标签页切换逻辑
// ===============================
function switchTab(tabName) {
    document.querySelectorAll(SELECTORS.TAB_BTNS).forEach(btn => {
        const isActive = btn.dataset.tab === tabName;
        btn.classList.toggle('active', isActive);
        btn.setAttribute('aria-selected', isActive);
    });

    document.querySelectorAll(SELECTORS.TAB_CONTENT).forEach(content => {
        const isActive = content.id === `${tabName}-tab`;
        content.classList.toggle('active', isActive);
        content.setAttribute('aria-hidden', !isActive);
    });
}

// ===============================
// 自动补全输入框（使用 <datalist>）
// ===============================
function initializeAutocompleteForInput(inputId, suggestions) {
    const input = document.getElementById(inputId);
    if (!input || !suggestions) return;

    const datalist = document.createElement('datalist');
    datalist.id = `${inputId}-list`;
    
    suggestions.forEach(item => {
        const option = document.createElement('option');
        option.value = item;
        datalist.appendChild(option);
    });
    
    document.body.appendChild(datalist);
    input.setAttribute('list', datalist.id);
}

// ===============================
// 查询功能
// ===============================
function queryLine() {
    const lineSelect = document.querySelector(SELECTORS.LINE_SELECT);
    const resultBox = document.querySelector(SELECTORS.LINE_RESULT);
    
    if (!lineSelect || !resultBox) return;
    
    const lineId = lineSelect.value;
    
    if (!lineId || !metroData.lines[lineId]) {
        resultBox.innerHTML = '<div class="error-message">线路不存在</div>';
        return;
    }
    
    const stations = metroData.lines[lineId];
    const html = `
        <h3>线路${lineId} - 共${stations.length}个站点</h3>
        <div class="station-list">
            ${stations.map((station, index) => 
                `<div class="station-item">${index + 1}. ${escapeHtml(station)}</div>`
            ).join('')}
        </div>
    `;
    
    resultBox.innerHTML = html;
}

function queryStation() {
    const stationInput = document.querySelector(SELECTORS.STATION_INPUT);
    const resultBox = document.querySelector(SELECTORS.STATION_RESULT);
    
    if (!stationInput || !resultBox) return;
    
    const stationName = stationInput.value.trim();
    
    if (!stationName) {
        resultBox.innerHTML = '<div class="error-message">请输入站点名称</div>';
        return;
    }
    
    if (!metroData.stationLines || !metroData.stationLines[stationName]) {
        resultBox.innerHTML = `<div class="error-message">站点"${escapeHtml(stationName)}"不存在</div>`;
        return;
    }
    
    const lines = metroData.stationLines[stationName];
    const html = `
        <h3>${escapeHtml(stationName)}</h3>
        <p>该站点位于：</p>
        <div style="margin-top: 15px;">
            ${lines.map(lineId => `<span class="line-badge">${lineId}号线</span>`).join('')}
        </div>
        <p style="margin-top: 20px; color: #666;">
            共经过 <strong>${lines.length}</strong> 条线路
        </p>
    `;
    
    resultBox.innerHTML = html;
}

function queryPath() {
    const startInput = document.querySelector(SELECTORS.START_STATION);
    const endInput = document.querySelector(SELECTORS.END_STATION);
    const resultBox = document.querySelector(SELECTORS.PATH_RESULT);
    
    if (!startInput || !endInput || !resultBox) return;
    
    const start = startInput.value.trim();
    const end = endInput.value.trim();
    
    if (!start || !end) {
        resultBox.innerHTML = '<div class="error-message">请完整输入起点和终点</div>';
        return;
    }
    
    if (!metroData.stations || !metroData.stations.includes(start)) {
        resultBox.innerHTML = `<div class="error-message">起点"${escapeHtml(start)}"不存在</div>`;
        return;
    }
    
    if (!metroData.stations.includes(end)) {
        resultBox.innerHTML = `<div class="error-message">终点"${escapeHtml(end)}"不存在</div>`;
        return;
    }
    
    if (start === end) {
        resultBox.innerHTML = '<div class="error-message">起点和终点不能相同</div>';
        return;
    }
    
    resultBox.innerHTML = '<div class="loading"><div class="spinner"></div></div>';
    
    // 使用 requestAnimationFrame 优化性能
    requestAnimationFrame(() => {
        const path = dijkstra(start, end);
        displayPath(path, resultBox);
    });
}

// ===============================
// Dijkstra算法 - 最短路径计算
// ===============================
function dijkstra(start, end) {
    if (!metroData.stations || !metroData.adjacency) {
        return null;
    }

    const stations = metroData.stations;
    const adjacency = metroData.adjacency;
    const dist = {};
    const prev = {};
    const unvisited = new Set(stations);
    
    stations.forEach(station => {
        dist[station] = Infinity;
        prev[station] = null;
    });
    
    dist[start] = 0;
    
    while (unvisited.size > 0) {
        let minStation = null;
        let minDist = Infinity;
        
        for (const station of unvisited) {
            if (dist[station] < minDist) {
                minDist = dist[station];
                minStation = station;
            }
        }
        
        if (minStation === null || minStation === end) {
            break;
        }
        
        unvisited.delete(minStation);
        
        const neighbors = adjacency[minStation] || [];
        for (const neighbor of neighbors) {
            if (unvisited.has(neighbor)) {
                const alt = dist[minStation] + 1;
                if (alt < dist[neighbor]) {
                    dist[neighbor] = alt;
                    prev[neighbor] = minStation;
                }
            }
        }
    }
    
    if (dist[end] === Infinity) {
        return null;
    }
    
    const path = [];
    let current = end;
    while (current !== null) {
        path.unshift(current);
        current = prev[current];
    }
    
    return path;
}

// ===============================
// 显示路径结果
// ===============================
function displayPath(path, resultBox) {
    if (!path || !path.length) {
        resultBox.innerHTML = '<div class="error-message">无路径可达</div>';
        return;
    }
    
    if (!metroData.stationLines) {
        resultBox.innerHTML = '<div class="error-message">数据错误</div>';
        return;
    }
    
    const stationLines = metroData.stationLines;
    const pathLength = path.length - 1;
    const routeSegments = buildRouteSegments(path, stationLines);
    const transferCount = routeSegments.length - 1;
    
    const html = `
        <div class="route-header">
            <h3>路线规划</h3>
            <div class="route-stats">
                <div class="stat-item"><strong>${pathLength}</strong> 站</div>
                <div class="stat-item"><strong>${transferCount}</strong> 次换乘</div>
            </div>
        </div>
        <ul class="route-list">
            ${path.map((station, index) => formatPathItem(station, index, path, routeSegments, stationLines)).join('')}
        </ul>
    `;
    
    resultBox.innerHTML = html;
}

function buildRouteSegments(path, stationLines) {
    const routeSegments = [];
    let currentLine = null;
    let segmentStart = path[0];
    
    for (let i = 0; i < path.length - 1; i++) {
        const current = path[i];
        const next = path[i + 1];
        const commonLines = findCommonLine(current, next, stationLines);
        const nextLine = commonLines[0] || (stationLines[next] && stationLines[next][0]);
        
        if (currentLine === null) {
            currentLine = nextLine;
            segmentStart = current;
        } else if (currentLine !== nextLine && nextLine) {
            routeSegments.push({ line: currentLine, start: segmentStart, end: current });
            currentLine = nextLine;
            segmentStart = current;
        }
    }
    
    if (currentLine) {
        routeSegments.push({ line: currentLine, start: segmentStart, end: path[path.length - 1] });
    }
    
    return routeSegments;
}

function formatPathItem(station, index, path, routeSegments, stationLines) {
    const escapedStation = escapeHtml(station);
    
    if (index === 0) {
        const firstLine = routeSegments[0]?.line || '';
        return `
            <li class="route-item">
                <span class="line-badge">${firstLine}号线</span>
                <strong>${escapedStation}</strong>（起点）
            </li>`;
    }
    
    if (index === path.length - 1) {
        return `<li class="route-item"><strong>${escapedStation}</strong>（终点）</li>`;
    }
    
    const isTransfer = routeSegments.some(seg => seg.end === station && stationLines[station]?.length > 1);
    
    if (isTransfer) {
        const prevLine = routeSegments.find(seg => seg.end === station)?.line;
        const nextLine = routeSegments.find(seg => seg.start === station)?.line;
        
        if (prevLine && nextLine && prevLine !== nextLine) {
            return `
                <li class="route-item transfer">
                    <span class="line-badge transfer-badge">${nextLine}号线</span>
                    在<strong>${escapedStation}</strong>换乘
                </li>`;
        }
    }
    
    return `<li class="route-item">${escapedStation}</li>`;
}

// ===============================
// 工具函数
// ===============================
function findCommonLine(station1, station2, stationLines) {
    const lines1 = stationLines[station1] || [];
    const lines2 = stationLines[station2] || [];
    return lines1.filter(line => lines2.includes(line));
}

function escapeHtml(text) {
    const div = document.createElement('div');
    div.textContent = text;
    return div.innerHTML;
}

// 页面加载完成后初始化
loadMetroData();
