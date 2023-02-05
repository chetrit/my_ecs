#!/usr/bin/env bash
#!/usr/bin/env fish

if [ "$1" == 'clean' ]
then
    rm unit_tests
    cd $PWD/build/
    rm -rf *
    touch .gitkeep
    cd ../
    exit 0
fi

cd $PWD/build/
cmake ../
cd ../
cmake --build $PWD/build/
