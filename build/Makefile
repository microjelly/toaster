SDCC_TARGETS := $(shell find scripts/sdcc -type f|cut -c9-)

$(PWD)/bin:
	@mkdir -p $(PWD)/bin

$(PWD)/bin/.dapper: $(PWD)/bin
	@echo Downloading dapper
	@curl -sL https://releases.rancher.com/dapper/v0.5.4/dapper-`uname -s`-`uname -m` > $(PWD)/bin/.dapper.tmp
	@@chmod +x $(PWD)/bin/.dapper.tmp
	@$(PWD)/bin/.dapper.tmp -v
	@mv $(PWD)/bin/.dapper.tmp $(PWD)/bin/.dapper

$(SDCC_TARGETS): $(PWD)/bin/.dapper
	@echo "Building $@"
	cd ../ && DOCKER_BUILDKIT=1 $(PWD)/bin/.dapper --target sdcc -f build/Dockerfile.dapper build/scripts/$@

.PHONY: help
.DEFAULT_GOAL := help

help:
	@$(PWD)/scripts/help.sh

clean:
	@rm -rf $(PWD)/bin $(PWD)/Dockerfile.dapper[0-9]*
	@docker rmi toaster:master