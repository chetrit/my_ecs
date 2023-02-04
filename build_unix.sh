#!/usr/bin/env bash
#!/usr/bin/env fish

if [ "$1" == 'clean' ]
then
    rm r-type_client
    rm r-type_server
    rm unit_tests
    cd $PWD/build/
    rm -rf *
    touch .gitkeep
    cd ../
    return
fi

cd $PWD/build/
cmake ../
cd ../
cmake --build $PWD/build/
