echo "Running unit tests:"

#for i in tests/*_tests
for j in ./tests/*_tests_marked
do
	i=$(echo $j | rev | cut -c 8- | rev)
	if test -f $i
	then
		if $VALGRIND ./$i 2>> tests/tests.log
		then
			echo $i PASS
		else
			echo "ERROR in test $i: here's tests/tests.log"
			echo "------"
			tail tests/tests.log
			exit 1
		fi
	fi
done

echo ""
