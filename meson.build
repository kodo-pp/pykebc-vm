project('pykebc-vm', 'cpp', version: '1.0.0', default_options: ['cpp_std=c++17'])


sources = [
]

includes = include_directories(
    'include',
)


test_sources = ['test/src/test.cpp']
test_includes = [include_directories('test/include')] + [includes]


dependencies = [
    dependency('libbinary_format'),
    dependency('pex-loader'),
]


libpykebc_vm = library(
    'pykebc_vm',
    sources,
    include_directories: includes,
    dependencies: dependencies,
)


catch2_test_executable = executable(
    'catch2_test',
    test_sources,
    include_directories: test_includes,
    link_with: libpykebc_vm,
    dependencies: dependencies,
)

test('catch2_test_suit', catch2_test_executable)

pkg = import('pkgconfig')
pkg.generate(
    description: 'A library for parsing and running pyke bytecode. Written for pyke',
    filebase: 'pykebc-vm',
    libraries: libpykebc_vm,
    name: 'pykebc-vm',
    subdirs: 'include',
)
