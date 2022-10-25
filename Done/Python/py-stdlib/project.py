import enum

import isort
import sys
import platform
import importlib
from types import ModuleType
import inspect


def get_packages():
    modules = isort.stdlibs.py38.stdlib

    result = set()
    for name in modules:
        if name[0] == '_' or name == 'this' or name == 'antigravity':
            continue
        result.add(name)
    return result


def task1():
    external_packages = get_packages()
    version = sys.version_info
    print(f'Python {version.major}.{version.minor}.{version.micro} on {platform.system()} {platform.release()}')
    print(f'Stdlib contains {len(external_packages)} external modules and packages: ')
    print(str(external_packages)[1:-1])


###############################################

def get_real():
    external_packages = get_packages()

    modules = set()
    not_importable = set()

    for name in external_packages:
        try:
            importlib.import_module(name)
            modules.add(name)
        except:
            not_importable.add(name)
    return modules, not_importable


def task2():
    version = sys.version_info
    modules, not_importable = get_real()
    print(
        f'\nThese StdLib packages on Python-{version.major}.{version.minor}.{version.micro}/{platform.system()} {platform.release()} '
        f'are not importable:')
    print(str(not_importable)[1:-1])


###############################################

def module_dependency(modules, name):
    if name not in modules:
        raise Exception(f'{name} is not importable module')
    result = set()

    try:
        importlib.import_module(name)
    except:
        print(f'err name: {name}')

    for key, val in vars(sys.modules[name]).items():
        if isinstance(val, ModuleType):
            md_name = val.__name__

            try:
                index = md_name.index(".")
                md_name = md_name[0:index]
            except:
                pass

            result.add(md_name)

    return result


def get_core_modules(modules):
    result = set()
    for name in modules:
        names = module_dependency(modules, name)
        if len(names) == 0:
            result.add(name)

    return result


def get_custom_by_value(d, num, is_reverse):
    sorted_dict = dict(sorted(d.items(), key=lambda item: item[1], reverse=is_reverse))
    result = dict()

    count = 0
    for key, val in sorted_dict.items():
        if count > num:
            break
        result[key] = val
        count += 1
    return result


def most_dependent_modules(modules):
    result = dict((name, 0) for name in modules)
    for md_name in modules:
        count = len(module_dependency(modules, md_name))
        result[md_name] = count

    return get_custom_by_value(result, 5, True)


def task3():
    modules, not_importable = get_real()
    core_modules = get_core_modules(modules)
    dict = most_dependent_modules(modules)

    print(f'\nThe following StdLib packages are most dependent:')
    for key, val in dict.items():
        print(f'{key + ":":15s} {val}')

    print(f'The {len(core_modules)} core packages are:')
    print(str(core_modules)[1:-1])


###############################################

def count_classes(modules):
    result = dict()
    for m in modules:
        count = 0
        for name, obj in inspect.getmembers(sys.modules[m]):
            if inspect.isclass(obj):
                if issubclass(obj, enum.Enum):
                    continue
                else:
                    count = count + 1
        result[m] = count
    return result


def largest_module_by_class(classes):
    return get_custom_by_value(classes, 5, True)


def modules_without_class(classes):
    result = set()
    for key, val in classes.items():
        if val == 0:
            result.add(key)
    return result


def explore_package(package):
    importlib.import_module(package)
    pack = sys.modules[package]
    file_name = 'builtin_binary'

    try:
        file_name = pack.__file__
        n = len(file_name)
        if file_name[n - 3:n] == '.py':
            return package, file_name, 0
        elif file_name[n - 3:n] == '.so':
            return package, file_name, 1
        else:
            raise Exception(f'unsupported file: {file_name}')
    except:
        return package, file_name, 2


def get_py_modules(modules):
    result = set()
    for m in modules:
        package, file_name, type = explore_package(m)
        if type == 0:
            result.add((package, file_name))
    return result


def count_file_line(path):
    count = 0
    for line in open(path, encoding="utf8"):
        count += 1
    return count


def get_lines(modules):
    result = dict()
    py_modules = get_py_modules(modules)

    for m in py_modules:
        key = m[0]
        num_lines = count_file_line(m[1])
        result[key] = num_lines

    return result


def largest_module_by_line(module_lines):
    return get_custom_by_value(module_lines, 5, True)


def smallest_module_by_line(module_lines):
    return get_custom_by_value(module_lines, 5, False)


def task4():
    modules, _ = get_real()
    counted_classes = count_classes(modules)
    largest_module = largest_module_by_class(counted_classes)
    without_class = modules_without_class(counted_classes)

    module_lines = get_lines(modules)
    largest_module_line = largest_module_by_line(module_lines)
    smallest_module_line = smallest_module_by_line(module_lines)

    print(f'\nlargest modules by class: ')
    print(str(largest_module)[1:-1])

    print(f'modules with no class: ')
    print(str(without_class)[1:-1])

    print(f'largest modules by line: ')
    print(str(largest_module_line)[1:-1])

    print(f'smallest modules by line: ')
    print(str(smallest_module_line)[1:-1])


###############################################

def module_dependency_map(modules):
    result = dict()
    for m in modules:
        result[m] = module_dependency(modules, m)
    return result


def build_graph(modules):
    indexes = list()

    for key, val in modules.items():
        indexes.append(key)

    n = len(indexes)
    adj = list()
    for i in range(n):
        adj.append([])

    for m in indexes:
        for name in modules[m]:
            try:
                i = indexes.index(m)
                j = indexes.index(name)
                if j not in adj[i]:
                    adj[i].append(j)
            except:
                continue

    return adj, indexes


def print_cycle(stack, v, cycles):
    st2 = [stack.pop()]
    while st2[-1] != v:
        st2.append(stack.pop())

    rs = []
    while len(st2) > 0:
        rs.append(st2[-1])
        stack.append(st2[-1])
        st2.pop()

    cycles.append(rs)


def process_DFS_tree(graph, stack, visited, cycles):
    for v in graph[stack[-1]]:
        if not visited[v]:
            stack.append(v)
            visited[v] = True
            process_DFS_tree(graph, stack, visited, cycles)
        elif visited[v] == True:
            print_cycle(stack, v, cycles)

    visited[stack[-1]] = 'done'
    stack.pop()


def find_cycles(graph, cycles):
    n = len(graph)
    visited = list()
    for i in range(n):
        visited.append(False)

    for v in range(n):
        if not visited[v]:
            stack = [v]
            visited[v] = True
            process_DFS_tree(graph, stack, visited, cycles)


def task5():
    real_modules, _ = get_real()
    modules = module_dependency_map(real_modules)
    adj, indexes = build_graph(modules)
    cycles = []
    find_cycles(adj, cycles)

    print(f'\nThe StdLib packages form a cycle of dependency: ')

    i = 0
    for item in cycles:
        result = f'{i}. '
        for v in item:
            result += indexes[v] + ' -> '

        i += 1
        print(result[0:(len(result) - 4)])


###############################################

task1()
task2()
task3()
task4()
task5()
