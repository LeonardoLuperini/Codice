#! /bin/bash

function avg {
	local arr=("$@")
	local n=${#arr[@]}
	if (( n != 0 )); then
		local sum=0
		for el in ${numbers[@]}; do
			sum=$(bc -l <<< "$sum + $el")
		done
		local mean=$(bc -l <<< "$sum / $n")
		echo "$mean"
	else 
		echo 0
	fi
}

function std {
	local arr=("$@")
	local n=${#arr[@]}
	if (( n != 0)); then
		local sum=0
		local mean=$(avg "${arr[@]}")
		for value in "${arr[@]}"; do
			sum=$(bc -l <<< "$sum + ($value - $mean) ^ 2")
		done
		local variance=$(bc -l <<< "$sum / $n")
		local stddev=$(bc -l <<< "sqrt($variance)")
		echo "$stddev"
	else 
		echo 0
	fi
}

function readfile {
	local -n arr="$1"
	while read -r line; do
		local float=$( echo "$line" | grep -o -E "[+-]?[0-9]+([.][0-9]+)?" )
		if [[ ! -z "$float" ]]; then
			arr+=("$float")
		fi
	done < "$2"
}

function loop {
	echo "dir:$1"
	for f in "$1"/* ; do
		local numbers=()
		if [[ -f $f ]]; then
			readfile "numbers" "$f"
			printf "%-5lu %-10lf %-10lf %-20s\n" "${#numbers[@]}" $(avg "${numbers[@]}") $(std "${numbers[@]}") $(basename "$f")
		fi
	done
	
	for f in "$1"/* ; do
		if [[ -d $f ]]; then
			loop "$f"
		fi
	done
}

if (( $# != 1 )); then
	echo "La sintassi corretta è: ./$@ [dir]"
	exit 1
fi

if [[ ! -d $1 ]]; then
	echo "La cartella $1 non esiste!"
	exit 1
fi



printf "%-10s %-10s %-10s %-20s\n" "n" "avg" "std" "file"
printf -- '-%.0s' {1..50}; printf "\n"
loop "$1"
