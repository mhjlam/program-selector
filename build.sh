#!/bin/bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

while (( "$#" )); do
	case "$1" in
		-b|--build)
			BUILD='true'
			shift
			;;
		-r|--run)
			RUN='true'
			BUILD='true'
			shift
			;;
		-d|--debug) # doesn't work yet
			DEBUG='true'
			shift
			;;
		--) # unsupported flags
			shift
			break
		;;
		*)
			echo "Invalid option $1."
			exit 1
		;;
		esac
done

cd "$DIR/build"
./premake5.exe vs2019

configuration=$([ $DEBUG == true ] && echo "Debug" || echo "Release")

if [[ $BUILD == true ]]; then
	msbuild.exe $DIR/build/program_selector.sln -t:Build -p:Configuration=$configuration -m
fi

if [[ $RUN == true ]]; then
	"${DIR}/bin/$configuration/program_selector.exe"
fi
