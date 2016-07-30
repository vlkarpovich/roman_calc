# Makefile
# The project name is the directory name

PRJ_NAME = $(notdir $(CURDIR))
src = $(wildcard src/*.c)
tests = $(wildcard tests/*.c)
obj = $(src:.c=.o)
test_obj = $(tests:.c=.o)

LDFLAGS = -lcheck -lpthread -lrt
LOCAL_LIB = -L./ -l$(PRJ_NAME)

all: lib_$(PRJ_NAME) $(PRJ_NAME) check_$(PRJ_NAME) check

$(PRJ_NAME):$(obj)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LOCAL_LIB)

check_$(PRJ_NAME):$(test_obj)
	$(CXX) -o $@ $^ $(LDFLAGS) $(LOCAL_LIB)

lib_$(PRJ_NAME):$(obj)
	@ar r lib$(PRJ_NAME).a $?

check:
	./check_$(PRJ_NAME)

clean:
	rm */*.o
	rm *.a
	rm $(PRJ_NAME)
	rm check_$(PRJ_NAME)


