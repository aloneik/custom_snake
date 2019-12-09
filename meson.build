project('snake', 'cpp')

includes = include_directories(['src/include'])

game_sources = [
    'src/food.cpp',
    'src/snake.cpp'
]

dependencies = [
    dependency('boost', version: '>=1.67'),
    dependency('sfml-system', version: '>=2.5'),
    dependency('sfml-window', version: '>=2.5'),
    dependency('sfml-graphics', version: '>=2.5')
]

main_sources = game_sources + ['src/main.cpp']
executable('snake.out',
    main_sources,
    dependencies: dependencies,
    include_directories: includes
)

test_sources = game_sources + ['tests/tests.cpp']
tests_exe = executable(
    'tests.out',
    test_sources,
    dependencies: dependencies,
    include_directories: includes
)
test('Tests', tests_exe)