CC=g++
FILES=replacer.cc
LIBS=
INC=
OUT=lxrepl

build-lib:
	$(CC) -shared -fPIC -Wall -Wextra -o build/lib$(OUT).so $(FILES) && sudo cp build/lib$(OUT).so /usr/lib/lib$(OUT).so && \
	cp build/lib$(OUT).so ../MatchZy-Webhook && cp replacer.h ../MatchZy-Webhook

build:
	$(CC) -g -Wall -Wextra -o $(OUT) $(FILES)