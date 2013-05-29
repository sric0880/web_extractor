CC = g++
INCLUDES = -I/usr/include -I/usr/include/c++/4.7 -I/usr/local/include
LIBDIR = -L/usr/local/lib
LIB = -lpthread -lboost_regex -lNLPIR -lmysqlclient -lmysqlcppconn
OUTDIR = ./obj
OBJ = HtmlProcessor.o TextExtractor.o test.o \
	Dictionary.o DuplicateRemoval.o \
	InfoExtractor.o OutputMysql.o \
	Template.o \
	TemplatePongo.o TemplateHiall.o

OPTIONS = -O0 -g3 -Wall -c -fmessage-length=0 -std=gnu++0x

all: init web_extractor

web_extractor: $(OBJ)
	$(CC) $(OUTDIR)/Dictionary.o \
	$(OUTDIR)/DuplicateRemoval.o $(OUTDIR)/InfoExtractor.o \
	$(OUTDIR)/OutputMysql.o $(OUTDIR)/Template.o \
	$(OUTDIR)/TemplateHiall.o $(OUTDIR)/TemplatePongo.o \
	$(OUTDIR)/TextExtractor.o $(OUTDIR)/HtmlProcessor.o \
	$(OUTDIR)/test.o -o"web_extractor" $(LIB) $(LIBDIR)

Dictionary.o:
	$(CC) $(INCLUDES) $(OPTIONS) -o $(OUTDIR)/Dictionary.o src/Dictionary.cpp

DuplicateRemoval.o:
	$(CC) $(INCLUDES) $(OPTIONS) -o $(OUTDIR)/DuplicateRemoval.o src/DuplicateRemoval.cpp

InfoExtractor.o:
	$(CC) $(INCLUDES) $(OPTIONS) -o $(OUTDIR)/InfoExtractor.o src/InfoExtractor.cpp

OutputMysql.o:
	$(CC) $(INCLUDES) $(OPTIONS) -o $(OUTDIR)/OutputMysql.o src/OutputMysql.cpp

Template.o:
	$(CC) $(INCLUDES) $(OPTIONS) -o $(OUTDIR)/Template.o src/Template.cpp

TemplateHiall.o:
	$(CC) $(INCLUDES) $(OPTIONS) -o $(OUTDIR)/TemplateHiall.o src/TemplateHiall.cpp

TemplatePongo.o:
	$(CC) $(INCLUDES) $(OPTIONS) -o $(OUTDIR)/TemplatePongo.o src/TemplatePongo.cpp

TextExtractor.o:
	$(CC) $(INCLUDES) $(OPTIONS) -o $(OUTDIR)/TextExtractor.o src/TextExtractor.cpp

HtmlProcessor.o:
	$(CC) $(INCLUDES) $(OPTIONS) -o $(OUTDIR)/HtmlProcessor.o src/HtmlProcessor.cpp

test.o:
	$(CC) $(INCLUDES) $(OPTIONS) -o $(OUTDIR)/test.o src/test.cpp

init:
	mkdir -p obj
clean:
	rm -rf  $(OUTDIR) web_extractor

