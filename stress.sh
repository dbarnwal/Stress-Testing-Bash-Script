#!/bin/bash
i=1
g++ -std=c++17 gen.cpp -o generator -O2
g++ -std=c++17 $1 -o original -O2
g++ -std=c++17 brute.cpp -o brute -O2
mx=$2
while [ $i -le $mx ]
do
	# Generate input
	./generator 
	./original < input.txt > output.txt
	./brute < input.txt > brute_output.txt
	# diff -w original_output.txt brute_output.txt || break
  if diff --brief --ignore-space-change output.txt brute_output.txt; then
    echo \#$i:[1m[32m$test_case Accepted[0m       
	else
		echo [1m[31mSample test \#$i: Wrong Answer[0m
		echo ======================================== 
		awk 'BEGIN {print "\033[36mINPUT:\033[0m"}{print $0}' input.txt
		echo ========================================
		awk 'BEGIN {print "\033[36mOUTPUT:\033[0m"}{print $0}' output.txt
		echo ========================================
		awk 'BEGIN {print "\033[36mBRUTE OUTPUT:\033[0m"}{print $0}' brute_output.txt
		echo ========================================
		echo ""
		echo "BRUTE OUTPUT : "	>> output.txt
		cat brute_output.txt >> output.txt
		break
	fi

	i=$((i+1))
done
rm brute
rm generator
rm original
rm brute_output.txt
# echo "I is $i"
# if [ $i != $mx ]
# then
# 	echo -n "Origi = " > output.txt
# 	cat output.txt >> output.txt
# 	echo "" >> output.txt
# 	echo -n "brute = "	>> output.txt
# 	cat brute_output.txt >> output.txt
# 	echo ""
# fi