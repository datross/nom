
BUNDLE = nom.lv2
INSTALL_DIR = /usr/local/lib/lv2


$(BUNDLE): manifest.ttl nom.so
	rm -rf $(BUNDLE)
	mkdir $(BUNDLE)
	cp manifest.ttl nom.so $(BUNDLE)

nom.so: nom.cpp
	g++ -shared -fPIC -DPIC nom.cpp `pkg-config --cflags --libs lv2-plugin` -o nom.so

install: $(BUNDLE)
	mkdir -p $(INSTALL_DIR)
	rm -rf $(INSTALL_DIR)/$(BUNDLE)
	cp -R $(BUNDLE) $(INSTALL_DIR)

clean:
	rm -rf $(BUNDLE) nom.so
