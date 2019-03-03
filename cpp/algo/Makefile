.PHONY: build test

all: build

build:
	./scripts/build.sh

test:
	./scripts/tests.sh -DUSE_KCOV=0

clean:
	rm -rf build/
