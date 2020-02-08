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
clear ; ARG=`echo "1 8 20 11 2 15 16 14 12 3 10 9 21 25 19 18 4 17 5 13 7 6 24 22 23"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG
clear ; ARG=`echo "20 5 2 10 19 3 12 9 11 14 8 6 18 17 1 16 7 15 13 4"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG
clear ; ARG=`echo "9 14 20 10 2 18 7 11 5 16 19 4 3 1 12 6 17 13 8 15"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG
clear ; ARG=`echo "81 83 56 45 8 97 93 17 1 73 53 47 75 15 0 89 30 71 34 46 43 65 99 33 67 25 98 22 2 77 4 35 21 57 18 69 24 11 74 91 54 63 60 94 61 58 78 39 12 36 27 48 51 80 41 3 10 55 44 84 59 87 29 20 49 23 90 26 31 66 72 42 82 95 62 7 52 50 16 76 92 5 96 40 28 79 70 85 86 6 38 68 64 14 19 13 32 88 37 9"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG
clear ; ARG=`echo "4 3 1 0 2"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG
clear ; ARG=`echo "77 33 47 79 66 81 43 26 19 25 18 89 70 85 55 93 5 78 63 39 10 12 34 83 75 95 50 24 0 68 36 99 72 13 69 28 92 84 9 7 21 45 8 49 3 52 56 48 29 58 71 40 35 91 57 96 86 54 67 51 32 27 11 38 97 62 42 87 4 30 74 94 23 17 61 88 46 65 90 76 31 73 37 53 41 80 6 1 22 60 44 98 20 59 64 14 15 82 2 16"` ; time ./push_swap $ARG | ../42-push_swap/checker -vcat $ARG

clear ; ARG=`ruby -e 'printf Array.new(5) { rand(-999999...999999) }.uniq.map { |i| i.to_s}.join(" ")'` ; time ./push_swap $ARG |  ../42-push_swap/checker -vcat $ARG ; echo $ARG
