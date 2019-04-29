l4cc: l4cc.c

test: l4cc
				./test.sh
clean:
				rm -f 4cc *.o *~ tmp*
