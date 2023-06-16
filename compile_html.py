html_file = "index.html"
target_file = "./lib/ui_server/index_html.h"

with open(html_file) as f:
    head = "#ifndef _INDEX_HTML_H_\n" + \
           "#define _INDEX_HTML_H_\n" + \
           "#include <Arduino.h>\n" + \
           "const char index_html[] PROGMEM = R\"rawliteral(\n"
    tail = ")rawliteral\";\n#endif"
    dump = head + f.read() + tail

    with open(target_file, "w") as t:
        t.write(dump)

