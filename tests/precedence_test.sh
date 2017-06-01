(echo A && echo B) || (echo C && echo D)
echo hi && test -e file || test -e file2 && echo world
echo hi && (test -e file || (test -e file2 && echo world))
echo hi && test -e file || (test -e file2 || echo world)
echo hi && (test -e file || (test -e file2 || echo world))
echo hi && (test -e file
echo hi && (test -e file || echo world
test -e file || (echo B && (echo C )
