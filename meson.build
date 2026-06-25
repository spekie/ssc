project('ssc', 'cpp',
  license: ['MIT'],
  license_files: ['LICENSE'],
  default_options: [
    'cpp_std=c++17',
    'warning_level=3'
  ]
)

src = [
  'src/main.cpp',
  'src/lexer.cpp',
  'src/parser.cpp',
  'src/codegen.cpp'
]

inc = include_directories('src')

executable(
  'ssc',
  src,
  include_directories: inc,
  install: true
)

install_man('docs/man/ssc.1')
