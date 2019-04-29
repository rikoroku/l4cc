## !/bin/bash
try() {
  expected="$1"
  input="$2"

  ./l4cc "$input" > tmp.s
  gcc -o tmp tmp.s
  ./tmp
  actual="$?"

  if [ "$actual" = "$expected" ]; then
    echo "$input => $actual"
  else
    echo "$expected expected, but got $actual"
    exit 1
  fi
}

try 21 '5+20-4'

echo OK
