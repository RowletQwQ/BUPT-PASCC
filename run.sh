 #!/bin/bash
cd /data/workspace/myshixun/open_set
for file in *.pas; do
    /usr/share/Pascal2C/build/pascal2c  "$file" "${file%.pas}.c"
done