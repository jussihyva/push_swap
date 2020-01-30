make
clear
echo -e "Evaluation?  \033[1;32m-->[y/n]<--\033[0m"
read k
if [ $k == "y" ]; then
	echo "cat -e author"
	cat -e author
	echo  -e "\033[33;7mpress enter\033[0m"
	read next
	make fclean
	clear
	echo  -e "\033[33;7mnorminette\033[0m"
	norminette
	echo  -e "\033[33;7mpress enter\033[0m"
	read next
	clear
	echo -e "\033[1;32mmake clean\033[0m"
	make clean
	echo -e "\033[1;32mmake fclean\033[0m"
	make fclean
	echo -e "\033[1;32mmake all\033[0m"
	make all
	echo -e "\033[1;32mmake re\033[0m"
	make re
	echo -e "\033[1;32mmake\033[0m"
	make
	echo  -e "\033[33;7mpress enter\033[0m"
	read next
	clear
	echo -e "1 must display \033[1;31mError\033[0m"
	./checker 1 2 43 k
	echo  -e "\033[33;7mpress enter\033[0m"
	read next
	
	echo -e "2 must display \033[1;31mError\033[0m"
	./checker 0 0 1 2 3
	echo  -e "\033[33;7mpress enter\033[0m"
	read next
	
	echo -e "3 must display \033[1;31mError\033[0m"
	./checker 12 0 15 2147483648
	echo  -e "\033[33;7mpress enter\033[0m"
	read next
	
	echo -e "4 must display \033[1;31mError\033[0m"
	echo -e "give invalid action and press enter"
	./checker 3 1 2
	echo  -e "\033[33;7mpress enter\033[0m"
	read next
	clear
	echo -e " must display \033[1;33mNothing\033[0m"
	./checker
	echo  -e "\033[33;7mpress enter\033[0m"
	read next
	clear
	echo -e "allways enter after command and after last enter press C - d"
	echo " "
	echo -e " must display \033[1;31mKO\033[0m"
	echo -e " give commands \033[1;31msa, pb, rrr\033[0m and C - d"
	./checker 0 9 1 8 2 7 3 6 4 5
	echo  -e "\033[33;7mpress enter\033[0m"
	read next
	
	echo -e "4 must display \033[1;31mKO\033[0m"
	echo -e " give commands that doesn't order the list and C - d"
	echo "./checker 0 1 2 3 4 5 6 8 9 7"
	./checker 0 1 2 3 4 5 6 8 9 7
	echo  -e "\033[33;7mpress enter\033[0m"
	read next
	clear
	echo -e "4 must display \033[1;32mOK\033[0m"
	echo -e "pres C - d"
	./checker 0 1 2
	echo  -e "\033[33;7mpress enter\033[0m"
	read next
	ne="y"
	while [ $ne == "y" ]; do
		echo -e "4 must display \033[1;32mOK\033[0m"
		echo -e " give commands \033[1;31mpb ra pb ra sa ra pa pa\033[0m and C - d"
		./checker 0 9 1 8 2
		echo  -e "\033[33;7mTry again?\033[0m\033[1;32m-->[y/n]<--\033[0m"
		read ne
	done
	echo  -e "\033[33;7mpress enter\033[0m"
	read next
	clear
	echo -e "4 must display \033[1;33mnothing\033[0m"
	echo "./push_swap 42"
	./push_swap 42
	echo  -e "\033[33;7mpress enter\033[0m"
	read next
	
	echo -e "4 must display \033[1;33mnothing\033[0m"
	echo "./push_swap 0 1 2 3"
	./push_swap 0 1 2 3
	echo  -e "\033[33;7mpress enter\033[0m"
	read next
	
	echo -e "4 must display \033[1;33mnothing\033[0m"
	echo "./push_swap 0 1 2 3 4 5 6 7 8 9"
	./push_swap 0 1 2 3 4 5 6 7 8 9
	echo  -e "\033[33;7mpress enter\033[0m"
	read next
	clear
	echo -e "4 must display \033[1;32mOK\033[0m"
	echo -e "and size 2 or 3"
	ARG="2 1 0"; ./push_swap $ARG | ./checker $ARG
	echo " "
	ARG="2 1 0"; ./push_swap $ARG
	echo  -e "\033[33;7mpress enter\033[0m"
	read next

	echo -e "4 must display \033[1;32mOK\033[0m"
	echo -e "and size no more that 12. Kudos if 8"
	ARG="1 5 2 4 3"; ./push_swap $ARG | ./checker $ARG
	echo " "
	ARG="1 5 2 4 3"; ./push_swap $ARG
	echo  -e "\033[33;7mpress enter\033[0m"
	read next
	clear
fi

echo -e "\033[1;33m-->Horible tests!<--\033[0m"
echo -e "Show ARG:s? \033[1;32m-->[y/n]<--\033[0m"
read varyn
echo "how many  numbers?"
read nb
x=1
declare -i sum=0
declare -i high=0
declare -i low=99999
declare -i hl=0
declare -i fails=0
while [ $x -le 100 ]; do
	ARG=$(printf '%s ' `seq 0 $((nb-1)) | sort -R`)
	if [ $varyn == "y" ]; then
		echo "$ARG"
	fi
	a=$(./push_swap $ARG | ./checker $ARG)
	sum+=`./push_swap $ARG | wc -l`
	hl=`./push_swap $ARG | wc -l`
	echo "steps $hl"
		if [ $high -lt $hl ]; then
			high=hl
		fi
		if [ $low -gt $hl ]; then
			low=hl
		fi
		if [ $a == "OK" ]; then
			echo -e "\033[1;32m$a\033[0m"
		else
			echo -e "\033[1;31m$a\033[0m"
			if [ $varyn != "y" ]; then
				echo "$ARG"
			fi
			(( fails++ ))
		fi
		(( x++ )); done
echo " "
echo "_____________________"
declare -i med=$(( sum/100 ))
echo "number: $nb"
echo "test: 100"
echo "fails: $fails"
echo "high: $high"
echo "low: $low"
echo "avarage: $med ($sum / 100)"
if [ $nb ==  5 ]; then
	echo "- Less than 13: pass"
	echo "- Precisely 8: Kudos"
fi
if [ $nb ==  100 ]; then
	echo "- Less than 700: 5"
	echo "- Less than 900: 4"
	echo "- Less than 1100: 3"
	echo "- Less than 1300: 2"
	echo "- Less than 1500: 1"
fi
if [ $nb ==  500 ]; then
	echo "- Less than 5500: 5"
	echo "- Less than 7000: 4"
	echo "- Less than 8500: 3"
	echo "- Less than 10000: 2"
	echo "- Less than 11500: 1"
fi
echo "_____________________"
echo "jhakala"
