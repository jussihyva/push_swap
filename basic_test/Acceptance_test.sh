#!/bin/bash

push_swap="../push_swap"
checker="../checker"

run_push_swap_error()
{
	echo "1:"
	$push_swap 12 34
	echo "2:"
	$push_swap
	echo "3:"
	$push_swap 12ee
	echo "4:"
	$push_swap ee13
	echo "5:"
	$push_swap dd34gg
	echo "6:"
	$push_swap 12 dd45
	echo "7:"
	$push_swap '12 56'
	echo "8:"
	$push_swap ''
	echo "9:"
	$push_swap '-'
	echo "10:"
	$push_swap "-" -6
	echo "11:"
	$push_swap '- 13'
	echo "12:"
	$push_swap - 12
	echo "13:"
	$push_swap -l
	return 1
}

run_checker_error()
{
	echo "1:"
	$checker 12 34
	echo "2:"
	$checker
	echo "3:"
	$checker 12ee
	echo "4:"
	$checker ee13
	echo "5:"
	$checker dd34gg
	echo "6:"
	$checker 12 dd45
	echo "7:"
	$checker '12 56'
	echo "8:"
	$checker ''
	echo "9:"
	$checker '-'
	echo "10:"
	$checker "-" -6
	echo "11:"
	$checker '- 13'
	echo "12:"
	$checker - 12
	echo "13:"
	$checker -l
	return 1
}

run_push_swap_error
run_checker_error
