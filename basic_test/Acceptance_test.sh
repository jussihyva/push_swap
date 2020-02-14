#!/bin/bash

push_swap="../push_swap"
checker="../checker"

run_push_swap_error()
{
	echo "ALL Error"
	echo "1:"
	$push_swap 12 3x4 
	echo "2:"
	$push_swap -u
	echo "3:"
	$push_swap 12ee
	echo "4:"
	$push_swap ee13
	echo "5:"
	$push_swap dd34gg
	echo "6:"
	$push_swap 12 dd45
	echo "7:"
	$push_swap '12 56' -
	echo "8:"
	$push_swap '' '' '-'
	echo "9:"
	$push_swap '-'
	echo "10:"
	$push_swap "-" -6
	echo "11:"
	$push_swap '- 13'
	echo "12:"
	$push_swap - 12
	echo "13:"
	$push_swap -l -l
	echo "14:"
	$push_swap 12 45 2147483648
	echo "15:"
	$push_swap 45 2147483648 67
	echo "16:"
	$push_swap 2147483648 45 16
	echo "17:"
	$push_swap 12 45 -2147483649
	echo "18:"
	$push_swap 45 -2147483649 67
	echo "19:"
	$push_swap -2147483649 45 16
	echo "20:"
	$push_swap 45 23 45
	echo "21:"
	$push_swap 23 23 45
	echo "22:"
	$push_swap 45 23 23

	return 1
}

run_checker_error()
{
	echo "ALL Error"
	echo "1:"
	$checker 12 3x4
	echo "2:"
	$checker -u
	echo "3:"
	$checker 12ee
	echo "4:"
	$checker ee13
	echo "5:"
	$checker dd34gg
	echo "6:"
	$checker 12 dd45
	echo "7:"
	$checker '12 56' -
	echo "8:"
	$checker '' '' '-'
	echo "9:"
	$checker '-'
	echo "10:"
	$checker "-" -6
	echo "11:"
	$checker '- 13'
	echo "12:"
	$checker - 12
	echo "13:"
	$checker -l -l
	echo "14:"
	$checker 12 45 2147483648
	echo "15:"
	$checker 45 2147483648 67
	echo "16:"
	$checker 2147483648 45 16
	echo "17:"
	$checker 12 45 -2147483649
	echo "18:"
	$checker 45 -2147483649 67
	echo "19:"
	$checker -2147483649 45 16
	echo "20:"
	$checker 45 23 45
	echo "21:"
	$checker 23 23 45
	echo "22:"
	$checker 45 23 23
	echo "23:"
	$checker 12 34 6 <<EOF
ttt
rra
EOF
	return 1
}

run_checker_OK()
{
	echo "ALL OK"
	echo "1:"
	$checker 12 34 6 <<EOF
pb
pb
pb
pb
pb
pb
pa
pa
pa
pa
pa
pa
rra
EOF
	echo "2:"
	$checker 12 34 6 <<EOF
pb
pb
pb
pb
pb
pb
rb
pa
pa
pa
pa
pa
pa
EOF
	echo "3:"
	$checker 34 12 6 <<EOF
sa
rra
EOF
	echo "4:"
	$checker 34 12 6 <<EOF
sa
ra
ra
EOF
	echo "5:"
	$checker -99999 -9999 999 -0 1 6 <<EOF
rb
rb
ss
sb
sa
rrr
rrr
rrr
rra
ss
rr
sa
ra
sa
rr
rr
EOF
	echo "6:"
	$checker -99999 -9999 999 -0 1 6 <<EOF
rr
ss
rrr
sb
sa
rr
EOF
	echo "7:"
	$checker -99999 -9999 999 -0 1 6 <<EOF
rb
ra
sa
ss
ss
rrb
rr
rrr
rra
sb
sa
rr
EOF
	echo "8:"
	$checker -99999 -9999 999 -0 1 6 <<EOF
rr
ss
rrr
sb
sa
rr
EOF
	return 1
}

run_checker_KO()
{
	echo "ALL KO"
	echo "1:"
	$checker 34 12 6 <<EOF
sa
ra
EOF
	echo "2:"
	$checker 34 12 6 <<EOF
sa
ra
EOF
	echo "3:"
	$checker -99999 -9999 999 -0 1 6 <<EOF
rb
rb
ss
rrr
sb
rrb
EOF
	return 1
}

run_pus_swap_checker_OK()
{
	echo "ALL OK"
	echo "1:"
	ARG="`ruby -e 'printf Array.new(8) { rand(-99999...99999) }.uniq.map { |i| i.to_s}.join(" ")'`";
	$push_swap $ARG
	$push_swap $ARG | wc -l
	$push_swap $ARG | $checker $ARG
	return 1
}

run_push_swap_error
run_checker_error
run_checker_OK
run_checker_KO
run_pus_swap_checker_OK

