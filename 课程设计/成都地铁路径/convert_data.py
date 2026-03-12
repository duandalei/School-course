#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
成都地铁数据转换脚本
将txt格式的地铁数据转换为JSON格式供Web使用
"""

import json
import re
import sys
import os
from typing import Dict, List, Set


# 常量定义
INPUT_FILE = '成都地铁路径.txt'
OUTPUT_FILE = 'metro_data.json'
LINE_PATTERN = re.compile(r'线路(\d+):')


def read_metro_data(input_file: str) -> Dict[int, List[str]]:
    """
    从文件中读取地铁线路数据
    
    Args:
        input_file: 输入文件路径
        
    Returns:
        线路数据字典，格式为 {线路ID: [站点列表]}
        
    Raises:
        FileNotFoundError: 文件不存在
        IOError: 文件读取错误
    """
    lines_data = {}
    current_line = None
    
    if not os.path.exists(input_file):
        raise FileNotFoundError(f"数据文件不存在: {input_file}")
    
    try:
        with open(input_file, 'r', encoding='utf-8') as f:
            for line_num, line in enumerate(f, 1):
                line = line.strip()
                if not line:
                    continue
                
                # 检测线路标题
                match = LINE_PATTERN.match(line)
                if match:
                    current_line = int(match.group(1))
                    if current_line not in lines_data:
                        lines_data[current_line] = []
                    else:
                        print(f"警告: 线路{current_line}重复定义（第{line_num}行）")
                elif current_line is not None:
                    lines_data[current_line].append(line)
                else:
                    print(f"警告: 第{line_num}行数据未找到所属线路: {line}")
    
    except IOError as e:
        raise IOError(f"读取文件时发生错误: {e}")
    
    return lines_data


def build_station_indexes(lines_data: Dict[int, List[str]]) -> tuple:
    """
    构建站点索引
    
    Args:
        lines_data: 线路数据字典
        
    Returns:
        (所有站点列表, 站点到线路的映射字典)
    """
    all_stations: List[str] = []
    station_to_lines: Dict[str, List[int]] = {}
    
    for line_id, stations in lines_data.items():
        for station in stations:
            if station not in station_to_lines:
                station_to_lines[station] = []
                all_stations.append(station)
            if line_id not in station_to_lines[station]:
                station_to_lines[station].append(line_id)
    
    return sorted(all_stations), station_to_lines


def build_adjacency_list(lines_data: Dict[int, List[str]], all_stations: List[str]) -> Dict[str, List[str]]:
    """
    构建站点邻接关系（邻接表）
    
    Args:
        lines_data: 线路数据字典
        all_stations: 所有站点列表
        
    Returns:
        邻接表字典
    """
    adjacency_list: Dict[str, List[str]] = {station: [] for station in all_stations}
    
    for line_id, stations in lines_data.items():
        for i in range(len(stations)):
            station = stations[i]
            # 添加前一站
            if i > 0:
                prev_station = stations[i - 1]
                if prev_station not in adjacency_list[station]:
                    adjacency_list[station].append(prev_station)
            # 添加后一站
            if i < len(stations) - 1:
                next_station = stations[i + 1]
                if next_station not in adjacency_list[station]:
                    adjacency_list[station].append(next_station)
    
    return adjacency_list


def convert_to_web_format(lines_data: Dict[int, List[str]]) -> Dict:
    """
    转换为Web格式的数据结构
    
    Args:
        lines_data: 线路数据字典
        
    Returns:
        Web格式的数据字典
    """
    # 转换为字符串键的格式
    web_lines = {str(line_id): stations for line_id, stations in lines_data.items()}
    
    # 构建站点索引
    all_stations, station_to_lines = build_station_indexes(lines_data)
    
    # 转换为字符串键的站点线路映射
    web_station_lines = {
        station: [str(line_id) for line_id in line_ids]
        for station, line_ids in station_to_lines.items()
    }
    
    # 构建邻接表
    adjacency_list = build_adjacency_list(lines_data, all_stations)
    
    return {
        "lines": web_lines,
        "stations": sorted(all_stations),
        "stationLines": web_station_lines,
        "adjacency": adjacency_list
    }


def save_json(data: Dict, output_file: str) -> None:
    """
    保存数据为JSON文件
    
    Args:
        data: 要保存的数据字典
        output_file: 输出文件路径
        
    Raises:
        IOError: 文件写入错误
    """
    try:
        with open(output_file, 'w', encoding='utf-8') as f:
            json.dump(data, f, ensure_ascii=False, indent=2)
    except IOError as e:
        raise IOError(f"写入文件时发生错误: {e}")


def main():
    """主函数"""
    try:
        # 读取数据
        print(f"正在读取数据文件: {INPUT_FILE}")
        lines_data = read_metro_data(INPUT_FILE)
        
        if not lines_data:
            print("错误: 未读取到任何线路数据")
            sys.exit(1)
        
        # 转换为Web格式
        print("正在转换数据格式...")
        web_data = convert_to_web_format(lines_data)
        
        # 保存JSON
        print(f"正在保存JSON数据: {OUTPUT_FILE}")
        save_json(web_data, OUTPUT_FILE)
        
        # 统计信息
        total_stations = len(web_data['stations'])
        total_lines = len(web_data['lines'])
        
        print(f"\n✓ 转换完成！")
        print(f"  - 共 {total_lines} 条线路")
        print(f"  - 共 {total_stations} 个站点")
        print(f"  - JSON数据已保存到: {OUTPUT_FILE}")
        
    except FileNotFoundError as e:
        print(f"错误: {e}", file=sys.stderr)
        sys.exit(1)
    except IOError as e:
        print(f"错误: {e}", file=sys.stderr)
        sys.exit(1)
    except Exception as e:
        print(f"发生未知错误: {e}", file=sys.stderr)
        sys.exit(1)


if __name__ == '__main__':
    main()

