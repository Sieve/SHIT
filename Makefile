.PHONY: clean All

All:
	@echo "----------Building project:[ SHIT - Static-Release ]----------"
	@$(MAKE) -f  "SHIT.mk"
clean:
	@echo "----------Cleaning project:[ SHIT - Static-Release ]----------"
	@$(MAKE) -f  "SHIT.mk" clean
