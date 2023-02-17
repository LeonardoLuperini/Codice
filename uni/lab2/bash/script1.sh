#! /bin/bash

if [ $# -ne 2 ]; then	
	echo "Errore: $(basename $0) ha bisogno di una directory e un file da cracare"
	exit 1
fi

if [ ! -d $1 ]; then
	echo "Errore: $1 non è una directory"
	exit 1
fi

pushd $1 > /dev/null

for file in ./*; do
	if [ -f $file ]; then
		if grep $2 $file > /dev/null; then
			echo $file
		fi
	fi
done

popd

exit 0
