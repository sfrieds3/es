SUBDIRS := src
ES := es

all: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@

clean:
	rm -rf $(SUBDIRS)/$(ES)

.PHONY: all $(SUBDIRS)
