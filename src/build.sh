#!/bin/bash

# E.g.: ./build.sh -d --sqlite

cc="g++"
options="-I. -m32 -fPIC -Wall -fvisibility=hidden"

separator="-------------------------"
list_item=" - "
wait_indicator="..."

while [[ $# -gt 0 ]]; do
    arg="$1"
    case $arg in
        -d | --debug)
            debug="-g -ggdb -O0" # debug build without optimization
            ;;
        --sqlite)
            sqlite=true
            ;;
        -c | --curl)
            curl=true
            ;;
        --ssl)
            ssl=true
            ;;
        -u | --unsafe)
            unsafe=true
            ;;
        *)
            unrecognized_arg=$arg
            break
            ;;
    esac
    shift
done

if [ -v unrecognized_arg ]; then
    echo "Unrecognized argument \"$unrecognized_arg\", aborting."
    exit 1
fi

echo $separator
echo "Options:"

echo -n "$list_item"
echo -n "Debug:  "
if [ -v debug ]; then
    echo "ON"
else
    echo "OFF"
    debug=""
fi

echo -n "$list_item"
echo -n "Unsafe: "
if [ -v unsafe ]; then
    echo "ON"
    constants+=" -D ENABLE_UNSAFE=1"
else
    echo "OFF"
    constants+=" -D ENABLE_UNSAFE=0"
fi

sqlite_found=0
sqlite_link=""
sqlite_libpath="/usr/lib32/libsqlite3.so"
sqlite_libpath2="/usr/lib/i386-linux-gnu/libsqlite3.so"
sqlite_libpath3="/usr/lib/libsqlite3.so"
echo -n "$list_item"
echo -n "SQLite: "
if [ -v sqlite ]; then
    if [ -e "$sqlite_libpath" ] || [ -e "$sqlite_libpath2" ] || [ -e "$sqlite_libpath3" ]; then
        sqlite_found=1
        sqlite_link="-lsqlite3"
        constants+=" -D COMPILE_SQLITE=1"
        echo "ON"
    else
        echo "requested but lib not found, aborting."
        exit 1
    fi
else
    echo "OFF"
    constants+=" -D COMPILE_SQLITE=0"
fi

curl_found=0
curl_link=""
curl_libpath="/usr/lib/i386-linux-gnu/libcurl.so.4"
echo -n "$list_item"
echo -n "cURL:   "
if [ -v curl ]; then
    if [ -e "$curl_libpath" ]; then
        curl_found=1
        curl_link="-lcurl"
        constants+=" -D COMPILE_CURL=1"
        echo "ON"
    else
        echo "requested but lib not found, aborting."
        exit 1
    fi
else
    echo "OFF"
    constants+=" -D COMPILE_CURL=0"
fi

echo -n "$list_item"
echo -n "SSL:    "
if [ -v ssl ]; then
    echo "ON"
    constants+=" -D COMPILE_SSL=1"
    ssl_link="-lssl -lcrypto"
else
    echo "OFF"
    constants+=" -D COMPILE_SSL=0"
fi

echo $separator
echo "Compiling:"

mkdir -p ../bin
mkdir -p objects

echo -n "$list_item"
echo -n "cracking.cpp"
echo $wait_indicator
$cc $debug $options $constants -c cracking.cpp -o objects/cracking.opp

echo -n "$list_item"
echo -n "libcod.cpp"
echo $wait_indicator
$cc $debug $options $constants -c libcod.cpp -o objects/libcod.opp

echo -n "$list_item"
echo -n "qvsnprintf.c"
echo $wait_indicator
$cc $debug $options $constants -c vendor/qvsnprintf.c -o objects/qvsnprintf.opp

echo -n "$list_item"
echo -n "gsc.cpp"
echo $wait_indicator
$cc $debug $options $constants -c gsc.cpp -o objects/gsc.opp

echo -n "$list_item"
echo -n "gsc_entity.cpp"
echo $wait_indicator
$cc $debug $options $constants -c gsc_entity.cpp -o objects/gsc_entity.opp

echo -n "$list_item"
echo -n "gsc_player.cpp"
echo $wait_indicator
$cc $debug $options $constants -c gsc_player.cpp -o objects/gsc_player.opp

echo -n "$list_item"
echo -n "gsc_bots.cpp"
echo $wait_indicator
$cc $debug $options $constants -c gsc_bots.cpp -o objects/gsc_bots.opp

echo -n "$list_item"
echo -n "gsc_weapons.cpp"
echo $wait_indicator
$cc $debug $options $constants -c gsc_weapons.cpp -o objects/gsc_weapons.opp

echo -n "$list_item"
echo -n "gsc_exec.cpp"
echo $wait_indicator
$cc $debug $options $constants -c gsc_exec.cpp -o objects/gsc_exec.opp

echo -n "$list_item"
echo -n "gsc_utils.cpp"
echo $wait_indicator
$cc $debug $options $constants -c gsc_utils.cpp -o objects/gsc_utils.opp

echo -n "$list_item"
echo -n "jump.cpp"
echo $wait_indicator
$cc $debug $options $constants -c jump.cpp -o objects/jump.opp

if [ $sqlite_found == 1 ]; then
    echo -n "$list_item"
    echo -n "gsc_sqlite.cpp"
    echo $wait_indicator
    $cc $debug $options $constants -c gsc_sqlite.cpp -o objects/gsc_sqlite.opp
fi

if [ $curl_found == 1 ]; then
    echo -n "$list_item"
    echo -n "gsc_curl.cpp"
    echo $wait_indicator
    $cc $debug $options $constants -c gsc_curl.cpp -o objects/gsc_curl.opp
fi

echo -n "Linking libcod1.so"
echo $wait_indicator
objects="$(ls objects/*.opp)"
$cc -m32 -shared -L/lib32 -o ../bin/libcod1.so -ldl $objects -lpthread $sqlite_link $curl_link $ssl_link

echo $separator

rm objects -r
