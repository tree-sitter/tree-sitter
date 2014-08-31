function usage {
  cat <<-EOF
USAGE

  $0  [-dghv] [-f focus-string]

OPTIONS

  -h  print this message

  -d  run tests in a debugger (either lldb or gdb)

  -g  run tests with valgrind

  -v  run tests with verbose output

  -f  focus tests to those containing the substring

EOF
}

function run_tests {
  local debug
  local args
  local valgrind
  local target=$1
  local cmd="out/Default/${target}"
  shift

  while getopts "hdgvf:" option; do
    case ${option} in
      h)
        usage
        exit
        ;;
      d)
        debug=true
        ;;
      f)
        args="$args --only='${OPTARG}'"
        ;;
      v)
        args="$args --reporter=spec"
        ;;
      g)
        valgrind=true
        ;;
    esac
  done

  make $target

  if [[ -n $valgrind ]]; then
    eval valgrind \
      --suppressions=./etc/valgrind.supp \
      --dsymutil=yes \
      $cmd \
      $args 2>&1 | \
      grep --color -E '\w+_specs?.cc:\d+|$'

  elif [[ -n $debug ]]; then
    if which -s gdb; then
      eval gdb $cmd -- $args
    elif which -s lldb; then
      eval lldb $cmd -- $args
    else
      echo "No debugger found"
      exit 1
    fi

  else
    eval time $cmd $args
  fi
}
