kb := "kuriko"
km := "default"

clean:
    rm -rf ./*.bin

build: clean
    qmk compile --compiledb -j 24 -kb {{kb}} -km {{km}}
