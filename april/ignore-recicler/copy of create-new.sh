#!/bin/bash -e

NEWNAME=$1

if [ "x$1" == "x" ]; then
    exit 0
fi

if [ -d "$NEWNAME" ]; then
    echo    "$NEWNAME already exists"
    exit 1
fi

mkdir "$NEWNAME"

echo    "#!/bin/bash -e

SOURCE=./$NEWNAME.cc
EXEOUT=./$NEWNAME

# generate the executable
g++ \$SOURCE -o \$EXEOUT

# run the executable
\$EXEOUT

# remove the resulted executable; supress warnings
rm \$EXEOUT > /dev/null
" > "$NEWNAME/build-run.sh"

echo    "
#include <iostream>

using namespace std;

int main ()
{
	cout << \"Hello World!\\n\";
	return 0;
}
" > "$NEWNAME/$NEWNAME.cc"
