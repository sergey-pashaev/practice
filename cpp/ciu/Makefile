.PHONY: build test

all: build

build:
	./scripts/build.sh
	rc -J . || true

test:
	./scripts/tests.sh -DUSE_KCOV=0

clean:
	rm -rf build/
