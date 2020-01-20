ruby -e "puts (1..50).to_a.shuffle.join(' ')"
ruby -e "puts (1..100).to_a.shuffle.join(' ')"

| ../42-push_swap/checker -vcat 
time ./push_swap

time ./push_swap 34 41 22 43 8 36 31 2 44 48 24 12 28 49 17 10 7 5 19 30 39 13 16 35 50 26 46 32 37 20 42 3 45 33 18 11 9 1 27 29 38 6 4 21 25 15 47 40 14 23 | ../42-push_swap/checker -vcat 34 41 22 43 8 36 31 2 44 48 24 12 28 49 17 10 7 5 19 30 39 13 16 35 50 26 46 32 37 20 42 3 45 33 18 11 9 1 27 29 38 6 4 21 25 15 47 40 14 23

time ./push_swap 96 77 2 32 20 82 30 58 67 74 92 81 13 3 65 85 68 10 89 52 78 33 7 12 54 83 21 23 76 66 47 11 37 40 9 98 99 18 43 55 59 25 38 24 94 87 44 36 49 90 29 19 69 80 60 72 22 16 93 28 45 50 8 27 46 63 88 70 4 5 35 61 15 75 71 48 6 14 97 64 1 31 62 42 57 79 39 95 86 51 41 17 91 100 56 26 84 34 53 73 | ../42-push_swap/checker -vcat 96 77 2 32 20 82 30 58 67 74 92 81 13 3 65 85 68 10 89 52 78 33 7 12 54 83 21 23 76 66 47 11 37 40 9 98 99 18 43 55 59 25 38 24 94 87 44 36 49 90 29 19 69 80 60 72 22 16 93 28 45 50 8 27 46 63 88 70 4 5 35 61 15 75 71 48 6 14 97 64 1 31 62 42 57 79 39 95 86 51 41 17 91 100 56 26 84 34 53 73

clear ; ARG=`echo "3 2 1"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG
clear ; ARG=`echo "2 3 4 1"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG
clear ; ARG=`ruby -e "puts (1..3).to_a.shuffle.join(' ')"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG ; echo $ARG
clear ; ARG=`ruby -e "puts (1..20).to_a.shuffle.join(' ')"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG ; echo $ARG
clear ; ARG=`ruby -e "puts (-1..3).to_a.shuffle.join(' ')"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG ; echo $ARG


clear ; ARG=`echo "1 2 3"` ; time ./push_swap $ARG | ../42-push_swap/checker $ARG
clear ; ARG=`echo "1 3 2"` ; time ./push_swap $ARG | ../42-push_swap/checker $ARG
clear ; ARG=`echo "2 1 3"` ; time ./push_swap $ARG | ../42-push_swap/checker $ARG
clear ; ARG=`echo "2 3 1"` ; time ./push_swap $ARG | ../42-push_swap/checker $ARG
clear ; ARG=`echo "3 1 2"` ; time ./push_swap $ARG | ../42-push_swap/checker $ARG
clear ; ARG=`echo "3 2 1"` ; time ./push_swap $ARG | ../42-push_swap/checker $ARG
clear ; ARG=`echo "1 0 3 2 -1"` ; time ./push_swap $ARG | ../42-push_swap/checker $ARG

Fix these test cases:
clear ; ARG=`echo "1 3 2"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG
clear ; ARG=`echo "2 3 1"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG
clear ; ARG=`echo "1 3 2 4"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG
clear ; ARG=`echo "1 4 3 2"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG
clear ; ARG=`echo "7 6 9 8"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG

clear ; ARG=`echo "1 0 3 2 -1"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG
clear ; ARG=`echo "2 3 0 1 -1"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG
clear ; ARG=`echo "3 -1 0 1 2"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG
clear ; ARG=`echo "0 3 2 -1 1"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG
clear ; ARG=`echo "0 -1 3 2 1"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG
clear ; ARG=`echo "2 1 0 -1 3"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG

clear ; ARG=`echo "3 2 1 0 -1"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG

clear ; ARG=`echo "2 4 3 1"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG
clear ; ARG=`echo "0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 22 21"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG
clear ; ARG=`echo "5 4 3 2 1 0 -1"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG
clear ; ARG=`echo "2 1 0 -1 5 4 3"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG
clear ; ARG=`echo "7 3 6 8 2 1 0 4 9 5"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG


clear ; ARG=`ruby -e 'printf Array.new(5) { rand(-999999...999999) }.uniq.map { |i| i.to_s}.join(" ")'` ; time ./push_swap $ARG |  ../42-push_swap/checker -vcat $ARG ; echo $ARG
