.PHONY: install dev-install check tests

install:
	python3 -m pip install -r requirements.txt

dev-install:
	python3 -m pip install -e .

check:
	python3 -m mypy src/*

tests:
	python3 -m unittest discover tests/
