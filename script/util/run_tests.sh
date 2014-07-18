function run_tests {
  local cmd=$1
  shift

  local debug=
  local args=

  while getopts "dvf:" option; do
    case ${option} in
      d)
        debug=true
        ;;
      f)
        args="$args --only='${OPTARG}'"
        ;;
      v)
        args="$args --reporter=spec"
        ;;
      *)
        exit
        ;;
    esac
  done

  if [[ -n $debug ]]; then
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
