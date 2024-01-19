.PHONY: FORCE
all: FORCE
	$(MAKE) -C .. bitcoins_qt test_bitcoins_qt
clean: FORCE
	$(MAKE) -C .. bitcoins_qt_clean test_bitcoins_qt_clean
check: FORCE
	$(MAKE) -C .. test_bitcoins_qt_check
bitcoins-qt bitcoins-qt.exe: FORCE
	 $(MAKE) -C .. bitcoins_qt
apk: FORCE
	$(MAKE) -C .. bitcoins_qt_apk
