#!/usr/bin/env python3

import re
import sys
import argparse
from logging import Logger, basicConfig, getLogger
from os import getenv, environ, pathsep
from pathlib import Path
from typing import List, Set, Optional


logger = getLogger(__name__)  # type: Logger


class Expander:
    local_include = re.compile(
        r'#include\s*"([a-z_]*(|.hpp))"\s*')
    atcoder_include = re.compile(
        r'#include\s*["<](kuro/[a-z_]*(|.hpp))[">]\s*')

    include_guard = re.compile(r'#.*KURO_[A-Z_]*_HPP')

    def is_ignored_line(self, line) -> bool:
        if self.include_guard.match(line):
            return True
        if line.strip() == "#pragma once":
            return True
        if line.strip().startswith('//'):
            return True
        return False

    def __init__(self, lib_paths: List[Path]):
        self.lib_paths = lib_paths

    included = set()  # type: Set[Path]

    def find_kuro(self, kuro_name: str) -> Path:
        for lib_path in self.lib_paths:
            path = lib_path / kuro_name
            if path.exists():
                return path
        logger.error('cannot find: {}'.format(kuro_name))
        raise FileNotFoundError()

    def expand_kuro(self, kuro_file_path: Path) -> List[str]:
        if kuro_file_path in self.included:
            logger.info('already included: {}'.format(kuro_file_path.name))
            return []
        self.included.add(kuro_file_path)
        logger.info('include: {}'.format(kuro_file_path.name))

        kuro_source = open(str(kuro_file_path)).read()

        result = []  # type: List[str]
        for line in kuro_source.splitlines():
            if self.is_ignored_line(line):
                continue

            m = self.atcoder_include.match(line)
            if m:
                name = m.group(1)
                result.extend(self.expand_kuro(self.find_kuro(name)))
                continue
            
            m = self.local_include.match(line)
            if m:
                name = m.group(1)
                result.extend(self.expand_kuro(kuro_file_path.parent / name))
                continue

            result.append(line)

        return result

    def expand(self, source: str) -> str:
        self.included = set()
        result = []  # type: List[str]
        for line in source.splitlines():
            m = self.atcoder_include.match(line)
            if m:
                kuro_path = self.find_kuro(m.group(1))
                result.extend(self.expand_kuro(kuro_path))
                continue

            result.append(line)
        return '\n'.join(result)


if __name__ == "__main__":
    basicConfig(
        format="%(asctime)s [%(levelname)s] %(message)s",
        datefmt="%H:%M:%S",
        level=getenv('LOG_LEVEL', 'INFO'),
    )
    parser = argparse.ArgumentParser(description='Expander')
    parser.add_argument('source', help='Source File')
    parser.add_argument('submit', default='submit.cpp', help='Submit File')
    parser.add_argument('-c', '--console',
                        action='store_true', help='Print to Console')
    parser.add_argument('--lib', help='Path to Atcoder Library')
    opts = parser.parse_args()

    lib_paths = []
    if opts.lib:
        lib_paths.append(Path(opts.lib))
    if 'CPLUS_INCLUDE_PATH' in environ:
        lib_paths.extend(
            map(Path, filter(None, environ['CPLUS_INCLUDE_PATH'].split(pathsep))))
    lib_paths.append(Path.cwd())
    expander = Expander(lib_paths)
    source = open(opts.source).read()
    output = expander.expand(source)

    if opts.console:
        print(output)
    else:
        # with open('/mnt/c/C++/combined.cpp', 'w') as f:
        with open(opts.submit, 'w') as f:
            f.write(output)
